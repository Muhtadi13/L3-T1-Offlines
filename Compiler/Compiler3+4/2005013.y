//change declaration list

%{
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

%}

%union{
	Node *intermediateNode;
	SymbolInfo* symbolInfo;
}

%locations

%type<intermediateNode> start program unit func_declaration func_definition parameter_list compound_statement 
%type<intermediateNode> var_declaration type_specifier declaration_list statements statement expression_statement 
%type<intermediateNode> variable expression logic_expression rel_expression simple_expression term unary_expression 
%type<intermediateNode> factor argument_list arguments expression_list
%right <symbolInfo> ASSIGNOP
%left <symbolInfo> LOGICOP
%left  <symbolInfo> RELOP
%left  <symbolInfo> ADDOP
%left  <symbolInfo> MULOP
%right <symbolInfo> NOT
%right <symbolInfo> INCOP DECOP
%left <symbolInfo> RPAREN
%left <symbolInfo> ELSE

%token <symbolInfo> IF FOR WHILE RETURN PRINTLN LPAREN LCURL RCURL END_OF_FILE
%token <symbolInfo> LTHIRD RTHIRD COMMA SEMICOLON INT FLOAT VOID CONST_INT CONST_FLOAT ID LOOP
/* %left 
%right */

//%nonassoc 


%%

start : program
	{
		Node* nd=new Node();
		nd->setName("start");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("start");
		nd->setGrammar("start : program");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		root=$$;
		$$->print(0,outtree);

	}
	;

program : program unit 
	{
		Node* nd=new Node();
		nd->setName("program");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("program");
		nd->setGrammar("program : program unit");
		nd->addChild($1);
		nd->addChild($2);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		
	}
	| unit
	{
		Node* nd=new Node();
		nd->setName("program");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("program");
		nd->setGrammar("program : unit ");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
	}
	;
	
