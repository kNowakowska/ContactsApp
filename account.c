#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include"account.h"

/** Struktura Contact. Struktura wykorzystana do tworzenia jednokierunkowej uporządkowanej (według id) listy kontaktów. */
struct Contact{
    unsigned int id; /**< Numer id konktaktu (przydzielany automatycznie).*/
    char name[15]; /**< Tablica znaków przechowująca imie kontaktu.*/
    char surname[15]; /**< Tablica znaków przechowująca nazwisko kontaktu.*/
    char city[15]; /**< Tablica znaków przechowująca miasto zamieszkania kontaktu.*/
    char street_name[15]; /**< Tablica znaków przechowująca nazwę ulicy w adresie kontaktu.*/
    char street_number[10]; /**< Tablica znaków przechowująca numer domu kontaktu.*/
    char postcode[6]; /**< Tablica znaków przechowująca kod pocztowy kontaktu.*/
    char postname[15]; /**< Tablica znaków przechowująca nazwę poczty kontaktu.*/
    char phone_number[10]; /**< Tablica znaków przechowująca numer telefonu kontaktu.*/
    char email[20]; /**< Tablica znaków przechowująca adres e-mail kontaktu.*/
    struct Contact *next; /**< Wskaźnik na następny element listy. */
};

/**
* Funkcja odpowiadająca za utworzenie pierwszego elementu listy kontaktów (alokacja pamięci).
* @param name Tablica znaków przechowująca imię kontaktu.
* @param surname Tablica znaków przechowująca nazwisko kontaktu.
* @param city Tablica znaków przechowująca miasto zamieszkania kontaktu.
* @param street_name Tablica znaków przechowująca nazwę ulicy w adresie kontaktu.
* @param street_number Tablica znaków przechowująca numer domu kontaktu.
* @param postcode Tablica znaków przechowująca kod pocztowy kontaktu.
* @param postname Tablice znaków przechowująca nazwę poczty kontaktu.
* @param phone_number Tablica znaków przechowująca numer telefonu kontaktu.
* @param email Tablica znaków przechowująca adres email kontaktu.
* @return Funkcja zwraca wskaźnik na utworzony element będący początkiem listy kontaktów.
*/
struct Contact *create_list(char name[15], char surname[15], char city[15], char street_name[15], char street_number[15], char postcode[6],char postname[15], char phone_number[10], char email[20]){
    struct Contact *front =(struct Contact *)malloc(sizeof(struct Contact));
    if(NULL != front){
        front->id=1;
        strcpy(front->name, name);
        strcpy(front->surname, surname);
        strcpy(front->city, city);
        strcpy(front->street_name, street_name);
        strcpy(front->street_number, street_number);
        strcpy(front->postcode, postcode);
        strcpy(front->postname, postname);
        strcpy(front->phone_number, phone_number);
        strcpy(front->email, email);
        front->next=NULL;
    }
    return front;
}

/**
* Funkcja pomocniczna której zadaniem jest dodanie elementu na koniec listy.
* Funkcja nie zwraca żadnej wartości.
* @param back Wskaźnik na ostatni element listy kontaktów.
* @param new_node Wskaźnik na dodawany do listy element.
*/
void insert_back(struct Contact *back, struct Contact *new_node){
    back->next=new_node;
}
/**
* Funkcja tworząca nowy element, wypełniająca go odpowiednimi danymi oraz dodająca go na koniec listy.
* @param front Wskaźnik na wskaźnik do pierwszego elementu listy.
* @param name Tablica znaków przechowująca imię kontaktu.
* @param surname Tablica znaków przechowująca nazwisko kontaktu.
* @param city Tablica znaków przechowująca miasto zamieszkania kontaktu.
* @param street_name Tablica znaków przechowująca nazwę ulicy zamieszkania kontaktu.
* @param street_number Tablica znaków przechowująca numer domu kontaktu.
* @param postcode Tablica znaków przechowująca kod pocztowy kontaktu.
* @param postname Tablice znaków przechowująca nazwę poczty kontaktu.
* @param phone_number Tablica znaków przechowująca numer telefonu kontaktu.
* @param email Tablica znaków przechowująca adres email kontaktu.
* @return Funkcja zwraca wartość logiczną true - jeśli dodanie elementu sie powiedzie, false - jeśli się nie powiedzie.
* @see create_list()
* @see insert_back()
*/
bool insert_node(struct Contact **front, char name[15], char surname[15], char city[15], char street_name[15], char street_number[15], char postcode[6],char postname[15], char phone_number[10], char email[20]){
    if(NULL==*front){
        *front=create_list(name,surname, city, street_name, street_number, postcode, postname, phone_number, email);
        return true;
    }
    struct Contact *new_node = (struct Contact *)malloc(sizeof(struct Contact));
    struct Contact *tmp=*front, *prev=NULL;
    if(new_node){
        strcpy(new_node->name, name);
        strcpy(new_node->surname, surname);
        strcpy(new_node->city, city);
        strcpy(new_node->street_name, street_name);
        strcpy(new_node->street_number, street_number);
        strcpy(new_node->postcode,postcode);
        strcpy(new_node->postname, postname);
        strcpy(new_node->phone_number, phone_number);
        strcpy(new_node->email, email);
        new_node->next=NULL;
        while(tmp){
            prev=tmp;
            tmp=tmp->next;
        }
        new_node->id=prev->id +1;
        insert_back(prev, new_node);
        return true;
    }
    return false;
}

/**
* Funkcja pomocnicza odpowiadająca za usunięcie elementu z początku listy (zwolnienie pamięci).
* @param front Wskaźnik na początek listy kontaktów.
* @return Funkcja zwraca wskaźnik na pierwszy nieusunięty element na liście.
*/
struct Contact *delete_front(struct Contact *front){
    struct Contact *next = front->next;
    free(front);
    return next;
}

