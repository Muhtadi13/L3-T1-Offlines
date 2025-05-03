#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "2005013_SymbolTable.h"

using namespace std;
extern bool globalScope;
extern int labelcount;
extern SymbolTable *sTable;
extern int baseOffset;
extern int baseOffsetPrev;
extern string activeFunction;
class Node{

    private:
        int startLocation;
        int endLocation;
        vector<Node *> child;
        string typeSpecifier;
        string grammar;
        string name;
        bool zero;
        
        SymbolInfo *sInfo;
        string truelist;
        string falselist;
        string nextlist;
        bool isItABoolean;


    public:

    Node(){
        startLocation=-1;
        endLocation=-1;
        child=vector<Node *>();
        typeSpecifier="";
        grammar="";
        name="";
        zero=false;
        sInfo=NULL;
        truelist="";
        falselist="";
        nextlist="";
        isItABoolean=false;
    }
    
    void setSymbolInfo(SymbolInfo *s){
        sInfo=s;
    } 
    SymbolInfo* getSymbolInfo(){
        return sInfo;
    } 
    void setName(string s){
        name=s;
    } 
    string getName(){
        return name;
    } 
    int getStart(){
        return startLocation;
    }
    int getEnd(){
        return endLocation;
    }
    vector<Node *> getChild(){
        return child;
    }
    string getGrammar(){
        return grammar;
    }
    string getTypeSpecifier(){
        return typeSpecifier;
    }
    bool isZero(){
        return zero;
    }
    

    void setZero(){
        zero=true;
    }
    void setStart(int st){
        startLocation=st;
    }
    void setEnd(int en){
        endLocation=en;
    }
    void addChild(Node *node){
        child.push_back(node);
    }

    void setGrammar(string g){
        grammar=g;
    }
    void setTypeSpecifier(string tsf){
        typeSpecifier=tsf;
    }
    void print(int gap,ofstream &out){

        if(this==nullptr){
            return;
        }
        for(int i=0;i<gap;i++){
            out<<" ";
        }
        out<<grammar << " 	<Line: " <<startLocation << "-" << endLocation<< ">\n";
        for(int i=0;i<child.size();i++){
           child[i]-> print(gap+1,out);
        }
    } 

    void flowControl(Node *target,string truelabel,string falselabel,string nextlabel,bool needsJump){
        target->truelist=truelabel;
        target->falselist=falselabel;
        target->nextlist=nextlabel;
        target->isItABoolean=needsJump;
    }

    string createLabel(){
        return "L"+to_string(++labelcount);
    }
    void replaceString(string &source, string const &tofind, string const &target)
    {
        for (string::size_type i = 0; (i = source.find(tofind, i)) != string::npos;)
        {
            source.replace(i, tofind.length(), target);
            i += target.length();
        }
    }
   
