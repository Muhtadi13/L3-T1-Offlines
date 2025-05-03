/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "2005013.y"

#pragma once
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include "2005013_Node.h"
#include "2005013_SymbolTable.h"

//#define YYSTYPE SymbolInfo*

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int yylineno;

SymbolTable *sTable;
Node *root;
ofstream outtree;
ofstream outlog;
ofstream outerror;
ofstream outasm;
vector<pair<string,string>> paramsOfFunction;
vector<string> argsOfFunction;
vector<pair<pair<string,string>,int>> varNameTypeSz;
extern int linecount;
extern int errorcount;
bool synerror=false;
bool globalScope=true;
int labelcount=0;
int baseOffset=0;
int baseOffsetPrev=0;
string activeFunction="";

void yyerror(char *s){
	//write your code
}
void replaceCharInString(string &source, string const &tofind, string const &target){
    for (string::size_type i = 0; (i = source.find(tofind, i)) != string::npos;)
    {
        source.replace(i, tofind.length(), target);
        i += target.length();
    }
}
string UpperString(string &str){
    string ret = str;
    for (int i = 0; i < ret.size(); i++)
    {
        ret[i] = toupper(ret[i]);
    }
    return ret;
}
void optimizeCode(ifstream &ipf,ofstream &opf){

	string instruction;
	vector<string> tmpholder;
	vector<string> finalcode;
	while(getline(ipf,instruction)){
		tmpholder.push_back(instruction);
	}


	for(int i=0;i<tmpholder.size();i++){
		string commandstmp=tmpholder[i];
		replaceCharInString(commandstmp,","," ");
		replaceCharInString(commandstmp,"\t"," ");
		string word;
		stringstream iss(commandstmp);
		vector<string> commands;
		while (iss >> word){  
			commands.push_back(word);
		}
		
		if(commands.size()==3){

			if((commands[0]=="ADD" || commands[0]=="SUB") && commands[2]=="0"){
				continue;
			}else if(commands[0]=="IMUL" && commands[2]=="1"){
				continue;
			}else if(commands[0]=="MOV"){
				if(finalcode.size()>0){
					string tmpcom= finalcode.back();
					
					replaceCharInString(tmpcom,","," ");
					replaceCharInString(tmpcom,"\t"," ");
					string word2;
					stringstream iss2(tmpcom);
					vector<string> commands2;
					while (iss2 >> word2){  
						commands2.push_back(word2);
					}
					if(commands2.size()==3 && commands2[0]=="MOV" && commands2[2]==commands[1] && commands2[1]==commands[2]){
						continue;
					}
				}
			}
		}else if(commands.size()==2){
			if(commands[0]=="POP"){
				if(finalcode.size()>0){
					string tmpcom= finalcode.back();
					
					replaceCharInString(tmpcom,","," ");
					replaceCharInString(tmpcom,"\t"," ");
					string word2;
					stringstream iss2(tmpcom);
					vector<string> commands2;
					while (iss2 >> word2){  
						commands2.push_back(word2);
					}
					if(commands2.size()==2 && commands2[0]=="PUSH" && commands2[1]==commands[1]){
						finalcode.pop_back();
						continue;
					}
				}

			}
		}
		finalcode.push_back(tmpholder[i]);
		
	
	}

	for(int i=0;i<finalcode.size();i++){
		opf<<finalcode[i]<<"\n";
	}
}


#line 202 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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

#line 324 "y.tab.c"

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


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ASSIGNOP = 3,                   /* ASSIGNOP  */
  YYSYMBOL_LOGICOP = 4,                    /* LOGICOP  */
  YYSYMBOL_RELOP = 5,                      /* RELOP  */
  YYSYMBOL_ADDOP = 6,                      /* ADDOP  */
  YYSYMBOL_MULOP = 7,                      /* MULOP  */
  YYSYMBOL_NOT = 8,                        /* NOT  */
  YYSYMBOL_INCOP = 9,                      /* INCOP  */
  YYSYMBOL_DECOP = 10,                     /* DECOP  */
  YYSYMBOL_RPAREN = 11,                    /* RPAREN  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_PRINTLN = 17,                   /* PRINTLN  */
  YYSYMBOL_LPAREN = 18,                    /* LPAREN  */
  YYSYMBOL_LCURL = 19,                     /* LCURL  */
  YYSYMBOL_RCURL = 20,                     /* RCURL  */
  YYSYMBOL_END_OF_FILE = 21,               /* END_OF_FILE  */
  YYSYMBOL_LTHIRD = 22,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 23,                    /* RTHIRD  */
  YYSYMBOL_COMMA = 24,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 25,                 /* SEMICOLON  */
  YYSYMBOL_INT = 26,                       /* INT  */
  YYSYMBOL_FLOAT = 27,                     /* FLOAT  */
  YYSYMBOL_VOID = 28,                      /* VOID  */
  YYSYMBOL_CONST_INT = 29,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 30,               /* CONST_FLOAT  */
  YYSYMBOL_ID = 31,                        /* ID  */
  YYSYMBOL_LOOP = 32,                      /* LOOP  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_start = 34,                     /* start  */
  YYSYMBOL_program = 35,                   /* program  */
  YYSYMBOL_unit = 36,                      /* unit  */
  YYSYMBOL_func_declaration = 37,          /* func_declaration  */
  YYSYMBOL_func_definition = 38,           /* func_definition  */
  YYSYMBOL_parameter_list = 39,            /* parameter_list  */
  YYSYMBOL_compound_statement = 40,        /* compound_statement  */
  YYSYMBOL_41_1 = 41,                      /* $@1  */
  YYSYMBOL_var_declaration = 42,           /* var_declaration  */
  YYSYMBOL_type_specifier = 43,            /* type_specifier  */
  YYSYMBOL_declaration_list = 44,          /* declaration_list  */
  YYSYMBOL_expression_list = 45,           /* expression_list  */
  YYSYMBOL_statements = 46,                /* statements  */
  YYSYMBOL_statement = 47,                 /* statement  */
  YYSYMBOL_expression_statement = 48,      /* expression_statement  */
  YYSYMBOL_variable = 49,                  /* variable  */
  YYSYMBOL_expression = 50,                /* expression  */
  YYSYMBOL_logic_expression = 51,          /* logic_expression  */
  YYSYMBOL_rel_expression = 52,            /* rel_expression  */
  YYSYMBOL_simple_expression = 53,         /* simple_expression  */
  YYSYMBOL_term = 54,                      /* term  */
  YYSYMBOL_unary_expression = 55,          /* unary_expression  */
  YYSYMBOL_factor = 56,                    /* factor  */
  YYSYMBOL_argument_list = 57,             /* argument_list  */
  YYSYMBOL_arguments = 58                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   174

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   165,   165,   182,   196,   210,   222,   236,   250,   322,
     391,   455,   517,   549,   573,   598,   614,   634,   634,   688,
     721,   775,   795,   813,   833,   867,   927,   951,  1018,  1071,
    1088,  1101,  1125,  1138,  1154,  1166,  1178,  1190,  1231,  1269,
    1315,  1363,  1401,  1454,  1485,  1506,  1529,  1560,  1629,  1642,
    1675,  1691,  1704,  1731,  1743,  1770,  1782,  1810,  1822,  1858,
    1878,  1898,  1917,  1929,  1999,  2028,  2053,  2072,  2092,  2114,
    2127,  2140,  2165
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ASSIGNOP", "LOGICOP",
  "RELOP", "ADDOP", "MULOP", "NOT", "INCOP", "DECOP", "RPAREN", "ELSE",
  "IF", "FOR", "WHILE", "RETURN", "PRINTLN", "LPAREN", "LCURL", "RCURL",
  "END_OF_FILE", "LTHIRD", "RTHIRD", "COMMA", "SEMICOLON", "INT", "FLOAT",
  "VOID", "CONST_INT", "CONST_FLOAT", "ID", "LOOP", "$accept", "start",
  "program", "unit", "func_declaration", "func_definition",
  "parameter_list", "compound_statement", "$@1", "var_declaration",
  "type_specifier", "declaration_list", "expression_list", "statements",
  "statement", "expression_statement", "variable", "expression",
  "logic_expression", "rel_expression", "simple_expression", "term",
  "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-77)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      58,   -77,   -77,   -77,    18,    58,   -77,   -77,   -77,   -77,
       3,   -77,   -77,   -77,    42,    66,    45,    -2,   -11,   -77,
     -77,    10,     2,    12,    62,    25,    33,    47,   -77,   -77,
      50,    58,   -77,    57,   -77,    49,   -77,   113,   -77,   -77,
      73,   117,    65,   -77,   143,   143,    97,    98,    99,   117,
     102,   117,   -77,   -77,   -77,    52,   113,   -77,   -77,    11,
      81,   -77,   -77,    13,    80,   -77,   118,    87,   126,   -77,
     -77,   -77,     8,   -77,   -77,    93,   -77,   -77,   117,    32,
     117,   109,   105,   139,   143,   117,   122,   130,   -77,   -77,
     143,   -77,   -77,   -77,   143,   143,   143,   143,   -77,   117,
     142,    32,   144,   -77,   145,   -77,   -77,   146,   100,   131,
     140,   -77,   -77,   153,   126,   -77,   -77,   113,   117,   113,
     135,   -77,   143,   -77,   117,   150,   152,   -77,   -77,   -77,
     154,   113,   113,   -77,   -77,   -77
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    21,    22,    23,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    29,    26,     0,     0,     0,     0,    20,
      16,     0,     0,    15,     0,     0,    24,    17,     9,    11,
       0,     0,    14,     0,    28,     0,    19,     0,     8,    10,
      13,     0,     0,    50,     0,     0,     0,     0,     0,     0,
       0,     0,    44,    65,    66,    46,     0,    36,    34,     0,
       0,    32,    35,    62,     0,    48,    51,    53,    55,    57,
      61,    12,     0,    30,    25,    62,    59,    60,     0,     0,
       0,     0,     0,     0,    70,     0,     0,    26,    18,    33,
       0,    67,    68,    45,     0,     0,     0,     0,    27,     0,
       0,     0,     0,    43,     0,    64,    72,     0,    69,     0,
       0,    49,    52,    54,    56,    58,    31,     0,     0,     0,
       0,    63,     0,    47,     0,    38,     0,    41,    42,    71,
       0,     0,     0,    40,    39,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -77,   -77,   -77,   159,   -77,   -77,   -77,    -6,   -77,    31,
      14,   -77,   -77,   -77,   -51,   -76,   -43,   -41,   -73,    72,
      74,    71,   -38,   -77,   -77,   -77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,    22,    57,    37,    58,
      59,    15,    72,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,   107,   108
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      73,    75,    75,   101,    13,    86,    76,    77,    81,    89,
      83,   106,    13,    30,    10,    29,    90,   111,    11,    10,
      26,    24,    91,    92,    39,   118,    31,    25,    98,    27,
      23,     9,    99,    43,    14,    28,     9,   100,    44,   102,
      45,    75,    87,    32,   109,    40,    20,    75,    34,   129,
      51,    75,    75,    75,    75,    35,    21,    52,   116,   115,
      16,    53,    54,    55,    17,    33,   125,    36,   127,    27,
      84,     1,     2,     3,    85,    38,    41,   126,    42,    75,
     134,   135,    43,   130,     1,     2,     3,    44,    74,    45,
      18,    19,    95,    96,    46,    47,    48,    49,    50,    51,
      27,    88,    91,    92,    71,    93,    52,     1,     2,     3,
      53,    54,    55,    56,    43,    78,    79,    80,    43,    44,
      82,    45,    94,    44,   122,    45,    46,    47,    48,    49,
      50,    51,    27,    97,   103,    51,   104,   110,    52,     1,
       2,     3,    53,    54,    55,    56,    53,    54,    55,    44,
     105,    45,    17,   117,   123,   119,   120,   121,   124,    96,
     128,    51,   131,   132,    12,   133,   112,   114,     0,   113,
       0,     0,    53,    54,    55
};

