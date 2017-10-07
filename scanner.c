#include <stdio.h>
#include <string.h>
#include "lex.yy.c"

YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

FILE* in_file;
FILE* out_file;

typedef struct {
    char name[MAX_DEFINE_STRUCT];
    char value[MAX_DEFINE_STRUCT];
    struct define_struct *next;

}define_struct;

define_struct *first_define_node = NULL;
define_struct *last_define_node = NULL;
char* constant_sustitute = NULL;
char* latex_data = "";
int reserved_words = 0;
int ids = 0;
int literals = 0;
int operators = 0;
int separators = 0;

typedef struct{
    int kind;
    char* value;
}token;

token get_token(){
    token tok;
    tok.kind = yylex();
    tok.value = yytext;

    return tok;
}

void include_found(token tok){

    int open_file = 1;
    while(tok.kind != FILENAME){
        if(tok.kind == LT){
            open_file = 0;
            tok = get_token();
            return;
        }
        tok = get_token();
    }

    if(open_file == 0 || tok.value == ">"){

        while(tok.kind != ENTER){tok = get_token();}
    }

    if(tok.kind == FILENAME){
        if ( include_stack_ptr >= MAX_INCLUDE_DEPTH ){
            fprintf( stderr, "Demasiados include anidados" );
            exit( 1 );
        }
        printf("FILE: %s\n\n", tok.value);
        yyin = fopen(tok.value, "r" );
        include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
    
        if ( ! yyin ) error("No yyin\n");
    
        yy_switch_to_buffer(yy_create_buffer( yyin, YY_BUF_SIZE));
    }

    return;
    
}

int ignore_multi_comment(token tok){
    tok = get_token();
    while(tok.kind != CMC){
        tok = get_token();

        if(tok.kind == 0 || tok.kind == EOF){
            fprintf(stderr, "Comentario sin cierre\n");
            return 1;
        }
    }
}

void search_define_constant(char* id){
    define_struct *aux;
    aux = first_define_node;

    while(aux != NULL){
        
        if(!strcmp(id, aux->name)){
            constant_sustitute = aux->value;
            break;
        }

        aux = aux->next;
    }
    return;
}

void define_found(token tok){

    define_struct *def;
    def = (define_struct *) malloc(sizeof(define_struct));

    tok = get_token();
    while(tok.kind > 10000){tok = get_token();}
    strcpy(def->name, tok.value);

    tok = get_token();
    while(tok.kind > 10000){tok = get_token();}
    strcpy(def->value, tok.value);
    
    def->next = NULL;

    if (first_define_node==NULL) {
        first_define_node = def;
        last_define_node = def;
        }
     else {
          /* el que hasta ahora era el último tiene que apuntar al nuevo */
          last_define_node->next = def;
          /* hacemos que el nuevo sea ahora el último */
          last_define_node = def;
     }
    
    return;
}

int preprocess(token current_token, int quote){
    if(quote==1) current_token = get_token();

    while(current_token.kind != 0) {
        
        constant_sustitute = "";

        switch(current_token.kind){

            case OSC: //open single comment

            printf("OSC: %d\n", current_token.kind);
            printf("VALUE: %s\n\n", current_token.value);
                while(current_token.kind != ENTER){
                    current_token = get_token();
                }

                break;

            case OMC: //open multi comment
            printf("OMC: %d\n", current_token.kind);
            printf("VALUE: %s\n\n", current_token.value);
                if(ignore_multi_comment(current_token)==1){
                    return 1;
                }
                break;
            
            case INCLUDE:
                include_found(current_token);
                current_token = get_token();
                break;

            case DEFINE:
                define_found(current_token);
                current_token = get_token();
                break;

            case GT:
                current_token = get_token();
                break;
            

            case ID:
                search_define_constant(current_token.value);

                if(constant_sustitute != "") 
                    current_token.value = constant_sustitute;

            default:
                fprintf(yyout, "%s", current_token.value);
                current_token = get_token();
                break;
        }
    }

    if(--include_stack_ptr<0){
        return 0;

    }else{
        yy_delete_buffer(YY_CURRENT_BUFFER);
        yy_switch_to_buffer(include_stack[include_stack_ptr]);
        current_token = get_token();
        preprocess(current_token, 1);
    }
}