/**
* Funkcja znajdująca element poprzedzający element o podanym id.
* @param front Wskaźnik na początek listy kontaktów.
* @param id Numer id elementu, którego poprzednik jest szukany.
* @return Funkcja zwraca wskaźnik do znalezionego elementu.
*/
struct Contact *find_prev_node(struct Contact *front, unsigned int id){
    struct Contact * prev = NULL;
    while ((NULL!=front)&&front->id!=id){
        prev=front;
        front=front->next;
    }
    return prev;
}

/**
* Funkcja usuwająca element po danym elemencie z listy.
* Nie zwraca żadnej wartości.
* @param node Wskaźnik do elementu, którego następnik należy usunąć.
*/
void delete_after(struct Contact *node){
    struct Contact *next= node->next;
    if (NULL!=next){
        node->next=next->next;
        free(next);
    }
}

/**
* Funkcja usuwająca z listy element o danym id.
* @param front Wskaźnik na początek listy kontaktów.
* @param id Numer id elementu, który należy usunąć.
* @return Funkcja zwraca wskaźnik do początku listy kontaktów.
* @see delete_front()
* @see find_prev_node()
* @see delete_after()
*/
struct Contact *delete_node(struct Contact *front,unsigned int id){
    if (NULL==front){
        return NULL;
    }
    if (front->id == id)
        return delete_front(front);
    struct Contact *prev = find_prev_node(front,id);
    delete_after(prev);
    return(front);
}

/**
* Funkcja wyszukująca element po jego id.
* @param front Wskaźnik do początku listy kontaktów.
* @param id Numer id wyszukiwanego kontaktu.
* @return Funkcja zwraca wskaźnik do znalezionego elementu lub wartość NULL.
*/
struct Contact *find_node(struct Contact *front, unsigned int id){
    if(front==NULL)
        return NULL;
    struct Contact *node=front;
    while(node && node->id!=id){
        node=node->next;
    }
    return node;
}

/**
* Funkcja zarządzająca wyszukiwaniem kontaktu.
* Posiada rozbudowane menu, które umożliwia wyszukiwanie po dowolnym polu. Jeżeli znajdzie pasujące kontakty (ignorując wielkość liter), wyświetla je. Nie zwraca żadnej wartości.
* @param front Wskaźnik na początek listy kontaktów.
* @see print_contact()
*/
void find_contacts(struct Contact *front){
    struct Contact *tmp=NULL;
    char name[15], surname[15], city[15], street_name[15], street_number[10], postcode[6], postname[15], phone_number[10], email[20];
    int id;
    int option=0;
    do{
        puts("Wybierz pole wedlug ktorego chcesz wyszukac?\n\n\t\t1-id\n\t\t2-imie\n\t\t3-nazwisko\n\t\t4-miasto zamieszkania\n\t\t5-nazwa ulicy\n\t\t6-numer domu\n\t\t7-kod pocztowy\n\t\t8-poczta\n\t\t9-numer telefonu\n\t\t10-adres email\n\t\t0-wyjscie\n");
        scanf("%d",&option);
        switch (option){
        case 1:
            puts("Podaj id.");
            scanf("%d", &id);
            if(!print_contact(front, id)){
                printf("Nie udalo sie znalezc kontaktu.\n");
            }
            break;
        case 2:
            puts("Podaj imie lub jego fragment.");
            scanf("%15s", name);
            tmp=front;
            printf("Znalezione kontakty: \n");
            while(tmp){
                if(stricmp(tmp->name, name)==0){
                    print_contact(front, tmp->id);
                }else if(strstr(tmp->name, name)){
                    print_contact(front, tmp->id);
                }
                tmp=tmp->next;
            }
            break;
        case 3:
            puts("Podaj nazwisko lub jego fragment.");
            scanf("%15s", surname);
            tmp=front;
            printf("Znalezione kontakty: \n");
            while(tmp){
                if(stricmp(tmp->surname, surname)==0){
                    print_contact(front, tmp->id);
                }else if(strstr(tmp->surname, surname)){
                    print_contact(front, tmp->id);
                }
                tmp=tmp->next;
            }
            break;
        case 4:
            puts("Podaj nazwe miasta lub jego fragment.");
            scanf("%15s", city);
            tmp=front;
            printf("Znalezione kontakty: \n");
            while(tmp){
                if(stricmp(tmp->city, city)==0){
                    print_contact(front, tmp->id);
                }else if(strstr(tmp->city, city)){
                    print_contact(front, tmp->id);
                }
                tmp=tmp->next;
            }
            break;
        case 5:
            puts("Podaj nazwe ulicy lub jej fragment.");
            scanf("%15s", street_name);
            tmp=front;
            printf("Znalezione kontakty: \n");
            while(tmp){
                if(stricmp(tmp->street_name, street_name)==0){
                    print_contact(front, tmp->id);
                }else if(strstr(tmp->street_name, street_name)){
                    print_contact(front, tmp->id);
                }
                tmp=tmp->next;
            }
            break;
        case 6:
            puts("Podaj numer domu lub jego fragment.");
            scanf("%10s", street_number);
            tmp=front;
            printf("Znalezione kontakty: \n");
            while(tmp){
                if(stricmp(tmp->street_number, street_number)==0){
                    print_contact(front, tmp->id);
                }else if(strstr(tmp->street_number, street_number)){
                    print_contact(front, tmp->id);
                }
                tmp=tmp->next;
            }
            break;
        case 7:
            puts("Podaj kod pocztowy lub jego fragment.");
            scanf("%6s", postcode);
            tmp=front;
            printf("Znalezione kontakty: \n");
            while(tmp){
                if(stricmp(tmp->postcode, postcode)==0){
                    print_contact(front, tmp->id);
                }else if(strstr(tmp->postcode, postcode)){
                    print_contact(front, tmp->id);
                }
                tmp=tmp->next;
            }
            break;
        case 8:
            puts("Podaj nazwe poczty lub jej fragment.");
            scanf("%15s", postname);
            tmp=front;
            printf("Znalezione kontakty: \n");
            while(tmp){
                if(stricmp(tmp->postname, postname)==0){
                    print_contact(front, tmp->id);
                }else if(strstr(tmp->postname, postname)){
                    print_contact(front, tmp->id);
                }
                tmp=tmp->next;
            }
            break;
        case 9:
            puts("Podaj numer telefonu lub jego fragment.");
            scanf("%10s", phone_number);
            tmp=front;
            printf("Znalezione kontakty: \n");
            while(tmp){
                if(stricmp(tmp->phone_number, phone_number)==0){
                    print_contact(front, tmp->id);
                }else if(strstr(tmp->phone_number, phone_number)){
                    print_contact(front, tmp->id);
                }
                tmp=tmp->next;
            }
            break;
        case 10:
            puts("Podaj adres e-mail lub jego fragment.");
            scanf("%10s", email);
            tmp=front;
            printf("Znalezione kontakty: \n");
            while(tmp){
                if(stricmp(tmp->email, email)==0){
                    print_contact(front, tmp->id);
                }else if(strstr(tmp->email, email)){
                    print_contact(front, tmp->id);
                }
                tmp=tmp->next;
            }
            break;
        case 0:
                puts("Koniec edycji.");
            break;
        default:
                puts("Nie ma takiej opcji.");
        }
    }while(option!=0);
}

