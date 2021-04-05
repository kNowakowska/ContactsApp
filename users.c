#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include"users.h"
/**
* @file users.h
* Plik z deklaracjami funkcji odpowiedzialnych za obsługę użytkowników.
*/

#include"account.h"
/**
* @file account.h
* Plik z deklaracjami funkcji odpowiedzialnych za obslugę kontaktów danego użytkownika.
*/

/** Struktura Users. Struktura bierze udział w tworzeniu listy jednokierunkowej nieuporządkowanej przechowującej użytkowników. */
struct Users{
    struct Users *next; /**< Wskaźnik na następny element listy. */
    char nickname[15]; /**< Tablica znaków przechowująca login użytkownika. */
    char password[15]; /**< Tablica znaków przechowująca hasło użytkownika. */
    char file_name[27]; /**< Nazwa pliku, w którym dany użytkownik będzie przechowywał kontakty. */
};

/**
* Funkcja tworząca tablicę użytkowników.
* W przypadku gdy nie ma żadnych użytkowników funkcja tworzy pierwszego użytkownika (alokuje pamięć), przypisuje do niego nazwę pliku oraz wypełnia pola struktury danymi.
* @param nickname Tablica znaków przechowująca login użytkownika.
* @param password Tablica znaków przechowująca hasło użytkownika.
* @return Funkcja zwraca wskaźnik na pierwszy element listy.
*/
struct Users *create_users_list(char nickname[15], char password[15]){
    char file_name[27]="";
    strcat(file_name,"contacts");
    strcat(file_name,nickname);
    strcat(file_name, ".txt");
    struct Users *front = (struct Users *)malloc(sizeof (struct Users));
    if (NULL != front){
        strcpy(front->nickname, nickname);
        strcpy(front->password, password);
        front->next = NULL;
        strcpy(front->file_name, file_name);
    }
    return front;
}

/**
* Funkcja pomocnicza, dodająca element do końca listy użytkowników.
* Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na pierwszy element listy.
* @param new_node Wskaźnik na dodawany do listy element.
*/
void insert_user_back(struct Users *front, struct Users *new_node){
    struct Users *back=front;
    while(back->next){
            back=back->next;
    }
    back->next = new_node;
}

/**
* Funkcja dodająca nowego użytkownika.
* Funkcja tworzy nowego użytkownika (alokuje pamięć), uzupełnia jego dane oraz wstawia go na koniec listy.
* @param front Wskaźnik na początek listy użytkowników.
* @param nickname Tablica znaków przechowująca login dodawanego użytkownika.
* @param password Tablica znaków przechowująca hasło dodawanego użytkownika.
* @see insert_user_back()
*/
void add_new_user(struct Users *front, char nickname[15], char password[15]){
    char file_name[27]="";
    strcat(file_name,"contacts");
    strcat(file_name,nickname);
    strcat(file_name, ".txt");
    if (front != NULL){
        struct Users *new_user = (struct Users *)malloc(sizeof(struct Users));
        if (NULL != new_user){
            strcpy(new_user->nickname, nickname);
            strcpy(new_user->password, password);
            strcpy(new_user->file_name, file_name);
            new_user->next = NULL ;
            insert_user_back(front, new_user);
        }
    }
}

/**
* Funkcja pobierająca użytkowników z pliku i dodająca ich do listy.
* Funkcja wywoływana zawsze na początku działania programu, odpowiada za załadowanie wszystkich użytkowników z pliku "listOfUsers.txt" do listy.
* @param front Wskaźnik na początek listy uzytkowników.
* @return Funkcja zwraca wskaźnik na początek listy użytkowników.
* @see create_users_list()
* @see add_new_user()
*/
struct Users *loadingUsers(struct Users *front){
    char nickname[15], password[15], tmp_string[15];
    FILE *file = fopen("listOfUsers.txt", "r");
    if(!file)
        return NULL;
    fscanf(file, "%c", tmp_string);
    while(!feof(file)){
        fscanf(file,"%15s",tmp_string);
        strcpy(nickname, tmp_string);
        fscanf(file,"%15s",tmp_string);
        strcpy(password, tmp_string);

        if(front==NULL){
            front=create_users_list(nickname, password);
        }else{
            add_new_user(front, nickname, password);
        }
    }
    fclose(file);
    return front;
}

/**
* Funkcja zapisująca listę użytkowników w pliku.
* Funkcja wywoływana za końcu działania programu, odpowiada za zapis użytkowników z listy w pliku "listOfUsers.txt".
* @param front Wskaźnik na pierwszy element listy.
* @return Funkcja zwraca wartość logiczną: true - w przypadku gdy zapis się powiódł, false - gdy zapis się nie powiódł.
*/
bool updatingUsersFile(struct Users *front){
    FILE *file=fopen("listOfUsers.txt", "w");
    if(file){
        for (; NULL != front; front = front->next){
            fprintf(file, "%15s%15s", front->nickname, front->password);
            if(front->next!=NULL)
                fprintf(file, "\n");
        }
        fclose(file);
        return true;
    }
    return false;
}