static const yytype_int16 yycheck[] =
{
      41,    44,    45,    79,     1,    56,    44,    45,    49,    60,
      51,    84,     1,    11,     0,    21,     3,    90,     0,     5,
      31,    23,     9,    10,    30,   101,    24,    29,    20,    19,
      16,     0,    24,     1,    31,    25,     5,    78,     6,    80,
       8,    84,    31,    31,    85,    31,     1,    90,    23,   122,
      18,    94,    95,    96,    97,    22,    11,    25,    99,    97,
      18,    29,    30,    31,    22,     3,   117,    20,   119,    19,
      18,    26,    27,    28,    22,    25,    19,   118,    29,   122,
     131,   132,     1,   124,    26,    27,    28,     6,    23,     8,
      24,    25,     5,     6,    13,    14,    15,    16,    17,    18,
      19,    20,     9,    10,    31,    25,    25,    26,    27,    28,
      29,    30,    31,    32,     1,    18,    18,    18,     1,     6,
      18,     8,     4,     6,    24,     8,    13,    14,    15,    16,
      17,    18,    19,     7,    25,    18,    31,    15,    25,    26,
      27,    28,    29,    30,    31,    32,    29,    30,    31,     6,
      11,     8,    22,    11,    23,    11,    11,    11,    18,     6,
      25,    18,    12,    11,     5,    11,    94,    96,    -1,    95,
      -1,    -1,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,    27,    28,    34,    35,    36,    37,    38,    42,
      43,     0,    36,     1,    31,    44,    18,    22,    24,    25,
       1,    11,    39,    43,    23,    29,    31,    19,    25,    40,
      11,    24,    31,     3,    23,    22,    20,    41,    25,    40,
      43,    19,    29,     1,     6,     8,    13,    14,    15,    16,
      17,    18,    25,    29,    30,    31,    32,    40,    42,    43,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    31,    45,    50,    23,    49,    55,    55,    18,    18,
      18,    50,    18,    50,    18,    22,    47,    31,    20,    47,
       3,     9,    10,    25,     4,     5,     6,     7,    20,    24,
      50,    48,    50,    25,    31,    11,    51,    57,    58,    50,
      15,    51,    52,    53,    54,    55,    50,    11,    48,    11,
      11,    11,    24,    23,    18,    47,    50,    47,    25,    51,
      50,    12,    11,    11,    47,    47
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    37,    37,
      38,    38,    39,    39,    39,    39,    39,    41,    40,    40,
      42,    43,    43,    43,    44,    44,    44,    44,    44,    44,
      45,    45,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    48,    48,    49,    49,    50,    50,
      50,    51,    51,    52,    52,    53,    53,    54,    54,    55,
      55,    55,    56,    56,    56,    56,    56,    56,    56,    57,
      57,    58,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       6,     5,     4,     3,     2,     1,     1,     0,     4,     2,
       3,     1,     1,     1,     3,     6,     1,     7,     4,     1,
       1,     3,     1,     2,     1,     1,     1,     7,     5,     7,
       6,     5,     5,     3,     1,     2,     1,     4,     1,     3,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     2,
       2,     1,     1,     4,     3,     1,     1,     2,     2,     1,
       0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program  */
#line 166 "2005013.y"
        {
		Node* nd=new Node();
		nd->setName("start");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("start");
		nd->setGrammar("start : program");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		root=(yyval.intermediateNode);
		(yyval.intermediateNode)->print(0,outtree);

	}
#line 1600 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 183 "2005013.y"
        {
		Node* nd=new Node();
		nd->setName("program");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("program");
		nd->setGrammar("program : program unit");
		nd->addChild((yyvsp[-1].intermediateNode));
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		
	}
#line 1618 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 197 "2005013.y"
        {
		Node* nd=new Node();
		nd->setName("program");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("program");
		nd->setGrammar("program : unit ");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
	}
#line 1634 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 211 "2005013.y"
        {
		Node* nd=new Node();
		nd->setName("unit");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("unit");
		nd->setGrammar("unit : var_declaration ");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
	}
#line 1650 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 223 "2005013.y"
        {
		Node* nd=new Node();
		nd->setName("unit");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("unit");
		nd->setGrammar("unit : func_declaration ");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";


	}
#line 1668 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 237 "2005013.y"
        {
		Node* nd=new Node();
		nd->setName("unit");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("unit");
		nd->setGrammar("unit : func_definition ");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
	}
#line 1684 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 251 "2005013.y"
        {

				Node* nd_id=new Node();
		nd_id->setStart((yylsp[-4]).first_line);
		nd_id->setEnd((yylsp[-4]).last_line);
		//nd_id->setName($2->getName());
		nd_id->setTypeSpecifier((yyvsp[-4].symbolInfo)->getType());
		nd_id->setSymbolInfo((yyvsp[-4].symbolInfo));
		
		//nd_id->setName($2->getName());
		nd_id->setGrammar((yyvsp[-4].symbolInfo)->getType()+" : "+(yyvsp[-4].symbolInfo)->getName());

				Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-3]).first_line);
		nd_lp->setEnd((yylsp[-3]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-3].symbolInfo));
				Node* nd_rp=new Node();
		nd_rp->setStart((yylsp[-1]).first_line);
		nd_rp->setEnd((yylsp[-1]).last_line);
		nd_rp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_rp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_rp->setSymbolInfo((yyvsp[-1].symbolInfo));

				Node* nd_sc=new Node();
		nd_sc->setStart((yylsp[0]).first_line);
		nd_sc->setEnd((yylsp[0]).last_line);
		nd_sc->setTypeSpecifier((yyvsp[-4].symbolInfo)->getType());
		nd_sc->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_sc->setSymbolInfo((yyvsp[0].symbolInfo));
				Node* nd=new Node();
		nd->setName("func_declaration");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("func_declaration");
		nd->setGrammar("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON ");
		nd->addChild((yyvsp[-5].intermediateNode));
		nd->addChild(nd_id);
		nd->addChild(nd_lp);
		nd->addChild((yyvsp[-2].intermediateNode));
		nd->addChild(nd_rp);
		nd->addChild(nd_sc);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		SymbolInfo* func=new SymbolInfo();
		func->setInherentType("func_decl");
		func->setRettypeOrArrayType((yyvsp[-5].intermediateNode)->getTypeSpecifier());
		func->setType((yyvsp[-4].symbolInfo)->getType());
		func->setName((yyvsp[-4].symbolInfo)->getName());
		for(int i=0;i<paramsOfFunction.size();i++){
			func->addParam(paramsOfFunction[i]);
		}
		paramsOfFunction.clear();
		SymbolInfo* fnd=sTable->LookUp((yyvsp[-4].symbolInfo)->getName());
		if(fnd==NULL){
			sTable->Insert(func);
			nd_id->setSymbolInfo(func);
		}
		else if(fnd->getInherentType()=="variable"){
			errorcount++;
			outerror << "Line# " << (yylsp[-4]).first_line << ": " << "'" << (yyvsp[-4].symbolInfo)->getName() << "' redeclared as different kind of symbol\n";
		}else if((fnd->getInherentType()=="func_def" || fnd->getInherentType()=="func_decl") && (!fnd->funcComp(func))){
			errorcount++;
			outerror << "Line# " << (yylsp[-4]).first_line << ": " << "Conflicting types for '" << (yyvsp[-4].symbolInfo)->getName() << "'\n";
		}
		

	
	}
#line 1760 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 323 "2005013.y"
        {
						Node* nd_id=new Node();
		nd_id->setStart((yylsp[-3]).first_line);
		nd_id->setEnd((yylsp[-3]).last_line);
		//nd_id->setName($2->getName());
		nd_id->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
		nd_id->setSymbolInfo((yyvsp[-3].symbolInfo));
		nd_id->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());
				
				Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-2]).first_line);
		nd_lp->setEnd((yylsp[-2]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-2].symbolInfo));

				Node* nd_rp=new Node();
		nd_rp->setStart((yylsp[-1]).first_line);
		nd_rp->setEnd((yylsp[-1]).last_line);
		nd_rp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_rp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_rp->setSymbolInfo((yyvsp[-1].symbolInfo));
			
				Node* nd_sc=new Node();
		nd_sc->setStart((yylsp[0]).first_line);
		nd_sc->setEnd((yylsp[0]).last_line);
		nd_sc->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_sc->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_sc->setSymbolInfo((yyvsp[0].symbolInfo));

		Node* nd=new Node();
		nd->setName("func_declaration");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("func_declaration");
		nd->setGrammar("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON ");
		nd->addChild((yyvsp[-4].intermediateNode));
		nd->addChild(nd_id);
		nd->addChild(nd_lp);
		nd->addChild(nd_rp);
		nd->addChild(nd_sc);
		(yyval.intermediateNode)=nd;
		SymbolInfo* func=new SymbolInfo();
		func->setInherentType("func_decl");
		func->setRettypeOrArrayType((yyvsp[-4].intermediateNode)->getTypeSpecifier());
		func->setType((yyvsp[-3].symbolInfo)->getType());
		func->setName((yyvsp[-3].symbolInfo)->getName());

		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		//outlog<<$2->getName()<<"\n";
		SymbolInfo* fnd=sTable->LookUp((yyvsp[-3].symbolInfo)->getName());
		
		if(fnd==NULL){
			sTable->Insert(func);
			nd_id->setSymbolInfo(func);
		}
		else if(fnd->getInherentType()=="variable"){
			errorcount++;
			outerror << "Line# " << (yylsp[-3]).first_line << ": " << "'" << (yyvsp[-3].symbolInfo)->getName() << "' redeclared as different kind of symbol\n";
		}else if((fnd->getInherentType()=="func_def" || fnd->getInherentType()=="func_decl") && (!fnd->funcComp(func))){
			errorcount++;
			outerror << "Line# " << (yylsp[-3]).first_line << ": " << "Conflicting types for '" << (yyvsp[-3].symbolInfo)->getName() << "'\n";
		}

		
	}