    void getRecursiveCode(ofstream &out){
        if(this==nullptr)
          return;
          cout<<name<<"\n";
        if(name=="start"){
            child[0]->getRecursiveCode(out);
            print_newline(out);
            print_output(out);
            out<<"END MAIN\n";

        }else if(name=="func_definition"){
            out<<"\t\t;Line No: "<<startLocation<<"\n";
            
            SymbolInfo* currentFunc=child[1]->getSymbolInfo();
            string nam=currentFunc->getName();
            vector<pair<string,string>>params = currentFunc->getParams();
            activeFunction=nam;
            printFuncDefHeader(out,nam);
            enterfunction(out,params);
            string last=createLabel();
            SymbolInfo* inTable=sTable->LookUp(nam);
            inTable->setTerminal(last);
            currentFunc->setTerminal(last);

            for(int i=0;i<child.size();i++){
                child[i]->getRecursiveCode(out);
            }
            int paramSz = params.size();
            out<<last<<":\n";
            printFuncDefFooter(out,nam,paramSz);
            sTable->exitScope();
        }else if(name=="var_declaration"){
            for(int i=0;i<child.size();i++){
                child[i]->getRecursiveCode(out);
            }
            string type=child[0]->getTypeSpecifier();
            vector<pair<pair<string,string>,int>> varNameTypeSz=child[1]->getSymbolInfo()->getVars();
            string scope=sTable->getCurrentScopeTable()->getID();
            if(scope!="1"){
                SymbolInfo* curSym=sTable->LookUp(activeFunction);
                curSym->setVars(varNameTypeSz);
                printVarDecl(out,type,varNameTypeSz);
            }
        }else if(name=="compound_statement"){
            if(nextlist=="")
                nextlist=createLabel();
            if(child.size()==3){
                //cout<<"chichi\n";
                flowControl(child[1],"",falselist,nextlist,isItABoolean);
            }
            for(int i=0;i<child.size();i++){
                child[i]->getRecursiveCode(out);
            }
        }else if(name=="statements"){
            if(child.size()==1){
                flowControl(child[0],"","",nextlist,false);
            }else if(child.size()==2){
                flowControl(child[0],"","",createLabel(),false);
                flowControl(child[1],"","",nextlist,false);
            }
            for(int i=0;i<child.size();i++){
                child[i]->getRecursiveCode(out);
            }
            out<<nextlist<<":\n";

        }else if(name=="statement"){
             out<<"\t\t;Line No: "<<startLocation<<"\n";
            if(child.size()==1){
                // if(child[0]->getName()=="compound_statement")
                //     flowControl(child[0],"","",nextlist,false);
                child[0]->getRecursiveCode(out);
            }else{
                if(child[0]->getSymbolInfo()->getType()=="FOR"){
                    for(int i=0;i<3;i++){
                        child[i]->getRecursiveCode(out);
                    }//initializing

                    string loopstart=createLabel();
                    out<<loopstart<<":\n"; //starting loop
                    flowControl(child[3],createLabel(),nextlist,"",true);
                    flowControl(child[6],"","",createLabel(),false);

                    child[3]->getRecursiveCode(out);
                    out<<child[3]->truelist<<":\n";
                    child[6]->getRecursiveCode(out);
                    //not giving any label here cause statement has a label of its own
                    child[4]->getRecursiveCode(out);
                    out<<"\n\tJMP "<<loopstart<<"\n";
                    out<<"\t"<<child[6]->nextlist<<":\n";
                    //cout<<child[6]->nextlist<<"chhththththrkkkkkkkkk\n";
                }else if(child[0]->getSymbolInfo()->getType()=="IF"){
                    if(child.size()==5){
                        flowControl(child[2],createLabel(),nextlist,"",true);
                        flowControl(child[4],"","",nextlist,false);
                        child[2]->getRecursiveCode(out);
                        out<<child[2]->truelist<< ":\n";
                        child[4]->getRecursiveCode(out);
                        

                    }else{
                        flowControl(child[2],createLabel(),createLabel(),"",true);
                        flowControl(child[4],"","",child[2]->falselist,false);
                        flowControl(child[6],"","",nextlist,false);
                        child[2]->getRecursiveCode(out);
                        out<<child[2]->truelist<< ":\n";
                        child[4]->getRecursiveCode(out);
                        out<< "\tJMP "<< this->nextlist<< "\n";
                        out<< child[2]->falselist<< ":\n";
                        child[6]->getRecursiveCode(out);

                    }
                }else if(child[0]->getSymbolInfo()->getType()=="WHILE"){
                    
                    string loopstart=createLabel();
                    out<<loopstart<<":\n"; //starting loop
                    flowControl(child[2],createLabel(),nextlist,"",true);
                    flowControl(child[4],"","",nextlist,false);

                    child[2]->getRecursiveCode(out);
                    out<<child[2]->truelist<<":\n";
                    //not giving any label here cause statement has a label of its own
                    child[4]->getRecursiveCode(out);
                    out<<"\n\tJMP "<<loopstart<<"\n";

                }else if(child[0]->getSymbolInfo()->getType()=="PRINTLN"){
                    

                    int base=sTable->getCurrentScopeTable()->getBaseOffset();
                    SymbolInfo* currentvar=sTable->LookUp(child[2]->getSymbolInfo()->getName());
                    string scope=sTable->LookUpPositon(currentvar->getName()).second;

                    cout<<scope<<" "<<current_exception<<" scooop\n";
                    if(scope=="1"){
                        out<< "\tMOV AX, "<< child[2]->getSymbolInfo()->getName() <<"\n";
                        out<< "\tCALL print_output\n";
                        out<< "\tCALL new_line\n";
                    }
                    else{
                        out<< "\tPUSH BP\n";
                        out<< "\tMOV BX, "<< -currentvar->getDistanceFromTop()<< "\n";
                        out<< "\tADD BP, BX\n";
                        out<< "\tMOV AX, [BP]\n";
                        out<< "\tCALL print_output\n";
                        out<< "\tCALL new_line\n";
                        out<< "\tPOP BP\n";
                    }
                     //<<"lllllllllll\n";
                    
                }else if(child[0]->getSymbolInfo()->getType()=="RETURN"){
                    child[1]->getRecursiveCode(out);
                    out<< "\tMOV DX,CX\n";
                    string lastlabel=sTable->LookUp(activeFunction)->getTerminal();
                    out<< "\tJMP "<< lastlabel <<"\n";  
                   
                }
            }
        }else if(name=="expression_statement"){//finish
            if(child.size()==2){
                flowControl(child[0],truelist,falselist,nextlist,isItABoolean);
            }
            cout<<truelist<<" "<<falselist<<"esesesesesees\n";
            for(int i=0;i<child.size();i++){
                child[i]->getRecursiveCode(out);
            }
        }else if(name=="expression"){//finish
            if(child.size()==1){//only logic_exp i.e. || &&
                 flowControl(child[0],truelist,falselist,nextlist,isItABoolean);
                child[0]->getRecursiveCode(out);
                
            }else if(child.size()==3){
                 flowControl(child[2],"","","",false);
                child[2]->getRecursiveCode(out);
            
                //let us use AX,BX for 3 address codes
                //so we will store any other constants in CX
                //i.e we will store the evaluation of any type of expression in CX

                SymbolInfo* grandChildSymbol=sTable->LookUp(child[0]->getChild()[0]->getSymbolInfo()->getName());
                string scope=sTable->LookUpPositon(grandChildSymbol->getName()).second;

                if(scope=="1"){
                    if(grandChildSymbol->getArraySize()==-1){
                        child[0]->getRecursiveCode(out);
                        out<<"\tMOV "<<grandChildSymbol->getName()<<" , CX\n";
                    }else{

                        out<< "\tPUSH CX\n";
                        child[0]->getRecursiveCode(out);
                        out<< "\tPOP AX\n";
                        out<< "\tPOP CX\n";
                        out<< "\tMOV [BP], CX\n";
                        out<< "\tMOV BP, AX\n";

                    }

                }else{
                    out<< "\tPUSH CX\n";
                    child[0]->getRecursiveCode(out);
                    out<< "\tPOP AX\n";
                    out<< "\tPOP CX\n";
                    out<< "\tMOV [BP], CX\n";
                    out<< "\tMOV BP, AX\n";

                }
                
            }
        }else if(name=="logic_expression"){
            
             if(child.size()==1){//only rel_exp i.e. < <= ==
                flowControl(child[0],truelist,falselist,nextlist,isItABoolean);
                cout<<"here1\n";
                child[0]->getRecursiveCode(out);
                
            }else if(child.size()==3){
                cout<<"here3\n";
                cout<<child[0]->getName()<<"\n";
                if(child[1]->getSymbolInfo()->getName()=="||"){
                    flowControl(child[0],truelist,createLabel(),"",isItABoolean);
                }else if(child[1]->getSymbolInfo()->getName()=="&&"){
                    flowControl(child[0],createLabel(),falselist,"",isItABoolean);
                }
                flowControl(child[2],truelist,falselist,"",isItABoolean);
                cout<<"here4\n";
                child[0]->getRecursiveCode(out);
                if(isItABoolean){
                    if (child[1]->getSymbolInfo()->getName()=="&&"){
                        out<<child[0]->truelist<<":\n";
                    }else{
                        out<<child[0]->falselist<<":\n";
                    }
                }else{
                    out<<"\n\tPUSH CX\n";
                }
                child[2]->getRecursiveCode(out);
                cout<<"here5\n";
            
                if(!isItABoolean){
                out<< "\tPOP AX\n";
                if(child[1]->getSymbolInfo()->getName()=="||"){
                    string x = createLabel();
                    string y = createLabel();
                    string z = createLabel();
                    string a = createLabel();
                    out<< "\tCMP AX, 0\n";
                    out<< "\tJE "<< x<< "\n";
                    out<< "\tJMP "<< y<< "\n";
                    out<< x<< ":\n";
                    out<< "\tJCXZ "<< z<< "\n";
                    out<< y<< ":\n";
                    out<< "\tMOV CX, 1\n";
                    out<< "\tJMP "<< a<< "\n";
                    out<< z<< ":\n";
                    out<< "\tMOV CX, 0\n";
                    out<< a<< ":\n";
                }
                else{
                    string x = createLabel();
                    string y = createLabel();
                    string z = createLabel();
                    out<< "\tCMP AX, 0\n";
                    out<< "\tJE "<< x<< "\n";
                    out<< "\tJCXZ "<< x<< "\n";
                    out<< "\tJMP "<< y<< "\n";
                    out<< x<< ":\n";
                    out<< "\tMOV CX, 0\n";
                    out<< "\tJMP "<< z<< "\n";
                    out<< y<< ":\n";
                    out<< "\tMOV CX, 1\n";
                    out<< z<< ":\n";
                }
            }
                
                
            }
        }else if(name=="rel_expression"){
            
             if(child.size()==1){//only rel_exp i.e. < <= ==
                flowControl(child[0],truelist,falselist,nextlist,isItABoolean);
                child[0]->getRecursiveCode(out);
                
            }else if(child.size()==3){
    
                child[0]->getRecursiveCode(out);
                out<<"\n\tPUSH CX\n";
                child[2]->getRecursiveCode(out);
                
                string jumpst = "";
                if(child[1]->getSymbolInfo()->getName() == "<") jumpst ="JL";
                else if(child[1]->getSymbolInfo()->getName() == ">") jumpst ="JG";
                else if(child[1]->getSymbolInfo()->getName() == ">=") jumpst ="JGE";
                else if(child[1]->getSymbolInfo()->getName() == "<=") jumpst ="JLE";
                else if(child[1]->getSymbolInfo()->getName() == "==") jumpst ="JE";
                else if(child[1]->getSymbolInfo()->getName() == "!=") jumpst ="JNE";

                cout<<truelist<<" "<<falselist<<"\tftftftftftftft\n";
                if(truelist=="") truelist=createLabel();
                if(falselist=="") falselist=createLabel();

                out<< "\tPOP AX\n";
                out<<"\tCMP AX,CX\n";
                out<<"\t"<<jumpst<<" "<<truelist<<"\n";
                out<<"\tJMP "<<falselist<<"\n";
                if(!isItABoolean){
                    out<<truelist<< ":\n";
                    out<< "\tMOV CX, 1\n";
                    string jmp2 = createLabel();
                    out<< "\tJMP "<< jmp2<< "\n";
                    out<< falselist<< ":\n";
                    out<< "\tMOV CX, 0\n";
                    out<<jmp2<< ":\n";
                }
            
            }
                
        }else if(name=="simple_expression"){
            
             if(child.size()==1){//only rel_exp i.e. < <= ==
                flowControl(child[0],truelist,falselist,nextlist,isItABoolean);
                child[0]->getRecursiveCode(out);
                
            }else if(child.size()==3){
    
                child[0]->getRecursiveCode(out);
                out<<"\n\tPUSH CX\n";
                child[2]->getRecursiveCode(out);
                out<< "\tPOP AX\n";
                if(child[1]->getSymbolInfo()->getName()=="+") out<< "\tADD CX, AX\n";
                if(child[1]->getSymbolInfo()->getName()=="-") out<< "\tSUB AX, CX\n\tMOV CX, AX\n";
                doJump(out,isItABoolean,truelist,falselist);
            
            }
                
        }else if(name=="term"){
            
             if(child.size()==1){//only rel_exp i.e. < <= ==
                flowControl(child[0],truelist,falselist,nextlist,isItABoolean);
                child[0]->getRecursiveCode(out);
                
            }else if(child.size()==3){
    
                child[0]->getRecursiveCode(out);
                out<< "\tPUSH CX\n";
                child[2]->getRecursiveCode(out);
                out<< "\tPOP AX\n";
                if(child[1]->getSymbolInfo()->getName()=="*"){
                    out<< "\tIMUL CX\n";
                    out<< "\tMOV CX, AX\n";
                }
                else if(child[1]->getSymbolInfo()->getName()=="/"){
                    out<< "\tCWD\n";
                    out<< "\tIDIV CX\n";
                    out<< "\tMOV CX, AX\n";
                }
                else if(child[1]->getSymbolInfo()->getName()=="%"){
                    out<< "\tCWD\n";
                    out<< "\tIDIV CX\n";
                    out<< "\tMOV CX, DX\n";
                }
                doJump(out,isItABoolean,truelist,falselist);
        
            
            }
                
        }else if(name=="unary_expression"){
            
             if(child.size()==1){//only rel_exp i.e. < <= ==
                flowControl(child[0],truelist,falselist,nextlist,isItABoolean);
                child[0]->getRecursiveCode(out);
                
            }else if(child.size()==2){

                if(child[0]->getSymbolInfo()->getType()=="ADDOP"){
                    flowControl(child[1],truelist,falselist,nextlist,isItABoolean);
                    child[1]->getRecursiveCode(out);
                    if(child[0]->getSymbolInfo()->getName()=="-"){
                        out<<"\tNEG CX\n";
                    }
                }if(child[0]->getSymbolInfo()->getType()=="NOT"){
                    
                    flowControl(child[1],falselist,truelist,"",isItABoolean);
                    child[1]->getRecursiveCode(out);
                     if(!isItABoolean){
                        string l1 = createLabel();
                        string l2 = createLabel();
                        out<< "\tJCXZ "<<l2<<"\n";
                        out<< "\tMOV CX,0\n";
                        out<< "\tJMP "<< l1<< "\n"; 
                        out<< l2<<":\n";
                        out<< "\tMOV CX,1\n";
                        out<< l1<<":\n";
                    }   
                }
            }
                
        }else if(name=="factor"){
            
             if(child.size()==1){//only rel_exp i.e. < <= ==
                if(child[0]->getName()=="variable"){
                    child[0]->getRecursiveCode(out);
                     SymbolInfo* grandChildSymbol=sTable->LookUp(child[0]->getChild()[0]->getSymbolInfo()->getName());
                    string scope=sTable->LookUpPositon(grandChildSymbol->getName()).second;
                    //cout<<grandChildSymbol->getName()<<"nammmm\n";

                    //cout<<grandChildSymbol->getArraySize()<<"ggggggg\n";

                    if(scope=="1"){
                        
                        if(grandChildSymbol->getArraySize()==-1){
                            child[0]->getRecursiveCode(out);
                            out<<"\tMOV CX ,"<<grandChildSymbol->getName()<<"\n";
                        }else{

                            out<< "\tMOV CX, [BP]\n";
                            out<< "\tPOP BP\n";

                        }

                    }else{
                        out<< "\tMOV CX, [BP]\n";
                        out<< "\tPOP BP\n";

                    }
                    doJump(out,isItABoolean,truelist,falselist);
                    
                }else if(child[0]->getTypeSpecifier()=="CONST_INT"){
                    child[0]->getRecursiveCode(out);
                    out<< "\tMOV CX, "+child[0]->getSymbolInfo()->getName()+"\n";
                    doJump(out,isItABoolean,truelist,falselist);
                }                
            }else if(child.size()==2){

                child[0]->getRecursiveCode(out);
                SymbolInfo* grandChildSymbol=sTable->LookUp(child[0]->getChild()[0]->getSymbolInfo()->getName());
                string scope=sTable->LookUpPositon(grandChildSymbol->getName()).second;

                if(scope=="1"){
                    if(grandChildSymbol->getArraySize()==-1){
                        out<<"\tMOV CX ,"<<grandChildSymbol->getName()<<"\n";
                    }else{
                        out<< "\tMOV CX, [BP]\n";   
                    }

                }else{
                    out<< "\tMOV CX, [BP]\n";
                }
                out<< "\tMOV AX, CX\n";


                if(child[1]->getTypeSpecifier()=="INCOP"){
                    out<< "\tINC CX\n";
                }else{
                    out<< "\tDEC CX\n";
                }
                if(scope=="1"){
                    if(grandChildSymbol->getArraySize()==-1){
                        out<< "\tMOV "<< grandChildSymbol->getName()<< ", CX\n";
                    }else{
                        out<< "\tMOV [BP], CX\n";
                        out<< "\tPOP BP\n";
                    }
                }else{
                    out<< "\tMOV [BP], CX\n";
                    out<< "\tPOP BP\n";
                }
                out<< "\tMOV CX, AX\n";
                doJump(out,isItABoolean,truelist,falselist);
                
            }else if(child.size()==3){
                child[1]->getRecursiveCode(out);
                doJump(out,isItABoolean,truelist,falselist);

            }else if(child.size()==4){
                child[2]->getRecursiveCode(out);
                int base=sTable->getCurrentScopeTable()->getBaseOffset();
                SymbolInfo* currentFunc=sTable->LookUp(child[0]->getSymbolInfo()->getName());
                string nam=currentFunc->getName();
                vector<pair<string,string>>params = currentFunc->getParams();
                //cout<<params.size()<<"sueuru\n";
                auto vars=currentFunc->getVars();  
                int varsOff=totVarsOffset(vars);              
                out<< "\tCALL "+child[0]->getSymbolInfo()->getName()+"\n";
                out<< "\tMOV CX, DX\n";
                //out<< "\tADD SP, "<< params.size()+2<<"\n";

                doJump(out,isItABoolean,truelist,falselist);

            }
                
        }else if(name=="variable"){//finish
            SymbolInfo* childSymbol=sTable->LookUp(child[0]->getSymbolInfo()->getName());
            string scope=sTable->LookUpPositon(childSymbol->getName()).second;
            int base=sTable->getCurrentScopeTable()->getBaseOffset();
           // cout<<scope<<" "<<childSymbol->getName()<<" "<<-childSymbol->getDistanceFromTop()<<"nam\n";
            cout<<childSymbol->getArraySize()<<"cccccccc\n";
            if(scope=="1"){
                if(childSymbol->getArraySize()>-1){
                    
                    child[2]->getRecursiveCode(out);//code for expression i.e. number
                    out<< "\tLEA SI, "<< childSymbol->getName()<< "\n";
                    out<< "\tADD SI, CX\n"; //doubling for integer
                    out<< "\tADD SI, CX\n"; //careful here we may need CX later
                    out<< "\tPUSH BP\n";
                    out<< "\tMOV BP, SI\n";

                }
            }else{
                if(childSymbol->getArraySize()>-1){
                    child[2]->getRecursiveCode(out);
                    out<< "\tPUSH BP\n";
                    out<< "\tMOV BX, CX\n";
                    out<< "\tADD BX, BX\n";
                    out<< "\tADD BX, "<< -childSymbol->getDistanceFromTop()<< "\n";
                    out<< "\tADD BP, BX\n";

                }else{
                    out<< "\tPUSH BP\n";
                    out<< "\tMOV BX, "<< -childSymbol->getDistanceFromTop()<< "\n";
                    out<< "\tADD BP, BX\n";
                }
            }
        }else if(name=="argument_list"){
            if(child.size()>0)
            child[0]->getRecursiveCode(out);
            
        }else if(name=="arguments"){
            child[0]->getRecursiveCode(out);

            if(child.size()==3){
                child[2]->getRecursiveCode(out);
            }
            //cout<<"jaja\n";
            out<<"\tPUSH CX\n";
            
        }else{
            for(int i=0;i<child.size();i++){
                child[i]->getRecursiveCode(out);
            }
        }
    }
    void enterfunction(ofstream &out,vector<pair<string,string>> paramsOfFunction){
        
        sTable->enterScope();
        //cout<<sTable->getCurrentScopeTable()->getID()<<"ididid\n";
        
        baseOffset+=(paramsOfFunction.size()*2+2);
        sTable->getCurrentScopeTable()->setBaseOffset(baseOffset);
        int tmpoffset=-(paramsOfFunction.size()*2+2);
        for(int i=0;i<paramsOfFunction.size();i++){
                SymbolInfo *sinfo=new SymbolInfo();
				sinfo->setName(paramsOfFunction[i].first);
				sinfo->setType(paramsOfFunction[i].second);
				sinfo->setInherentType("parameter");
                sinfo->setDistanceFromTop(tmpoffset);
                tmpoffset+=2;
               // cout<<sinfo->getName()<<" "<<sinfo->getDistanceFromTop()<<"sdfs\n";
				sTable->Insert(sinfo);	
        }
        //might need to add array or not for params
        //paramsOfFunction.clear();


    }
    void printGlobalVars(ofstream &out){
        ScopeTable *scope=sTable->getCurrentScopeTable();
        SymbolInfo *stemp;
        SymbolInfo** headList=scope->getHead();
        for (int i = 0; i < scope->getTableSize(); i++)
        {
            if(headList[i]==NULL)
            continue;
            //out<<"\t"<<i+1;
            
            stemp = headList[i];
            while (stemp != NULL)
            {
                
                if(stemp->getInherentType()=="variable"){
            
                    out <<stemp->getName()<<" DW "<< abs(stemp->getArraySize()) << " DUP (0000H)\n";
                        // baseOffset+=(2*stemp->getArraySize());
                        //out<<stemp->getType()<<"\n"; 
                }
                stemp->setDistanceFromTop(-100);
                stemp = stemp->getNextSymbolPointer();
            }
        }


    }
    void doJump(ofstream &out,bool really,string truely,string falsely){
        if(really){
            out<<"\tCMP CX , 0\n";
            out<<"\tJE "<<falsely<<"\n";
            out<<"\tJMP "<<truely<<"\n";
        }
    }

