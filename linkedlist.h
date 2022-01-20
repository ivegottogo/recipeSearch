//
// Created by label on 2021-12-20.
//

#ifndef TP3_INF3135_A21_LINKEDLIST_H
#define TP3_INF3135_A21_LINKEDLIST_H

#endif //TP3_INF3135_A21_LINKEDLIST_H

typedef struct Category {
    char category_name[50];
    int nb_recipes;
    struct Category * next;
    struct Recipe * head;
} Category;

typedef struct Category_head {
    int nb_categories;
    struct Category *head;
} Category_head;

typedef struct Recipe {
    char recipe[120];
    struct Recipe * next;
} recipe;

Category_head *catptr;
void add_category(char cat[]);
void initialize_nodes();
void insert_head_category(struct Category* new_cat);
void printcats();
void insert_category_last(struct Category* new_cat);
void add_recipe(char recipe[], char cat[]);