#line 1831 "y.tab.c"
    break;

  case 10: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN compound_statement  */
#line 392 "2005013.y"
                {
				Node* nd_id=new Node();
		nd_id->setStart((yylsp[-4]).first_line);
		nd_id->setEnd((yylsp[-4]).last_line);
		//nd_id->setName($2->getName());
		nd_id->setTypeSpecifier((yyvsp[-4].symbolInfo)->getType());
		nd_id->setSymbolInfo((yyvsp[-4].symbolInfo));
		
		nd_id->setGrammar((yyvsp[-4].symbolInfo)->getType()+" : "+(yyvsp[-4].symbolInfo)->getName());
				Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-3]).first_line);
		nd_lp->setEnd((yylsp[-3]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-3].symbolInfo));
				Node* nd_rp=new Node();
		nd_rp->setStart((yylsp[-1]).first_line);
		nd_rp->setEnd((yylsp[-1]).last_line);
		nd_rp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_rp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_rp->setSymbolInfo((yyvsp[-1].symbolInfo));

		Node* nd=new Node();
		nd->setName("func_definition");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("func_definition");
		nd->setGrammar("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		nd->addChild((yyvsp[-5].intermediateNode));
		nd->addChild(nd_id);
		nd->addChild(nd_lp);
		nd->addChild((yyvsp[-2].intermediateNode));
		nd->addChild(nd_rp);
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		SymbolInfo* func=new SymbolInfo();
		func->setInherentType("func_def");
		func->setRettypeOrArrayType((yyvsp[-5].intermediateNode)->getTypeSpecifier());
		func->setType((yyvsp[-4].symbolInfo)->getType());
		func->setName((yyvsp[-4].symbolInfo)->getName());
		for(int i=0;i<paramsOfFunction.size();i++){
			func->addParam(paramsOfFunction[i]);
		}
		paramsOfFunction.clear();
		SymbolInfo* fnd=sTable->LookUp((yyvsp[-4].symbolInfo)->getName());
		if(fnd==NULL){
			sTable->Insert(func);
			nd_id->setSymbolInfo(func);
		}else if(fnd->getInherentType()=="variable"){
			errorcount++;
			outerror << "Line# " << (yylsp[-4]).first_line << ": " << "'" << (yyvsp[-4].symbolInfo)->getName() << "' redeclared as different kind of symbol\n";
		}else if(fnd->getInherentType()=="func_def"){
			//cout<<fnd->getInherentType()<<"jhgdsdf\n";
			errorcount++;
			outerror <<"Line# " << (yylsp[-4]).first_line << ": " << "Multiple definition of '" << (yyvsp[-4].symbolInfo)->getName() << "'\n";
		}else if((fnd->getInherentType()=="func_decl") && (!fnd->funcComp(func))){	
			errorcount++;
			outerror << "Line# " << (yylsp[-4]).first_line << ": " << "Conflicting types for '" << (yyvsp[-4].symbolInfo)->getName() << "'\n";
		}

		}
#line 1899 "y.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN RPAREN compound_statement  */
#line 456 "2005013.y"
                {
				Node* nd_id=new Node();
		nd_id->setStart((yylsp[-3]).first_line);
		nd_id->setEnd((yylsp[-3]).last_line);
		//nd_id->setName($2->getName());
		nd_id->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
		nd_id->setSymbolInfo((yyvsp[-3].symbolInfo));
		nd_id->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());
				
				Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-2]).first_line);
		nd_lp->setEnd((yylsp[-2]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-3].symbolInfo));

				Node* nd_rp=new Node();
		nd_rp->setStart((yylsp[-1]).first_line);
		nd_rp->setEnd((yylsp[-1]).last_line);
		nd_rp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_rp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_rp->setSymbolInfo((yyvsp[-1].symbolInfo));

		Node* nd=new Node();
		nd->setName("func_definition");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("func_definition");
		nd->setGrammar("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
		nd->addChild((yyvsp[-4].intermediateNode));
		nd->addChild(nd_id);
		nd->addChild(nd_lp);
		nd->addChild(nd_rp);
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		SymbolInfo* func=new SymbolInfo();
		func->setInherentType("func_def");
		func->setRettypeOrArrayType((yyvsp[-4].intermediateNode)->getTypeSpecifier());
		func->setType((yyvsp[-3].symbolInfo)->getType());
		func->setName((yyvsp[-3].symbolInfo)->getName());
		SymbolInfo* fnd=sTable->LookUp((yyvsp[-3].symbolInfo)->getName());
		if(fnd==NULL){
			sTable->Insert(func);
			nd_id->setSymbolInfo(func);
		}
		else if(fnd->getInherentType()=="variable"){
			errorcount++;
			outerror << "Line# " << (yylsp[-3]).first_line << ": " << "'" << (yyvsp[-3].symbolInfo)->getName() << "' redeclared as different kind of symbol\n";
		}else if(fnd->getInherentType()=="func_def"){
			errorcount++;
			outerror <<"Line# " << (yylsp[-3]).first_line << ": " << "Multiple definition of '" << (yyvsp[-3].symbolInfo)->getName() << "'\n";
		} else if((fnd->getInherentType()=="func_decl") && (!fnd->funcComp(func))){
			// //<<fnd->getName()<<" "<<fnd->getParams().size()<<" "<<fnd->getInherentType()<<"jhgdsdf\n";
			errorcount++;
			outerror << "Line# " << (yylsp[-3]).first_line << ": " << "Conflicting types for '" << (yyvsp[-3].symbolInfo)->getName() << "'\n";
		}
		}
#line 1962 "y.tab.c"
    break;

  case 12: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 518 "2005013.y"
                {
					Node* nd_com=new Node();
		nd_com->setStart((yylsp[-2]).first_line);
		nd_com->setEnd((yylsp[-2]).last_line);
		nd_com->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
		nd_com->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());
		nd_com->setSymbolInfo((yyvsp[-2].symbolInfo));
				Node* nd_id=new Node();
		nd_id->setStart((yylsp[0]).first_line);
		nd_id->setEnd((yylsp[0]).last_line);
		//nd_id->setName($4->getName());
		nd_id->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_id->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_id->setSymbolInfo((yyvsp[0].symbolInfo));

		Node* nd=new Node();
		nd->setName("parameter_list");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("parameter_list");
		nd->setGrammar("parameter_list  : parameter_list COMMA type_specifier ID");
		nd->addChild((yyvsp[-3].intermediateNode));
		nd->addChild(nd_com);
		nd->addChild((yyvsp[-1].intermediateNode));
		nd->addChild(nd_id);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		paramsOfFunction.push_back({(yyvsp[0].symbolInfo)->getName(),(yyvsp[-1].intermediateNode)->getTypeSpecifier()});

		}
#line 1998 "y.tab.c"
    break;

  case 13: /* parameter_list: parameter_list COMMA type_specifier  */
#line 550 "2005013.y"
                {
								Node* nd_com=new Node();
		nd_com->setStart((yylsp[-1]).first_line);
		nd_com->setEnd((yylsp[-1]).last_line);
		nd_com->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_com->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_com->setSymbolInfo((yyvsp[-1].symbolInfo));

		Node* nd=new Node();
		nd->setName("parameter_list");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("parameter_list");
		nd->setGrammar("parameter_list  : parameter_list COMMA type_specifier");
		nd->addChild((yyvsp[-2].intermediateNode));
		nd->addChild(nd_com);
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		paramsOfFunction.push_back({"NN",(yyvsp[0].intermediateNode)->getTypeSpecifier()});

		}
#line 2026 "y.tab.c"
    break;

  case 14: /* parameter_list: type_specifier ID  */
#line 574 "2005013.y"
                {

				Node* nd_id=new Node();
		nd_id->setStart((yylsp[0]).first_line);
		nd_id->setEnd((yylsp[0]).last_line);
		//nd_id->setName($2->getName());
		nd_id->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_id->setSymbolInfo((yyvsp[0].symbolInfo));
		
		nd_id->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());

		Node* nd=new Node();
		nd->setName("parameter_list");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("parameter_list");
		nd->setGrammar("parameter_list  : type_specifier ID");
		nd->addChild((yyvsp[-1].intermediateNode));
		nd->addChild(nd_id);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		paramsOfFunction.push_back({(yyvsp[0].symbolInfo)->getName(),(yyvsp[-1].intermediateNode)->getTypeSpecifier()});
		}
#line 2055 "y.tab.c"
    break;

  case 15: /* parameter_list: type_specifier  */
#line 599 "2005013.y"
                {
					Node* nd=new Node();
		nd->setName("parameter_list");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("parameter_list");
		nd->setGrammar("parameter_list  : type_specifier");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		paramsOfFunction.push_back({"NN",(yyvsp[0].intermediateNode)->getTypeSpecifier()});

		}
#line 2074 "y.tab.c"
    break;

  case 16: /* parameter_list: error  */
#line 615 "2005013.y"
                {
			yyclearin;
			yyerrok;

			Node* nd=new Node();
			nd->setName("parameter_list");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("parameter_list");
			nd->setGrammar("syntax error");
			(yyval.intermediateNode)=nd;

			//outlog<<"Error at line no "<<$$->getStart()<<" : "<<$$->getGrammar()<<"\n";
			

		}
#line 2095 "y.tab.c"
    break;

  case 17: /* $@1: %empty  */
#line 634 "2005013.y"
                          {
			sTable->enterScope();
			for(int i=0;i<paramsOfFunction.size();i++){

				SymbolInfo *sinfo=new SymbolInfo();
				sinfo->setName(paramsOfFunction[i].first);
				sinfo->setType(paramsOfFunction[i].second);
				sinfo->setInherentType("variable");
				
				SymbolInfo* cmp=sTable->getCurrentScopeTable()->Lookup(sinfo->getName());
				if(cmp==NULL){
					sTable->Insert(sinfo);
				}else{
					errorcount++;
					outerror<<"Line# "<<(yylsp[0]).first_line<<": "<<"Redefinition of parameter '"<<sinfo->getName()<<"'\n";
				}
			}


		}
#line 2120 "y.tab.c"
    break;

  case 18: /* compound_statement: LCURL $@1 statements RCURL  */
#line 655 "2005013.y"
                {
			Node* nd_lc=new Node();
		nd_lc->setStart((yylsp[-3]).first_line);
		nd_lc->setEnd((yylsp[-3]).last_line);
		nd_lc->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
		nd_lc->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());
		nd_lc->setSymbolInfo((yyvsp[-3].symbolInfo));

		Node* nd_rc=new Node();
		nd_rc->setStart((yylsp[0]).first_line);
		nd_rc->setEnd((yylsp[0]).last_line);
		nd_rc->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_rc->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_rc->setSymbolInfo((yyvsp[0].symbolInfo));


		Node* nd=new Node();
		nd->setName("compound_statement");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("compound_statement");
		nd->setGrammar("compound_statement : LCURL statements RCURL");
		nd->addChild(nd_lc);
		nd->addChild((yyvsp[-1].intermediateNode));
		nd->addChild(nd_rc);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		sTable->printAllTables(outlog);

		sTable->exitScope();

				
		}