    void printAssemblyCode(ofstream &out){
        out<<".MODEL SMALL\n.STACK 100H\n\n.DATA\n";
        printGlobalVars(out);
        out<<"NUMBER DB \"00000$\"\n\n";
        out << ".CODE" << "\n" ;
        getRecursiveCode(out);
    }

    void printFuncDefHeader(ofstream &out,string nam){ 

         
	    out<<"\n" << nam << " PROC\n" ; 
        if(nam == "main"){
            out << "\n\tMOV AX , @DATA\n\tMOV DS , AX\n" ;  
        }
        string code = "\n\tPUSH BP\n"
                    "\tMOV BP , SP\n";

        out << code ; 
        
    }
    void printFuncDefFooter(ofstream &out,string nam,int sz){
         
         string code = "\n\tMOV SP , BP\n"
                        "\tPOP BP\n" ; 
        out << code ; 
           

        if(nam == "main"){ 
           
            out <<	"\n\tMOV AH , 4CH\n" ; 
            out <<	"\tINT 21H\n" ; 
            out << "\nMAIN ENDP\n" ; 
        } else {
            
            if(sz==0){
                out << "\tRET\n";

            }else{
                out << "\tRET " << sz*2 << "\n" ; 
            }
            out<<"\n" << nam << " ENDP\n" ; 
        }
       
    }
    int totVarsOffset(vector<pair<pair<string,string>,int>> varNameTypeSz){
        int count=0;
         for(int i=0;i<varNameTypeSz.size();i++){
            count+=varNameTypeSz[i].second;
            //cout<<varNameTypeSz[i].first.first<<"hdhdhd\n\n";
         }
         return count*2;
    }   