/**
* Funkcja zarządzająca edycją kontaktu.
* Poprzez menu umożliwia wybór pola do edycji. Każda zmiana danych kontaktu wymaga potwierdzenia. Nie zwraca żadnej wartości.
* @param front Wskaźnik do początku listy kontaktów.
* @param id Numer id edytowanego kontaktu.
* @see find_node()
* @see print_contact()
*/
void editContact(struct Contact *front, unsigned int id){
    struct Contact *node=find_node(front, id);
    int option=0;
    char answer;

    char edit_name[15],edit_surname[15], city[15],street_name[15], street_number[15], postname[15], phone_number[15], email[15],  postcode[6];
    if(node && node->id ==id){
        print_contact(front, id);
        puts("Czy na pewno chcesz edytowac ten kontakt? (t/n)");
        scanf(" %c", &answer);
        if(answer=='t'|| answer=='T'){
            do{
            puts("Co chcesz edytowac?\n\n\t\t1-imie\n\t\t2-nazwisko\n\t\t3-miasto zamieszkania\n\t\t4-nazwa ulicy\n\t\t5-numer domu\n\t\t6-kod pocztowy\n\t\t7-poczta\n\t\t8-numer telefonu\n\t\t9-adres email\n\t\t0-nic\n");
            scanf("%d",&option);
            switch (option){
            case 1:
                puts("Podaj nowe imie.");
                scanf("%15s", edit_name);
                strcpy(node->name, edit_name);
                break;
            case 2:
                puts("Podaj nowe nazwisko.");
                scanf("%15s", edit_surname);
                strcpy(node->surname, edit_surname);
                break;
            case 3:
                puts("Podaj nowe miasto.");
                scanf("%15s", city);
                strcpy(node->city, city);
                break;
            case 4:
                puts("Podaj nowa nazwe ulicy.");
                scanf("%15s", street_name);
                strcpy(node->street_name, street_name);
                break;
            case 5:
                puts("Podaj nowy numer domu.");
                scanf("%15s", street_number);
                strcpy(node->street_number, street_number);
                break;
            case 6:
                puts("Podaj nowy kod pocztowy.");
                scanf("%6s", postcode);
                strcpy(node->postcode,postcode);
                break;
            case 7:
                puts("Podaj nowa nazwe poczty.");
                scanf("%15s", postname);
                strcpy(node->postname, postname);
                break;
            case 8:
                puts("Podaj nowy numer telefonu.");
                scanf("%15s", phone_number);
                strcpy(node->phone_number, phone_number);
                break;
            case 9:
                puts("Podaj nowy adres email.");
                scanf("%15s", email);
                strcpy(node->email, email);
                break;
            case 0:
                puts("Koniec edycji.");
                break;
            default:
                puts("Nie ma takiej opcji.");
            }
            }while(option!=0);
        }

    }else{
        puts("Taki kontakt nie istnieje!");
    }
}

/**
* Funkcja wyświetlająca całą listę kontaktów.
* Nie zwraca żadnej wartości.
* @param front Wskaźnik na początek listy kontaktów.
*/
void print_list(struct Contact *front){
    printf("\nLista kontaktow: \n");
    for(; NULL!=front; front = front->next){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", front->id, front->name, front->surname, front->city, front->street_name, front->street_number, front->postcode, front->postname, front->phone_number, front->email);
    }
    printf("\n");
}

/**
* Funkcja wyświetlająca kontakt o podanym id.
* @param front Wskaźnik na początek listy kontaktów.
* @param id Numer id kontaktu, który należy wyświetlić.
* @return Funkcja zwraca wartość true w przypadku znalezienia i wyswietlenia kontaktu lub wartość false w przypadku nie znalezienia kontaktu o takim id.
* @see find_node()
*/
bool print_contact(struct Contact *front, unsigned int id){
    struct Contact *node = find_node(front, id);
    if(node){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", node->id, node->name, node->surname, node->city, node->street_name, node->street_number, node->postcode, node->postname, node->phone_number, node->email);
        return true;
    }else
        return false;
}

/**
* Funkcja usuwająca całą listę kontaktów.
* Zwalnia alokowaną pamięć.Wykorzystywana na koniec działania programu po zapisaniu kontaktów do pliku. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na wskaźnik do początkowego elementu listy.
*/
void remove_list(struct Contact **front){
    while (NULL != *front){
        struct Contact *next =(*front)->next;
        free(*front);
        *front=next;
    }
}

