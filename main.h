#ifndef MAIN_H
#define MAIN_H

include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void _puts(char *argv);
int _putchar(char cat);
char *_strdup( const char *str);
char *_strcpy(char *cat, char *kitty);
char *_strncat(char *cat, char *kitty, int num);
char *_strncpy(char *cat, char *kitty, int num);
char *_strchr(char *p, char x);
int _strlength(char *);
void _commentremover(char *cat);
void filemode(char *);
void interactivemode(char *argv);
int _putchar(char);
#define LENGTH_COMMAnd 1024
#define NEGATIVE -1
#define BUF_Wr_ON 5000
#define BUF_RD_ON 5000

#endif /* MAIN_H */
