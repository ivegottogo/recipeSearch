//
// Created by label on 2021-12-21.
//

#ifndef TP3_INF3135_A21_STATISTIQUES_H
#define TP3_INF3135_A21_STATISTIQUES_H

#endif //TP3_INF3135_A21_STATISTIQUES_H
int count_lines(FILE* f);
void countUnique(FILE* f);
int countWords (FILE *f);
int number_of_categories ();
int number_of_recipes ();
char* popular_category();
char* longest_recipe (FILE *f);
void write_file(FILE *fw, FILE *f);