void init_pdf(){
    out_file = fopen("Presentation/Project1_Presentation.tex", "w");
    latex_data = "\
\\documentclass[10pt]{beamer}\n\
\n\
\\usetheme[progressbar=frametitle]{metropolis}\n\
\\usepackage{appendixnumberbeamer}\n\
\\usepackage[utf8]{inputenc}\n\
\\usepackage{booktabs}\n\
\\usepackage[scale=2]{ccicons}\n\
\\usepackage{pgfplots}\n\
\\usepackage{tikz}\n\
\\usepackage{graphicx}\n\
\\usepackage[export]{adjustbox}\n\
\\usetikzlibrary{shapes}\n\
\\usepackage{multicol}\n\
\\usepackage{multirow}\n\
\\usepgfplotslibrary{dateplot}\n\
\\usepackage{xspace}\n\
\\usepackage{color}\n\
\\usepackage[T1]{fontenc}\n\
\\usepackage{underscore}\n\
\\usepackage{bchart} \n\
\\usepackage{url} \n\
\\usecolortheme{albatross}\n\
\\setbeamercolor{normal text}{bg=black, fg=white} \n\
\n\
\\setbeamerfont{normal text}{size=3pt} \n\
\\newcommand{\\themename}{\\textbf{\\textsc{metropolis}}\\xspace}\n\
\n\
\\title{\\small Instituto Tecnologico de Costa Rica \\newline \n\
        Compiladores e Interpretes \\newline \n\
        Proyecto1: Analizador Lexico \\newline \n\
        Prof: Francisco Torres Rojas}\n\
\\date{II Semestre 2017}\n\
\\author{\\large Jason Barrantes A. 2015048456 \\newline \n\
                 Randy Morales G. 2015085446 \\newline}\n\
\n\
\\pgfdeclarelayer{background}\n\
\\pgfdeclarelayer{foreground}\n\
\\pgfsetlayers{background,main,foreground}\n\
\\def\\angle{0}\n\
\\def\\radius{3}\n\
\\def\\cyclelist{{\"orange\",\"blue\",\"red\",\"green\",\"purple\"}} \n\
\\newcount\\cyclecount \\cyclecount=-1 \n\
\\newcount\\ind \\ind=-1 \n\
\n\
\\begin{document}\n\
\n\
\\maketitle\n\
\\begin{frame}{CONTENIDOS}\n\
    \\setbeamertemplate{section in toc}[sections numbered]\n\
    \\tableofcontents\n\
\\end{frame}\n\
\n\
\\section{FLEX Y FASE DE SCANNING}\n\
\\begin{frame}{FLEX}\n\
    Flex : Fast Lexical Analyzer Generator. \\newline \\newline \n\
    Es una herramienta para generar scanners, es decir, programas que reconocen \n\
    patrones léxicos. Flex lee la(s) entrada(s) dada(s), con la descripción de un \n\
    escáner a generar. La descripción está formada de pares de expresiones \n\
    regulares y código C, llamadas \\textbf{reglas}. \\newline \\newline \n\
    Flex genera como salida un archivo C, \\textbf{lex.yy.c}, que define una \n\
    rutina \\textbf{yylex()}. Este archivo se compila y enlaza con la biblioteca \n\
    \\textbf{-lfl} para producir un ejecutable. \n\
    Al ejecutar el ejecutable, este analiza su entrada en busca de las expresiones \n\
    regulares. Cada vez que encuentra uno, ejecuta el código C respectivo. \n\
\\end{frame}\n\
\n\
\\begin{frame}{SCANNING}\n\
    Es el proceso mediante el cual el flujo de caracteres se agrupa en cadenas que \n\
    representan las palabras de un lenguaje, llamadas \\textbf{lexemas} que \n\
    corresponden a elementos gramaticales específicos de ese lenguaje, llamados \n\
    \\textbf{tokens.} \\newline \\newline \n\
    Los \\textbf{tokens} son los bloques fundamentales de la estructura gramatical \n\
    de un programa, representando elementos básicos como identificadores, \n\
    literales numéricos, palabras reservadas y operadores específicos del lenguaje.\n\
    Se suele asociar un código a cada estructura gramatical. \n\
    Los \\textbf{lexemas} son las secuencias de caracteres con la que concuerda \n\
    el patrón para un componente léxico. En otras palabras, son los valores \n\
    particulares encontrados en la(s) entrada(s) para cada token. \n\
\\end{frame}\n\
\n\
\\begin{frame}{SCANNING}\n\
    \\setlength{\\arrayrulewidth}{1mm}\n\
    \\setlength{\\tabcolsep}{16pt}\n\
    \\renewcommand{\\arraystretch}{1.5}\n\
    \n\
    \\centering \n\
    \\begin{tabular}{ |p{2cm}|p{2cm}|p{2cm}| }\n\
    \\hline\n\
    \\multicolumn{3}{|c|}{Elementos del Token} \\\\ \n\
    \\hline\n\
    Token & Código & Lexema \\\\ \n\
    \\hline\n\
    LITERAL & 1 & 1990 \\\\ \n\
    IDENTIFIER & 2 & curso \\\\ \n\
    SEMICOLON & 20 & ; \\\\ \n\
    \\hline\n\
    \\end{tabular}\n\
\\end{frame}\n\
\\section{CÓDIGO FUENTE}\n\
";

    fprintf(out_file, "%s\n", latex_data);
    return;
}

