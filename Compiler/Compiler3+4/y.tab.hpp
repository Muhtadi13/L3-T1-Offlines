/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_HPP_INCLUDED
# define YY_YY_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ASSIGNOP = 258,                /* ASSIGNOP  */
    LOGICOP = 259,                 /* LOGICOP  */
    RELOP = 260,                   /* RELOP  */
    ADDOP = 261,                   /* ADDOP  */
    MULOP = 262,                   /* MULOP  */
    NOT = 263,                     /* NOT  */
    INCOP = 264,                   /* INCOP  */
    DECOP = 265,                   /* DECOP  */
    RPAREN = 266,                  /* RPAREN  */
    ELSE = 267,                    /* ELSE  */
    IF = 268,                      /* IF  */
    FOR = 269,                     /* FOR  */
    WHILE = 270,                   /* WHILE  */
    RETURN = 271,                  /* RETURN  */
    PRINTLN = 272,                 /* PRINTLN  */
    LPAREN = 273,                  /* LPAREN  */
    LCURL = 274,                   /* LCURL  */
    RCURL = 275,                   /* RCURL  */
    END_OF_FILE = 276,             /* END_OF_FILE  */
    LTHIRD = 277,                  /* LTHIRD  */
    RTHIRD = 278,                  /* RTHIRD  */
    COMMA = 279,                   /* COMMA  */
    SEMICOLON = 280,               /* SEMICOLON  */
    INT = 281,                     /* INT  */
    FLOAT = 282,                   /* FLOAT  */
    VOID = 283,                    /* VOID  */
    CONST_INT = 284,               /* CONST_INT  */
    CONST_FLOAT = 285,             /* CONST_FLOAT  */
    ID = 286,                      /* ID  */
    LOOP = 287                     /* LOOP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ASSIGNOP 258
#define LOGICOP 259
#define RELOP 260
#define ADDOP 261
#define MULOP 262
#define NOT 263
#define INCOP 264
#define DECOP 265
#define RPAREN 266
#define ELSE 267
#define IF 268
#define FOR 269
#define WHILE 270
#define RETURN 271
#define PRINTLN 272
#define LPAREN 273
#define LCURL 274
#define RCURL 275
#define END_OF_FILE 276
#define LTHIRD 277
#define RTHIRD 278
#define COMMA 279
#define SEMICOLON 280
#define INT 281
#define FLOAT 282
#define VOID 283
#define CONST_INT 284
#define CONST_FLOAT 285
#define ID 286
#define LOOP 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 134 "2005013.y"

	Node *intermediateNode;
	SymbolInfo* symbolInfo;

#line 136 "y.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */
