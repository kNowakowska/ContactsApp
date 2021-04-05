#ifndef USERS_H_INCLUDED
#define USERS_H_INCLUDED

extern void mainInterface();
extern void dataInput(char nickname[15], char password[15]);
extern struct Users *create_users_list(char nickname[15], char password[15]);
extern void insert_user_back(struct Users *front, struct Users *new_node);
extern void add_new_user(struct Users *front, char nickname[15], char password[15]);
extern struct Users *loadingUsers(struct Users *front);
extern bool updatingUsersFile(struct Users *front);
extern struct Users *delete_user_front(struct Users *front);
extern struct Users *find_user_prev_node(struct Users *front, char nickname[15]);
extern void delete_user_after(struct Users *node);
extern struct Users *delete_user_node(struct Users *front, char nickname[15]);
extern void print_all_users(struct Users *front);
extern void remove_users_list(struct Users **front);

extern bool passwordCheck(struct Users *front, char nickname[15], char password[15]);
extern bool changePassword(struct Users *front, char nickname[15], char prev_password[15], char new_password[15]);
extern struct Users *signIn(struct Users *front, char nickname[15], char password[15]);

#endif // USERS_H_INCLUDED
