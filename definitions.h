char string[MAXIDLEN];

char *messageDec = " \n \tpush eax \n";


char *messageRet = " \n \tpop eax \n";

// ¿Está en la tabla de simbolos?
extern int lookup(char s);

// Pongalo en la tabla de simbolos.
extern void enter(char s);

// Función que genera el código en ensamblador. (No se usa :v)
void generate(char s, char m, char l, char p);

// Función que extrae el nombre o la posición en donde se encuentra en la tabla de símbolos
char *extract(int source);

// Función que revisa si la palabra está en la tabla de símbolos.
void check_id(char s);

// Crea un nuevo nombre del temporal
char *get_temp(void);

// Inicializa los valores
void start(void);

// Finaliza todos los procesos, cierra el archivo y ejecuta ensamblador
void finish(void);

// Asignar el valor a unas variables. (mov ax, bx)
void assign(void);

// Obtiene el operador que este ejecutando en este momento.
float process_op(void);

// Realiza la lógica de la expresión, me revisa constant_folding.
int gen_infix(void);

// Leer variable.
void read_id(int in_var);

// Revisa si la palabra existe llamando a check id
float process_id(void);

// Convierte un literal a número.
float process_literal(int tok);

// Escribe en ensamblador.
void write_expr(int out_expr);

// Realiza el análisis y la escritura en caso de recibir dos literales.
float constant_folding(char *p1);

// Realiza el análisis condicional
int if_condition(int left_operand, int center_operand, int right_operand);

// Realiza el constant folding en la condición, verificando que el primero sea cero.
int const_fold_conditional(void);
