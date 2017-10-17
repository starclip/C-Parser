extern FILE *output;
extern FILE *fileErrors;
char line[1000];

void init_beamer(){
    fprintf(output, "%s\n", "\\documentclass[10pt]{beamer}");
    fprintf(output, "%s\n", "\\usepackage{appendixnumberbeamer}");
    fprintf(output, "%s\n", "\\usetheme[progressbar=frametitle]{metropolis}");
    fprintf(output, "%s\n", "\\usepackage[utf8]{inputenc}");
    fprintf(output, "%s\n", "\\usepackage{graphicx}");
    fprintf(output, "%s\n", "\\usepackage{booktabs}");
    fprintf(output, "%s\n", "\\usepackage{multicol}");
    fprintf(output, "%s\n", "\\usepackage{multirow}");
    fprintf(output, "%s\n", "\\usepackage{xspace}");
    fprintf(output, "%s\n", "\\usepackage{color}");
    fprintf(output, "%s\n", "\\usepackage{underscore}");
    fprintf(output, "%s\n", "\\usepackage{url}");
    fprintf(output, "%s\n", "\\usepackage{verbatim}");
    fprintf(output, "%s\n", "\\usepackage{listings}");
    fprintf(output, "%s\n", "\\lstdefinestyle{ErrorStyle}{");
    fprintf(output, "%s\n", "   identifierstyle=\\color{red},");
    fprintf(output, "%s\n", "   numberstyle=\\tiny\\color{yellow},");
    fprintf(output, "%s\n", "   literate={0}{{{\\color{red}0}}}1");
    fprintf(output, "%s\n", "            {1}{{{\\color{red}1}}}1");
    fprintf(output, "%s\n", "            {2}{{{\\color{red}2}}}1");
    fprintf(output, "%s\n", "            {3}{{{\\color{red}3}}}1");
    fprintf(output, "%s\n", "            {4}{{{\\color{red}4}}}1");
    fprintf(output, "%s\n", "            {5}{{{\\color{red}5}}}1");
    fprintf(output, "%s\n", "            {6}{{{\\color{red}6}}}1");
    fprintf(output, "%s\n", "            {7}{{{\\color{red}7}}}1");
    fprintf(output, "%s\n", "            {8}{{{\\color{red}8}}}1");
    fprintf(output, "%s\n", "            {9}{{{\\color{red}9}}}1");
    fprintf(output, "%s\n", "            {.0}{{{\\color{red}.0}}}2");
    fprintf(output, "%s\n", "            {.1}{{{\\color{red}.1}}}2");
    fprintf(output, "%s\n", "            {.2}{{{\\color{red}.2}}}2");
    fprintf(output, "%s\n", "            {.3}{{{\\color{red}.3}}}2");
    fprintf(output, "%s\n", "            {.4}{{{\\color{red}.4}}}2");
    fprintf(output, "%s\n", "            {.5}{{{\\color{red}.5}}}2");
    fprintf(output, "%s\n", "            {.6}{{{\\color{red}.6}}}2");
    fprintf(output, "%s\n", "            {.7}{{{\\color{red}.7}}}2");
    fprintf(output, "%s\n", "            {.8}{{{\\color{red}.8}}}2");
    fprintf(output, "%s\n", "            {.9}{{{\\color{red}.9}}}2");
    fprintf(output, "%s\n", "            {(}{{\\color{red}{(}}}{1}");
    fprintf(output, "%s\n", "            {)}{{\\color{red}{)}}}{1}");
    fprintf(output, "%s\n", "            {-}{{\\color{red}{-}}}{1}");
    fprintf(output, "%s\n", "            {:}{{\\color{red}{:}}}{1}");
    fprintf(output, "%s\n", "   }");
    fprintf(output, "%s\n", "\\lstdefinestyle{CStyle}{");
    fprintf(output, "%s\n", "   backgroundcolor=\\color{black},");
    fprintf(output, "%s\n", "   commentstyle=\\color{green},");
    fprintf(output, "%s\n", "   keywordstyle=\\color{blue},");
    fprintf(output, "%s\n", "   identifierstyle=\\color{green},");
    fprintf(output, "%s\n", "   numberstyle=\\tiny\\color{yellow},");
    fprintf(output, "%s\n", "   stringstyle=\\color{purple},");
    fprintf(output, "%s\n", "   basicstyle=\\footnotesize,");
    fprintf(output, "%s\n", "   breakatwhitespace=false,");
    fprintf(output, "%s\n", "   breaklines=true,");
    fprintf(output, "%s\n", "   captionpos=b,");
    fprintf(output, "%s\n", "   keepspaces=true,");
    fprintf(output, "%s\n", "   numbers=left,");
    fprintf(output, "%s\n", "   numbersep=5pt,");
    fprintf(output, "%s\n", "   showspaces=false,");
    fprintf(output, "%s\n", "   showstringspaces=false,");
    fprintf(output, "%s\n", "   showtabs=false,");
    fprintf(output, "%s\n", "   tabsize=2,");
    fprintf(output, "%s\n", "   language=C,");
    fprintf(output, "%s\n", "   literate={0}{{{\\color{magenta}0}}}1");
    fprintf(output, "%s\n", "            {1}{{{\\color{magenta}1}}}1");
    fprintf(output, "%s\n", "            {2}{{{\\color{magenta}2}}}1");
    fprintf(output, "%s\n", "            {3}{{{\\color{magenta}3}}}1");
    fprintf(output, "%s\n", "            {4}{{{\\color{magenta}4}}}1");
    fprintf(output, "%s\n", "            {5}{{{\\color{magenta}5}}}1");
    fprintf(output, "%s\n", "            {6}{{{\\color{magenta}6}}}1");
    fprintf(output, "%s\n", "            {7}{{{\\color{magenta}7}}}1");
    fprintf(output, "%s\n", "            {8}{{{\\color{magenta}8}}}1");
    fprintf(output, "%s\n", "            {9}{{{\\color{magenta}9}}}1");
    fprintf(output, "%s\n", "            {.0}{{{\\color{magenta}.0}}}2");
    fprintf(output, "%s\n", "            {.1}{{{\\color{magenta}.1}}}2");
    fprintf(output, "%s\n", "            {.2}{{{\\color{magenta}.2}}}2");
    fprintf(output, "%s\n", "            {.3}{{{\\color{magenta}.3}}}2");
    fprintf(output, "%s\n", "            {.4}{{{\\color{magenta}.4}}}2");
    fprintf(output, "%s\n", "            {.5}{{{\\color{magenta}.5}}}2");
    fprintf(output, "%s\n", "            {.6}{{{\\color{magenta}.6}}}2");
    fprintf(output, "%s\n", "            {.7}{{{\\color{magenta}.7}}}2");
    fprintf(output, "%s\n", "            {.8}{{{\\color{magenta}.8}}}2");
    fprintf(output, "%s\n", "            {.9}{{{\\color{magenta}.9}}}2");
    fprintf(output, "%s\n", "            {(}{{\\color{yellow}{(}}}{1}");
    fprintf(output, "%s\n", "            {)}{{\\color{yellow}{)}}}{1}");
    fprintf(output, "%s\n", "   }");
    fprintf(output, "%s\n", "\\usecolortheme{albatross}");
    fprintf(output, "%s\n", "\\setbeamercolor{normal text}{bg=black, fg=white}");
    fprintf(output, "%s\n", "\\setbeamerfont{normal text}{size=3pt}");
    fprintf(output, "%s\n", "\\newcommand{\\themename}{\\textbf{\\textsc{metropolis}}\\xspace}");
}