#line 2158 "y.tab.c"
    break;

  case 19: /* compound_statement: LCURL RCURL  */
#line 689 "2005013.y"
                {
				Node* nd_lc=new Node();
		nd_lc->setStart((yylsp[-1]).first_line);
		nd_lc->setEnd((yylsp[-1]).last_line);
		nd_lc->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_lc->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_lc->setSymbolInfo((yyvsp[-1].symbolInfo));

		Node* nd_rc=new Node();
		nd_rc->setStart((yylsp[0]).first_line);
		nd_rc->setEnd((yylsp[0]).last_line);
		nd_rc->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_rc->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_rc->setSymbolInfo((yyvsp[0].symbolInfo));

		Node* nd=new Node();
		nd->setName("compound_statement");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("compound_statement");
		nd->setGrammar("compound_statement : LCURL RCURL");
		nd->addChild(nd_lc);
		nd->addChild(nd_rc);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		sTable->enterScope();
		sTable->printAllTables(outlog);
		sTable->exitScope();

		}
#line 2193 "y.tab.c"
    break;

  case 20: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 722 "2005013.y"
                 {
				
		Node* nd_sc=new Node();
		nd_sc->setStart((yylsp[0]).first_line);
		nd_sc->setEnd((yylsp[0]).last_line);
		nd_sc->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_sc->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_sc->setSymbolInfo((yyvsp[0].symbolInfo));

		Node* nd=new Node();
		nd->setName("var_declaration");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("var_declaration");
		nd->setGrammar("var_declaration : type_specifier declaration_list SEMICOLON");
		nd->addChild((yyvsp[-2].intermediateNode));
		nd->addChild((yyvsp[-1].intermediateNode));
		nd->addChild(nd_sc);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		SymbolInfo *declarationSymbol=new SymbolInfo();
		declarationSymbol->setName("declaration_list");
	
		for(int i=0;i<varNameTypeSz.size();i++){
			SymbolInfo *sinfo=new SymbolInfo();
			sinfo->setName(varNameTypeSz[i].first.first);
			sinfo->setType((yyvsp[-2].intermediateNode)->getTypeSpecifier());
			sinfo->setInherentType("variable");
			sinfo->setArraySize(varNameTypeSz[i].second);
			sinfo->setRettypeOrArrayType((yyvsp[-2].intermediateNode)->getTypeSpecifier());
			//nd->addVar(varNameTypeSz[i]);
			SymbolInfo* cmp=sTable->getCurrentScopeTable()->Lookup(sinfo->getName());
			if((yyvsp[-2].intermediateNode)->getTypeSpecifier()=="VOID"){
				errorcount++;
				outerror<<"Line# "<<(yyloc).first_line<<": "<<"Variable or field '"<<sinfo->getName()<<"'declared void \n";
			}else if(cmp==NULL){
				sTable->Insert(sinfo);
				declarationSymbol->addVar(varNameTypeSz[i]);
			}else{
				// //<<cmp->getName()<<" "<<cmp->getRettypeOrArrayType()<<"\n";
				errorcount++;
				outerror<<"Line# "<<(yyloc).first_line<<": "<<"Conflicting types for '"<<sinfo->getName()<<"'\n";
			}
			
	
		}
		(yyvsp[-1].intermediateNode)->setSymbolInfo(declarationSymbol);
		varNameTypeSz.clear();

		}
#line 2249 "y.tab.c"
    break;

  case 21: /* type_specifier: INT  */
#line 776 "2005013.y"
                {
			Node* nd_int=new Node();
		nd_int->setStart((yylsp[0]).first_line);
		nd_int->setEnd((yylsp[0]).last_line);
		nd_int->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_int->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_int->setSymbolInfo((yyvsp[0].symbolInfo));
				
				Node* nd=new Node();
		nd->setName("type_specifier");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("INT");
		nd->setGrammar("type_specifier	: INT");
		nd->addChild(nd_int);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		}
#line 2273 "y.tab.c"
    break;

  case 22: /* type_specifier: FLOAT  */
#line 796 "2005013.y"
                {
			Node* nd_fl=new Node();
		nd_fl->setStart((yylsp[0]).first_line);
		nd_fl->setEnd((yylsp[0]).last_line);
		nd_fl->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_fl->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_fl->setSymbolInfo((yyvsp[0].symbolInfo));
				Node* nd=new Node();
		nd->setName("type_specifier");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("FLOAT");
		nd->setGrammar("type_specifier	: FLOAT");
		nd->addChild(nd_fl);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		}
#line 2295 "y.tab.c"
    break;

  case 23: /* type_specifier: VOID  */
#line 814 "2005013.y"
                {
			Node* nd_vd=new Node();
		nd_vd->setStart((yylsp[0]).first_line);
		nd_vd->setEnd((yylsp[0]).last_line);
		nd_vd->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_vd->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_vd->setSymbolInfo((yyvsp[0].symbolInfo));
				Node* nd=new Node();
		nd->setName("type_specifier");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("VOID");
		nd->setGrammar("type_specifier	: VOID");
		nd->addChild(nd_vd);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		}
#line 2317 "y.tab.c"
    break;

  case 24: /* declaration_list: declaration_list COMMA ID  */
#line 834 "2005013.y"
                        {
					Node* nd_com=new Node();
			nd_com->setStart((yylsp[-1]).first_line);
			nd_com->setEnd((yylsp[-1]).last_line);
			nd_com->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
			nd_com->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
			nd_com->setSymbolInfo((yyvsp[-1].symbolInfo));
			Node* nd_id=new Node();

			nd_id->setStart((yylsp[0]).first_line);
			nd_id->setEnd((yylsp[0]).last_line);
			(yyvsp[0].symbolInfo)->setInherentType("variable");
			nd_id->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
			nd_id->setSymbolInfo((yyvsp[0].symbolInfo));
			nd_id->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
			nd_id->setSymbolInfo((yyvsp[0].symbolInfo));

			Node* nd=new Node();
			nd->setName("declaration_list");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("declaration_list");
			nd->setGrammar("declaration_list : declaration_list COMMA ID");
			nd->addChild((yyvsp[-2].intermediateNode));
			nd->addChild(nd_com);
			nd->addChild(nd_id);
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

			varNameTypeSz.push_back({{(yyvsp[0].symbolInfo)->getName(),(yyvsp[0].symbolInfo)->getType()},-1});
			// //<<$3->getType()<<"\n";
				
			}
#line 2355 "y.tab.c"
    break;

  case 25: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 868 "2005013.y"
                        {
									Node* nd_com=new Node();
			nd_com->setStart((yylsp[-4]).first_line);
			nd_com->setEnd((yylsp[-4]).last_line);
			nd_com->setTypeSpecifier((yyvsp[-4].symbolInfo)->getType());
			nd_com->setGrammar((yyvsp[-4].symbolInfo)->getType()+" : "+(yyvsp[-4].symbolInfo)->getName());
			nd_com->setSymbolInfo((yyvsp[-4].symbolInfo));

			Node* nd_id=new Node();
			nd_id->setStart((yylsp[-3]).first_line);
			nd_id->setEnd((yylsp[-3]).last_line);
			//nd_id->setName($3->getName());
			nd_id->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
			(yyvsp[-3].symbolInfo)->setInherentType("variable");
			(yyvsp[-3].symbolInfo)->setArraySize(stoi((yyvsp[-1].symbolInfo)->getName()));
			nd_id->setSymbolInfo((yyvsp[-3].symbolInfo));
			nd_id->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());

			Node* nd_lt=new Node();
			nd_lt->setStart((yylsp[-2]).first_line);
			nd_lt->setEnd((yylsp[-2]).last_line);
			nd_lt->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
			nd_lt->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());
			nd_lt->setSymbolInfo((yyvsp[-2].symbolInfo));

			Node* nd_ci=new Node();
			nd_ci->setStart((yylsp[-1]).first_line);
			nd_ci->setEnd((yylsp[-1]).last_line);
			nd_ci->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
			nd_ci->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
			if((yyvsp[-2].symbolInfo)->getName()=="0"){
				nd_ci->setZero();
			}
			nd_ci->setSymbolInfo((yyvsp[-1].symbolInfo));

			Node* nd_rt=new Node();
			nd_rt->setStart((yylsp[0]).first_line);
			nd_rt->setEnd((yylsp[0]).last_line);
			nd_rt->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
			nd_rt->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
			nd_rt->setSymbolInfo((yyvsp[0].symbolInfo));

			Node* nd=new Node();
			nd->setName("declaration_list");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("declaration_list");
			nd->setGrammar("declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
			nd->addChild((yyvsp[-5].intermediateNode));
			nd->addChild(nd_com);
			nd->addChild(nd_id);
			nd->addChild(nd_lt);
			nd->addChild(nd_ci);
			nd->addChild(nd_rt);
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
			varNameTypeSz.push_back({{(yyvsp[-3].symbolInfo)->getName(),(yyvsp[-3].symbolInfo)->getType()},stoi((yyvsp[-1].symbolInfo)->getName())});

			}
#line 2419 "y.tab.c"
    break;

  case 26: /* declaration_list: ID  */
#line 928 "2005013.y"
                        {
					Node* nd_id=new Node();
			nd_id->setStart((yylsp[0]).first_line);
			nd_id->setEnd((yylsp[0]).last_line);
			//nd_id->setName($1->getName());
			(yyvsp[0].symbolInfo)->setInherentType("variable");
			nd_id->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
			nd_id->setSymbolInfo((yyvsp[0].symbolInfo));
			nd_id->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());


					Node* nd=new Node();
			nd->setName("declaration_list");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("declaration_list");
			nd->setGrammar("declaration_list : ID");
			nd->addChild(nd_id);
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
			varNameTypeSz.push_back({{(yyvsp[0].symbolInfo)->getName(),(yyvsp[0].symbolInfo)->getType()},-1});

			}
#line 2447 "y.tab.c"
    break;

  case 27: /* declaration_list: ID LTHIRD RTHIRD ASSIGNOP LCURL expression_list RCURL  */
