/* Scanner.h */

extern void yyerror(const char *);  /* prints grammar violation message */

extern int sym_type(const char *);  /* returns type from symbol table */

#define sym_type(identifier) IDENTIFIER /* with no symbol table, fake it */

static void comment(void);
static void include(void);
static int check_type(void);
void count();
void printLexicalErrors(void);
int yywrap(void);
void printLexicalErrors(void);
void search_define_constant();
void format_string(char* string);
void write_to_processed_file(char* string);
