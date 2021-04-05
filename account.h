#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED

#include <stdbool.h>

extern void userInterface(char nickname[15], char file_name[27]);
extern struct Contact *create_list(char name[15], char surname[15], char city[15], char street_name[15], char street_number[15], char postcode[6],char postname[15], char phone_number[10], char email[20]);
extern void insert_back(struct Contact *back, struct Contact *new_node);
extern bool insert_node(struct Contact **front, char name[15], char surname[15], char city[15], char street_name[15], char street_number[15], char postcode[6],char postname[15], char phone_number[10], char email[20]);
extern struct Contact *delete_front(struct Contact *front);
extern struct Contact *find_prev_node(struct Contact *front,unsigned int id);
extern void delete_after(struct Contact *node);
extern struct Contact *delete_node(struct Contact *front,unsigned int id);
extern struct Contact *find_node(struct Contact *front, unsigned int id);
extern void print_list(struct Contact *front);
extern bool print_contact(struct Contact *front, unsigned int id);
extern void remove_list(struct Contact **front);
extern struct Contact *loadingContacts(struct Contact *front, char file_name[27]);
extern bool updatingContactsFile(struct Contact *front, char file_name[27]);
extern void editContact(struct Contact *front, unsigned int id);
extern void find_contacts(struct Contact *front);

extern void sort_name_asc(struct Contact *front);
extern void sort_surname_asc(struct Contact *front);
extern void sort_city_asc(struct Contact *front);
extern void sort_streetname_asc(struct Contact *front);
extern void sort_streetnumber_asc(struct Contact *front);
extern void sort_postcode_asc(struct Contact *front);
extern void sort_postname_asc(struct Contact *front);
extern void sort_phonenumber_asc(struct Contact *front);
extern void sort_email_asc(struct Contact *front);

extern void sort_name_desc(struct Contact *front);
extern void sort_surname_desc(struct Contact *front);
extern void sort_city_desc(struct Contact *front);
extern void sort_streetname_desc(struct Contact *front);
extern void sort_streetnumber_desc(struct Contact *front);
extern void sort_postcode_desc(struct Contact *front);
extern void sort_postname_desc(struct Contact *front);
extern void sort_phonenumber_desc(struct Contact *front);
extern void sort_email_desc(struct Contact *front);
extern void sorting_interface(struct Contact *front);

extern struct Group *create_group_list(char title[15]);
extern struct Group *add_group(struct Group *first_group, char title[15]);
extern bool delete_group(struct Group **first_group, char title[15]);
extern struct Group *find_group(struct Group *first_group, char title[15]);
extern void print_group(struct Group *group);
extern void edit_group(struct Group *group, char title[15], struct Contact *front);
extern void print_all_groups(struct Group *first_group);
extern void add_contact_to_group(struct Group *group, struct Contact *contact);
extern void rewrite_array(struct Group *group);
extern void delete_contact_from_group(struct Group *group, struct Contact *contact);
extern struct Group *loadingGroups(struct Group *front, struct Contact *first_contact, char user_nickname[15]);
extern bool updatingGroupsFile(struct Group *front, char user_nickname[15]);
extern void remove_group_list(struct Group **front);
extern void group_interface(struct Contact *first_contact, char user_nickname[15]);
#endif // ACCOUNT_H_INCLUDED