#line 952 "2005013.y"
                        {
				Node* nd_id=new Node();
			nd_id->setStart((yylsp[-6]).first_line);
			nd_id->setEnd((yylsp[-6]).last_line);
			//nd_id->setName($1->getName());
			(yyvsp[-6].symbolInfo)->setInherentType("variable");
			nd_id->setTypeSpecifier((yyvsp[-6].symbolInfo)->getType());
			nd_id->setSymbolInfo((yyvsp[-6].symbolInfo));
			nd_id->setGrammar((yyvsp[-6].symbolInfo)->getType()+" : "+(yyvsp[-6].symbolInfo)->getName());


			Node* nd_lt=new Node();
			nd_lt->setStart((yylsp[-5]).first_line);
			nd_lt->setEnd((yylsp[-5]).last_line);
			nd_lt->setTypeSpecifier((yyvsp[-5].symbolInfo)->getType());
			nd_lt->setGrammar((yyvsp[-5].symbolInfo)->getType()+" : "+(yyvsp[-5].symbolInfo)->getName());
			nd_lt->setSymbolInfo((yyvsp[-5].symbolInfo));

			Node* nd_aop=new Node();
			nd_aop->setStart((yylsp[-3]).first_line);
			nd_aop->setEnd((yylsp[-3]).last_line);
			nd_aop->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
			nd_aop->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());
			nd_aop->setSymbolInfo((yyvsp[-3].symbolInfo));

			Node* nd_rt=new Node();
			nd_rt->setStart((yylsp[-4]).first_line);
			nd_rt->setEnd((yylsp[-4]).last_line);
			nd_rt->setTypeSpecifier((yyvsp[-4].symbolInfo)->getType());
			nd_rt->setGrammar((yyvsp[-4].symbolInfo)->getType()+" : "+(yyvsp[-4].symbolInfo)->getName());
			nd_rt->setSymbolInfo((yyvsp[-4].symbolInfo));

					Node* nd_lcurl=new Node();
			nd_lcurl->setStart((yylsp[-2]).first_line);
			nd_lcurl->setEnd((yylsp[-2]).last_line);
			nd_lcurl->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
			nd_lcurl->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());
			nd_lcurl->setSymbolInfo((yyvsp[-2].symbolInfo));
					Node* nd_rcurl=new Node();
			nd_rcurl->setStart((yylsp[0]).first_line);
			nd_rcurl->setEnd((yylsp[0]).last_line);
			nd_rcurl->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
			nd_rcurl->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
			nd_rcurl->setSymbolInfo((yyvsp[0].symbolInfo));

			Node* nd=new Node();
			nd->setName("declaration_list");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("declaration_list");
			nd->setGrammar("ID LTHIRD RTHIRD ASSIGNOP LCURL expression_list RCURL");
			nd->addChild(nd_id);
			nd->addChild(nd_lt);
			nd->addChild(nd_rt);
			nd->addChild(nd_aop);
			nd->addChild(nd_lcurl);
			nd->addChild((yyvsp[-1].intermediateNode));
			nd->addChild(nd_rcurl);
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
			//varNameTypeSz.push_back({{$1->getName(),$1->getType()},stoi($3->getName())});




			}
#line 2518 "y.tab.c"
    break;

  case 28: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 1019 "2005013.y"
                        {
							Node* nd_id=new Node();
			nd_id->setStart((yylsp[-3]).first_line);
			nd_id->setEnd((yylsp[-3]).last_line);
			//nd_id->setName($1->getName());
			(yyvsp[-3].symbolInfo)->setInherentType("variable");
			(yyvsp[-3].symbolInfo)->setArraySize(stoi((yyvsp[-1].symbolInfo)->getName()));
			nd_id->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
			nd_id->setSymbolInfo((yyvsp[-3].symbolInfo));
			nd_id->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());


			Node* nd_lt=new Node();
			nd_lt->setStart((yylsp[-2]).first_line);
			nd_lt->setEnd((yylsp[-2]).last_line);
			nd_lt->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
			nd_lt->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());
			nd_lt->setSymbolInfo((yyvsp[-2].symbolInfo));

			Node* nd_ci=new Node();
			nd_ci->setStart((yylsp[-1]).first_line);
			nd_ci->setEnd((yylsp[-1]).last_line);
			nd_ci->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
			nd_ci->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
			if((yyvsp[-1].symbolInfo)->getName()=="0"){
				nd_ci->setZero();
			}
			nd_ci->setSymbolInfo((yyvsp[-1].symbolInfo));

			Node* nd_rt=new Node();
			nd_rt->setStart((yylsp[0]).first_line);
			nd_rt->setEnd((yylsp[0]).last_line);
			nd_rt->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
			nd_rt->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
			nd_rt->setSymbolInfo((yyvsp[0].symbolInfo));

			Node* nd=new Node();
			nd->setName("declaration_list");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("declaration_list");
			nd->setGrammar("declaration_list : ID LSQUARE CONST_INT RSQUARE");
			nd->addChild(nd_id);
			nd->addChild(nd_lt);
			nd->addChild(nd_ci);
			nd->addChild(nd_rt);
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
			varNameTypeSz.push_back({{(yyvsp[-3].symbolInfo)->getName(),(yyvsp[-3].symbolInfo)->getType()},stoi((yyvsp[-1].symbolInfo)->getName())});

			}
#line 2574 "y.tab.c"
    break;

  case 29: /* declaration_list: error  */
#line 1072 "2005013.y"
                        {
				yyclearin;
				yyerrok;

				Node* nd=new Node();
				nd->setName("declaration_list");
				nd->setStart((yyloc).first_line);
				nd->setEnd((yyloc).last_line);
				nd->setTypeSpecifier("declaration_list");
				nd->setGrammar("syntax error");
				(yyval.intermediateNode)=nd;
				//outlog<<"Error at line no "<<$$->getStart()<<" : "<<$$->getGrammar()<<"\n";

			}
#line 2593 "y.tab.c"
    break;

  case 30: /* expression_list: expression  */
#line 1089 "2005013.y"
                {
			Node* nd=new Node();
			nd->setName("expression_list");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("expression_list");
			nd->setGrammar("expression_list : expression");
			nd->addChild((yyvsp[0].intermediateNode));
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		}
#line 2610 "y.tab.c"
    break;

  case 31: /* expression_list: expression_list COMMA expression  */
#line 1102 "2005013.y"
                {
			Node* nd_lp=new Node();
			nd_lp->setStart((yylsp[-1]).first_line);
			nd_lp->setEnd((yylsp[-1]).last_line);
			nd_lp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
			nd_lp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
			nd_lp->setSymbolInfo((yyvsp[-1].symbolInfo));

			Node* nd=new Node();
			nd->setName("expression_list");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("expression_list");
			nd->setGrammar("expression_list : expression_list COMMA expression");
			nd->addChild((yyvsp[-2].intermediateNode));
			nd->addChild(nd_lp);
			nd->addChild((yyvsp[0].intermediateNode));
			(yyval.intermediateNode)=nd;
			outlog<<nd->getGrammar()<<"\n";
			
		}
#line 2636 "y.tab.c"
    break;

  case 32: /* statements: statement  */
#line 1126 "2005013.y"
                {
			Node* nd=new Node();
			nd->setName("statements");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statements");
			nd->setGrammar("statements : statement");
			nd->addChild((yyvsp[0].intermediateNode));
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		}
#line 2653 "y.tab.c"
    break;

  case 33: /* statements: statements statement  */
#line 1139 "2005013.y"
                {
			Node* nd=new Node();
			nd->setName("statements");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statements");
			nd->setGrammar("statements : statements statement");
			nd->addChild((yyvsp[-1].intermediateNode));
			nd->addChild((yyvsp[0].intermediateNode));
			(yyval.intermediateNode)=nd;
			outlog<<nd->getGrammar()<<"\n";
			
		}
#line 2671 "y.tab.c"
    break;

  case 34: /* statement: var_declaration  */
#line 1155 "2005013.y"
                {	
			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : var_declaration");
			nd->addChild((yyvsp[0].intermediateNode));
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		}
#line 2687 "y.tab.c"
    break;

  case 35: /* statement: expression_statement  */
#line 1167 "2005013.y"
                {
			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : expression_statement");
			nd->addChild((yyvsp[0].intermediateNode));
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		}
#line 2703 "y.tab.c"
    break;

  case 36: /* statement: compound_statement  */
#line 1179 "2005013.y"
                {
			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : compound_statement");
			nd->addChild((yyvsp[0].intermediateNode));
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		}
#line 2719 "y.tab.c"
    break;

  case 37: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 1191 "2005013.y"
                {
			Node* nd_for=new Node();
			nd_for->setStart((yylsp[-6]).first_line);
			nd_for->setEnd((yylsp[-6]).last_line);
			nd_for->setTypeSpecifier((yyvsp[-6].symbolInfo)->getType());
			nd_for->setGrammar((yyvsp[-6].symbolInfo)->getType()+" : "+(yyvsp[-6].symbolInfo)->getName());
			nd_for->setSymbolInfo((yyvsp[-6].symbolInfo));

			Node* nd_lp=new Node();
			nd_lp->setStart((yylsp[-5]).first_line);
			nd_lp->setEnd((yylsp[-5]).last_line);
			nd_lp->setTypeSpecifier((yyvsp[-5].symbolInfo)->getType());
			nd_lp->setGrammar((yyvsp[-5].symbolInfo)->getType()+" : "+(yyvsp[-5].symbolInfo)->getName());
			nd_lp->setSymbolInfo((yyvsp[-5].symbolInfo));

			Node* nd_rp=new Node();
			nd_rp->setStart((yylsp[-1]).first_line);
			nd_rp->setEnd((yylsp[-1]).last_line);
			nd_rp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
			nd_rp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
			nd_rp->setSymbolInfo((yyvsp[-1].symbolInfo));

			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
			nd->addChild(nd_for);
			nd->addChild(nd_lp);
			nd->addChild((yyvsp[-4].intermediateNode));
			nd->addChild((yyvsp[-3].intermediateNode));
			nd->addChild((yyvsp[-2].intermediateNode));
			nd->addChild(nd_rp);
			nd->addChild((yyvsp[0].intermediateNode));
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";


		}
#line 2764 "y.tab.c"
    break;

  case 38: /* statement: IF LPAREN expression RPAREN statement  */