/**
* Funkcja odpowiadająca za odczyt kontaktów z pliku i utworzenie z nich listy.
* Wywoływana po zalogowaniu użytkownika.
* @param front Wskaźnik do początku listy kontaktów.
* @param file_name Tablica znaków przechowująca nazwę pliku, w którym dany użytkownik przechowuje kontaktu.
* @return Funkcja zwraca wskaźnik do początku tablicy po jej aktualizacji.
* @see insert_node()
*/
struct Contact *loadingContacts(struct Contact *front, char file_name[27]){
    FILE *file = fopen(file_name, "r");
    char name[15], surname[15], city[15], street_name[15], street_number[15],postname[15], phone_number[10],email[20], postcode[6];
    if(!file)
        return NULL;
    printf("%c", fgetc(file));
    while(!feof(file)){
        fscanf(file,"%15s",name);
        fscanf(file,"%15s",surname);
        fscanf(file,"%15s",city);
        fscanf(file,"%15s",street_name);
        fscanf(file,"%15s",street_number);
        fscanf(file,"%6s",postcode);
        fscanf(file,"%15s",postname);
        fscanf(file,"%10s",phone_number);
        fscanf(file,"%20s",email);

        insert_node(&front, name, surname, city, street_name, street_number, postcode, postname, phone_number, email);
    }
    fclose(file);
    return front;
}

/**
* Funkcja odpowiadająca za zapis listy kontaktów do pliku.
* Wywoływana na życzenie użytkownika.
* @param front Wskaźnik na początek listy kontaktów.
* @param file_name Tablica znaków przechowująca nazwę pliku, w którym dany użytkownik przechowuje kontakty.
* @return Funkcja zwraca wartość logiczną true w przypadku powodzenia operacji lub false w przypadku niepowodzenia.
*/
bool updatingContactsFile(struct Contact *front, char file_name[27]){
    FILE *file=fopen(file_name, "w");
    if(file){
        for (; NULL != front; front = front->next){
            fprintf(file, "%15s%15s%15s%15s%15s%6s%15s%10s%20s", front->name, front->surname, front->city, front->street_name, front->street_number, front->postcode, front->postname, front->phone_number, front->email);
            if(front->next!=NULL)
                fprintf(file, "\n");
        }
        fclose(file);
        return true;
    }else{
        puts("Nie udalo sie zapisac kontaktow.");
    }
    return false;
}

/** Struktura MetaList. Struktura wykorzystywana do tworzenia metalisty przy sortowaniu listy kontaktów. */
struct MetaList{
    struct Contact *contact_ptr; /**< Wskaźnik do elementu (kontaktu) oryginalnej listy. */
    struct MetaList *next; /**< Wskaźnik na następny element metalisty. */
};

/**
* Funkcja pomocniczna odpowiadająca za usunięcię metalisty i zwolnienie alokowanej pamięci.
* Nie zwraca żadnej wartości.
* @param front Wskaźnik na wskaźnik na początek metalisty kontaktów.
*/
void remove_mList(struct MetaList **front){
    while (NULL != *front){
        struct MetaList *next =(*front)->next;
        free(*front);
        *front=next;
    }
}

/**
* Funkcja sortująca rosnąco według imienia.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_name_asc(struct Contact *front){
    struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->name, new_node->contact_ptr->name)>=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->name, new_node->contact_ptr->name)<0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca rosnąco według nazwiska.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_surname_asc(struct Contact *front){
     struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->surname, new_node->contact_ptr->surname)>=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->surname, new_node->contact_ptr->surname)<0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca rosnąco według miasta zamieszkania.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_city_asc(struct Contact *front){
   struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->city, new_node->contact_ptr->city)>=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->city, new_node->contact_ptr->city)<0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca rosnąco według nazwy ulicy zamieszkania.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_streetname_asc(struct Contact *front){
    struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->street_name, new_node->contact_ptr->street_name)>=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->street_name, new_node->contact_ptr->street_name)<0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca rosnąco według numeru domu.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_streetnumber_asc(struct Contact *front){
   struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->street_number, new_node->contact_ptr->street_number)>=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->street_number, new_node->contact_ptr->street_number)<0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca rosnąco według kodu pocztowego.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_postcode_asc(struct Contact *front){
    struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->postcode, new_node->contact_ptr->postcode)>=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->postcode, new_node->contact_ptr->postcode)<0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca rosnąco według nazwy poczty.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_postname_asc(struct Contact *front){
  struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->postname, new_node->contact_ptr->postname)>=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->postname, new_node->contact_ptr->postname)<0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca rosnąco według numeru telefonu.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_phonenumber_asc(struct Contact *front){
   struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->phone_number, new_node->contact_ptr->phone_number)>=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->phone_number, new_node->contact_ptr->phone_number)<0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca rosnąco według adresu email.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_email_asc(struct Contact *front){
   struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->email, new_node->contact_ptr->email)>=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->email, new_node->contact_ptr->email)<0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca malejąco według imienia.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_name_desc(struct Contact *front){
    struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->name, new_node->contact_ptr->name)<=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->name, new_node->contact_ptr->name)>0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca malejąco według nazwiska.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_surname_desc(struct Contact *front){
    struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->surname, new_node->contact_ptr->surname)<=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->surname, new_node->contact_ptr->surname)>0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca malejąco według miasta zamieszkania.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_city_desc(struct Contact *front){
    struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->city, new_node->contact_ptr->city)<=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->city, new_node->contact_ptr->city)>0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca malejąco według nazwy ulicy .
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_streetname_desc(struct Contact *front){
    struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->street_name, new_node->contact_ptr->street_name)<=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->street_name, new_node->contact_ptr->street_name)>0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca malejąco według numeru domu.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_streetnumber_desc(struct Contact *front){
    struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->street_number, new_node->contact_ptr->street_number)<=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->street_number, new_node->contact_ptr->street_number)>0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca malejąco według kodu pocztowego.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_postcode_desc(struct Contact *front){
   struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->postcode, new_node->contact_ptr->postcode)<=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->postcode, new_node->contact_ptr->postcode)>0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca melejąco według nazwy poczty.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_postname_desc(struct Contact *front){
   struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->postname, new_node->contact_ptr->postname)<=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->postname, new_node->contact_ptr->postname)>0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca malejąco według numeru telefonu.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_phonenumber_desc(struct Contact *front){
    struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->phone_number, new_node->contact_ptr->phone_number)<=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->phone_number, new_node->contact_ptr->phone_number)>0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Funkcja sortująca malejąco według adresu email.
* Funkcja wykorzystuje metalistę stworzoną z użyciem struktury MetaList.Po posortowaniu metalista jest wyświetlana i usuwana. Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów. Lista nie jest modyfikowana, jedynie przeglądane są jej elementy.
* @see remove_mList()
*/
void sort_email_desc(struct Contact *front){
    struct MetaList *mList=NULL;
    while(front){
        struct MetaList *new_node = (struct MetaList *)malloc(sizeof(struct MetaList));
        new_node->next=NULL;
        new_node->contact_ptr=front;
        if(mList==NULL){
            mList=new_node;
        }else{
            if(strcmp(mList->contact_ptr->email, new_node->contact_ptr->email)<=0){
                new_node->next=mList;
                mList=new_node;
            }else{
                struct MetaList *prev=NULL, *tmp=mList;
                while(tmp&&strcmp(tmp->contact_ptr->email, new_node->contact_ptr->email)>0){
                    prev=tmp;
                    tmp=tmp->next;
                }
                 if(NULL!=prev->next){
                    new_node->next=prev->next;
                    prev->next=new_node;
                 }
                else
                    prev->next=new_node;
            }
        }
        front=front->next;
    }
    struct MetaList *tmp=mList;
    puts("Posortowana lista:");
    while(tmp){
        printf("%d Imie: %s Nazwisko: %s Adres: %s ul.%s %s %s %s Telefon: %s Email: %s\n", tmp->contact_ptr->id, tmp->contact_ptr->name, tmp->contact_ptr->surname, tmp->contact_ptr->city, tmp->contact_ptr->street_name, tmp->contact_ptr->street_number, tmp->contact_ptr->postcode, tmp->contact_ptr->postname, tmp->contact_ptr->phone_number, tmp->contact_ptr->email);
        tmp=tmp->next;
    }
    remove_mList(&mList);
}

