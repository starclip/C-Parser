/*DECLARACIONES*/
%{
    #include "scanner.h"
%}

digits [0-9]+
alphanumeric [a-zA-Z0-9\_]+
filename {alphanumeric}\.{alphanumeric}
single_comment "//"[a-zA-Z0-9\_ \t \. \: \# \" \']*
multi_comment "/*"[a-zA-Z0-9\_ \t \. \: \# \" \' \n \- \_]*"*/"

/*REGLAS*/
%%
"auto"			                return AUTO;
"break"			                return BREAK;
"case"			                return CASE;
"char"			                return CHAR;
"const"			                return CONST;
"continue"		                return CONTINUE;
"default"		                return DEFAULT;
"do"			                return DO;
"double"		                return DOUBLE;
"else"			                return ELSE;
"enum"			                return ENUM;
"extern"		                return EXTERN;
"float"			                return FLOAT;
"for"			                return FOR;
"goto"			                return GOTO;
"if"			                return IF;
"int"			                return INT;
"long"			                return LONG;
"register"		                return REGISTER;
"return"		                return RETURN;
"short"			                return SHORT;
"signed"		                return SIGNED;
"sizeof"		                return SIZEOF;
"static"		                return STATIC;
"struct"		                return STRUCT;
"switch"		                return SWITCH;
"typedef"		                return TYPEDEF;
"union"			                return UNION;
"unsigned"		                return UNSIGNED;
"void"			                return VOID;
"volatile"		                return VOLATILE;
"while"			                return WHILE;
"="                             return ASSIGN;
"<="                            return LE;
">="                            return GE;
"=="                            return EQUAL;
"!="                            return NOTEQUAL;
">"	                            return GT;
"<"	                            return LT;
"||" 	                        return OR;
"&&"  	                        return AND;
">>="			                return RIGHT_ASSIGN;
"<<="			                return LEFT_ASSIGN;
"+="			                return ADD_ASSIGN;
"-="			                return SUB_ASSIGN;
"*="			                return MUL_ASSIGN;
"/="			                return DIV_ASSIGN;
"%="			                return MOD_ASSIGN;
"&="			                return AND_ASSIGN;
"^="			                return XOR_ASSIGN;
"|="			                return OR_ASSIGN;
">>"			                return RIGHT_OP;
"<<"			                return LEFT_OP;
"++"			                return INC_OP;
"--"			                return DEC_OP;
"->"			                return PTR_OP;
"|" 	                        return BOR;
"&"	                            return BAND;
"^"	                            return BXOR;
"{"                             return OCB;
"}"                             return CCB;
"["                             return OB;
"]"                             return CB;
","                             return COMMA;
":"                             return COLON;
";"                             return SEMICOLON;
"("                             return LPAREN;
")"                             return RPAREN;
"+"                             return PLUS;
"-"                             return MINUS;
"*"                             return MULT;
"/"                             return DIV;
"~"			                    return ONE_COMPL;
"\%"			                return MOD;
"\\"			                return SPECIAL;
"?"			                    return IF_OP;
"!"                             return NOT;
[\#]                            return HASH;
[\"]                            return QUOTE;
{digits}   				        return INTEGER;
{digits}\.{digits}              return FLOAT;
{alphanumeric}   	            return ID;
{filename}                      return FILENAME;
{single_comment}                return OSC;
{multi_comment}                 return OMC;
"*/"                            return CMC;
[ \t]		                    return " ";
#include                        return INCLUDE;
#define                         return DEFINE;
[ \n]                           { yylineno++; return ENTER;}
.                               {printf("ERROR EN LINEA %d : -- Token %s\n", yylineno,yytext); return ERROR;}
\/\*(.*\n)*.*\*\/               ;
%%

int yywrap(void){
    return 1;
}