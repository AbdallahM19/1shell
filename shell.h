#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
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
#include <signal.h>
#include <sys/stat.h>
extern char **environ;

#define LENGTH_COMMAnd 1024
#define NEGATIVE -1
#define BUF_Wr_ON 5000
#define BUF_RD_ON 5000
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: number of field
 * @str: string
 * @next: points to the next mode
*/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @arge: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit() s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
*/
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	int argc;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;
/*main.c*/
void execute_command(char *command, int interactive);
void non_interactive();
void interactive_mode();
/*string fuction4*/
int _strspn(const char *str, const char *accept);
char *_strpbrk(char *str, const char *accept);
char *strtok_custom(char *str, const char *delimiters);
/*string function 3*/
char *_strncat(char *cat, char *kitty, int num);
char *_strncpy(char *cat, char *kitty, int num);
char *_strchr(char *p, char x);
/*string function 2*/
int _putchar(char cat);
void _puts(char *argv);
char *_strdup( const char *str);
char *_strcpy(char *cat, char *kitty);
/*string function 1*/
int _strlength(char *);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *cat, const char *kitty);
char *_strcat(char *dest, char *src);
/*path.c*/
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);
/*more function 2*/
void error_message(const char *program_name, int error_code, const char *file_name);
/*void error_massege(char *cat, char *argv);*/
int _erratoi(char *s);
void print_error (info_t *info, char *estr);
int print_d(int input, int fd);
char *convert_number (long int num, int base, int flags);
void _commentremover(char *cat);
/*more function.c*/
int is_delim (char c, char *delim);
int isalpha (int c);
int _atoi (char *s);
/*memory functtion 2*/
int bfree (void **ptr);
/*memory fuction*/
char *_memset (char *s, char b, unsigned int n);
void ffree (char **pp);
void *_realloc (void *ptr, unsigned int old_size, unsigned int new_size);
/*liststr2.c*/
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with (list_t *node, char *prefix, char c);
ssize_t get_node_index (list_t *head, list_t *node);
/*liststr.c*/
list_t *add_node (list_t **head, const char *str, int num);
list_t *add_node_end (list_t **head, const char *str, int num);
size_t print_list_str (const list_t *h);
int delete_node_at_index (list_t **head, unsigned int index);
void free_list (list_t **head_ptr);
/*info.c*/
void clear_info (info_t *info);
void set_info (info_t *info, char **av);
void free_info (info_t *info, int all);
/*hsh.c*/
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);
/*getlie.c*/
void sigintHandler(__attribute__((unused)) int sig_num);
int _getline(info_t *info, char **ptr, size_t *length);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
ssize_t get_input(info_t *info);
ssize_t input_buf(info_t *info, char **buf, size_t *len);

char *_strncat(char *cat, char *kitty, int num);
char *_strncpy(char *cat, char *kitty, int num);


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, NULL, \
        0, 0, 0}
/**
 * struct builtin - contains a builtin string and related function
 * @type: builtin commend flag
 * @func: function
*/
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/*builtin_emulators.c*/
int _myexit (info_t *);
int _mycd (info_t *);
int _myhelp (info_t *);

/* builtin_emulators2.c*/
int _myhistory (info_t *);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias (info_t *info);

/* env.c module */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* env2.c module */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* file_io_functions.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* err_string_functions.c*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/**/
void print_env(char **env);
char *_strncpy(char *dest, char *src, int n);
/**/


/* chain.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif /* SHELL_H */