unit : var_declaration
	{
		Node* nd=new Node();
		nd->setName("unit");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("unit");
		nd->setGrammar("unit : var_declaration ");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
	}
    | func_declaration
	{
		Node* nd=new Node();
		nd->setName("unit");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("unit");
		nd->setGrammar("unit : func_declaration ");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";


	}
    | func_definition
	{
		Node* nd=new Node();
		nd->setName("unit");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("unit");
		nd->setGrammar("unit : func_definition ");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
	}
    ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
	{

				Node* nd_id=new Node();
		nd_id->setStart(@2.first_line);
		nd_id->setEnd(@2.last_line);
		//nd_id->setName($2->getName());
		nd_id->setTypeSpecifier($2->getType());
		nd_id->setSymbolInfo($2);
		
		//nd_id->setName($2->getName());
		nd_id->setGrammar($2->getType()+" : "+$2->getName());

				Node* nd_lp=new Node();
		nd_lp->setStart(@3.first_line);
		nd_lp->setEnd(@3.last_line);
		nd_lp->setTypeSpecifier($3->getType());
		nd_lp->setGrammar($3->getType()+" : "+$3->getName());
		nd_lp->setSymbolInfo($3);
				Node* nd_rp=new Node();
		nd_rp->setStart(@5.first_line);
		nd_rp->setEnd(@5.last_line);
		nd_rp->setTypeSpecifier($5->getType());
		nd_rp->setGrammar($5->getType()+" : "+$5->getName());
		nd_rp->setSymbolInfo($5);

				Node* nd_sc=new Node();
		nd_sc->setStart(@6.first_line);
		nd_sc->setEnd(@6.last_line);
		nd_sc->setTypeSpecifier($2->getType());
		nd_sc->setGrammar($6->getType()+" : "+$6->getName());
		nd_sc->setSymbolInfo($6);
				Node* nd=new Node();
		nd->setName("func_declaration");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("func_declaration");
		nd->setGrammar("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON ");
		nd->addChild($1);
		nd->addChild(nd_id);
		nd->addChild(nd_lp);
		nd->addChild($4);
		nd->addChild(nd_rp);
		nd->addChild(nd_sc);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		SymbolInfo* func=new SymbolInfo();
		func->setInherentType("func_decl");
		func->setRettypeOrArrayType($1->getTypeSpecifier());
		func->setType($2->getType());
		func->setName($2->getName());
		for(int i=0;i<paramsOfFunction.size();i++){
			func->addParam(paramsOfFunction[i]);
		}
		paramsOfFunction.clear();
		SymbolInfo* fnd=sTable->LookUp($2->getName());
		if(fnd==NULL){
			sTable->Insert(func);
			nd_id->setSymbolInfo(func);
		}
		else if(fnd->getInherentType()=="variable"){
			errorcount++;
			outerror << "Line# " << @2.first_line << ": " << "'" << $2->getName() << "' redeclared as different kind of symbol\n";
		}else if((fnd->getInherentType()=="func_def" || fnd->getInherentType()=="func_decl") && (!fnd->funcComp(func))){
			errorcount++;
			outerror << "Line# " << @2.first_line << ": " << "Conflicting types for '" << $2->getName() << "'\n";
		}
		

	
	}
	| type_specifier ID LPAREN RPAREN SEMICOLON
	{
						Node* nd_id=new Node();
		nd_id->setStart(@2.first_line);
		nd_id->setEnd(@2.last_line);
		//nd_id->setName($2->getName());
		nd_id->setTypeSpecifier($2->getType());
		nd_id->setSymbolInfo($2);
		nd_id->setGrammar($2->getType()+" : "+$2->getName());
				
				Node* nd_lp=new Node();
		nd_lp->setStart(@3.first_line);
		nd_lp->setEnd(@3.last_line);
		nd_lp->setTypeSpecifier($3->getType());
		nd_lp->setGrammar($3->getType()+" : "+$3->getName());
		nd_lp->setSymbolInfo($3);

				Node* nd_rp=new Node();
		nd_rp->setStart(@4.first_line);
		nd_rp->setEnd(@4.last_line);
		nd_rp->setTypeSpecifier($4->getType());
		nd_rp->setGrammar($4->getType()+" : "+$4->getName());
		nd_rp->setSymbolInfo($4);
			
				Node* nd_sc=new Node();
		nd_sc->setStart(@5.first_line);
		nd_sc->setEnd(@5.last_line);
		nd_sc->setTypeSpecifier($5->getType());
		nd_sc->setGrammar($5->getType()+" : "+$5->getName());
		nd_sc->setSymbolInfo($5);

		Node* nd=new Node();
		nd->setName("func_declaration");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("func_declaration");
		nd->setGrammar("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON ");
		nd->addChild($1);
		nd->addChild(nd_id);
		nd->addChild(nd_lp);
		nd->addChild(nd_rp);
		nd->addChild(nd_sc);
		$$=nd;
		SymbolInfo* func=new SymbolInfo();
		func->setInherentType("func_decl");
		func->setRettypeOrArrayType($1->getTypeSpecifier());
		func->setType($2->getType());
		func->setName($2->getName());

		outlog<<$$->getGrammar()<<"\n";
		//outlog<<$2->getName()<<"\n";
		SymbolInfo* fnd=sTable->LookUp($2->getName());
		
		if(fnd==NULL){
			sTable->Insert(func);
			nd_id->setSymbolInfo(func);
		}
		else if(fnd->getInherentType()=="variable"){
			errorcount++;
			outerror << "Line# " << @2.first_line << ": " << "'" << $2->getName() << "' redeclared as different kind of symbol\n";
		}else if((fnd->getInherentType()=="func_def" || fnd->getInherentType()=="func_decl") && (!fnd->funcComp(func))){
			errorcount++;
			outerror << "Line# " << @2.first_line << ": " << "Conflicting types for '" << $2->getName() << "'\n";
		}

		
	}
	;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
		{
				Node* nd_id=new Node();
		nd_id->setStart(@2.first_line);
		nd_id->setEnd(@2.last_line);
		//nd_id->setName($2->getName());
		nd_id->setTypeSpecifier($2->getType());
		nd_id->setSymbolInfo($2);
		
		nd_id->setGrammar($2->getType()+" : "+$2->getName());
				Node* nd_lp=new Node();
		nd_lp->setStart(@3.first_line);
		nd_lp->setEnd(@3.last_line);
		nd_lp->setTypeSpecifier($3->getType());
		nd_lp->setGrammar($3->getType()+" : "+$3->getName());
		nd_lp->setSymbolInfo($3);
				Node* nd_rp=new Node();
		nd_rp->setStart(@5.first_line);
		nd_rp->setEnd(@5.last_line);
		nd_rp->setTypeSpecifier($5->getType());
		nd_rp->setGrammar($5->getType()+" : "+$5->getName());
		nd_rp->setSymbolInfo($5);

		Node* nd=new Node();
		nd->setName("func_definition");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("func_definition");
		nd->setGrammar("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		nd->addChild($1);
		nd->addChild(nd_id);
		nd->addChild(nd_lp);
		nd->addChild($4);
		nd->addChild(nd_rp);
		nd->addChild($6);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		SymbolInfo* func=new SymbolInfo();
		func->setInherentType("func_def");
		func->setRettypeOrArrayType($1->getTypeSpecifier());
		func->setType($2->getType());
		func->setName($2->getName());
		for(int i=0;i<paramsOfFunction.size();i++){
			func->addParam(paramsOfFunction[i]);
		}
		paramsOfFunction.clear();
		SymbolInfo* fnd=sTable->LookUp($2->getName());
		if(fnd==NULL){
			sTable->Insert(func);
			nd_id->setSymbolInfo(func);
		}else if(fnd->getInherentType()=="variable"){
			errorcount++;
			outerror << "Line# " << @2.first_line << ": " << "'" << $2->getName() << "' redeclared as different kind of symbol\n";
		}else if(fnd->getInherentType()=="func_def"){
			//cout<<fnd->getInherentType()<<"jhgdsdf\n";
			errorcount++;
			outerror <<"Line# " << @2.first_line << ": " << "Multiple definition of '" << $2->getName() << "'\n";
		}else if((fnd->getInherentType()=="func_decl") && (!fnd->funcComp(func))){	
			errorcount++;
			outerror << "Line# " << @2.first_line << ": " << "Conflicting types for '" << $2->getName() << "'\n";
		}

		}
		| type_specifier ID LPAREN RPAREN compound_statement
		{
				Node* nd_id=new Node();
		nd_id->setStart(@2.first_line);
		nd_id->setEnd(@2.last_line);
		//nd_id->setName($2->getName());
		nd_id->setTypeSpecifier($2->getType());
		nd_id->setSymbolInfo($2);
		nd_id->setGrammar($2->getType()+" : "+$2->getName());
				
				Node* nd_lp=new Node();
		nd_lp->setStart(@3.first_line);
		nd_lp->setEnd(@3.last_line);
		nd_lp->setTypeSpecifier($3->getType());
		nd_lp->setGrammar($3->getType()+" : "+$3->getName());
		nd_lp->setSymbolInfo($2);

				Node* nd_rp=new Node();
		nd_rp->setStart(@4.first_line);
		nd_rp->setEnd(@4.last_line);
		nd_rp->setTypeSpecifier($4->getType());
		nd_rp->setGrammar($4->getType()+" : "+$4->getName());
		nd_rp->setSymbolInfo($4);

		Node* nd=new Node();
		nd->setName("func_definition");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("func_definition");
		nd->setGrammar("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
		nd->addChild($1);
		nd->addChild(nd_id);
		nd->addChild(nd_lp);
		nd->addChild(nd_rp);
		nd->addChild($5);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		SymbolInfo* func=new SymbolInfo();
		func->setInherentType("func_def");
		func->setRettypeOrArrayType($1->getTypeSpecifier());
		func->setType($2->getType());
		func->setName($2->getName());
		SymbolInfo* fnd=sTable->LookUp($2->getName());
		if(fnd==NULL){
			sTable->Insert(func);
			nd_id->setSymbolInfo(func);
		}
		else if(fnd->getInherentType()=="variable"){
			errorcount++;
			outerror << "Line# " << @2.first_line << ": " << "'" << $2->getName() << "' redeclared as different kind of symbol\n";
		}else if(fnd->getInherentType()=="func_def"){
			errorcount++;
			outerror <<"Line# " << @2.first_line << ": " << "Multiple definition of '" << $2->getName() << "'\n";
		} else if((fnd->getInherentType()=="func_decl") && (!fnd->funcComp(func))){
			// //<<fnd->getName()<<" "<<fnd->getParams().size()<<" "<<fnd->getInherentType()<<"jhgdsdf\n";
			errorcount++;
			outerror << "Line# " << @2.first_line << ": " << "Conflicting types for '" << $2->getName() << "'\n";
		}
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		{
					Node* nd_com=new Node();
		nd_com->setStart(@2.first_line);
		nd_com->setEnd(@2.last_line);
		nd_com->setTypeSpecifier($2->getType());
		nd_com->setGrammar($2->getType()+" : "+$2->getName());
		nd_com->setSymbolInfo($2);
				Node* nd_id=new Node();
		nd_id->setStart(@4.first_line);
		nd_id->setEnd(@4.last_line);
		//nd_id->setName($4->getName());
		nd_id->setTypeSpecifier($4->getType());
		nd_id->setGrammar($4->getType()+" : "+$4->getName());
		nd_id->setSymbolInfo($4);

		Node* nd=new Node();
		nd->setName("parameter_list");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("parameter_list");
		nd->setGrammar("parameter_list  : parameter_list COMMA type_specifier ID");
		nd->addChild($1);
		nd->addChild(nd_com);
		nd->addChild($3);
		nd->addChild(nd_id);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		paramsOfFunction.push_back({$4->getName(),$3->getTypeSpecifier()});

		}
		| parameter_list COMMA type_specifier
		{
								Node* nd_com=new Node();
		nd_com->setStart(@2.first_line);
		nd_com->setEnd(@2.last_line);
		nd_com->setTypeSpecifier($2->getType());
		nd_com->setGrammar($2->getType()+" : "+$2->getName());
		nd_com->setSymbolInfo($2);

		Node* nd=new Node();
		nd->setName("parameter_list");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("parameter_list");
		nd->setGrammar("parameter_list  : parameter_list COMMA type_specifier");
		nd->addChild($1);
		nd->addChild(nd_com);
		nd->addChild($3);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		paramsOfFunction.push_back({"NN",$3->getTypeSpecifier()});

		}
 		| type_specifier ID
		{

				Node* nd_id=new Node();
		nd_id->setStart(@2.first_line);
		nd_id->setEnd(@2.last_line);
		//nd_id->setName($2->getName());
		nd_id->setTypeSpecifier($2->getType());
		nd_id->setSymbolInfo($2);
		
		nd_id->setGrammar($2->getType()+" : "+$2->getName());

		Node* nd=new Node();
		nd->setName("parameter_list");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("parameter_list");
		nd->setGrammar("parameter_list  : type_specifier ID");
		nd->addChild($1);
		nd->addChild(nd_id);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		paramsOfFunction.push_back({$2->getName(),$1->getTypeSpecifier()});
		}
		| type_specifier
		{
					Node* nd=new Node();
		nd->setName("parameter_list");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("parameter_list");
		nd->setGrammar("parameter_list  : type_specifier");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		paramsOfFunction.push_back({"NN",$1->getTypeSpecifier()});

		}
		|
		error
		{
			yyclearin;
			yyerrok;

			Node* nd=new Node();
			nd->setName("parameter_list");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("parameter_list");
			nd->setGrammar("syntax error");
			$$=nd;

			//outlog<<"Error at line no "<<$$->getStart()<<" : "<<$$->getGrammar()<<"\n";
			

		}
 		;

 		
compound_statement : LCURL{
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
					outerror<<"Line# "<<@1.first_line<<": "<<"Redefinition of parameter '"<<sinfo->getName()<<"'\n";
				}
			}


		} 
		statements RCURL
		{
			Node* nd_lc=new Node();
		nd_lc->setStart(@1.first_line);
		nd_lc->setEnd(@1.last_line);
		nd_lc->setTypeSpecifier($1->getType());
		nd_lc->setGrammar($1->getType()+" : "+$1->getName());
		nd_lc->setSymbolInfo($1);

		Node* nd_rc=new Node();
		nd_rc->setStart(@4.first_line);
		nd_rc->setEnd(@4.last_line);
		nd_rc->setTypeSpecifier($4->getType());
		nd_rc->setGrammar($4->getType()+" : "+$4->getName());
		nd_rc->setSymbolInfo($4);


		Node* nd=new Node();
		nd->setName("compound_statement");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("compound_statement");
		nd->setGrammar("compound_statement : LCURL statements RCURL");
		nd->addChild(nd_lc);
		nd->addChild($3);
		nd->addChild(nd_rc);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		sTable->printAllTables(outlog);

		sTable->exitScope();

				
		}
		| LCURL RCURL
		{
				Node* nd_lc=new Node();
		nd_lc->setStart(@1.first_line);
		nd_lc->setEnd(@1.last_line);
		nd_lc->setTypeSpecifier($1->getType());
		nd_lc->setGrammar($1->getType()+" : "+$1->getName());
		nd_lc->setSymbolInfo($1);

		Node* nd_rc=new Node();
		nd_rc->setStart(@2.first_line);
		nd_rc->setEnd(@2.last_line);
		nd_rc->setTypeSpecifier($2->getType());
		nd_rc->setGrammar($2->getType()+" : "+$2->getName());
		nd_rc->setSymbolInfo($2);

		Node* nd=new Node();
		nd->setName("compound_statement");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("compound_statement");
		nd->setGrammar("compound_statement : LCURL RCURL");
		nd->addChild(nd_lc);
		nd->addChild(nd_rc);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		sTable->enterScope();
		sTable->printAllTables(outlog);
		sTable->exitScope();

		}
		;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
 		 {
				
		Node* nd_sc=new Node();
		nd_sc->setStart(@3.first_line);
		nd_sc->setEnd(@3.last_line);
		nd_sc->setTypeSpecifier($3->getType());
		nd_sc->setGrammar($3->getType()+" : "+$3->getName());
		nd_sc->setSymbolInfo($3);

		Node* nd=new Node();
		nd->setName("var_declaration");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("var_declaration");
		nd->setGrammar("var_declaration : type_specifier declaration_list SEMICOLON");
		nd->addChild($1);
		nd->addChild($2);
		nd->addChild(nd_sc);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		SymbolInfo *declarationSymbol=new SymbolInfo();
		declarationSymbol->setName("declaration_list");
	
		for(int i=0;i<varNameTypeSz.size();i++){
			SymbolInfo *sinfo=new SymbolInfo();
			sinfo->setName(varNameTypeSz[i].first.first);
			sinfo->setType($1->getTypeSpecifier());
			sinfo->setInherentType("variable");
			sinfo->setArraySize(varNameTypeSz[i].second);
			sinfo->setRettypeOrArrayType($1->getTypeSpecifier());
			//nd->addVar(varNameTypeSz[i]);
			SymbolInfo* cmp=sTable->getCurrentScopeTable()->Lookup(sinfo->getName());
			if($1->getTypeSpecifier()=="VOID"){
				errorcount++;
				outerror<<"Line# "<<@$.first_line<<": "<<"Variable or field '"<<sinfo->getName()<<"'declared void \n";
			}else if(cmp==NULL){
				sTable->Insert(sinfo);
				declarationSymbol->addVar(varNameTypeSz[i]);
			}else{
				// //<<cmp->getName()<<" "<<cmp->getRettypeOrArrayType()<<"\n";
				errorcount++;
				outerror<<"Line# "<<@$.first_line<<": "<<"Conflicting types for '"<<sinfo->getName()<<"'\n";
			}
			
	
		}
		$2->setSymbolInfo(declarationSymbol);
		varNameTypeSz.clear();

		}
		;
 		 
type_specifier	: INT
		{
			Node* nd_int=new Node();
		nd_int->setStart(@1.first_line);
		nd_int->setEnd(@1.last_line);
		nd_int->setTypeSpecifier($1->getType());
		nd_int->setGrammar($1->getType()+" : "+$1->getName());
		nd_int->setSymbolInfo($1);
				
				Node* nd=new Node();
		nd->setName("type_specifier");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("INT");
		nd->setGrammar("type_specifier	: INT");
		nd->addChild(nd_int);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		}
 		| FLOAT
		{
			Node* nd_fl=new Node();
		nd_fl->setStart(@1.first_line);
		nd_fl->setEnd(@1.last_line);
		nd_fl->setTypeSpecifier($1->getType());
		nd_fl->setGrammar($1->getType()+" : "+$1->getName());
		nd_fl->setSymbolInfo($1);
				Node* nd=new Node();
		nd->setName("type_specifier");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("FLOAT");
		nd->setGrammar("type_specifier	: FLOAT");
		nd->addChild(nd_fl);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		}
 		| VOID
		{
			Node* nd_vd=new Node();
		nd_vd->setStart(@1.first_line);
		nd_vd->setEnd(@1.last_line);
		nd_vd->setTypeSpecifier($1->getType());
		nd_vd->setGrammar($1->getType()+" : "+$1->getName());
		nd_vd->setSymbolInfo($1);
				Node* nd=new Node();
		nd->setName("type_specifier");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("VOID");
		nd->setGrammar("type_specifier	: VOID");
		nd->addChild(nd_vd);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		}
 		;
 		
declaration_list : declaration_list COMMA ID
			{
					Node* nd_com=new Node();
			nd_com->setStart(@2.first_line);
			nd_com->setEnd(@2.last_line);
			nd_com->setTypeSpecifier($2->getType());
			nd_com->setGrammar($2->getType()+" : "+$2->getName());
			nd_com->setSymbolInfo($2);
			Node* nd_id=new Node();

			nd_id->setStart(@3.first_line);
			nd_id->setEnd(@3.last_line);
			$3->setInherentType("variable");
			nd_id->setTypeSpecifier($3->getType());
			nd_id->setSymbolInfo($3);
			nd_id->setGrammar($3->getType()+" : "+$3->getName());
			nd_id->setSymbolInfo($3);

			Node* nd=new Node();
			nd->setName("declaration_list");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("declaration_list");
			nd->setGrammar("declaration_list : declaration_list COMMA ID");
			nd->addChild($1);
			nd->addChild(nd_com);
			nd->addChild(nd_id);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";

			varNameTypeSz.push_back({{$3->getName(),$3->getType()},-1});
			// //<<$3->getType()<<"\n";
				
			}
 		  	| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
			{
									Node* nd_com=new Node();
			nd_com->setStart(@2.first_line);
			nd_com->setEnd(@2.last_line);
			nd_com->setTypeSpecifier($2->getType());
			nd_com->setGrammar($2->getType()+" : "+$2->getName());
			nd_com->setSymbolInfo($2);

			Node* nd_id=new Node();
			nd_id->setStart(@3.first_line);
			nd_id->setEnd(@3.last_line);
			//nd_id->setName($3->getName());
			nd_id->setTypeSpecifier($3->getType());
			$3->setInherentType("variable");
			$3->setArraySize(stoi($5->getName()));
			nd_id->setSymbolInfo($3);
			nd_id->setGrammar($3->getType()+" : "+$3->getName());

			Node* nd_lt=new Node();
			nd_lt->setStart(@4.first_line);
			nd_lt->setEnd(@4.last_line);
			nd_lt->setTypeSpecifier($4->getType());
			nd_lt->setGrammar($4->getType()+" : "+$4->getName());
			nd_lt->setSymbolInfo($4);

			Node* nd_ci=new Node();
			nd_ci->setStart(@5.first_line);
			nd_ci->setEnd(@5.last_line);
			nd_ci->setTypeSpecifier($5->getType());
			nd_ci->setGrammar($5->getType()+" : "+$5->getName());
			if($4->getName()=="0"){
				nd_ci->setZero();
			}
			nd_ci->setSymbolInfo($5);

			Node* nd_rt=new Node();
			nd_rt->setStart(@6.first_line);
			nd_rt->setEnd(@6.last_line);
			nd_rt->setTypeSpecifier($6->getType());
			nd_rt->setGrammar($6->getType()+" : "+$6->getName());
			nd_rt->setSymbolInfo($6);

			Node* nd=new Node();
			nd->setName("declaration_list");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("declaration_list");
			nd->setGrammar("declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
			nd->addChild($1);
			nd->addChild(nd_com);
			nd->addChild(nd_id);
			nd->addChild(nd_lt);
			nd->addChild(nd_ci);
			nd->addChild(nd_rt);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";
			varNameTypeSz.push_back({{$3->getName(),$3->getType()},stoi($5->getName())});

			}
 		  	| ID
			{
					Node* nd_id=new Node();
			nd_id->setStart(@1.first_line);
			nd_id->setEnd(@1.last_line);
			//nd_id->setName($1->getName());
			$1->setInherentType("variable");
			nd_id->setTypeSpecifier($1->getType());
			nd_id->setSymbolInfo($1);
			nd_id->setGrammar($1->getType()+" : "+$1->getName());


					Node* nd=new Node();
			nd->setName("declaration_list");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("declaration_list");
			nd->setGrammar("declaration_list : ID");
			nd->addChild(nd_id);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";
			varNameTypeSz.push_back({{$1->getName(),$1->getType()},-1});

			}
			| ID LTHIRD RTHIRD ASSIGNOP LCURL expression_list RCURL
			{
				Node* nd_id=new Node();
			nd_id->setStart(@1.first_line);
			nd_id->setEnd(@1.last_line);
			//nd_id->setName($1->getName());
			$1->setInherentType("variable");
			nd_id->setTypeSpecifier($1->getType());
			nd_id->setSymbolInfo($1);
			nd_id->setGrammar($1->getType()+" : "+$1->getName());


			Node* nd_lt=new Node();
			nd_lt->setStart(@2.first_line);
			nd_lt->setEnd(@2.last_line);
			nd_lt->setTypeSpecifier($2->getType());
			nd_lt->setGrammar($2->getType()+" : "+$2->getName());
			nd_lt->setSymbolInfo($2);

			Node* nd_aop=new Node();
			nd_aop->setStart(@4.first_line);
			nd_aop->setEnd(@4.last_line);
			nd_aop->setTypeSpecifier($4->getType());
			nd_aop->setGrammar($4->getType()+" : "+$4->getName());
			nd_aop->setSymbolInfo($4);

			Node* nd_rt=new Node();
			nd_rt->setStart(@3.first_line);
			nd_rt->setEnd(@3.last_line);
			nd_rt->setTypeSpecifier($3->getType());
			nd_rt->setGrammar($3->getType()+" : "+$3->getName());
			nd_rt->setSymbolInfo($3);

					Node* nd_lcurl=new Node();
			nd_lcurl->setStart(@5.first_line);
			nd_lcurl->setEnd(@5.last_line);
			nd_lcurl->setTypeSpecifier($5->getType());
			nd_lcurl->setGrammar($5->getType()+" : "+$5->getName());
			nd_lcurl->setSymbolInfo($5);
					Node* nd_rcurl=new Node();
			nd_rcurl->setStart(@7.first_line);
			nd_rcurl->setEnd(@7.last_line);
			nd_rcurl->setTypeSpecifier($7->getType());
			nd_rcurl->setGrammar($7->getType()+" : "+$7->getName());
			nd_rcurl->setSymbolInfo($7);

			Node* nd=new Node();
			nd->setName("declaration_list");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("declaration_list");
			nd->setGrammar("ID LTHIRD RTHIRD ASSIGNOP LCURL expression_list RCURL");
			nd->addChild(nd_id);
			nd->addChild(nd_lt);
			nd->addChild(nd_rt);
			nd->addChild(nd_aop);
			nd->addChild(nd_lcurl);
			nd->addChild($6);
			nd->addChild(nd_rcurl);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";
			//varNameTypeSz.push_back({{$1->getName(),$1->getType()},stoi($3->getName())});




			}
 		  	| ID LTHIRD CONST_INT RTHIRD
			{
							Node* nd_id=new Node();
			nd_id->setStart(@1.first_line);
			nd_id->setEnd(@1.last_line);
			//nd_id->setName($1->getName());
			$1->setInherentType("variable");
			$1->setArraySize(stoi($3->getName()));
			nd_id->setTypeSpecifier($1->getType());
			nd_id->setSymbolInfo($1);
			nd_id->setGrammar($1->getType()+" : "+$1->getName());


			Node* nd_lt=new Node();
			nd_lt->setStart(@2.first_line);
			nd_lt->setEnd(@2.last_line);
			nd_lt->setTypeSpecifier($2->getType());
			nd_lt->setGrammar($2->getType()+" : "+$2->getName());
			nd_lt->setSymbolInfo($2);

			Node* nd_ci=new Node();
			nd_ci->setStart(@3.first_line);
			nd_ci->setEnd(@3.last_line);
			nd_ci->setTypeSpecifier($3->getType());
			nd_ci->setGrammar($3->getType()+" : "+$3->getName());
			if($3->getName()=="0"){
				nd_ci->setZero();
			}
			nd_ci->setSymbolInfo($3);

			Node* nd_rt=new Node();
			nd_rt->setStart(@4.first_line);
			nd_rt->setEnd(@4.last_line);
			nd_rt->setTypeSpecifier($4->getType());
			nd_rt->setGrammar($4->getType()+" : "+$4->getName());
			nd_rt->setSymbolInfo($4);

			Node* nd=new Node();
			nd->setName("declaration_list");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("declaration_list");
			nd->setGrammar("declaration_list : ID LSQUARE CONST_INT RSQUARE");
			nd->addChild(nd_id);
			nd->addChild(nd_lt);
			nd->addChild(nd_ci);
			nd->addChild(nd_rt);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";
			varNameTypeSz.push_back({{$1->getName(),$1->getType()},stoi($3->getName())});

			}
			|
			error
			{
				yyclearin;
				yyerrok;

				Node* nd=new Node();
				nd->setName("declaration_list");
				nd->setStart(@$.first_line);
				nd->setEnd(@$.last_line);
				nd->setTypeSpecifier("declaration_list");
				nd->setGrammar("syntax error");
				$$=nd;
				//outlog<<"Error at line no "<<$$->getStart()<<" : "<<$$->getGrammar()<<"\n";

			}
 		  	;

expression_list : expression
		{
			Node* nd=new Node();
			nd->setName("expression_list");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("expression_list");
			nd->setGrammar("expression_list : expression");
			nd->addChild($1);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";

		} 
		| expression_list COMMA expression
		{
			Node* nd_lp=new Node();
			nd_lp->setStart(@2.first_line);
			nd_lp->setEnd(@2.last_line);
			nd_lp->setTypeSpecifier($2->getType());
			nd_lp->setGrammar($2->getType()+" : "+$2->getName());
			nd_lp->setSymbolInfo($2);

			Node* nd=new Node();
			nd->setName("expression_list");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("expression_list");
			nd->setGrammar("expression_list : expression_list COMMA expression");
			nd->addChild($1);
			nd->addChild(nd_lp);
			nd->addChild($3);
			$$=nd;
			outlog<<nd->getGrammar()<<"\n";
			
		}
		;
 		  
statements : statement
		{
			Node* nd=new Node();
			nd->setName("statements");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statements");
			nd->setGrammar("statements : statement");
			nd->addChild($1);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";

		}
	   	| statements statement
		{
			Node* nd=new Node();
			nd->setName("statements");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statements");
			nd->setGrammar("statements : statements statement");
			nd->addChild($1);
			nd->addChild($2);
			$$=nd;
			outlog<<nd->getGrammar()<<"\n";
			
		}
	   	;
	   
statement : var_declaration
		{	
			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : var_declaration");
			nd->addChild($1);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";
		}
		| expression_statement
		{
			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : expression_statement");
			nd->addChild($1);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";
		}
		| compound_statement
		{
			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : compound_statement");
			nd->addChild($1);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";
		}
		| FOR LPAREN expression_statement expression_statement expression RPAREN statement
		{
			Node* nd_for=new Node();
			nd_for->setStart(@1.first_line);
			nd_for->setEnd(@1.last_line);
			nd_for->setTypeSpecifier($1->getType());
			nd_for->setGrammar($1->getType()+" : "+$1->getName());
			nd_for->setSymbolInfo($1);

			Node* nd_lp=new Node();
			nd_lp->setStart(@2.first_line);
			nd_lp->setEnd(@2.last_line);
			nd_lp->setTypeSpecifier($2->getType());
			nd_lp->setGrammar($2->getType()+" : "+$2->getName());
			nd_lp->setSymbolInfo($2);

			Node* nd_rp=new Node();
			nd_rp->setStart(@6.first_line);
			nd_rp->setEnd(@6.last_line);
			nd_rp->setTypeSpecifier($6->getType());
			nd_rp->setGrammar($6->getType()+" : "+$6->getName());
			nd_rp->setSymbolInfo($6);

			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
			nd->addChild(nd_for);
			nd->addChild(nd_lp);
			nd->addChild($3);
			nd->addChild($4);
			nd->addChild($5);
			nd->addChild(nd_rp);
			nd->addChild($7);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";


		}
		| IF LPAREN expression RPAREN statement
		{
			Node* nd_if=new Node();
			nd_if->setStart(@1.first_line);
			nd_if->setEnd(@1.last_line);
			nd_if->setTypeSpecifier($1->getType());
			nd_if->setGrammar($1->getType()+" : "+$1->getName());
			nd_if->setSymbolInfo($1);

			Node* nd_lp=new Node();
			nd_lp->setStart(@2.first_line);
			nd_lp->setEnd(@2.last_line);
			nd_lp->setTypeSpecifier($2->getType());
			nd_lp->setGrammar($2->getType()+" : "+$2->getName());
			nd_lp->setSymbolInfo($2);
			
			Node* nd_rp=new Node();
			nd_rp->setStart(@4.first_line);
			nd_rp->setEnd(@4.last_line);
			nd_rp->setTypeSpecifier($4->getType());
			nd_rp->setGrammar($4->getType()+" : "+$4->getName());
			nd_rp->setSymbolInfo($4);		
			
			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : IF LPAREN expression RPAREN statement");
			nd->addChild(nd_if);
			nd->addChild(nd_lp);
			nd->addChild($3);
			nd->addChild(nd_rp);
			nd->addChild($5);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";

		}
		| IF LPAREN expression RPAREN statement ELSE statement
		{
						Node* nd_if=new Node();
			nd_if->setStart(@1.first_line);
			nd_if->setEnd(@1.last_line);
			nd_if->setTypeSpecifier($1->getType());
			nd_if->setGrammar($1->getType()+" : "+$1->getName());
			nd_if->setSymbolInfo($1);

			Node* nd_lp=new Node();
			nd_lp->setStart(@2.first_line);
			nd_lp->setEnd(@2.last_line);
			nd_lp->setTypeSpecifier($2->getType());
			nd_lp->setGrammar($2->getType()+" : "+$2->getName());
			nd_lp->setSymbolInfo($2);
			
			Node* nd_rp=new Node();
			nd_rp->setStart(@4.first_line);
			nd_rp->setEnd(@4.last_line);
			nd_rp->setTypeSpecifier($4->getType());
			nd_rp->setGrammar($4->getType()+" : "+$4->getName());
			nd_rp->setSymbolInfo($4);
				Node* nd_el=new Node();
			nd_el->setStart(@6.first_line);
			nd_el->setEnd(@6.last_line);
			nd_el->setTypeSpecifier($6->getType());
			nd_el->setGrammar($6->getType()+" : "+$6->getName());
			nd_el->setSymbolInfo($6);		
			
			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : IF LPAREN expression RPAREN statement ELSE statement");
			nd->addChild(nd_if);
			nd->addChild(nd_lp);
			nd->addChild($3);
			nd->addChild(nd_rp);
			nd->addChild($5);
			nd->addChild(nd_el);
			nd->addChild($7);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";

		}
		| LOOP statement WHILE LPAREN expression RPAREN
		{
			Node* nd_loop=new Node();
			nd_loop->setStart(@1.first_line);
			nd_loop->setEnd(@1.last_line);
			nd_loop->setTypeSpecifier($1->getType());
			nd_loop->setGrammar($1->getType()+" : "+$1->getName());
			nd_loop->setSymbolInfo($1);
		
			Node* nd_wh=new Node();
			nd_wh->setStart(@3.first_line);
			nd_wh->setEnd(@3.last_line);
			nd_wh->setTypeSpecifier($3->getType());
			nd_wh->setGrammar($3->getType()+" : "+$3->getName());
			nd_wh->setSymbolInfo($3);

			Node* nd_lp=new Node();
			nd_lp->setStart(@4.first_line);
			nd_lp->setEnd(@4.last_line);
			nd_lp->setTypeSpecifier($4->getType());
			nd_lp->setGrammar($4->getType()+" : "+$4->getName());
			nd_lp->setSymbolInfo($4);
			
			Node* nd_rp=new Node();
			nd_rp->setStart(@6.first_line);
			nd_rp->setEnd(@6.last_line);
			nd_rp->setTypeSpecifier($6->getType());
			nd_rp->setGrammar($6->getType()+" : "+$6->getName());
			nd_rp->setSymbolInfo($3);

			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : LOOP statement WHILE LPAREN expression RPAREN");
			nd->addChild(nd_loop);
			nd->addChild($2);
			nd->addChild(nd_wh);
			nd->addChild(nd_lp);
			nd->addChild($5);
			nd->addChild(nd_rp);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";



		} 
		| WHILE LPAREN expression RPAREN statement
		{
			Node* nd_wh=new Node();
			nd_wh->setStart(@1.first_line);
			nd_wh->setEnd(@1.last_line);
			nd_wh->setTypeSpecifier($1->getType());
			nd_wh->setGrammar($1->getType()+" : "+$1->getName());
			nd_wh->setSymbolInfo($1);

			Node* nd_lp=new Node();
			nd_lp->setStart(@2.first_line);
			nd_lp->setEnd(@2.last_line);
			nd_lp->setTypeSpecifier($2->getType());
			nd_lp->setGrammar($2->getType()+" : "+$2->getName());
			nd_lp->setSymbolInfo($2);

			Node* nd_rp=new Node();
			nd_rp->setStart(@4.first_line);
			nd_rp->setEnd(@4.last_line);
			nd_rp->setTypeSpecifier($4->getType());
			nd_rp->setGrammar($4->getType()+" : "+$4->getName());
			nd_rp->setSymbolInfo($4);

			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : WHILE LPAREN expression RPAREN statement");
			nd->addChild(nd_wh);
			nd->addChild(nd_lp);
			nd->addChild($3);
			nd->addChild(nd_rp);
			nd->addChild($5);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";

		}
		| PRINTLN LPAREN ID RPAREN SEMICOLON
		{
			Node* nd_pn=new Node();
			nd_pn->setStart(@1.first_line);
			nd_pn->setEnd(@1.last_line);
			nd_pn->setTypeSpecifier($1->getType());
			nd_pn->setGrammar($1->getType()+" : "+$1->getName());
			nd_pn->setSymbolInfo($1);

			Node* nd_lp=new Node();
			nd_lp->setStart(@2.first_line);
			nd_lp->setEnd(@2.last_line);
			nd_lp->setTypeSpecifier($2->getType());
			nd_lp->setGrammar($2->getType()+" : "+$2->getName());
			nd_lp->setSymbolInfo($2);

			Node* nd_id=new Node();
			nd_id->setStart(@3.first_line);
			nd_id->setEnd(@3.last_line);
			//nd_id->setName($3->getName());
			nd_id->setTypeSpecifier($3->getType());
			nd_id->setSymbolInfo($3);
			nd_id->setGrammar($3->getType()+" : "+$3->getName());

			Node* nd_rp=new Node();
			nd_rp->setStart(@4.first_line);
			nd_rp->setEnd(@4.last_line);
			nd_rp->setTypeSpecifier($4->getType());
			nd_rp->setGrammar($4->getType()+" : "+$4->getName());
			nd_rp->setSymbolInfo($4);
			
			Node* nd_sc=new Node();
			nd_sc->setStart(@5.first_line);
			nd_sc->setEnd(@5.last_line);
			nd_sc->setTypeSpecifier($5->getType());
			nd_sc->setGrammar($5->getType()+" : "+$5->getName());
			nd_sc->setSymbolInfo($5);

			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
			nd->addChild(nd_pn);
			nd->addChild(nd_lp);
			nd->addChild(nd_id);
			nd->addChild(nd_rp);
			nd->addChild(nd_sc);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";

		}
		| RETURN expression SEMICOLON
		{
			Node* nd_rt=new Node();
			nd_rt->setStart(@1.first_line);
			nd_rt->setEnd(@1.last_line);
			nd_rt->setTypeSpecifier($1->getType());
			nd_rt->setGrammar($1->getType()+" : "+$1->getName());
			nd_rt->setSymbolInfo($1);

			Node* nd_sc=new Node();
			nd_sc->setStart(@3.first_line);
			nd_sc->setEnd(@3.last_line);
			nd_sc->setTypeSpecifier($3->getType());
			nd_sc->setGrammar($3->getType()+" : "+$3->getName());
			nd_sc->setSymbolInfo($3);

			Node* nd=new Node();
			nd->setName("statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("statement");
			nd->setGrammar("statement : RETURN expression SEMICOLON");
			nd->addChild(nd_rt);
			nd->addChild($2);
			nd->addChild(nd_sc);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";

		}
		;
	  
expression_statement : SEMICOLON	
			{
				Node* nd_sc=new Node();
			nd_sc->setStart(@1.first_line);
			nd_sc->setEnd(@1.last_line);
			nd_sc->setTypeSpecifier($1->getType());
			nd_sc->setGrammar($1->getType()+" : "+$1->getName());
			nd_sc->setSymbolInfo($1);

					
			Node* nd=new Node();
			nd->setName("expression_statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("expression_statement");
			nd->setGrammar("expression_statement 	: SEMICOLON");
			nd->addChild(nd_sc);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";

			}		
			| expression SEMICOLON 
			{
				Node* nd_sc=new Node();
			nd_sc->setStart(@2.first_line);
			nd_sc->setEnd(@2.last_line);
			nd_sc->setTypeSpecifier($2->getType());
			nd_sc->setGrammar($2->getType()+" : "+$2->getName());
			nd_sc->setSymbolInfo($2);
					
			Node* nd=new Node();
			nd->setName("expression_statement");
			nd->setStart(@$.first_line);
			nd->setEnd(@$.last_line);
			nd->setTypeSpecifier("expression_statement");
			nd->setGrammar("expression_statement 	: expression SEMICOLON");
			nd->addChild($1);
			nd->addChild(nd_sc);
			$$=nd;
			outlog<<$$->getGrammar()<<"\n";

			}
			;
	  
variable : ID 	
	{
		Node* nd_id=new Node();
		nd_id->setStart(@1.first_line);
		nd_id->setEnd(@1.last_line);
		//nd_id->setName($1->getName());
		nd_id->setTypeSpecifier($1->getType());
		nd_id->setSymbolInfo($1);
		nd_id->setGrammar($1->getType()+" : "+$1->getName());
		
		Node* nd=new Node();
		nd->setName("variable");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("variable");
		nd->setGrammar("variable : ID");

		SymbolInfo* cmp=sTable->LookUp($1->getName());
		if(cmp!=NULL && cmp->getInherentType()=="variable"){
			nd_id->setTypeSpecifier(cmp->getRettypeOrArrayType());
			nd->setTypeSpecifier(cmp->getRettypeOrArrayType());
		}else{
			errorcount++;
			outerror<<"Line# "<<@1.first_line<<": "<<"Undeclared variable '"<<$1->getName()<<"'\n";
		}
		nd->addChild(nd_id);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
	
		
	}	
	| ID LTHIRD expression RTHIRD 
	{
		Node* nd_id=new Node();
		nd_id->setStart(@1.first_line);
		nd_id->setEnd(@1.last_line);
		//nd_id->setName($1->getName());
		nd_id->setTypeSpecifier($1->getType());
		nd_id->setSymbolInfo($1);
		nd_id->setGrammar($1->getType()+" : "+$1->getName());

		//outlog<<$1->getName()<<" "<<$1->getType()<<"\n";
				Node* nd_lt=new Node();
		nd_lt->setStart(@2.first_line);
		nd_lt->setEnd(@2.last_line);
		nd_lt->setTypeSpecifier($2->getType());
		nd_lt->setGrammar($2->getType()+" : "+$2->getName());
		nd_lt->setSymbolInfo($2);
				Node* nd_rt=new Node();
		nd_rt->setStart(@4.first_line);
		nd_rt->setEnd(@4.last_line);
		nd_rt->setTypeSpecifier($4->getType());
		nd_rt->setGrammar($4->getType()+" : "+$4->getName());
		nd_rt->setSymbolInfo($4);
				
		Node* nd=new Node();
		nd->setName("variable");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("variable");
		nd->setGrammar("variable : ID LSQUARE expression RSQUARE");
		SymbolInfo* cmp=sTable->LookUp($1->getName());
		if(cmp == NULL)
		{
			errorcount++;
			outerror<<"Line# "<<@1.first_line<<": "<<"Undeclared variable '"<<$1->getName()<<"'\n";

		}
		else if((cmp->getInherentType() == "func_def") || (cmp->getInherentType() == "func_decl"))
		{
			errorcount++;
			outerror<<"Line# "<<@1.first_line<<": "<<"Undeclared variable '"<<$1->getName()<<"'\n";
		}
		else if(cmp->getInherentType()=="variable" && cmp->getArraySize() == -1)
		{
			errorcount++;
			outerror<<"Line# "<<@1.first_line<<": "<<"'"<<$1->getName()<<"' is not an array\n";
		}
		else if($3->getTypeSpecifier() != "INT")
		{
			// //<<$3->getTypeSpecifier()<<"\n";
			errorcount++;
			outerror<<"Line# "<<@3.first_line<<": "<<"Array subscript is not an integer \n";

		}
		else if(cmp->getInherentType()=="variable" && cmp->getArraySize() > -1)
		{
			nd_id->setTypeSpecifier(cmp->getRettypeOrArrayType());
			nd->setTypeSpecifier(cmp->getRettypeOrArrayType());
		}
		nd->addChild(nd_id);
		nd->addChild(nd_lt);
		nd->addChild($3);
		nd->addChild(nd_rt);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

	}
	;
	 
expression : logic_expression	
	{
		Node* nd=new Node();
		nd->setName("expression");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("expression : logic_expression");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

	}
	| variable ASSIGNOP logic_expression 
	{
		Node* nd_ap=new Node();
		nd_ap->setStart(@2.first_line);
		nd_ap->setEnd(@2.last_line);
		nd_ap->setTypeSpecifier($2->getType());
		nd_ap->setGrammar($2->getType()+" : "+$2->getName());
		nd_ap->setSymbolInfo($2);
				
		Node* nd=new Node();
		nd->setName("expression");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("expression : variable ASSIGNOP logic_expression");
		nd->addChild($1);
		nd->addChild(nd_ap);
		nd->addChild($3);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		if($3->getTypeSpecifier() == "VOID")
		{
			errorcount++;
			outerror<<"Line# "<<@3.first_line<<": "<<"void cannot be used in expression \n";
		}
		else if($1->getTypeSpecifier() == "INT" && $3->getTypeSpecifier() == "FLOAT")
		{
			errorcount++;
			outerror<<"Line# "<<@1.first_line<<": "<<"Warning: possible loss of data in assignment of FLOAT to INT \n";
		}
		
	}
	|
	error
	{
		yyclearin;
		yyerrok;

		Node* nd=new Node();
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("error");
		nd->setGrammar("syntax error");
		$$=nd;
		//outlog<<"Error at line no "<<$$->getStart()<<" : "<<$$->getGrammar()<<"\n";

	}	
	;
			
logic_expression : rel_expression 	
		{
			Node* nd=new Node();
			nd->setName("logic_expression");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("logic_expression : rel_expression ");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		}
		| rel_expression LOGICOP rel_expression 
		{
			Node* nd_lp=new Node();
		nd_lp->setStart(@2.first_line);
		nd_lp->setEnd(@2.last_line);
		nd_lp->setTypeSpecifier($2->getType());
		nd_lp->setGrammar($2->getType()+" : "+$2->getName());
		nd_lp->setSymbolInfo($2);
				
		Node* nd=new Node();
		nd->setName("logic_expression");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		
		if($3->getTypeSpecifier()=="VOID" || $1->getTypeSpecifier()=="VOID")
		nd->setTypeSpecifier("VOID");
		else 
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("logic_expression : rel_expression LOGICOP rel_expression");
		nd->addChild($1);
		nd->addChild(nd_lp);
		nd->addChild($3);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		}	
		;
			
rel_expression	: simple_expression
		{
			Node* nd=new Node();
			nd->setName("rel_expression");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("rel_expression : simple_expression ");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";	
		} 
		| simple_expression RELOP simple_expression	
		{
			Node* nd_lp=new Node();
		nd_lp->setStart(@2.first_line);
		nd_lp->setEnd(@2.last_line);
		nd_lp->setTypeSpecifier($2->getType());
		nd_lp->setGrammar($2->getType()+" : "+$2->getName());
		nd_lp->setSymbolInfo($2);
				
		Node* nd=new Node();
		nd->setName("rel_expression");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
	
		if($3->getTypeSpecifier()=="VOID" || $1->getTypeSpecifier()=="VOID")
		nd->setTypeSpecifier("VOID");
		else 
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("rel_expression : simple_expression RELOP simple_expression");
		nd->addChild($1);
		nd->addChild(nd_lp);
		nd->addChild($3);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		}
		;
				
simple_expression : term 
		{
			Node* nd=new Node();
			nd->setName("simple_expression");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("simple_expression : term");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";	
		}
		| simple_expression ADDOP term 
		{
			Node* nd_lp=new Node();
		nd_lp->setStart(@2.first_line);
		nd_lp->setEnd(@2.last_line);
		nd_lp->setTypeSpecifier($2->getType());
		nd_lp->setGrammar($2->getType()+" : "+$2->getName());
		nd_lp->setSymbolInfo($2);
				
		Node* nd=new Node();
		nd->setName("simple_expression");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);

		if($3->getTypeSpecifier()=="VOID" || $1->getTypeSpecifier()=="VOID")
		nd->setTypeSpecifier("VOID");
		else 
		nd->setTypeSpecifier($1->getTypeSpecifier());

		nd->setGrammar("simple_expression : simple_expression ADDOP term");
		nd->addChild($1);
		nd->addChild(nd_lp);
		nd->addChild($3);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		}
		;
					
term :	unary_expression
	{
		Node* nd=new Node();
		nd->setName("term");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("term : unary_expression");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";	
	}
    |  term MULOP unary_expression
    {
		Node* nd_lp=new Node();
		nd_lp->setStart(@2.first_line);
		nd_lp->setEnd(@2.last_line);
		nd_lp->setTypeSpecifier($2->getType());
		nd_lp->setGrammar($2->getType()+" : "+$2->getName());
		nd_lp->setSymbolInfo($2);
				
		Node* nd=new Node();
		nd->setName("term");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		if($3->getTypeSpecifier()=="VOID" || $1->getTypeSpecifier()=="VOID")
		nd->setTypeSpecifier("VOID");
		else 
		nd->setTypeSpecifier($1->getTypeSpecifier());

		nd->setGrammar("term : term MULOP unary_expression");
		nd->addChild($1);
		nd->addChild(nd_lp);
		nd->addChild($3);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		if(($2->getName() == "%") && ($1->getTypeSpecifier() != "INT" || $3->getTypeSpecifier() != "INT"))
		{
			errorcount++;
			outerror<<"Line# "<<@1.first_line<<": Operands of modulous must be integers\n";
		}else if(($2->getName() == "/" || $2->getName() == "%") && ($3->getTypeSpecifier() == "INT" && $3->isZero()))
		{
			errorcount++;
			outerror<<"Line# "<<@1.first_line<<": Warning: division by zero i=0f=1Const=0\n";
		}
	}
	;

unary_expression : ADDOP unary_expression  
		{
		Node* nd_lp=new Node();
		nd_lp->setStart(@1.first_line);
		nd_lp->setEnd(@1.last_line);
		nd_lp->setTypeSpecifier($1->getType());
		nd_lp->setGrammar($1->getType()+" : "+$1->getName());
		nd_lp->setSymbolInfo($1);
				
		Node* nd=new Node();
		nd->setName("unary_expression");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($2->getTypeSpecifier());
		nd->setGrammar("unary_expression : ADDOP unary_expression ");
		nd->addChild(nd_lp);
		nd->addChild($2);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		}
		| NOT unary_expression 
		{
			Node* nd_lp=new Node();
		nd_lp->setStart(@1.first_line);
		nd_lp->setEnd(@1.last_line);
		nd_lp->setTypeSpecifier($1->getType());
		nd_lp->setGrammar($1->getType()+" : "+$1->getName());
		nd_lp->setSymbolInfo($1);
				
		Node* nd=new Node();
		nd->setName("unary_expression");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($2->getTypeSpecifier());
		nd->setGrammar("unary_expression : NOT unary_expression ");
		nd->addChild(nd_lp);
		nd->addChild($2);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		}
		| factor 
		{
				Node* nd=new Node();
		nd->setName("unary_expression");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("unary_expression : factor");
		nd->addChild($1);
		if($1->isZero()){
			nd->setZero();
		}
		// //<<nd->isZero()<<" una zerozero\n";
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		}
		;
	
factor	: variable 
	{
		Node* nd=new Node();
		nd->setName("factor");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("factor : variable");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
	}
	| ID LPAREN argument_list RPAREN
	{
		Node* nd_id=new Node();
		nd_id->setStart(@1.first_line);
		nd_id->setEnd(@1.last_line);
		//nd_id->setName($1->getName());
		nd_id->setTypeSpecifier($1->getType());
		nd_id->setSymbolInfo($1);
		nd_id->setGrammar($1->getType()+" : "+$1->getName());

		Node* nd_lp=new Node();
		nd_lp->setStart(@2.first_line);
		nd_lp->setEnd(@2.last_line);
		nd_lp->setTypeSpecifier($2->getType());
		nd_lp->setGrammar($2->getType()+" : "+$2->getName());
		nd_lp->setSymbolInfo($2);

		Node* nd_rp=new Node();
		nd_rp->setStart(@4.first_line);
		nd_rp->setEnd(@4.last_line);
		nd_rp->setTypeSpecifier($4->getType());
		nd_rp->setGrammar($4->getType()+" : "+$4->getName());
		nd_rp->setSymbolInfo($4);
				Node* nd=new Node();
		nd->setName("factor");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("factor");
		nd->setGrammar("factor  : ID LPAREN argument_list RPAREN");
		
		SymbolInfo* cmp=sTable->LookUp($1->getName());
		if(cmp==NULL || cmp->getInherentType()=="variable"){
			errorcount++;
			outerror<< "Line# " << @1.first_line << ": " << "Undeclared function '" << $1->getName() << "'\n";

		}else if(cmp->getInherentType()=="func_def" || cmp->getInherentType()=="func_decl"){
			vector<pair<string,string>> prev=cmp->getParams();
			if(prev.size()<argsOfFunction.size()){
				errorcount++;
				outerror << "Line# " << @1.first_line << ": Too many arguments to function '" << $1->getName() << "'\n";

			}else if(prev.size()>argsOfFunction.size()){
				errorcount++;
				outerror << "Line# " << @1.first_line << ": Too few arguments to function '" << $1->getName() << "'\n";

			}else{
				for(int i=0;i<prev.size();i++){
					if(prev[i].second==argsOfFunction[i]){
						continue;
					}
					// //<<prev[i]<<" "<<argsOfFunction[i]<<"\n";
					errorcount++;
					outerror << "Line# " << @1.first_line << ": Type mismatch for argument " << i+1 << " of '" << $1->getName() << "'\n"; 

				}
			}
			nd->setTypeSpecifier(cmp->getRettypeOrArrayType());
			
			// //<<nd->getTypeSpecifier()<<" "<<cmp->getName()<<" ttsf\n";
		}
		argsOfFunction.clear();
		nd->addChild(nd_id);
		nd->addChild(nd_lp);
		nd->addChild($3);
		nd->addChild(nd_rp);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		

	}
	| LPAREN expression RPAREN
	{
		
		Node* nd_lp=new Node();
		nd_lp->setStart(@1.first_line);
		nd_lp->setEnd(@1.last_line);
		nd_lp->setTypeSpecifier($1->getType());
		nd_lp->setGrammar($1->getType()+" : "+$1->getName());
		nd_lp->setSymbolInfo($1);

		Node* nd_rp=new Node();
		nd_rp->setStart(@3.first_line);
		nd_rp->setEnd(@3.last_line);
		nd_rp->setTypeSpecifier($3->getType());
		nd_rp->setGrammar($3->getType()+" : "+$3->getName());
		nd_rp->setSymbolInfo($3);
				
		Node* nd=new Node();
		nd->setName("factor");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($2->getTypeSpecifier());
		nd->setGrammar("factor  : LPAREN expression RPAREN");
		nd->addChild(nd_lp);
		nd->addChild($2);
		nd->addChild(nd_rp);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
	}
	| CONST_INT 
	{
		Node* nd_int=new Node();
		nd_int->setStart(@1.first_line);
		nd_int->setEnd(@1.last_line);
		nd_int->setTypeSpecifier($1->getType());
		nd_int->setGrammar($1->getType()+" : "+$1->getName());
		nd_int->setSymbolInfo($1);
		
				Node* nd=new Node();
		nd->setName("factor");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("INT");
		nd->setGrammar("factor  : CONST_INT");
		if($1->getName()=="0"){
			nd_int->setZero();
			nd->setZero();
		}
		//<<nd->isZero()<<" zerozero\n";
		nd->addChild(nd_int);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		
	} 
	| CONST_FLOAT
	{
		Node* nd_fl=new Node();
		nd_fl->setStart(@1.first_line);
		nd_fl->setEnd(@1.last_line);
		nd_fl->setTypeSpecifier($1->getType());
		nd_fl->setGrammar($1->getType()+" : "+$1->getName());
		nd_fl->setSymbolInfo($1);
				Node* nd=new Node();
		nd->setName("factor");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("FLOAT");
		nd->setGrammar("factor  : CONST_FLOAT");
		nd->addChild(nd_fl);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

	}
	| variable INCOP 
	{
				Node* nd_inc=new Node();
		nd_inc->setStart(@2.first_line);
		nd_inc->setEnd(@2.last_line);
		nd_inc->setTypeSpecifier($2->getType());
		nd_inc->setGrammar($2->getType()+" : "+$2->getName());
		nd_inc->setSymbolInfo($2);		
				Node* nd=new Node();
		nd->setName("factor");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("factor  : variable INCOP");
		nd->addChild($1);
		nd->addChild(nd_inc);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

	}
	| variable DECOP
	{
		Node* nd_dec=new Node();
		nd_dec->setStart(@2.first_line);
		nd_dec->setEnd(@2.last_line);
		nd_dec->setTypeSpecifier($2->getType());
		nd_dec->setGrammar($2->getType()+" : "+$2->getName());
		nd_dec->setSymbolInfo($2);		
				Node* nd=new Node();
		nd->setName("factor");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier($1->getTypeSpecifier());
		nd->setGrammar("factor  : variable DECOP");
		nd->addChild($1);
		nd->addChild(nd_dec);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

	}
	;
	
argument_list : arguments
		{
			Node* nd=new Node();
		nd->setName("argument_list");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("argument_list");
		nd->setGrammar("argument_list : arguments");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		}
		|
		{
		Node* nd=new Node();
		nd->setName("argument_list");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("argument_list");
		nd->setGrammar("argument_list : ");
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		}
		;
	
arguments : arguments COMMA logic_expression
		{
			Node* nd_com=new Node();
		nd_com->setStart(@2.first_line);
		nd_com->setEnd(@2.last_line);
		nd_com->setTypeSpecifier($2->getType());
		nd_com->setGrammar($2->getType()+" : "+$2->getName());
		nd_com->setSymbolInfo($2);
				
		Node* nd=new Node();
		nd->setName("arguments");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("arguments");
		nd->setGrammar("arguments : arguments COMMA logic_expression");
		nd->addChild($1);
		nd->addChild(nd_com);
		nd->addChild($3);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";

		argsOfFunction.push_back($3->getTypeSpecifier());
		
			
		}
	    | logic_expression
		{
		Node* nd=new Node();
		nd->setName("arguments");
		nd->setStart(@$.first_line);
		nd->setEnd(@$.last_line);
		nd->setTypeSpecifier("arguments");
		nd->setGrammar("arguments : logic_expression");
		nd->addChild($1);
		$$=nd;
		outlog<<$$->getGrammar()<<"\n";
		argsOfFunction.push_back($1->getTypeSpecifier());
		// //<<$1->getTypeSpecifier()<<" types\n";
		}
	    ;
 

%%
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