void cover(){
    fprintf(output, "%s\n", "\\title{\\small Instituto Tecnológico de Costa Rica \\newline \n\
        Compiladores e Intérpretes \\newline \n\
        Proyecto2: Análisis Sintáctico \\newline \n\
        Prof: Francisco Torres Rojas} \n\
\\date{II Semestre 2017} \n\
\\author{\\large Jason Barrantes A. 2015048456 \\newline \n\
                 Randy Morales G. 2015085446 \\newline} \n\
\n\
\\def\\ContinueLineNumber{\\lstset{firstnumber=last}} \n\
\\def\\StartLineAt#1{\\lstset{firstnumber=#1}} \n\
\\let\\numberLineAt\\StartLineAt \n\
\\begin{document} \n\
\\maketitle \n\
\\begin{frame}[fragile]{CONTENIDOS} \n\
    \\setbeamertemplate{section in toc}[sections numbered] \n\
    \\tableofcontents \n\
\\end{frame} \n\
");
}

void bison_and_parsing(){
    fprintf(output, "%s\n", "\\section{BISON Y FASE DE PARSING}\n\
\\begin{frame}[fragile]{BISON} \n\
    BISON es un proyecto creado por GNU, por lo que es la versión libre de YACC. \n\
    Es un programa que genera analizadores sintácticos con propósitos generales. \n\
    Este está disponible para cualquier sistema operativo y se usa acompañado de \\textbf{Flex}. \n\
    Convierte la descripción de un lenguaje, escrita con una gramática libre de contexto (CFG), \n\
    en un programa en C, C++ o Java que realiza el análisis sintáctico. Para la utilización de Bison, \n\
    es necesaria tener la gramática a analizar. \\newline \n\
    \n\
    Al compilarse el archivo Bison se generan dos archivos , un \\textbf{archivo .h} y otro .c. \n\
    El archivo .h debe incluirse en el archivo de Lex/Flex. \n\
\\end{frame} \n\
\n\
\\begin{frame}[fragile]{ELEMENTOS} \n\
    El archivo de codificación de Bison tiene cuatro secciones: \n\
    \n\
    \\%{ \n\
    \n\
    Declaraciones C \n\
    \n\
    \\%} \n\
    \n\
    Declaraciones Yacc/Bison \n\
    \n\
    \\%Declaracion de Token \n\
    \n\
    \\%\\% \n\
    \n\
    Reglas de la gramática \n\
    \n\
    \\%\\% \n\
    \n\
    Código C \n\
\\end{frame} \n\
\\begin{frame}[fragile]{ELEMENTOS} \n\
    \\%\\{, \\%\\} sirven para delimitar el encabezado, donde usualmente se colocan bibliotecas \n\
    \n\
    \\%\\% sirven para indicar cuales son las reglas \n\
    \n\
    Y por último la programación en C o llamadas a funciones en caso de ser necesario. \n\
    \n\
    \\%Token Se utiliza para definir los símbolos no terminales (tokens) de la gramática. \n\
    \n\
    \\%token NOMBRE_TOKEN \n\
    \n\
    Por convenio, los nombres de los tokens se escriben en mayúsculas y se pueden agrupar varios  \n\
    tokens en una línea si tienen en mismo tipo. \n\
\\end{frame} \n\
\n\
\\begin{frame}[fragile]{CREADORES} \n\
    \\begin{columns}[T] \n\
        \\begin{column}{.5\\textwidth} \n\
            \\begin{block}{ } \n\
                Bison fue escrito en un principio por Robert Corbett; Richard Stallman lo hizo \n\
                compatible con Yacc y Wilfred Hansen de la Carnegie Mellon University añadió soporte \n\
                para literales multicaracter y otras características. \n\
            \\end{block} \n\
        \\end{column} \n\
        \\begin{column}{.5\\textwidth} \n\
            \\begin{block}{Richard Stallman} \n\
                \\includegraphics[width=6cm,height=4cm]{stallman} \n\
            \\end{block} \n\
        \\end{column} \n\
    \\end{columns} \n\
\\end{frame} \n\
\n\
\\begin{frame}[fragile]{Parsing} \n\
    El parsing es la segunda fase de un compilador. La fase de parsing es el proceso donde se toma \n\
    el conjunto de tokens producidos por la fase de análisis léxico y se genera un \n\
    \\textbf{árbol de sintaxis}. Luego este se revisa de acuerdo a la gramática formal del \n\
    lenguaje definido y se verifica que las expresiones construidas por el arreglo de tokens \n\
    sean sintacticamente correctos. \\newline \n\
\\end{frame} \n\
\n\
\\section{CÓDIGO FUENTE} \n\
    \\begin{lstlisting}[style=CStyle] \n\
");
}

void code(){
    int c;
    while ((c = getc(myfile)) != EOF){
        fprintf(output, "%c",c);
    } 
}

void close_beamer(){
    fprintf(output, "%s\n", "    \\end{lstlisting} \n\
\\section{ERRORES} \n\
\\lstinputlisting[language=C, style=ErrorStyle]{errorsBeamer.txt} \n\
\\end{document}");
    fclose(output);
    system("pdflatex presentation.tex && evince -s presentation.pdf &");        
}
