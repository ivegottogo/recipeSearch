#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

//
// Created by jonat on 2021-11-23.
//

#ifndef TP3_OPENFILE_H
#define TP3_OPENFILE_H

#endif //TP3_OPENFILE_H

void launch_open_file (int argc, char filePath[]);
void check_argc(int argc);
void open_file(char file[]);
int check_characters(char lineToCheck[]);
int check_brackets(char lineToCheck[]);
void check_file(FILE *file);
void open_file(char file[]);
void open_write_file(char path[]);

FILE *f;
FILE *fw;
char line[120];
