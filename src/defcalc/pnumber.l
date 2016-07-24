/* This is the flex file for scanning real or imaginary numbers
 * in "scientific notation." */
%{

#include <string>
#include <stdexcept>
#include "pnumber.tab.hpp"

#define YY_NO_UNPUT

%}

/* This is so that we generate a default version of yywrap
 * function and therefore don't need to link with -lfl */
%option noyywrap

/* Use the "calcterm number" namespace */
%option prefix="ct_num_"

%%

"-"     { return NEGATIVE; }
"."     { return DOT;      }
"e"     { return E;        }
"i"     { return IMG;      }
[0-9]+  { ct_num_lval.integer = strdup( yytext );
          return INT;
        }
.       { throw std::logic_error( "cannot tokenize: " + std::string( yytext ) ); }

%%