#line 1232 "2005013.y"
                {
			Node* nd_if=new Node();
			nd_if->setStart((yylsp[-4]).first_line);
			nd_if->setEnd((yylsp[-4]).last_line);
			nd_if->setTypeSpecifier((yyvsp[-4].symbolInfo)->getType());
			nd_if->setGrammar((yyvsp[-4].symbolInfo)->getType()+" : "+(yyvsp[-4].symbolInfo)->getName());
			nd_if->setSymbolInfo((yyvsp[-4].symbolInfo));

			Node* nd_lp=new Node();
			nd_lp->setStart((yylsp[-3]).first_line);
			nd_lp->setEnd((yylsp[-3]).last_line);
			nd_lp->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
			nd_lp->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());
			nd_lp->setSymbolInfo((yyvsp[-3].symbolInfo));
			
			Node* nd_rp=new Node();
			nd_rp->setStart((yylsp[-1]).first_line);
			nd_rp->setEnd((yylsp[-1]).last_line);
			nd_rp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
			nd_rp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
			nd_rp->setSymbolInfo((yyvsp[-1].symbolInfo));		
			
			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : IF LPAREN expression RPAREN statement");
			nd->addChild(nd_if);
			nd->addChild(nd_lp);
			nd->addChild((yyvsp[-2].intermediateNode));
			nd->addChild(nd_rp);
			nd->addChild((yyvsp[0].intermediateNode));
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		}
#line 2806 "y.tab.c"
    break;

  case 39: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 1270 "2005013.y"
                {
						Node* nd_if=new Node();
			nd_if->setStart((yylsp[-6]).first_line);
			nd_if->setEnd((yylsp[-6]).last_line);
			nd_if->setTypeSpecifier((yyvsp[-6].symbolInfo)->getType());
			nd_if->setGrammar((yyvsp[-6].symbolInfo)->getType()+" : "+(yyvsp[-6].symbolInfo)->getName());
			nd_if->setSymbolInfo((yyvsp[-6].symbolInfo));

			Node* nd_lp=new Node();
			nd_lp->setStart((yylsp[-5]).first_line);
			nd_lp->setEnd((yylsp[-5]).last_line);
			nd_lp->setTypeSpecifier((yyvsp[-5].symbolInfo)->getType());
			nd_lp->setGrammar((yyvsp[-5].symbolInfo)->getType()+" : "+(yyvsp[-5].symbolInfo)->getName());
			nd_lp->setSymbolInfo((yyvsp[-5].symbolInfo));
			
			Node* nd_rp=new Node();
			nd_rp->setStart((yylsp[-3]).first_line);
			nd_rp->setEnd((yylsp[-3]).last_line);
			nd_rp->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
			nd_rp->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());
			nd_rp->setSymbolInfo((yyvsp[-3].symbolInfo));
				Node* nd_el=new Node();
			nd_el->setStart((yylsp[-1]).first_line);
			nd_el->setEnd((yylsp[-1]).last_line);
			nd_el->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
			nd_el->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
			nd_el->setSymbolInfo((yyvsp[-1].symbolInfo));		
			
			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : IF LPAREN expression RPAREN statement ELSE statement");
			nd->addChild(nd_if);
			nd->addChild(nd_lp);
			nd->addChild((yyvsp[-4].intermediateNode));
			nd->addChild(nd_rp);
			nd->addChild((yyvsp[-2].intermediateNode));
			nd->addChild(nd_el);
			nd->addChild((yyvsp[0].intermediateNode));
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		}
#line 2856 "y.tab.c"
    break;

  case 40: /* statement: LOOP statement WHILE LPAREN expression RPAREN  */
#line 1316 "2005013.y"
                {
			Node* nd_loop=new Node();
			nd_loop->setStart((yylsp[-5]).first_line);
			nd_loop->setEnd((yylsp[-5]).last_line);
			nd_loop->setTypeSpecifier((yyvsp[-5].symbolInfo)->getType());
			nd_loop->setGrammar((yyvsp[-5].symbolInfo)->getType()+" : "+(yyvsp[-5].symbolInfo)->getName());
			nd_loop->setSymbolInfo((yyvsp[-5].symbolInfo));
		
			Node* nd_wh=new Node();
			nd_wh->setStart((yylsp[-3]).first_line);
			nd_wh->setEnd((yylsp[-3]).last_line);
			nd_wh->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
			nd_wh->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());
			nd_wh->setSymbolInfo((yyvsp[-3].symbolInfo));

			Node* nd_lp=new Node();
			nd_lp->setStart((yylsp[-2]).first_line);
			nd_lp->setEnd((yylsp[-2]).last_line);
			nd_lp->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
			nd_lp->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());
			nd_lp->setSymbolInfo((yyvsp[-2].symbolInfo));
			
			Node* nd_rp=new Node();
			nd_rp->setStart((yylsp[0]).first_line);
			nd_rp->setEnd((yylsp[0]).last_line);
			nd_rp->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
			nd_rp->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
			nd_rp->setSymbolInfo((yyvsp[-3].symbolInfo));

			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : LOOP statement WHILE LPAREN expression RPAREN");
			nd->addChild(nd_loop);
			nd->addChild((yyvsp[-4].intermediateNode));
			nd->addChild(nd_wh);
			nd->addChild(nd_lp);
			nd->addChild((yyvsp[-1].intermediateNode));
			nd->addChild(nd_rp);
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";



		}
#line 2908 "y.tab.c"
    break;

  case 41: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 1364 "2005013.y"
                {
			Node* nd_wh=new Node();
			nd_wh->setStart((yylsp[-4]).first_line);
			nd_wh->setEnd((yylsp[-4]).last_line);
			nd_wh->setTypeSpecifier((yyvsp[-4].symbolInfo)->getType());
			nd_wh->setGrammar((yyvsp[-4].symbolInfo)->getType()+" : "+(yyvsp[-4].symbolInfo)->getName());
			nd_wh->setSymbolInfo((yyvsp[-4].symbolInfo));

			Node* nd_lp=new Node();
			nd_lp->setStart((yylsp[-3]).first_line);
			nd_lp->setEnd((yylsp[-3]).last_line);
			nd_lp->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
			nd_lp->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());
			nd_lp->setSymbolInfo((yyvsp[-3].symbolInfo));

			Node* nd_rp=new Node();
			nd_rp->setStart((yylsp[-1]).first_line);
			nd_rp->setEnd((yylsp[-1]).last_line);
			nd_rp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
			nd_rp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
			nd_rp->setSymbolInfo((yyvsp[-1].symbolInfo));

			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : WHILE LPAREN expression RPAREN statement");
			nd->addChild(nd_wh);
			nd->addChild(nd_lp);
			nd->addChild((yyvsp[-2].intermediateNode));
			nd->addChild(nd_rp);
			nd->addChild((yyvsp[0].intermediateNode));
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		}
#line 2950 "y.tab.c"
    break;

  case 42: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 1402 "2005013.y"
                {
			Node* nd_pn=new Node();
			nd_pn->setStart((yylsp[-4]).first_line);
			nd_pn->setEnd((yylsp[-4]).last_line);
			nd_pn->setTypeSpecifier((yyvsp[-4].symbolInfo)->getType());
			nd_pn->setGrammar((yyvsp[-4].symbolInfo)->getType()+" : "+(yyvsp[-4].symbolInfo)->getName());
			nd_pn->setSymbolInfo((yyvsp[-4].symbolInfo));

			Node* nd_lp=new Node();
			nd_lp->setStart((yylsp[-3]).first_line);
			nd_lp->setEnd((yylsp[-3]).last_line);
			nd_lp->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
			nd_lp->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());
			nd_lp->setSymbolInfo((yyvsp[-3].symbolInfo));

			Node* nd_id=new Node();
			nd_id->setStart((yylsp[-2]).first_line);
			nd_id->setEnd((yylsp[-2]).last_line);
			//nd_id->setName($3->getName());
			nd_id->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
			nd_id->setSymbolInfo((yyvsp[-2].symbolInfo));
			nd_id->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());

			Node* nd_rp=new Node();
			nd_rp->setStart((yylsp[-1]).first_line);
			nd_rp->setEnd((yylsp[-1]).last_line);
			nd_rp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
			nd_rp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
			nd_rp->setSymbolInfo((yyvsp[-1].symbolInfo));
			
			Node* nd_sc=new Node();
			nd_sc->setStart((yylsp[0]).first_line);
			nd_sc->setEnd((yylsp[0]).last_line);
			nd_sc->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
			nd_sc->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
			nd_sc->setSymbolInfo((yyvsp[0].symbolInfo));

			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
			nd->addChild(nd_pn);
			nd->addChild(nd_lp);
			nd->addChild(nd_id);
			nd->addChild(nd_rp);
			nd->addChild(nd_sc);
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		}
#line 3007 "y.tab.c"
    break;

  case 43: /* statement: RETURN expression SEMICOLON  */
#line 1455 "2005013.y"
                {
			Node* nd_rt=new Node();
			nd_rt->setStart((yylsp[-2]).first_line);
			nd_rt->setEnd((yylsp[-2]).last_line);
			nd_rt->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
			nd_rt->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());
			nd_rt->setSymbolInfo((yyvsp[-2].symbolInfo));

			Node* nd_sc=new Node();
			nd_sc->setStart((yylsp[0]).first_line);
			nd_sc->setEnd((yylsp[0]).last_line);
			nd_sc->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
			nd_sc->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
			nd_sc->setSymbolInfo((yyvsp[0].symbolInfo));

			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : RETURN expression SEMICOLON");
			nd->addChild(nd_rt);
			nd->addChild((yyvsp[-1].intermediateNode));
			nd->addChild(nd_sc);
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		}
#line 3040 "y.tab.c"
    break;

  case 44: /* expression_statement: SEMICOLON  */
