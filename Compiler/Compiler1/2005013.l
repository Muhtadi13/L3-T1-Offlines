%option noyywrap
%x SINGLECOMMENTBEGIN
%x MULTICOMMENTBEGIN
%x STRINGBEGIN

%{
#include "2005013_SymbolTable.cpp"
#include "2005013_functions.cpp"

SymbolTable sTable(10);
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
allchar {specialchar}|[^\\\'(\r?\n)]
emptychar \'\'
unfinishedchar \'({allchar}|\\)?
charlit \'{allchar}\'
manychar \'{allchar}{2,}\'

allsinglecommentchars ([^\\(\r?\n)]|[\\]{newline}|{specialchar})
allcharsinstrings ([^\\\"(\r?\n)]|[\\]{newline}|{specialchar})
allmulticommentchars ([^\*]|([\*]+[^\*\/]))

stringstart \"
stringend \"
singlecommentstart \/\/
multicommentstart \/\*
multicommentend \*\/


%%
<INITIAL><<EOF>> {
	return 0;
}
{newline} { 
	linecount++;
	cntf=0;
	cntw=0;
	cntt=0;
	cntv=0;	
	islinestart=true;
}
^[ \t\v\f]* {
	string tmp=string(yytext);
	cntw=count(tmp.begin(),tmp.end(),' ');
	cntt=count(tmp.begin(),tmp.end(),'\t');
	cntv=count(tmp.begin(),tmp.end(),'\v');
	cntf=count(tmp.begin(),tmp.end(),'\f');

}
{space} {}
"if"      | 
"else"    | 
"for"     |
"while"   |
"do"      |
"break"   | 
"int"     |
"char"    |
"float"   |
"double"  | 
"void"    |
"return"  |
"switch"  |
"case"    |
"default" |
"continue" {
	showWarning();	
	string down=string(yytext);
	string up=makeUpperString(down);
	outlog<<"Line# "<<linecount<<": Token <"<<up<<"> Lexeme "<<down<<" found"<<"\n";
	outtoken<<"<"<<up<<", "<<down<<">"<<"\n";
}

("+"|"-")							{showWarning();outlog<<"Line# "<<linecount<<": Token <ADDOP> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<ADDOP, "<<yytext<<">"<<"\n";}
("++"|"--")							{showWarning();outlog<<"Line# "<<linecount<<": Token <INCOP> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<INCOP, "<<yytext<<">"<<"\n";}
("<="|">="|"=="|"!="|"<"|">") 		{showWarning();outlog<<"Line# "<<linecount<<": Token <RELOP> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<RELOP, "<<yytext<<">"<<"\n";}
("*"|"/"|"%")						{showWarning();outlog<<"Line# "<<linecount<<": Token <MULOP> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<MULOP, "<<yytext<<">"<<"\n";}
("&"|"|"|"^"|"<<"|">>")				{showWarning();outlog<<"Line# "<<linecount<<": Token <BITOP> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<BITOP, "<<yytext<<">"<<"\n";}
("&&"|"||")							{showWarning();outlog<<"Line# "<<linecount<<": Token <LOGICOP> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<LOGICOP, "<<yytext<<">"<<"\n";}
("=")								{showWarning();outlog<<"Line# "<<linecount<<": Token <ASSIGNOP> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<ASSIGNOP, "<<yytext<<">"<<"\n";}
"!"									{showWarning();outlog<<"Line# "<<linecount<<": Token <NOT> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<NOT, "<<yytext<<">"<<"\n";}
"("									{showWarning();outlog<<"Line# "<<linecount<<": Token <LPAREN> Lexeme "<<yytext<<" found"<<"\n";    	outtoken<<"<LPAREN, "<<yytext<<">"<<"\n";}
")"									{showWarning();outlog<<"Line# "<<linecount<<": Token <RPAREN> Lexeme "<<yytext<<" found"<<"\n";    	outtoken<<"<RPAREN, "<<yytext<<">"<<"\n";}
"{"									{showWarning();
									tabcount++;
									cntt=tabcount;
									sTable.enterScope();
									outlog<<"Line# "<<linecount<<": Token <LCURL> Lexeme "<<yytext<<" found"<<"\n";    	outtoken<<"<LCURL, "<<yytext<<">"<<"\n";}
"}"									{tabcount--;
									showWarning();
									sTable.exitScope();
									outlog<<"Line# "<<linecount<<": Token <RCURL> Lexeme "<<yytext<<" found"<<"\n";    	outtoken<<"<RCURL, "<<yytext<<">"<<"\n";}
"["									{showWarning();outlog<<"Line# "<<linecount<<": Token <LSQUARE> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<LSQUARE, "<<yytext<<">"<<"\n";}
"]"									{showWarning();outlog<<"Line# "<<linecount<<": Token <RSQUARE> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<RSQUARE, "<<yytext<<">"<<"\n";}
","									{showWarning();outlog<<"Line# "<<linecount<<": Token <COMMA> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<COMMA, "<<yytext<<">"<<"\n";}
";"									{showWarning();outlog<<"Line# "<<linecount<<": Token <SEMICOLON> Lexeme "<<yytext<<" found"<<"\n";    outtoken<<"<SEMICOLON, "<<yytext<<">"<<"\n";}

{integer} {
	showWarning();
	outlog<<"Line# "<<linecount<<": Token <CONST_INT> Lexeme "<<yytext<<" found\n";
	outtoken<<"<CONST_INT, "<<yytext<<">"<<"\n";
	
}
{float} {
	showWarning();
	outlog<<"Line# "<<linecount<<": Token <CONST_FLOAT> Lexeme "<<yytext<<" found\n";
	outtoken<<"<CONST_FLOAT, "<<yytext<<">"<<"\n";
		
}
{identifier} {
	showWarning();
	bool success=sTable.Insert(string(yytext),"ID");
	outlog<<"Line# "<<linecount<<": Token <ID> Lexeme "<<yytext<<" found\n";
	outtoken<<"<ID, "<<yytext<<">"<<"\n";
	if(success){
	sTable.printAllTables(outlog);
	}else{
		outlog<<"\t"<<yytext<<" already exists in the current ScopeTable\n";
	}
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
	replaceString(cur,"\\\r\n","");
	replaceString(cur,"\\\n","");
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
	string cur=ans;
	replaceString(cur,"\\\r\n","");
	replaceString(cur,"\\\n","");
	BEGIN(INITIAL);
}

<MULTICOMMENTBEGIN><<EOF>> {
	errorcount++;
	linecount+=count(ans.begin(),ans.end(),'\n');
	outlog<<"Error at line# "<<linecount<<": UNFINISHED_COMMENT "<<ans<<"\n";
	return 0;
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
	string cur = replaceAllSpecialCharacter(ans);
	replaceString(cur,"\\\r\n","");
	replaceString(cur,"\\\n","");
	replaceBegin(cur,"\"","");
	replaceEnd(cur,"\"","");
	if(bscnt==0){
	outlog<<"Line# "<<linecount-bscnt<<": Token <SINGLE LINE STRING> Lexeme "<<ans<<" found\n";
	outtoken<<"<SINGLE LINE STRING, "<<cur<<">"<<"\n";
	}
	else{
		outlog<<"Line# "<<linecount-bscnt<<": Token <MULTI LINE STRING> Lexeme "<<ans<<" found\n";
	    outtoken<<"<MULTI LINE STRING, "<<cur<<">"<<"\n";

	}
	BEGIN(INITIAL);}


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
	return 0;
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
	outtoken<<"<CONST_CHAR, "<<cur<<">"<<"\n";
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

int main(int argc,char *argv[]){
	
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
	outtoken.open("2005013_token.txt");
	yyin= fin;
	yylex();
	fclose(yyin);
	sTable.printAllTables(outlog);
	outlog<<"Total lines: "<<linecount<<"\n"; 
	outlog<<"Total errors: "<<errorcount<<"\n";
	outlog<<"Total warnings: "<<warningcount<<"\n";
	outlog.close();
	outtoken.close();
	return 0;
}
