#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int get_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int exec_file(info_t *, char *);
char *chars_dup(char *, int, int);
char *get_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _insfd(char c, int fdes);
int _putsfd(char *str, int fdes);

/* toem_string.c */
int return_len_str(char *);
int lex_comp_str(char *, char *);
char *begin_with(const char *, const char *);
char *conc_two_str(char *, char *);

/* toem_string1.c */
char *cpy_string(char *, char *);
char *dup_string(const char *);
void in_string(char *);
int _putchar(char);

/* toem_exits.c */
char *_cpstring(char *, char *, int);
char *_strncat(char *, char *, int);
char *chastr(char *, char);

/* toem_tokenizer.c */
char **splt_words(char *, char *);
char **splt_2words(char *, char);

/* toem_realloc.c */
char *fill_mem(char *, char, unsigned int);
void sstring(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int free_p_null_ad(void **);

/* toem_atoi.c */
int inter_mode(info_t *);
int delimeter(char, char *);
int alpha_char(int);
int conv_str_to_i(char *);

/* toem_errors1.c */
int strtoi(char *);
void print_error(info_t *, char *);
int decimal_p(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int exit_shell(info_t *);
int chang_d(info_t *);
int mhelp(info_t *);

/* toem_builtin1.c */
int desp_history(info_t *);
int m_alias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void init_info(info_t *, char **);
void set_free_info(info_t *, int);

/* toem_environ.c */
char *fetch_env(info_t *, const char *);
int envi(info_t *);
int env_set(info_t *);
int env_unset(info_t *);
int pop_e_list(info_t *);

/* toem_getenv.c */
char **ret_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *fetch_history_file(info_t *info);
int changes_history(info_t *info);
int check_history(info_t *info);
int add_history_list(info_t *info, char *buf, int linecount);
int changeno_history(info_t *info);

/* toem_lists.c */
list_t *plus_node(list_t **, const char *, int);
list_t *plus_node_end(list_t **, const char *, int);
size_t str_print_only(const list_t *);
int at_index__del_node(list_t **, unsigned int);
void set_free_list(list_t **);

/* toem_lists1.c */
size_t len_list(const list_t *);
char **return_str_list(list_t *);
size_t list_print(const list_t *);
list_t *return_node_start(list_t *, char *, char);
ssize_t fetch_node_index(list_t *, list_t *);

/* toem_vars.c */
int chain_del(info_t *, char *, size_t *);
void cont_chain(info_t *, char *, size_t *, size_t, size_t);
int rep_tk_alias(info_t *);
int rep_tk_vars(info_t *);
int replace_string(char **, char *);

#endif