/**
* Główna funkcją zarządzająca sortowaniem.
* Umożliwia wybór sortowania malejąco lub rosnąco, a następnie wybór według którego pola należy posortować kontakty. Po wyborze danej opcji wywoływana jest odpowiadająca mu funkcja.
* Funkcja nie zwraca żadnej wartości.
* @param front Wskaźnik na początek oryginalnej listy kontaktów.
* @see sort_name_desc()
* @see sort_surname_desc()
* @see sort_city_desc()
* @see sort_streetname_desc()
* @see sort_streetnumber_desc()
* @see sort_postcode_desc()
* @see sort_postname_desc()
* @see sort_phonenumber_desc()
* @see sort_email_desc()
* @see sort_name_asc()
* @see sort_surname_asc()
* @see sort_city_asc()
* @see sort_streetname_asc()
* @see sort_streetnumber_asc()
* @see sort_postcode_asc()
* @see sort_postname_asc()
* @see sort_phonenumber_asc()
* @see sort_email_asc()
*/
void sorting_interface(struct Contact *front){
    int option_1=0;
    int option_2=0;
    do{
        puts("Jak chcesz posortowac elementy?\n\t1-nierosnaco\n\t2-niemalejaco\n0-wyjdz z opcji sortowania\n\n");
        scanf("%d",&option_1);
        switch(option_1){
        case 1:
            do{
                puts("Wedlug jakiego pola chcesz posortowac elementy?\n\t1-imie\n\t2-nazwisko\n\t3-miasto\n\t4-nazwa ulicy\n\t5-numer domu\n\t6-kod pocztowy\n\t7-nazwa poczty\n\t8-numer telefonu\n\t9-adres email\n\t0-wyjdz z opcji sortowania\n\n");
                scanf("%d",&option_2);
                switch(option_2){
                case 1:
                    sort_name_desc(front);
                    break;
                case 2:
                   sort_surname_desc(front);
                    break;
                case 3:
                    sort_city_desc(front);
                    break;
                case 4:
                    sort_streetname_desc(front);
                    break;
                case 5:
                    sort_streetnumber_desc(front);
                    break;
                case 6:
                    sort_postcode_desc(front);
                    break;
                case 7:
                    sort_postname_desc(front);
                    break;
                case 8:
                    sort_phonenumber_desc(front);
                    break;
                case 9:
                    sort_email_desc(front);
                    break;
                case 0:
                    break;
                default:
                    printf("Nie ma takiej opcji.\n");
                }
            }while(option_2!=0);
            break;
        case 2:
            do{
                puts("Wedlug jakiego pola chcesz posortowac elementy?\n\t1-imie\n\t2-nazwisko\n\t3-miasto\n\t4-nazwa ulicy\n\t5-numer domu\n\t6-kod pocztowy\n\t7-nazwa poczty\n\t8-numer telefonu\n\t9-adres email\n\t0-wyjdz z opcji sortowania\n\n");
                scanf("%d",&option_2);
                switch(option_2){
                case 1:
                    sort_name_asc(front);
                    break;
                case 2:
                    sort_surname_asc(front);
                    break;
                case 3:
                    sort_city_asc(front);
                    break;
                case 4:
                    sort_streetname_asc(front);
                    break;
                case 5:
                    sort_streetnumber_asc(front);
                    break;
                case 6:
                    sort_postcode_asc(front);
                    break;
                case 7:
                    sort_postname_asc(front);
                    break;
                case 8:
                    sort_phonenumber_asc(front);
                    break;
                case 9:
                    sort_email_asc(front);
                    break;
                case 0:
                    break;
                default:
                    printf("Nie ma takiej opcji.\n");
                }
            }while(option_2!=0);
            break;
        case 0:
            break;
        default:
            printf("Nie ma takiej opcji.\n");
        }
    }while(option_1!=0);
}

/** Struktura Group. Struktura wykorzystywana do tworzenia listy grup z kontaktami */
struct Group{
    char title[15]; /**< Nazwa grupy (unikalna). */
    int number_of_elements; /**< Liczba kontaktów w grupie */
    struct Contact **array; /**< Tablica wskaźników na elementy listy kontaktów (wskaźniki do kontaktów).*/
    struct Group *next; /**< Wskaźnik na następny element listy grup */
};