    void printVarDecl(ofstream &out,string type,vector<pair<pair<string,string>,int>> varNameTypeSz){
        if(sTable->getCurrentScopeTable()->getID()=="1"){
            
        }else{
            cout<<"last\n";
            int tot=0;
            int tmp=baseOffset;
            for(int i=0;i<varNameTypeSz.size();i++){
                    SymbolInfo *sinfo=new SymbolInfo();
                    sinfo->setName(varNameTypeSz[i].first.first);
                    sinfo->setType(type);
                    sinfo->setInherentType("variable");
                    sinfo->setArraySize(varNameTypeSz[i].second);
                    sinfo->setRettypeOrArrayType(type);
                    sinfo->setDistanceFromTop(baseOffset+2-tmp);
                    if(varNameTypeSz[i].second>-1){
                        tot+=varNameTypeSz[i].second;
                        baseOffset+=varNameTypeSz[i].second*2;
                    }else{
                        tot++;
                        baseOffset+=2;
                    }
                    // SymbolInfo* cmp=sTable->getCurrentScopeTable()->Lookup(sinfo->getName());
                    // if(!cmp){
                    sTable->Insert(sinfo);
                    cout<<"inserted\n";
                    //}
                    cout<<sTable->LookUp(sinfo->getName())->getDistanceFromTop()<<"\n";
                    cout<<sinfo->getName()<<" "<<sinfo->getDistanceFromTop()<<"top\n";
            }
            if(tot>0)
            out<<"\n\tSUB SP , "<<tot*2<<"\n";
		                
        }
    }
    void print_newline(ofstream &out){
        string nw="new_line proc\n"
                "\tpush ax\n"
                "\tpush dx\n"
                "\tmov ah,2\n"
                "\tmov dl,0Dh\n"
                "\tint 21h\n"
                "\tmov ah,2\n"
                "\tmov dl,0Ah\n"
                "\tint 21h\n"
                "\tpop dx\n"
                "\tpop ax\n"
                "\tret\n"
                "\tnew_line endp\n";

            out<<nw;

    }
    void print_output(ofstream &out){

       string ot=" print_output proc  ;print what is in ax\n"
                "\tpush ax\n"
                "\tpush bx\n"
                "\tpush cx\n"
                "\tpush dx\n"
                "\tpush si\n"
                "\tlea si,number\n"
                "\tmov bx,10\n"
                "\tadd si,4\n"
                "\tcmp ax,0\n"
                "\tjnge negate\n"
                "\tprint:\n"
                "\txor dx,dx\n"
                "\tdiv bx\n"
                "\tmov [si],dl\n"
                "\tadd [si],'0'\n"
                "\tdec si\n"
                "\tcmp ax,0\n"
                "\tjne print\n"
                "\tinc si\n"
                "\tlea dx,si\n"
                "\tmov ah,9\n"
                "\tint 21h\n"
                "\tpop si\n"
                "\tpop dx\n"
                "\tpop cx\n"
                "\tpop bx\n"
                "\tpop ax\n"
                "\tret\n"
                "\tnegate:\n"
                "\tpush ax\n"
                "\tmov ah,2\n"
                "\tmov dl,'-'\n"
                "\tint 21h\n"
                "\tpop ax\n"
                "\tneg ax\n"
                "\tjmp print\n"
                "print_output endp\n";
    
    out<<ot;
    }
};