void insert_code_pdf(){
    fprintf(out_file, "\\begin{frame}{CÓDIGO FUENTE}\n");
    int number_lines = 0;
    int tokens_count = 0;
    token current_token = get_token();
    while(current_token.kind == ENTER || current_token.kind > 1000000){current_token = get_token();}
    
        while(current_token.kind != 0) {
            printf("KIND: %d\n", current_token.kind);
            switch(current_token.kind){
                case AUTO:
                case BREAK:
                case CASE:
                case CHAR:
                case CONST:
                case CONTINUE:
                case DEFAULT:
                case DO:
                case DOUBLE:
                case ELSE:
                case ENUM:
                case EXTERN:
                case FOR:
                case GOTO:
                case IF:
                case INT:
                case LONG:
                case REGISTER:
                case RETURN:
                case SHORT:
                case SIGNED:
                case SIZEOF:
                case STATIC:
                case STRUCT:
                case SWITCH:
                case TYPEDEF:
                case UNION:
                case UNSIGNED:
                case VOID:
                case VOLATILE:
                case WHILE:
                    fprintf(out_file, "\\colorbox{orange!100} {%s}\n", current_token.value);
                    reserved_words++;
                    tokens_count++;
                    current_token = get_token();
                    break;
    
                case INTEGER:
                case FLOAT:
                    fprintf(out_file, "\\colorbox{red!100} {\\textbf\{%s}}\n", current_token.value);
                    literals++;
                    current_token = get_token();
                    break;
    
                case ID:
                case FILENAME:
                    fprintf(out_file, "\\colorbox{blue!100} {%s}\n", current_token.value);
                    ids++;
                    tokens_count++;
                    current_token = get_token();
                    break;
    
                case COLON:
                case SEMICOLON:
                case COMMA:
                case LPAREN:
                case RPAREN:
                case OB:
                case CB:
                    fprintf(out_file, "\\colorbox{green!100} {\\textbf\{%s}}\n", current_token.value);
                    separators++;
                    current_token = get_token();
                    break;
                
                case QUOTE:
                    fprintf(out_file, "\\colorbox{green!100} {\\textbf\{\\rq}}\n", current_token.value);
                    separators++;
                    current_token = get_token();
                    break;

                case SPECIAL:
                    fprintf(out_file, "\\colorbox{green!100} {$\\backslash$}\n", current_token.value);
                    separators++;
                    current_token = get_token();
                    break;  

                case HASH:
                case OCB:
                case CCB:
                    fprintf(out_file, "\\colorbox{green!100} {\\textbf\{\\%s}}\n", current_token.value);
                    separators++;
                    current_token = get_token();
                    break;
    
                case ASSIGN:
                case PLUS:
                case MINUS:
                case MULT:
                case DIV:
                case LE:
                case GE:
                case EQUAL:
                case NOTEQUAL:
                case GT:
                case LT:
                case OR:
                case RIGHT_ASSIGN:
                case LEFT_ASSIGN:
                case ADD_ASSIGN:
                case SUB_ASSIGN:
                case MUL_ASSIGN:
                case DIV_ASSIGN:
                case MOD_ASSIGN:
                case XOR_ASSIGN:
                case OR_ASSIGN:
                case RIGHT_OP:
                case LEFT_OP:
                case INC_OP:
                case DEC_OP:
                case PTR_OP:
                case ONE_COMPL:
                case IF_OP:
                    fprintf(out_file, "\\colorbox{purple!100} {\\textbf\{%s}}\n", current_token.value);
                    operators++;
                    current_token = get_token();
                    break;
                
                case MOD:
                case AND:
                case BOR:
                case BAND:
                case BXOR:
                case AND_ASSIGN:
                    fprintf(out_file, "\\colorbox{purple!100} {\\textbf\{\\%s}}\n", current_token.value);
                    operators++;
                    current_token = get_token();
                    break;

                
                case NOT:
                    fprintf(out_file, "\\colorbox{green!100} {\\textbf\{!}}\n");
                    separators++;
                    current_token = get_token();
                    break;
    
                case ENTER:
                    fprintf(out_file, "\n");
                    number_lines++;
                    current_token = get_token();
                    break;

                case ERROR:
                    fprintf(out_file, "\\colorbox{yellow!100} {%s}\n", current_token.value);
                    current_token = get_token();
                break;
    
                default:
                    current_token = get_token();
                    while(current_token.kind == ENTER || current_token.kind == EOF || current_token.kind > 1000000){current_token = get_token();}
                    break;
            }

            if(number_lines == 8 || tokens_count == 15){
                fprintf(out_file,"~\\\\ ~\\\\ \\colorbox{orange!100} {\\footnotesize RESERVADA} \n\
    \\colorbox{red!100} {\\footnotesize LITERAL}\n\
    \\colorbox{blue!100} {\\footnotesize IDENTIF}\n\
    \\colorbox{green!100} {\\footnotesize SEPARADOR}\n\
    \\colorbox{purple!100} {\\footnotesize OPERADOR}\n\
\\end{frame} \n");
                fprintf(out_file, "\\begin{frame}{CÓDIGO FUENTE}\n");
                number_lines = 0;
                tokens_count = 0;
            }
        }

        fprintf(out_file,"~\\\\ ~\\\\ \\colorbox{orange!100} {\\footnotesize RESERVADA} \n\
    \\colorbox{red!100} {\\footnotesize LITERAL}\n\
    \\colorbox{blue!100} {\\footnotesize IDENTIF}\n\
    \\colorbox{green!100} {\\footnotesize SEPARADOR}\n\
    \\colorbox{purple!100} {\\footnotesize OPERADOR}\n\
\\end{frame} \n");
    return;
}