/**
* Funkcja tworząca listę z pierwszą grupą.
* @param title Nazwa pierwszej grupy na liście.
* @return Funkcja zwraca wskaźnik na pierwszy element listy grup.
*/
struct Group *create_group_list(char title[15]){
    struct Group *group = (struct Group *)malloc(sizeof(struct Group));
    if(group){
        strcpy(group->title, title);
        group->number_of_elements=0;
        group->array=NULL;
        group->next=NULL;
    }
    return group;
}

/**
* Funkcja dodająca nowa grupę do listy.
* @param first_group Wskaźnik na początek listy grup.
* @param title Nazwa nowej grupy.
* @return Funkcja zwraca wskaźnik na początek listy z grupami.
* @see create_group_list()
*/
struct Group *add_group(struct Group *first_group, char title[15]){
    if(!first_group)
        first_group = create_group_list(title);

    else{
        for(struct Group *tmp=first_group; tmp; tmp=tmp->next){
            if(strcmp(tmp->title, title)==0)
                return NULL;
        }
        struct Group *group = (struct Group *)malloc(sizeof(struct Group));
        if(group){
            group->number_of_elements=0;
            strcpy(group->title, title);
            group->array=NULL;
            group->next=NULL;
        }
        struct Group *tmp=first_group;
        for(; tmp->next; tmp=tmp->next);
        tmp->next=group;
    }
    return first_group;
}

/**
* Funkcja odpowiadająca za usunięcie grupy kontaktów.
* @param first_group Wskażnika na wskaźnik na początek listy grup.
* @param title Nazwa usuwanej grupy.
* @return Funkcja zwraca wartość logiczną true w przypadku, gdy usuwanie się powiedzie, lub false, gdy usuwanie się nie powiedzie.
*/
bool delete_group(struct Group **first_group, char title[15]){
    struct Group *prev=NULL, *tmp=*first_group, *next=NULL;
    if(*first_group&&strcmp((*first_group)->title, title)==0){
        next=(*first_group)->next;
        free(*first_group);
        *first_group=next;
        return true;
    }
    for(; tmp && strcmp(tmp->title, title)!=0; ){
        prev=tmp;
        tmp=tmp->next;
    }
    if(tmp){
        if(tmp->next){
            prev->next=tmp->next;
        }else{
            prev->next=NULL;
        }
        free(tmp->array);
        tmp->array=NULL;
        free(tmp);
        tmp=NULL;
        return true;
    }
    return false;
}

/**
* Funkcja wyszukująca grupę po jej nazwie.
* @param first_group Wskaźnik na początek grupy.
* @param title Nazwa grupy.
* @return Funkcja zwraca wskaźnik na element o danej nazwie (lub wartość NULL).
*/
struct Group *find_group(struct Group *first_group, char title[15]){
    struct Group *tmp=first_group;
    while(tmp && strcmp(tmp->title, title)!=0){
        tmp=tmp->next;
    }
    return tmp;
}

/**
* Funkcja wypisująca zawartość grupy.
* Nie zwraca żadnej wartości.
* @param group Wskaźnik na grupę, której zawartość należy wypisać.
*/
void print_group(struct Group *group){
    printf("Grupa o nazwie \"%s\" posiada elementy:\n",group->title);
    for(int i=0; i<group->number_of_elements; i++){
        printf("Imie: %s Nazwisko: %s Id: %d\n", group->array[i]->name, group->array[i]->surname, group->array[i]->id);
    }
}

/**
* Funkcja dodająca kontakt do danej grupy.
* W przypadku, gdy dynamiczna tablica ze wskaźnikami na kontakty nie istnieje, jest ona tworzona (funkcja calloc), a jeśli istnieje jej rozmiar jest powiekszany o 1 i pamięć na nią jest realokowana (funkcja realloc).
* Funkcja nie zwraca żadnej wartości.
* @param group Wskaźnik na grupę do której dodawany będzie kontakt.
* @param contact Wskaźnik na kontakt, który dodawany będzie do grupy.
*/
void add_contact_to_group(struct Group *group, struct Contact *contact){
    group->number_of_elements++;
    if(group->number_of_elements==1){
        struct Contact **array = (struct Contact **)calloc(1, sizeof(struct Contact *));
        group->array=array;
        group->array[group->number_of_elements-1]=contact;
    }else{
        group->array=(struct Contact **)realloc(group->array, (group->number_of_elements)*sizeof(struct Contact *));
        group->array[group->number_of_elements-1]=contact;
    }
}

/**
* Funkcja pomocnicza przepisująca zawartość tablicy do mniejszej tablicy.
* W przypadku usuwania kontaktu z tablicy, funkcja realloc mogłaby nie zadziałać prawidłowo przez co użytkownik utraciłby część danych.
* Z tego względu zdecydowano się na stworzenie dodatkowej funkcji przepisującej starą tablicę do nowej o mniejszym rozmiarze.
* Funkcja nie zwraca żadnej wartości.
* @param group Wskaźnik do grupy, z której usuwany jest kontakt.
*/
void rewrite_array(struct Group *group){
    int size=group->number_of_elements;
    int new_size=size-1;
    struct Contact **array_1 = (struct Contact **)calloc(new_size, sizeof(struct Contact *));
    for(int i=0, j=0; i<new_size&& j<size; i++, j++){
        if(group->array[j]!=NULL){
            array_1[i]=group->array[j];
        }else
            i--;
    }
    group->number_of_elements=new_size;
    free(group->array);
    group->array=array_1;
}

/**
* Funkcja usuwająca kontakt z grupy.
* Nie zwraca żadnej wartości.
* @param group Wskaźnik na grupę, z której usuwany jest kontakt.
* @param contact Wskaźnik na kontakt, który usuwany jest z grupy.
* @see rewrite_array()
*/
void delete_contact_from_group(struct Group *group, struct Contact *contact){
    if(group->number_of_elements==1){
        free(group->array);
        group->array=NULL;
        group->number_of_elements--;
    }else{
        int i=0;
        for(; i<group->number_of_elements; i++){
            if(group->array[i]==contact)
                break;
        }
        group->array[i]=NULL;
        rewrite_array(group);
    }
}

