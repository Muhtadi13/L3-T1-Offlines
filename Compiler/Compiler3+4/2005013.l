%option noyywrap
%option yylineno
%x SINGLECOMMENTBEGIN
%x MULTICOMMENTBEGIN
%x STRINGBEGIN

%{
#include "2005013_SymbolInfo.h"
#include "2005013_functions.h"
#include "2005013_Node.h"
#include "y.tab.hpp"


int yycolumn = 1;
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
 yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
 yycolumn += yyleng;

extern ofstream outlog;
string ans;


%}

space [ \t\v\f]+
newline \r?\n
letter [a-zA-Z]
letter_ {letter}|_
digit [0-9]
alphanum {letter_}|{digit}
identifier {letter_}{alphanum}*
integer {digit}+
prefixnum {integer}{identifier}

power ([eE][+-]?{integer})
float {integer}\.{integer}{power}?|\.{integer}|{integer}{power}
manydecimalpoint {integer}*((\.)*{integer}){2,}{power}? 
illnum {integer}(\.{integer})?[eE][+-]?{integer}*\.{integer} 


specialchar \\[nt'"afrbv0]|\\\\
allchar {specialchar}|[^\\\'\r\n]
emptychar \'\'
unfinishedchar \'({allchar}|\\)?
charlit \'{allchar}\'
manychar \'{allchar}{2,}\'

allsinglecommentchars ([^\\\r\n]|[\\]{newline}|{specialchar})
/* allcharsinstrings ([^\\\"(\r?\n)]|[\\]{newline}|{specialchar}) i changed this later*/
allcharsinstrings ([^\\\"\r\n]|[\\]{newline}|{specialchar})
allmulticommentchars ([^\*]|([\*]+[^\*\/]))

stringstart \"
stringend \"
singlecommentstart \/\/
multicommentstart \/\*
multicommentend \*\/


%%
<INITIAL><<EOF>> {
	return END_OF_FILE;
}
{newline} { 
	linecount++;
	cntf=0;
	cntw=0;
	cntt=0;
	cntv=0;	
	islinestart=true;
	yycolumn=1;
}
^[ \t\v\f]* {
	string tmp=string(yytext);
	cntw=count(tmp.begin(),tmp.end(),' ');
	cntt=count(tmp.begin(),tmp.end(),'\t');
	cntv=count(tmp.begin(),tmp.end(),'\v');
	cntf=count(tmp.begin(),tmp.end(),'\f');

}
{space} {}
"if"      {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType(up);
	yylval.symbolInfo=sinfo;
	return IF;
} 
"else"    {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
			SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType(up);
	yylval.symbolInfo=sinfo;
	return ELSE;
} 
"for"     {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
			SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType(up);
	yylval.symbolInfo=sinfo;
	return FOR;
}
"while"   {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
			SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType(up);
	yylval.symbolInfo=sinfo;
	return WHILE;
}
"do"      {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
	//return DO;
}
"break"   {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
	//return BREAK;
} 
"int"     {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
			SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType(up);
	yylval.symbolInfo=sinfo;
	return INT;
}
"char"    {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
	//return CHAR;
}
"float"   {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
			SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType(up);
	yylval.symbolInfo=sinfo;
	return FLOAT;
}
"double"  {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
	//return DOUBLE;
} 
"void"    {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
			SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType(up);
	yylval.symbolInfo=sinfo;
	return VOID;
}
"return"  {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
		SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType(up);
	yylval.symbolInfo=sinfo;
	
	return RETURN;
}
"switch"  {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
	//return SWITCH;
}
"case"    {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
	//return CASE;
}
"default" {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
	//return DEFAULT;
}
"continue" {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
	//return CONTINUE;
}
"println" {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType(up);
	yylval.symbolInfo=sinfo;
	
	return PRINTLN;
}
"loop" {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	//outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType(up);
	yylval.symbolInfo=sinfo;
	
	return LOOP;
}

("+"|"-")	{
	showWarning();outlog<<"Line# "<<linecount<<": Token <ADDOP> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<ADDOP, "<<yytext<<">"<<"\n";
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("ADDOP");
	yylval.symbolInfo=sinfo;
	return ADDOP;
}
("++")	{
	showWarning();outlog<<"Line# "<<linecount<<": Token <INCOP> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<INCOP, "<<yytext<<">"<<"\n";
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("INCOP");
	yylval.symbolInfo=sinfo;
	return INCOP;
}
("--")	{
	showWarning();outlog<<"Line# "<<linecount<<": Token <DECOP> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<DECOP, "<<yytext<<">"<<"\n";
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("DECOP");
	yylval.symbolInfo=sinfo;
	return DECOP;
}

("<="|">="|"=="|"!="|"<"|">") 		{showWarning();outlog<<"Line# "<<linecount<<": Token <RELOP> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<RELOP, "<<yytext<<">"<<"\n"; */ */
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("RELOP");
	yylval.symbolInfo=sinfo;

	return RELOP;
}
("*"|"/"|"%")		{
	showWarning();outlog<<"Line# "<<linecount<<": Token <MULOP> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<MULOP, "<<yytext<<">"<<"\n";
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("MULOP");
	yylval.symbolInfo=sinfo;

	return MULOP;
}
("&"|"|"|"^"|"<<"|">>")	 {
	showWarning();outlog<<"Line# "<<linecount<<": Token <BITOP> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<BITOP, "<<yytext<<">"<<"\n";
//return BITOP;
}
("&&"|"||")		{
	showWarning();outlog<<"Line# "<<linecount<<": Token <LOGICOP> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<LOGICOP, "<<yytext<<">"<<"\n";
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("LOGICOP");
	yylval.symbolInfo=sinfo;

	return LOGICOP;
}
("=")		{
	showWarning();outlog<<"Line# "<<linecount<<": Token <ASSIGNOP> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<ASSIGNOP, "<<yytext<<">"<<"\n";
		SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("ASSIGNOP");
	yylval.symbolInfo=sinfo;
	return ASSIGNOP;
}
"!"			{
	showWarning();outlog<<"Line# "<<linecount<<": Token <NOT> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<NOT, "<<yytext<<">"<<"\n";
		SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("NOT");
	yylval.symbolInfo=sinfo;
return NOT;
}
"("   {
	showWarning();outlog<<"Line# "<<linecount<<": Token <LPAREN> Lexeme "<<yytext<<" found"<<"\n";    	//outtoken<<"<LPAREN, "<<yytext<<">"<<"\n";

		SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("LPAREN");
	yylval.symbolInfo=sinfo;
	return LPAREN;
}
")"		{
	showWarning();outlog<<"Line# "<<linecount<<": Token <RPAREN> Lexeme "<<yytext<<" found"<<"\n";    	//outtoken<<"<RPAREN, "<<yytext<<">"<<"\n";
		SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("RPAREN");
	yylval.symbolInfo=sinfo;
return RPAREN;
}
"{"	{
	showWarning();
	tabcount++;
	cntt=tabcount;
	outlog<<"Line# "<<linecount<<": Token <LCURL> Lexeme "<<yytext<<" found"<<"\n";    	//outtoken<<"<LCURL, "<<yytext<<">"<<"\n";
			SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("LCURL");
	yylval.symbolInfo=sinfo;
	return LCURL;
}
"}"		{
	tabcount--;
	showWarning();
	outlog<<"Line# "<<linecount<<": Token <RCURL> Lexeme "<<yytext<<" found"<<"\n";    	//outtoken<<"<RCURL, "<<yytext<<">"<<"\n";
			SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("RCURL");
	yylval.symbolInfo=sinfo;
	return RCURL;
}
"["		{
	showWarning();outlog<<"Line# "<<linecount<<": Token <LSQUARE> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<LSQUARE, "<<yytext<<">"<<"\n";
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("LSQUARE");
	yylval.symbolInfo=sinfo;
return LTHIRD;
}
"]"		{
	showWarning();outlog<<"Line# "<<linecount<<": Token <RSQUARE> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<RSQUARE, "<<yytext<<">"<<"\n";
		SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("RSQUARE");
	yylval.symbolInfo=sinfo;
return RTHIRD;
}
","									{
	showWarning();outlog<<"Line# "<<linecount<<": Token <COMMA> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<COMMA, "<<yytext<<">"<<"\n";
		SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("COMMA");
	yylval.symbolInfo=sinfo;
return COMMA;
}
";"									{
	showWarning();outlog<<"Line# "<<linecount<<": Token <SEMICOLON> Lexeme "<<yytext<<" found"<<"\n";    //outtoken<<"<SEMICOLON, "<<yytext<<">"<<"\n";
		SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("SEMICOLON");
	yylval.symbolInfo=sinfo;
return SEMICOLON;
}

{integer} {
	showWarning();
	outlog<<"Line# "<<linecount<<": Token <CONST_INT> Lexeme "<<yytext<<" found\n";
	//outtoken<<"<CONST_INT, "<<yytext<<">"<<"\n";
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("CONST_INT");
	yylval.symbolInfo=sinfo;
	return CONST_INT;
}
{float} {
	showWarning();
	outlog<<"Line# "<<linecount<<": Token <CONST_FLOAT> Lexeme "<<yytext<<" found\n";
	//outtoken<<"<CONST_FLOAT, "<<yytext<<">"<<"\n";
		SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("CONST_FLOAT");
	yylval.symbolInfo=sinfo;

	return CONST_FLOAT;
}
{identifier} {
	showWarning();
	outlog<<"Line# "<<linecount<<": Token <ID> Lexeme "<<yytext<<" found\n";
	//outtoken<<"<ID, "<<yytext<<">"<<"\n";
	SymbolInfo* sinfo=new SymbolInfo();
	sinfo->setName(yytext);
	sinfo->setType("ID");
	yylval.symbolInfo=sinfo;

	return ID;
}

{singlecommentstart} {
	showWarning(); 
	ans.clear();
	ans.append(yytext);
	BEGIN(SINGLECOMMENTBEGIN);
}

<SINGLECOMMENTBEGIN>{newline} {
	string cur=ans;
	int bscnt=count(ans.begin(),ans.end(),'\n');
	// replaceString(cur,"\\\r\n","");
	// replaceString(cur,"\\\n","");
	outlog<<"Line# "<<linecount<<": Token <SINGLE LINE COMMENT> Lexeme "<<ans<<" found\n";
	linecount+=bscnt;
	linecount++;
	cntf=0;
	cntw=0;
	cntt=0;
	cntv=0;
	BEGIN(INITIAL);
}

<SINGLECOMMENTBEGIN>{allsinglecommentchars} {
	ans.append(yytext);
}
<SINGLECOMMENTBEGIN>\\ {
	ans.append(yytext);
}
{multicommentstart} { 
	showWarning();
	ans.clear();
	ans.append(yytext);
	BEGIN(MULTICOMMENTBEGIN);
}


<MULTICOMMENTBEGIN>[\*]*{multicommentend} {
	ans.append(yytext);
	outlog<<"Line# "<<linecount<<": Token <MULTI LINE COMMENT> Lexeme "<<ans<<" found\n";
	linecount+=count(ans.begin(),ans.end(),'\n');
	// string cur=ans;
	// replaceString(cur,"\\\r\n","");
	// replaceString(cur,"\\\n","");
	BEGIN(INITIAL);
}

<MULTICOMMENTBEGIN><<EOF>> {
	errorcount++;
	linecount+=count(ans.begin(),ans.end(),'\n');
	outlog<<"Error at line# "<<linecount<<": UNFINISHED_COMMENT "<<ans<<"\n";
	return END_OF_FILE;
}

<MULTICOMMENTBEGIN>{allmulticommentchars} {
	ans.append(yytext);
}

{stringstart} {
	showWarning();
	ans.clear();
	ans.append(yytext);
	BEGIN(STRINGBEGIN);
}
<STRINGBEGIN>{stringend} { 
	ans.append(yytext);
	int bscnt=count(ans.begin(),ans.end(),'\n');
	linecount+=bscnt;;
	// string cur = replaceAllSpecialCharacter(ans);
	// replaceString(cur,"\\\r\n","");
	// replaceString(cur,"\\\n","");
	// replaceBegin(cur,"\"","");
	// replaceEnd(cur,"\"","");
	if(bscnt==0){
	outlog<<"Line# "<<linecount-bscnt<<": Token <SINGLE LINE STRING> Lexeme "<<ans<<" found\n";
	//outtoken<<"<SINGLE LINE STRING, "<<cur<<">"<<"\n";
	}
	else{
		outlog<<"Line# "<<linecount-bscnt<<": Token <MULTI LINE STRING> Lexeme "<<ans<<" found\n";
	    //outtoken<<"<MULTI LINE STRING, "<<cur<<">"<<"\n";

	}
	BEGIN(INITIAL);
}


<STRINGBEGIN>{newline} {
	errorcount++;	
	linecount+=count(ans.begin(),ans.end(),'\n');	
	outlog<<"Error at line# "<<linecount<<": UNFINISHED_STRING "<<ans<<"\n";
	linecount++;				
	cntf=0;
	cntw=0;
	cntt=0;
	cntv=0;
  	BEGIN(INITIAL);
}
<STRINGBEGIN><<EOF>> {
	errorcount++;
	linecount+=count(ans.begin(),ans.end(),'\n');
	outlog<<"Error at line# "<<linecount<<": UNFINISHED_STRING "<<ans<<"\n";
	return END_OF_FILE;
}

<STRINGBEGIN>{allcharsinstrings} {
	ans.append(yytext);
}
<STRINGBEGIN>\\ {
	ans.append(yytext);
}

{charlit} {
	showWarning();
	string tmp=string(yytext);
	linecount+=count(tmp.begin(),tmp.end(),'\n');
	string cur=replaceAllSpecialCharacter(tmp);
	replaceBegin(cur,"\'","");
	replaceEnd(cur,"\'","");
	replaceString(cur,"\\\r\n","");
	replaceString(cur,"\\\n","");
	outlog<<"Line# "<<linecount<<": Token <CONST_CHAR> Lexeme "<<cur<<" found\n";
	//outtoken<<"<CONST_CHAR, "<<cur<<">"<<"\n";
}
{manydecimalpoint} {
	showWarning();
	errorcount++;
	outlog<<"Error at line# "<<linecount<<": TOO_MANY_DECIMAL_POINTS "<<yytext<<"\n";
}
{manychar} {
	showWarning();
	errorcount++;
	outlog<<"Error at line# "<<linecount<<": MULTICHAR_CONST_CHAR "<<yytext<<"\n";
}
{illnum} {
	showWarning();
	errorcount++;
	outlog<<"Error at line# "<<linecount<<": ILLFORMED_NUMBER "<<yytext<<"\n";
}
{prefixnum} {
	showWarning();
	errorcount++;
	outlog<<"Error at line# "<<linecount<<": INVALID_ID_SUFFIX_NUM_PREFIX "<<yytext<<"\n";
}
{emptychar} {
	showWarning();
	errorcount++;
	outlog<<"Error at line# "<<linecount<<": EMPTY_CONST_CHAR "<<yytext<<"\n";
}
{unfinishedchar} {
	showWarning();
	errorcount++;
	outlog<<"Error at line# "<<linecount<<": UNFINISHED_CONST_CHAR "<<yytext<<"\n";
}


. {
	showWarning();
	errorcount++;
	outlog<<"Error at line# "<<linecount<<": UNRECOGNIZED_CHAR "<<yytext<<"\n";
}
%%

/* int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	outlog.open("2005013_log.txt");
	//outtoken.open("2005013_token.txt");
	yyin= fin;
	yylex();
	fclose(yyin);
	sTable.printAllTables(outlog);
	outlog<<"Total lines: "<<linecount<<"\n"; 
	outlog<<"Total errors: "<<errorcount<<"\n";
	outlog<<"Total warnings: "<<warningcount<<"\n";
	outlog.close();
	//outtoken.close();
	return 0;
} */