void finish_pdf(){

    int total = reserved_words + ids + literals + separators + operators;
    fprintf(out_file, "%s", "\\begin{frame}{Histograma Categorías Léxicas}\n");
    fprintf(out_file, "\\begin{tikzpicture} \n\
    \\begin{axis}[xbar,  \n\
      y axis line style = { opacity = 0 },  \n\
      axis x line       = none,  \n\
      tickwidth         = 0pt,  \n\
      enlarge y limits  = 0.2, \n\
      enlarge x limits  = 0.02, \n\
      symbolic y coords = {Reservadas, IDs, Literales, Separadores, Operadores}, \n\
      nodes near coords, \n\
    ] \n\
    \\addplot coordinates { (%d,Reservadas)         (%d,IDs) \n\
                           (%d,Literales)  (%d,Separadores) \n\
                            (%d,Operadores)}; \n\
    \\end{axis} \n\
    \\end{tikzpicture} \n\
    ~\\\\  ~\\\\ \n\
    TOTAL ENCONTRADO: \\textcolor{yellow!100} {%d} \n\
    \\end{frame} \n", reserved_words, ids, literals, separators, operators, total);
    
    fprintf(out_file, "%s", "\\begin{frame}{Histograma Categorías Léxicas}\n");
    fprintf(out_file, "%s", "\\begin{tikzpicture}[nodes = {font=\\sffamily}]\n");
    fprintf(out_file, "%s", "\\foreach \\percent/\\name in {\n");

    fprintf(out_file, "%.2f/Palabras Reservadas,", (float) reserved_words*100/total);
    fprintf(out_file, "%.2f/IDs,", (float) ids*100/total);
    fprintf(out_file, "%.2f/Literales,", (float) literals*100/total);
    fprintf(out_file, "%.2f/Separadores,", (float) separators*100/total);
    fprintf(out_file, "%.2f/Operadores", (float) operators*100/total);
    
    char* final = "\
    } {\n\
      \\ifx\\percent\\empty\\else               \% If \\percent is empty, do nothing \n\
        \\global\\advance\\cyclecount by 1     \% Advance cyclecount \n\
        \\global\\advance\\ind by 1            \% Advance list index \n\
        \\ifnum4<\\cyclecount                 \% If cyclecount is larger than list \n\
          \\global\\cyclecount=0              \%   reset cyclecount and \n\
          \\global\\ind=0                     \%   reset list index \n\
        \\fi \n\
        \\pgfmathparse{\\cyclelist[\\the\\ind]} % Get color from cycle list \n\
        \\edef\\color{\\pgfmathresult}         %   and store as \\color \n\
        \% Draw angle and set labels \n\
        \\draw[fill={\\color!50},draw={\\color}] (0,0) -- (\\angle:\\radius) \n\
          arc (\\angle:\\angle+\\percent*3.6:\\radius) -- cycle; \n\
        \\node at (\\angle+0.5*\\percent*3.6:0.7*\\radius) {\\percent\\,\\%}; \n\
        \\node[pin=\\angle+0.5*\\percent*3.6:\\name] \n\
          at (\\angle+0.5*\\percent*3.6:\\radius) {}; \n\
        \\pgfmathparse{\\angle+\\percent*3.6}  % Advance angle \n\
        \\xdef\\angle{\\pgfmathresult}         %   and store in \angle \n\
      \\fi \n\
    }; \n\
\\end{tikzpicture} \n\
\\end{frame}\n\
";

    fprintf(out_file, "%s", final);
    fprintf(out_file, "%s", "\\end{document}");
    fclose(out_file);
}

void create_pdf(){
    init_pdf();
    insert_code_pdf();
    finish_pdf();
    system("pdflatex -output-directory=Presentation -input-directory=Presentation Project1_Presentation.tex && evince -s Presentation/Project1_Presentation.pdf &");    
}

int main(int argc, char **argv){
    if(argc < 2) {
		fprintf(stderr, "Menos de 2 parametros\n");
		return 1;
    }

    in_file = fopen(argv[1], "r");
    yyin = in_file;
    out_file = fopen("preprocessed_file.c", "w");
    yyout = out_file;
    token current_token;
    current_token = get_token();
    preprocess(current_token, 0);
    fclose(in_file);
    fclose(out_file);

    in_file = fopen("preprocessed_file.c", "r");
    yyin = in_file;
    create_pdf();
    fclose(in_file);
    yyterminate();
    return 0;
}