#line 1486 "2005013.y"
                        {
				Node* nd_sc=new Node();
			nd_sc->setStart((yylsp[0]).first_line);
			nd_sc->setEnd((yylsp[0]).last_line);
			nd_sc->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
			nd_sc->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
			nd_sc->setSymbolInfo((yyvsp[0].symbolInfo));

					
			Node* nd=new Node();
			nd->setName("expression_statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("expression_statement");
			nd->setGrammar("expression_statement 	: SEMICOLON");
			nd->addChild(nd_sc);
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

			}
#line 3065 "y.tab.c"
    break;

  case 45: /* expression_statement: expression SEMICOLON  */
#line 1507 "2005013.y"
                        {
				Node* nd_sc=new Node();
			nd_sc->setStart((yylsp[0]).first_line);
			nd_sc->setEnd((yylsp[0]).last_line);
			nd_sc->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
			nd_sc->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
			nd_sc->setSymbolInfo((yyvsp[0].symbolInfo));
					
			Node* nd=new Node();
			nd->setName("expression_statement");
			nd->setStart((yyloc).first_line);
			nd->setEnd((yyloc).last_line);
			nd->setTypeSpecifier("expression_statement");
			nd->setGrammar("expression_statement 	: expression SEMICOLON");
			nd->addChild((yyvsp[-1].intermediateNode));
			nd->addChild(nd_sc);
			(yyval.intermediateNode)=nd;
			outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

			}
#line 3090 "y.tab.c"
    break;

  case 46: /* variable: ID  */
#line 1530 "2005013.y"
        {
		Node* nd_id=new Node();
		nd_id->setStart((yylsp[0]).first_line);
		nd_id->setEnd((yylsp[0]).last_line);
		//nd_id->setName($1->getName());
		nd_id->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_id->setSymbolInfo((yyvsp[0].symbolInfo));
		nd_id->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		
		Node* nd=new Node();
		nd->setName("variable");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("variable");
		nd->setGrammar("variable : ID");

		SymbolInfo* cmp=sTable->LookUp((yyvsp[0].symbolInfo)->getName());
		if(cmp!=NULL && cmp->getInherentType()=="variable"){
			nd_id->setTypeSpecifier(cmp->getRettypeOrArrayType());
			nd->setTypeSpecifier(cmp->getRettypeOrArrayType());
		}else{
			errorcount++;
			outerror<<"Line# "<<(yylsp[0]).first_line<<": "<<"Undeclared variable '"<<(yyvsp[0].symbolInfo)->getName()<<"'\n";
		}
		nd->addChild(nd_id);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
	
		
	}
#line 3125 "y.tab.c"
    break;

  case 47: /* variable: ID LTHIRD expression RTHIRD  */
#line 1561 "2005013.y"
        {
		Node* nd_id=new Node();
		nd_id->setStart((yylsp[-3]).first_line);
		nd_id->setEnd((yylsp[-3]).last_line);
		//nd_id->setName($1->getName());
		nd_id->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
		nd_id->setSymbolInfo((yyvsp[-3].symbolInfo));
		nd_id->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());

		//outlog<<$1->getName()<<" "<<$1->getType()<<"\n";
				Node* nd_lt=new Node();
		nd_lt->setStart((yylsp[-2]).first_line);
		nd_lt->setEnd((yylsp[-2]).last_line);
		nd_lt->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
		nd_lt->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());
		nd_lt->setSymbolInfo((yyvsp[-2].symbolInfo));
				Node* nd_rt=new Node();
		nd_rt->setStart((yylsp[0]).first_line);
		nd_rt->setEnd((yylsp[0]).last_line);
		nd_rt->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_rt->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_rt->setSymbolInfo((yyvsp[0].symbolInfo));
				
		Node* nd=new Node();
		nd->setName("variable");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("variable");
		nd->setGrammar("variable : ID LSQUARE expression RSQUARE");
		SymbolInfo* cmp=sTable->LookUp((yyvsp[-3].symbolInfo)->getName());
		if(cmp == NULL)
		{
			errorcount++;
			outerror<<"Line# "<<(yylsp[-3]).first_line<<": "<<"Undeclared variable '"<<(yyvsp[-3].symbolInfo)->getName()<<"'\n";

		}
		else if((cmp->getInherentType() == "func_def") || (cmp->getInherentType() == "func_decl"))
		{
			errorcount++;
			outerror<<"Line# "<<(yylsp[-3]).first_line<<": "<<"Undeclared variable '"<<(yyvsp[-3].symbolInfo)->getName()<<"'\n";
		}
		else if(cmp->getInherentType()=="variable" && cmp->getArraySize() == -1)
		{
			errorcount++;
			outerror<<"Line# "<<(yylsp[-3]).first_line<<": "<<"'"<<(yyvsp[-3].symbolInfo)->getName()<<"' is not an array\n";
		}
		else if((yyvsp[-1].intermediateNode)->getTypeSpecifier() != "INT")
		{
			// //<<$3->getTypeSpecifier()<<"\n";
			errorcount++;
			outerror<<"Line# "<<(yylsp[-1]).first_line<<": "<<"Array subscript is not an integer \n";

		}
		else if(cmp->getInherentType()=="variable" && cmp->getArraySize() > -1)
		{
			nd_id->setTypeSpecifier(cmp->getRettypeOrArrayType());
			nd->setTypeSpecifier(cmp->getRettypeOrArrayType());
		}
		nd->addChild(nd_id);
		nd->addChild(nd_lt);
		nd->addChild((yyvsp[-1].intermediateNode));
		nd->addChild(nd_rt);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

	}
#line 3196 "y.tab.c"
    break;

  case 48: /* expression: logic_expression  */
#line 1630 "2005013.y"
        {
		Node* nd=new Node();
		nd->setName("expression");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[0].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("expression : logic_expression");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

	}
#line 3213 "y.tab.c"
    break;

  case 49: /* expression: variable ASSIGNOP logic_expression  */
#line 1643 "2005013.y"
        {
		Node* nd_ap=new Node();
		nd_ap->setStart((yylsp[-1]).first_line);
		nd_ap->setEnd((yylsp[-1]).last_line);
		nd_ap->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_ap->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_ap->setSymbolInfo((yyvsp[-1].symbolInfo));
				
		Node* nd=new Node();
		nd->setName("expression");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[-2].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("expression : variable ASSIGNOP logic_expression");
		nd->addChild((yyvsp[-2].intermediateNode));
		nd->addChild(nd_ap);
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		if((yyvsp[0].intermediateNode)->getTypeSpecifier() == "VOID")
		{
			errorcount++;
			outerror<<"Line# "<<(yylsp[0]).first_line<<": "<<"void cannot be used in expression \n";
		}
		else if((yyvsp[-2].intermediateNode)->getTypeSpecifier() == "INT" && (yyvsp[0].intermediateNode)->getTypeSpecifier() == "FLOAT")
		{
			errorcount++;
			outerror<<"Line# "<<(yylsp[-2]).first_line<<": "<<"Warning: possible loss of data in assignment of FLOAT to INT \n";
		}
		
	}
#line 3249 "y.tab.c"
    break;

  case 50: /* expression: error  */
#line 1676 "2005013.y"
        {
		yyclearin;
		yyerrok;

		Node* nd=new Node();
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("error");
		nd->setGrammar("syntax error");
		(yyval.intermediateNode)=nd;
		//outlog<<"Error at line no "<<$$->getStart()<<" : "<<$$->getGrammar()<<"\n";

	}
#line 3267 "y.tab.c"
    break;

  case 51: /* logic_expression: rel_expression  */
#line 1692 "2005013.y"
                {
			Node* nd=new Node();
			nd->setName("logic_expression");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[0].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("logic_expression : rel_expression ");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		}
#line 3284 "y.tab.c"
    break;

  case 52: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 1705 "2005013.y"
                {
			Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-1]).first_line);
		nd_lp->setEnd((yylsp[-1]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-1].symbolInfo));
				
		Node* nd=new Node();
		nd->setName("logic_expression");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		
		if((yyvsp[0].intermediateNode)->getTypeSpecifier()=="VOID" || (yyvsp[-2].intermediateNode)->getTypeSpecifier()=="VOID")
		nd->setTypeSpecifier("VOID");
		else 
		nd->setTypeSpecifier((yyvsp[-2].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("logic_expression : rel_expression LOGICOP rel_expression");
		nd->addChild((yyvsp[-2].intermediateNode));
		nd->addChild(nd_lp);
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		}
#line 3313 "y.tab.c"
    break;

  case 53: /* rel_expression: simple_expression  */
#line 1732 "2005013.y"
                {
			Node* nd=new Node();
			nd->setName("rel_expression");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[0].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("rel_expression : simple_expression ");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";	
		}
#line 3329 "y.tab.c"
    break;

  case 54: /* rel_expression: simple_expression RELOP simple_expression  */
#line 1744 "2005013.y"
                {
			Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-1]).first_line);
		nd_lp->setEnd((yylsp[-1]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-1].symbolInfo));
				
		Node* nd=new Node();
		nd->setName("rel_expression");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
	
		if((yyvsp[0].intermediateNode)->getTypeSpecifier()=="VOID" || (yyvsp[-2].intermediateNode)->getTypeSpecifier()=="VOID")
		nd->setTypeSpecifier("VOID");
		else 
		nd->setTypeSpecifier((yyvsp[-2].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("rel_expression : simple_expression RELOP simple_expression");
		nd->addChild((yyvsp[-2].intermediateNode));
		nd->addChild(nd_lp);
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		}
#line 3358 "y.tab.c"
    break;

  case 55: /* simple_expression: term  */
#line 1771 "2005013.y"
                {
			Node* nd=new Node();
			nd->setName("simple_expression");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[0].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("simple_expression : term");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";	
		}
#line 3374 "y.tab.c"
    break;

  case 56: /* simple_expression: simple_expression ADDOP term  */
#line 1783 "2005013.y"
                {
			Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-1]).first_line);
		nd_lp->setEnd((yylsp[-1]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-1].symbolInfo));
				
		Node* nd=new Node();
		nd->setName("simple_expression");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);

		if((yyvsp[0].intermediateNode)->getTypeSpecifier()=="VOID" || (yyvsp[-2].intermediateNode)->getTypeSpecifier()=="VOID")
		nd->setTypeSpecifier("VOID");
		else 
		nd->setTypeSpecifier((yyvsp[-2].intermediateNode)->getTypeSpecifier());

		nd->setGrammar("simple_expression : simple_expression ADDOP term");
		nd->addChild((yyvsp[-2].intermediateNode));
		nd->addChild(nd_lp);
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		}
#line 3404 "y.tab.c"
    break;

  case 57: /* term: unary_expression  */
#line 1811 "2005013.y"
        {
		Node* nd=new Node();
		nd->setName("term");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[0].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("term : unary_expression");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";	
	}
#line 3420 "y.tab.c"
    break;

  case 58: /* term: term MULOP unary_expression  */
#line 1823 "2005013.y"
    {
		Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-1]).first_line);
		nd_lp->setEnd((yylsp[-1]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-1].symbolInfo));
				
		Node* nd=new Node();
		nd->setName("term");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		if((yyvsp[0].intermediateNode)->getTypeSpecifier()=="VOID" || (yyvsp[-2].intermediateNode)->getTypeSpecifier()=="VOID")
		nd->setTypeSpecifier("VOID");
		else 
		nd->setTypeSpecifier((yyvsp[-2].intermediateNode)->getTypeSpecifier());

		nd->setGrammar("term : term MULOP unary_expression");
		nd->addChild((yyvsp[-2].intermediateNode));
		nd->addChild(nd_lp);
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		if(((yyvsp[-1].symbolInfo)->getName() == "%") && ((yyvsp[-2].intermediateNode)->getTypeSpecifier() != "INT" || (yyvsp[0].intermediateNode)->getTypeSpecifier() != "INT"))
		{
			errorcount++;
			outerror<<"Line# "<<(yylsp[-2]).first_line<<": Operands of modulous must be integers\n";
		}else if(((yyvsp[-1].symbolInfo)->getName() == "/" || (yyvsp[-1].symbolInfo)->getName() == "%") && ((yyvsp[0].intermediateNode)->getTypeSpecifier() == "INT" && (yyvsp[0].intermediateNode)->isZero()))
		{
			errorcount++;
			outerror<<"Line# "<<(yylsp[-2]).first_line<<": Warning: division by zero i=0f=1Const=0\n";
		}
	}
#line 3458 "y.tab.c"
    break;

  case 59: /* unary_expression: ADDOP unary_expression  */
#line 1859 "2005013.y"
                {
		Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-1]).first_line);
		nd_lp->setEnd((yylsp[-1]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-1].symbolInfo));
				
		Node* nd=new Node();
		nd->setName("unary_expression");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[0].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("unary_expression : ADDOP unary_expression ");
		nd->addChild(nd_lp);
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		}
#line 3482 "y.tab.c"
    break;

  case 60: /* unary_expression: NOT unary_expression  */
#line 1879 "2005013.y"
                {
			Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-1]).first_line);
		nd_lp->setEnd((yylsp[-1]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-1].symbolInfo));
				
		Node* nd=new Node();
		nd->setName("unary_expression");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[0].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("unary_expression : NOT unary_expression ");
		nd->addChild(nd_lp);
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		}
#line 3506 "y.tab.c"
    break;

  case 61: /* unary_expression: factor  */
