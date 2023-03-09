%{
#include "y.tab.h"
%}

chiffre [0-9]
%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

  int yylex();

%}


%%
[ \t]+	;
{chiffre}+ { sscanf(yytext, "%d", &yylval);
             return INTEGER;}

.    {return yytext[0];}
%%