/**
* Funkcja umożliwiająca edycję grupy.
* Posiada dwie opcje: dodawanie kontaktu do grupy lub jego usuwanie. Wskazywanie kontaktu odbywa się z wykorzystaniem id.
* Nie zwraca żadnej wartości.
* @param group Wskaźnik na edytowaną grupę.
* @param title Nazwa edytowanej grupy.
* @param front Wskaźnik na początek listy kontaktów.
* @see find_node()
* @see add_contact_to_group()
* @see delete_contact_from_group()
*/
void edit_group(struct Group *group, char title[15], struct Contact *front){
    int option=0, id=0;
    struct Contact *contact=NULL;
    do{
        puts("Co chcesz zrobic?\n\t1-dodac kontakt do grupy\n\t2-usunac kontakt z grupy\n\t0-wyjsc");
        scanf("%d", &option);
        switch(option){
        case 1:
            puts("Podaj id osoby ktora chcesz dodac.");
            scanf(" %d", &id);
            contact=find_node(front, id);
            if(contact)
                add_contact_to_group(group, contact);
            else
                printf("Taki kontakt nie istnieje.\n");
            break;
        case 2:
            puts("Podaj id osoby ktora chcesz usunac.");
            scanf(" %d", &id);
            contact=find_node(front, id);
            if(contact)
                delete_contact_from_group(group, contact);
            else
                printf("Taki kontakt nie istnieje.\n");
            break;
        case 0:
            break;
        default:
            puts("Nie ma takiej opcji modyfikacji grupy.");
        }
    }while(option!=0);
}

/**
* Funkcja wyświetlająca wszystkie grupy i ich zawartość.
* Nie zwraca żadnej wartości.
* @param first_group Wskaźnik na początek listy grup.
*/
void print_all_groups(struct Group *first_group){
    if(first_group==NULL)
        printf("Obecnie nie ma zadnych grup.\n");
    for(;first_group; first_group=first_group->next){
        printf("Grupa o nazwie %s posiada elementy: \n", first_group->title);
        for(int i=0; i<first_group->number_of_elements; i++){
            printf("Imie: %s Nazwisko: %s Id: %d\n", first_group->array[i]->name, first_group->array[i]->surname, first_group->array[i]->id);
        }
        printf("\n");
    }
}

/**
* Funkcja odczytująca grupy z plików i dodająca je do listy.
* @param front Wskaźnik na początek listy grup.
* @param first_contact Wskaźnik na początek listy kontaktów.
* @param user_nickname Nazwa użytkownika (w celu utworzenia nazwy pliku do zapisu).
* @return Funkcja zwraca wskaźnik na początek listy grup.
* @see add_contact_to_group()
* @see find_group()
*/
struct Group *loadingGroups(struct Group *front, struct Contact *first_contact, char user_nickname[15]){
    char title[15], name[15], surname[15];
    int n;
    struct Contact *tmp = first_contact;
    struct Group *group=NULL;
    FILE *file = fopen(user_nickname, "r");
    if(file){
        while(!feof(file)){
            fscanf(file, "%15s", title);
            front=add_group(front, title);
            fscanf(file, "%d", &n);
            for(int i=0; i<n; i++){
                fscanf(file, "%15s", name);
                fscanf(file, "%15s", surname);
                tmp=first_contact;
                while(tmp){
                    if(strcmp(tmp->name, name)==0 && strcmp(tmp->surname, surname)==0){
                        break;
                    }
                    tmp=tmp->next;
                }
                group=find_group(front, title);
                if(tmp && group){
                    add_contact_to_group(group, tmp);
                }
            }
        }
        fclose(file);
    }
    return front;
}

/**
* Funkcja zapisująca stan grupy i ich zawartość do pliku.
* @param front Wskaźnik na początek listy grup.
* @param user_nickname Nazwa użytkownika (w celu utworzenia nazwy pliku do zapisu).
* @return Funkcja zwraca wartość logiczną: true - gdy zapis się powiedzie lub false - gdy zapis się nie powiedzie.
*/
bool updatingGroupsFile(struct Group *front, char user_nickname[15]){
    FILE *file = fopen(user_nickname, "w");
    if(file){
        for (; NULL != front ; front = front->next){
            fprintf(file, "%s %d ", front->title, front->number_of_elements);
            for(int i=0; i<front->number_of_elements; i++){
                fprintf(file, "%s %s", front->array[i]->name, front->array[i]->surname);
                if(i<front->number_of_elements-1)
                    fprintf(file, " ");
            }
            if(front->next!=NULL)
                fprintf(file, " \n");
        }
        fclose(file);
        return true;
    }else{
        puts("Nie udalo sie zapisac kontaktow.");
    }
    return false;
}

/**
* Funkcja usuwająca listę grup.
* Wywoływana na koniec funkcji zarządzającej grupami. Nie zwraca żadnej wartości.
* @param front Wskaźnik na wskaźnik na początek listy grup.
*/
void remove_group_list(struct Group **front){
    while(*front){
        struct Group *next = (*front)->next;
        free(*front);
        *front=next;
    }
}