#line 1899 "2005013.y"
                {
				Node* nd=new Node();
		nd->setName("unary_expression");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[0].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("unary_expression : factor");
		nd->addChild((yyvsp[0].intermediateNode));
		if((yyvsp[0].intermediateNode)->isZero()){
			nd->setZero();
		}
		// //<<nd->isZero()<<" una zerozero\n";
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		}
#line 3527 "y.tab.c"
    break;

  case 62: /* factor: variable  */
#line 1918 "2005013.y"
        {
		Node* nd=new Node();
		nd->setName("factor");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[0].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("factor : variable");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
	}
#line 3543 "y.tab.c"
    break;

  case 63: /* factor: ID LPAREN argument_list RPAREN  */
#line 1930 "2005013.y"
        {
		Node* nd_id=new Node();
		nd_id->setStart((yylsp[-3]).first_line);
		nd_id->setEnd((yylsp[-3]).last_line);
		//nd_id->setName($1->getName());
		nd_id->setTypeSpecifier((yyvsp[-3].symbolInfo)->getType());
		nd_id->setSymbolInfo((yyvsp[-3].symbolInfo));
		nd_id->setGrammar((yyvsp[-3].symbolInfo)->getType()+" : "+(yyvsp[-3].symbolInfo)->getName());

		Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-2]).first_line);
		nd_lp->setEnd((yylsp[-2]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-2].symbolInfo));

		Node* nd_rp=new Node();
		nd_rp->setStart((yylsp[0]).first_line);
		nd_rp->setEnd((yylsp[0]).last_line);
		nd_rp->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_rp->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_rp->setSymbolInfo((yyvsp[0].symbolInfo));
				Node* nd=new Node();
		nd->setName("factor");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("factor");
		nd->setGrammar("factor  : ID LPAREN argument_list RPAREN");
		
		SymbolInfo* cmp=sTable->LookUp((yyvsp[-3].symbolInfo)->getName());
		if(cmp==NULL || cmp->getInherentType()=="variable"){
			errorcount++;
			outerror<< "Line# " << (yylsp[-3]).first_line << ": " << "Undeclared function '" << (yyvsp[-3].symbolInfo)->getName() << "'\n";

		}else if(cmp->getInherentType()=="func_def" || cmp->getInherentType()=="func_decl"){
			vector<pair<string,string>> prev=cmp->getParams();
			if(prev.size()<argsOfFunction.size()){
				errorcount++;
				outerror << "Line# " << (yylsp[-3]).first_line << ": Too many arguments to function '" << (yyvsp[-3].symbolInfo)->getName() << "'\n";

			}else if(prev.size()>argsOfFunction.size()){
				errorcount++;
				outerror << "Line# " << (yylsp[-3]).first_line << ": Too few arguments to function '" << (yyvsp[-3].symbolInfo)->getName() << "'\n";

			}else{
				for(int i=0;i<prev.size();i++){
					if(prev[i].second==argsOfFunction[i]){
						continue;
					}
					// //<<prev[i]<<" "<<argsOfFunction[i]<<"\n";
					errorcount++;
					outerror << "Line# " << (yylsp[-3]).first_line << ": Type mismatch for argument " << i+1 << " of '" << (yyvsp[-3].symbolInfo)->getName() << "'\n"; 

				}
			}
			nd->setTypeSpecifier(cmp->getRettypeOrArrayType());
			
			// //<<nd->getTypeSpecifier()<<" "<<cmp->getName()<<" ttsf\n";
		}
		argsOfFunction.clear();
		nd->addChild(nd_id);
		nd->addChild(nd_lp);
		nd->addChild((yyvsp[-1].intermediateNode));
		nd->addChild(nd_rp);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		

	}
#line 3617 "y.tab.c"
    break;

  case 64: /* factor: LPAREN expression RPAREN  */
#line 2000 "2005013.y"
        {
		
		Node* nd_lp=new Node();
		nd_lp->setStart((yylsp[-2]).first_line);
		nd_lp->setEnd((yylsp[-2]).last_line);
		nd_lp->setTypeSpecifier((yyvsp[-2].symbolInfo)->getType());
		nd_lp->setGrammar((yyvsp[-2].symbolInfo)->getType()+" : "+(yyvsp[-2].symbolInfo)->getName());
		nd_lp->setSymbolInfo((yyvsp[-2].symbolInfo));

		Node* nd_rp=new Node();
		nd_rp->setStart((yylsp[0]).first_line);
		nd_rp->setEnd((yylsp[0]).last_line);
		nd_rp->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_rp->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_rp->setSymbolInfo((yyvsp[0].symbolInfo));
				
		Node* nd=new Node();
		nd->setName("factor");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[-1].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("factor  : LPAREN expression RPAREN");
		nd->addChild(nd_lp);
		nd->addChild((yyvsp[-1].intermediateNode));
		nd->addChild(nd_rp);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
	}
#line 3650 "y.tab.c"
    break;

  case 65: /* factor: CONST_INT  */
#line 2029 "2005013.y"
        {
		Node* nd_int=new Node();
		nd_int->setStart((yylsp[0]).first_line);
		nd_int->setEnd((yylsp[0]).last_line);
		nd_int->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_int->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_int->setSymbolInfo((yyvsp[0].symbolInfo));
		
				Node* nd=new Node();
		nd->setName("factor");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("INT");
		nd->setGrammar("factor  : CONST_INT");
		if((yyvsp[0].symbolInfo)->getName()=="0"){
			nd_int->setZero();
			nd->setZero();
		}
		//<<nd->isZero()<<" zerozero\n";
		nd->addChild(nd_int);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		
	}
#line 3679 "y.tab.c"
    break;

  case 66: /* factor: CONST_FLOAT  */
#line 2054 "2005013.y"
        {
		Node* nd_fl=new Node();
		nd_fl->setStart((yylsp[0]).first_line);
		nd_fl->setEnd((yylsp[0]).last_line);
		nd_fl->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_fl->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_fl->setSymbolInfo((yyvsp[0].symbolInfo));
				Node* nd=new Node();
		nd->setName("factor");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("FLOAT");
		nd->setGrammar("factor  : CONST_FLOAT");
		nd->addChild(nd_fl);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

	}
#line 3702 "y.tab.c"
    break;

  case 67: /* factor: variable INCOP  */
#line 2073 "2005013.y"
        {
				Node* nd_inc=new Node();
		nd_inc->setStart((yylsp[0]).first_line);
		nd_inc->setEnd((yylsp[0]).last_line);
		nd_inc->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_inc->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_inc->setSymbolInfo((yyvsp[0].symbolInfo));		
				Node* nd=new Node();
		nd->setName("factor");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[-1].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("factor  : variable INCOP");
		nd->addChild((yyvsp[-1].intermediateNode));
		nd->addChild(nd_inc);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

	}
#line 3726 "y.tab.c"
    break;

  case 68: /* factor: variable DECOP  */
#line 2093 "2005013.y"
        {
		Node* nd_dec=new Node();
		nd_dec->setStart((yylsp[0]).first_line);
		nd_dec->setEnd((yylsp[0]).last_line);
		nd_dec->setTypeSpecifier((yyvsp[0].symbolInfo)->getType());
		nd_dec->setGrammar((yyvsp[0].symbolInfo)->getType()+" : "+(yyvsp[0].symbolInfo)->getName());
		nd_dec->setSymbolInfo((yyvsp[0].symbolInfo));		
				Node* nd=new Node();
		nd->setName("factor");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier((yyvsp[-1].intermediateNode)->getTypeSpecifier());
		nd->setGrammar("factor  : variable DECOP");
		nd->addChild((yyvsp[-1].intermediateNode));
		nd->addChild(nd_dec);
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

	}
#line 3750 "y.tab.c"
    break;

  case 69: /* argument_list: arguments  */
#line 2115 "2005013.y"
                {
			Node* nd=new Node();
		nd->setName("argument_list");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("argument_list");
		nd->setGrammar("argument_list : arguments");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		}
#line 3766 "y.tab.c"
    break;

  case 70: /* argument_list: %empty  */
#line 2127 "2005013.y"
                {
		Node* nd=new Node();
		nd->setName("argument_list");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("argument_list");
		nd->setGrammar("argument_list : ");
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		}
#line 3782 "y.tab.c"
    break;

  case 71: /* arguments: arguments COMMA logic_expression  */
#line 2141 "2005013.y"
                {
			Node* nd_com=new Node();
		nd_com->setStart((yylsp[-1]).first_line);
		nd_com->setEnd((yylsp[-1]).last_line);
		nd_com->setTypeSpecifier((yyvsp[-1].symbolInfo)->getType());
		nd_com->setGrammar((yyvsp[-1].symbolInfo)->getType()+" : "+(yyvsp[-1].symbolInfo)->getName());
		nd_com->setSymbolInfo((yyvsp[-1].symbolInfo));
				
		Node* nd=new Node();
		nd->setName("arguments");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("arguments");
		nd->setGrammar("arguments : arguments COMMA logic_expression");
		nd->addChild((yyvsp[-2].intermediateNode));
		nd->addChild(nd_com);
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";

		argsOfFunction.push_back((yyvsp[0].intermediateNode)->getTypeSpecifier());
		
			
		}
#line 3811 "y.tab.c"
    break;

  case 72: /* arguments: logic_expression  */
#line 2166 "2005013.y"
                {
		Node* nd=new Node();
		nd->setName("arguments");
		nd->setStart((yyloc).first_line);
		nd->setEnd((yyloc).last_line);
		nd->setTypeSpecifier("arguments");
		nd->setGrammar("arguments : logic_expression");
		nd->addChild((yyvsp[0].intermediateNode));
		(yyval.intermediateNode)=nd;
		outlog<<(yyval.intermediateNode)->getGrammar()<<"\n";
		argsOfFunction.push_back((yyvsp[0].intermediateNode)->getTypeSpecifier());
		// //<<$1->getTypeSpecifier()<<" types\n";
		}
#line 3829 "y.tab.c"
    break;


#line 3833 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2182 "2005013.y"

int main(int argc,char *argv[])
{

if(argc != 2){
        outlog<<"Please provide input file name and try again."<<endl;
        return 0;
    }

    FILE *fin = freopen(argv[1], "r", stdin);
    if(fin == nullptr){
        outlog<<"Can't open specified file."<<endl;
        return 0;
    }

    outlog<<argv[1]<<" opened successfully."<<endl;
	outlog.open("log.txt");
	outtree.open("parsetree.txt");
	outerror.open("error.txt");
	outasm.open("code.asm");
	sTable=new SymbolTable(11);

    yyin = fin;

    yylineno = 1;


	yyparse();
	root->printAssemblyCode(outasm);
	outlog<<"Total lines: "<<linecount<<"\n"; 
	outlog<<"Total errors: "<<errorcount<<"\n";
	outasm.close();
	ifstream noopt("code.asm");
	ofstream opt("optimized_code.asm");
	optimizeCode(noopt,opt);
	cout<<"opt done\n";
	outlog.close();
	outerror.close();
	outtree.close();
	
	noopt.close();
	opt.close();

    fclose(yyin);
    return 0;
}