/**
* Funkcja pomocnicza usuwająca element z początku listy (zwalniająca pamięć).
* @param front Wskaźnik na początek listy.
* @return Funkcja zwraca wskaźnik na kolejny, nieusunięty element na liście.
*/
struct Users *delete_user_front(struct Users *front){
    struct Users *next = front->next;
    free(front);
    puts("Udalo sie usunac konto");
    return next;
}

/**
* Funkcja pomocnicza znajdująca element poprzedzający element do usunięcia.
* @param front Wskaźnik na pierwszy element listy.
* @param nickname Tablica znaków przechowująca login użytkowników.
* @return Funkcja zwraca wskaźnik na znaleziony element.
*/
struct Users *find_user_prev_node(struct Users *front, char nickname[15]){
    struct Users *prev = NULL;
    while((NULL != front) && (strcmp(front->nickname,nickname)!=0)){
        prev = front;
        front = front->next ;
    }
    return prev;
}

/**
* Funkcja pomocniczna usuwająca element następny po przekazanym elemencie.
* Funkcja nie zwracająca żadnej wartości.
* @param node Wskaźnik na element, który poprzedza usuwany element.
*/
void delete_user_after(struct Users *node){
    struct Users *next = node->next;
    if (NULL != next){
        node->next = next->next;
        free(next);
    }
}

/**
* Funkcja usuwająca użytkownika.
* @param front Wskaźnik na początek listy użytkowników.
* @param nickname Tablica znaków przechowująca login użytkownika.
* @return Funkcja zawraca wskaźnik na początek listy użytkowników.
* @see delete_user_front()
* @see find_user_prev_node()
* @see delete_user_after()
*/
struct Users *delete_user_node(struct Users *front, char nickname[15]){
    if(NULL == front)
        return NULL;
    if(strcmp(front->nickname,nickname)==0){
        return delete_user_front(front);
    }
    struct Users *prev = find_user_prev_node(front, nickname);
    delete_user_after(prev);
    puts("Udalo sie usunac konto");
    return front;
}

/**
* Funkcja wyświetlająca wszystkich dostępnych użytkowników.
* Nie zwraca żadnej wartości.
* @param front Wskaźnik na początek listy użytkowników.
*/
void print_all_users(struct Users *front){
    puts("\nDostepni uzytkownicy: ");
    for (; NULL != front; front = front->next)
        printf ("%s\n", front->nickname);
    printf ("\n");
}

/**
* Funkcja usuwająca listę użytkowników.
* Wywoływana jest po zapisaniu wszystkich użytkowników w pliku. Zwalnia pamięć przed zakończeniem programu. Nie zwraca żadnej wartości.
* @param front Wskaźnik na wskaźnik na początek listy użytkowników.
*/
void remove_users_list(struct Users **front){
    while (NULL != *front){
        struct Users *next =(*front)->next;
        free(*front);
        *front=next;
    }
}

/**
* Funkcja sprawdzająca istnienie użytkownika.
* @param front Wskaźnik na początek listy użytkowników.
* @param nickname Tablica znaków przechowująca login użytkownika, który szukany jest w tablicy.
* @return Funkcja zwraca wskaźnik na znalezionego użytkownika lub wartość NULL w przypadku nieznalezienia elementu.
*/
struct Users *user_check(struct Users *front, char nickname[15]){
    for (; NULL != front; front = front->next)
        if(strcmp(front->nickname, nickname)==0)
            return front;
    return NULL;
}

/**
* Funkcja sprawdzająca istnienie użytkownika o podanym loginie i haśle.
* @param front Wskaźnik na pierwszy element listy użytkowników.
* @param nickname Tablica znaków przechowująca login użytkownika.
* @param password Tablica znaków przechowująca hasło użytkownika.
* @return Funkcja zwraca wartość logiczna true jeżeli użytkownik o danym loginie istnieje i jego hasło jest prawidłowe, albo wartość false, gdy któryś z tych warunków jest niespełniony.
* @see user_check()
*/
bool passwordCheck(struct Users *front, char nickname[15], char password[15]){
    struct Users *tmp=user_check(front, nickname);
    if(tmp && strcmp(tmp->password, password)==0)
        return true;
    return false;
}

/**
* Funkcja dokonująca zmiany hasła danego użytkownika.
* @param front Wskaźnik na początek listy użytkowników.
* @param nickname Tablica znaków przechowująca login użytkownika.
* @param prev_password Tablica znaków przechowująca aktualne hasło użytkownika.
* @param new_password Tablica znaków przechowująca nowe hasło użytkownika.
* @return Funkcja zwraca wartość logiczną true w przypadku, gdy zmiana hasła się powiodła lub false w przypadku niepowodzenia.
* @see user_check()
*/
bool changePassword(struct Users *front, char nickname[15], char prev_password[15], char new_password[15]){
    struct Users *tmp=user_check(front, nickname);
    if(tmp && strcmp(tmp->password, prev_password)==0){
        strcpy(tmp->password, new_password);
        return true;
    }
    return false;
}