/**
* Funkcja umożliwiająca zarządzanie grupami.
* Umożliwia wybór spomiędzy opcji: wyświetlanie, dodawanie, usuwanie, edycja, zapisywanie grup. Nie zwraca żadnej wartości.
* @param first_contact Wskaźnik na pierwszy elementy listy kontaktów.
* @param user_nickname Tablica znaków przechowująca nazwę użytkownika.
* @see loadingGroups()
* @see print_all_groups()
* @see add_group()
* @see delete_group()
* @see find_group()
* @see print_group()
* @see edit_group()
* @see updatingGroupsFile()
* @see remove_group_list()
*/
void group_interface(struct Contact *first_contact, char user_nickname[15]){
    struct Group *first_group=NULL, *group=NULL;
    strcat(user_nickname, "-groups.txt");
    char title[15];
    first_group=loadingGroups(first_group, first_contact, user_nickname);
    int option=0;
    do{
        puts("Co chcesz zrobic?\n\t1-wyswietlic wszystkie grupy\n\t2-dodac nowa grupe\n\t3-usunac grupe\n\t4-wyszukac grupe\n\t5-edytowac grupe\n\t6-zapisac grupy do pliku\n\t0-wyjsc");
        scanf("%d", &option);
        switch(option){
        case 1:
            print_all_groups(first_group);
            break;
        case 2:
            printf("Podaj nazwe nowej grupy.\n");
            scanf("%15s", title);
            first_group=add_group(first_group,title);
            if(first_group)
                printf("Utworzono grupe. Przejdz do edycji grupy aby dodac do niej kontakty.\n");
            else
                printf("Nie udalo sie utworzyc gruby.\n");
            break;
        case 3:
            printf("Podaj nazwe grupy ktora chcesz usunac.\n");
            scanf("%15s", title);
            if(delete_group(&first_group, title))
                printf("Udalo sie usunac grupe.\n");
            else
                printf("Nie udalo sie usunac grupy.\n");
            break;
        case 4:
            printf("Podaj nazwe grupy ktora chcesz wyswietlic.\n");
            scanf("%15s", title);
            group=find_group(first_group, title);
            if(group)
                print_group(group);
            else
                printf("Nie ma takiej grupy.\n");
            break;
        case 5:
            printf("Podaj nazwe grupy ktora chcesz modyfikowac.\n");
            scanf("%15s", title);
            group=find_group(first_group, title);
            if(group)
                edit_group(group, title, first_contact);
            else
                printf("Nie ma takiej grupy.");
            break;
        case 6:
            updatingGroupsFile(first_group, user_nickname);
            break;
        case 0:
            remove_group_list(&first_group);
            break;
        default:
            puts("Nie ma takiej opcji.");
        }
    }while(option!=0);
}

/**
* Interfejs użytkownika, główna funkcja umożliwiająca zarządzanie kontaktami użytkownika.
* Funkcja ma postać menu, w którym użytkownik ma takie opcje jak wyświetlanie, dodawanie, usuwanie, edycja kontaktów. Ponadto może wyszukiwać kontakty czy je sortować oraz tworzyć grupy.
* Nie zwraca żadnej wartości.
* @param nickname Tablica znaków przechowująca login użytkownika.
* @param file_name Tablica znaków przechowująca nazwę pliku, gdzie zapisywane będą kontakty danego użytkownika.
* @see loadingContacts()
* @see print_list()
* @see insert_node()
* @see print_contact()
* @see delete_node()
* @see editContact()
* @see find_contacts()
* @see sorting_interface()
* @see updatingContactsFile()
* @see group_interface()
* @see remove_list()
*/
void userInterface(char nickname[15], char file_name[27]){
    struct Contact *first_contact =NULL;
    char name[15], surname[15], city[15], street_name[15], street_number[15],postname[15], phone_number[10],email[20], postcode[6];
    first_contact = loadingContacts(first_contact, file_name);
    int option=0, id=0;
    char answer;
    puts("____________________________");
    printf("Witaj %s w aplikacji Kontakty.", nickname);
    do{
        puts("\tCo chcesz zrobic?\n\t1-wyswietl kontakty\n\t2-dodaj nowy kontakt\n\t3-usun kontakt\n\t4-edytuj istniejacy kontakt\n\t5-wyszukaj kontakt\n\t6-sortuj kontakty wedlug\n\t7-zapisz kontakty do pliku\n\t8-zarzadzaj grupami\n\t0-wyloguj\n");
        scanf("%d", &option);
        switch(option){
            case 1:
                //wyswietlanie
                print_list(first_contact);
                break;
            case 2:
                //dodawanie kontaktu
                puts("Podaj imie, a nastepnie po ENTERZE nazwisko.");
                scanf("%14s",name);
                scanf("%14s",surname);
                puts("Podaj kolejno miasto, nazwe ulicy, numer domu.");
                scanf("%14s",city);
                scanf("%14s",street_name);
                scanf("%14s",street_number);
                puts("Podaj kolejno kod pocztowy jako ciag 5 liczb oraz nazwe poczty.");
                scanf("%5s", postcode);
                scanf("%14s", postname);
                puts("Podaj kolejno numer telefonu i adres email.");
                scanf("%9s", phone_number);
                scanf("%19s", email);
                if(!insert_node(&first_contact, name, surname, city, street_name, street_number, postcode, postname, phone_number, email)){
                    puts("Nie udalo sie dodac kontaktu.");
                }
                print_list(first_contact);
                break;
            case 3:
                //usuwanie kontaktu
                puts("Podaj id kontaktu, ktory chcesz usunac.");
                scanf(" %d", &id);
                if(print_contact(first_contact, id)){
                    puts("Czy na pewno chcesz usunac kontakt? (t/n)");
                    scanf(" %c", &answer);
                    if(answer=='t'|| answer=='T'){
                        first_contact=delete_node(first_contact, id);
                        print_list(first_contact);
                    }else
                        puts("Usuniecie kontaktu nie powiodlo sie.");
                }else
                    puts("Kontakt o takim id nie istnieje.");

                break;
            case 4:
                //edycja kontaktu
                puts("Podaj id kontaktu, ktory chcesz edytowac.");
                scanf(" %d", &id);
                editContact(first_contact, id);
                print_list(first_contact);
                break;
            case 5:
                //wyszukiwanie kontaktu
                find_contacts(first_contact);
                break;
            case 6:
                //sortowanie
                sorting_interface(first_contact);
                break;
            case 7:
                //aktualizacja pliku
                if(updatingContactsFile(first_contact, file_name))
                    puts("Udalo sie zaktualizowac plik z kontaktami.");
                else
                    puts("Nie udalo sie zaktualizowac pliku z kontaktami.");
                break;
            case 8:
                //zarzadzenie grupami
                group_interface(first_contact, nickname);
                break;
            case 0:
                //wyjscie
                remove_list(&first_contact);
                puts("Do widzenia!");
                break;
            default:
                puts("Nie ma takiej opcji!");
        }
    }while(option!=0);
}