/**
* Funkcja obsługująca logowanie użytkownika.
* @param front Wskaźnik na początek listy użytkowników.
* @param nickname Tablica znaków przechowująca login użytkownika.
* @param password Tablica znaków przechowująca hasło użytkownika.
* @return Funkcja zwraca wskaźnik na zalogowanego użytkownika lub w przypadku niepowodzenia wartość NULL.
* @see passwordCheck()
*/
struct Users *signIn(struct Users *front, char nickname[15], char password[15]){
    struct Users *user=user_check(front, nickname);
    if(NULL==front)
        return NULL;
    if(user && passwordCheck(front, nickname, password))
        puts("\nJestes zalogowany!");
    else{
        puts("Nieprawidlowe haslo lub nie ma takiego uzytkownika!");
        return NULL;
    }
    return user;
}

/**
* Funkcja odpowiadająca za pobieranie danych od użytkownika.
* Nie zwraca żadnej wartości.
* @param nickname Tablica znaków przechowująca login użytkownika.
* @param password Tablica znaków przechowująca hasło użytkownika.
*/
void dataInput(char nickname[15], char password[15]){
    puts("Podaj nazwe uzytkownika:");
    scanf("%15s", nickname);
    puts("Podaj haslo:");
    scanf("%15s", password);
}

/**
* Główny interfejs programu.
* Funkcja stanowi główne menu zarządzania użytkownikami, umożliwia dodawanie, usuwanie, edycje oraz wyświetlanie użytkowników, a także logowanie użytkownika.
* W niej odbywa się zapis/odczyt użytkowników z/do pliku. Nie przyjmuje ona żadnych parametrów ani nie zwraca żadnej wartości.
* @see dataInput()
* @see updatingUsersFile()
* @see loadingUsers()
* @see create_users_list()
* @see add_new_user()
* @see print_all_users()
* @see user_check()
* @see passwordCheck()
* @see changePassword()
* @see delete_user_node()
* @see remove_users_list()
* @see userInterface()
*/
void mainInterface(){
    struct Users *first_user=NULL;
    struct Users *user=NULL;
    char answer;
    char nickname[15], password[15], new_password[15];
    int option;

    first_user=loadingUsers(first_user);

    puts("____________________");
    puts("Witaj w aplikacji Kontakty.");
    if(!first_user){
        puts("Nie ma zadnych uzytkownikow. Czy chcesz zalozyc konto?(t/n)");
        scanf("%c", &answer);
        if(answer=='t'|| answer=='T'){
            dataInput(nickname, password);
            first_user=create_users_list(nickname, password);
            updatingUsersFile(first_user);
        }else{
            puts("Do widzenia!");
            return ;
        }
    }
    do{
        puts("\tCo chcesz zrobic?\n\t1-logowanie\n\t2-nowe konto\n\t3-zmiana hasla\n\t4-usuniecie konta\n\t5-wyswietl uzytkownikow\n\t0-wyjscie\n");
        scanf("%d", &option);
        switch(option){
        case 1:
            //logowanie usera
            dataInput(nickname, password);
            user=signIn(first_user, nickname, password);
            if(user){
                userInterface(nickname, user->file_name);
            }
            break;
        case 2:
            //tworzenie nowego konta
            dataInput(nickname, password);
            if(!user_check(first_user, nickname)){
                add_new_user(first_user, nickname, password);
                print_all_users(first_user);
            }else{
                printf("Takie konto juz istnieje!\n");
            }
            break;
        case 3:
            //zmiana hasla
            dataInput(nickname, password);
            if(passwordCheck(first_user, nickname, password)){
                puts("Podaj nowe haslo.");
                scanf("%15s", new_password);
                puts("Czy na pewno chcesz zmienic haslo? (t/n)");
                scanf(" %c", &answer);
                if(answer=='t'|| answer=='T'){
                    if(changePassword(first_user, nickname, password, new_password))
                        puts("Udalo sie zmienic haslo.");
                }else
                    puts("Nie udalo sie zmienic hasla.");
            }else
                puts("Nieprawidlowe haslo!");
            break;
        case 4:
            //usuniecie konta
            dataInput(nickname, password);
            puts("Czy na pewno chcesz usunac tego uzytkownika? (t/n)");
            scanf(" %c", &answer);
            if(answer=='t'|| answer=='T'){
                if(passwordCheck(first_user, nickname, password)){
                    first_user=delete_user_node(first_user, nickname);
                    updatingUsersFile(first_user);
                }else
                    puts("Nieprawidlowe haslo!");
            }else
                printf("Konto nie zostalo usuniete.\n");

            break;
        case 5:
            //wyswietlenie wszystkich userow
            print_all_users(first_user);
            break;
        case 0:
            //wyjscie i aktualizacja danych w pliku
            if(updatingUsersFile(first_user))
                puts("Udalo sie zaktualizowac plik.");
            else
                puts("Nie udalo sie zaktualizowac pliku.");
            remove_users_list(&first_user);
            puts("Do widzenia!");
            break;
        default:
            puts("Nie ma takiej opcji!");
        }
    } while(option!=0 && first_user);
}
