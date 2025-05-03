#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define lli long long
#define plli pair<lli, lli>
#define MAX 5000006
//#define cin in
//#define cout out



using namespace std;
class SymbolInfo
{
private:
    string name;
    string type;
    SymbolInfo *nextSymbolPointer;
    vector<pair<string,string>> parametersForFunction;
    vector<pair<pair<string,string>,int>> varNameTypeSz;

    string inherentType;
    int arraySize;
    string rettypeORarrType;
    int fromTopOfStack;
    string terminal;


public:
    SymbolInfo(){
        name="";
        type="";
        nextSymbolPointer=NULL;
        parametersForFunction=vector<pair<string,string>> ();
        varNameTypeSz=vector<pair<pair<string,string>,int>> ();
        inherentType="";
        rettypeORarrType="";
        arraySize=-1;
        fromTopOfStack=0;
        terminal="";
    }
    SymbolInfo(const SymbolInfo &s)
    {
        name = s.name;
        type = s.type;
        parametersForFunction=s.parametersForFunction;
        varNameTypeSz=s.varNameTypeSz;
        inherentType=s.inherentType;
        arraySize=s.arraySize;
        rettypeORarrType=s.rettypeORarrType;
        nextSymbolPointer = NULL;
        fromTopOfStack=s.fromTopOfStack;
        terminal=s.terminal;
    }
    ~SymbolInfo()
    {
        nextSymbolPointer = NULL; 
        parametersForFunction.clear();
        varNameTypeSz.clear();
    }
    void setDistanceFromTop(int x){
        fromTopOfStack=x;
    }
    int getDistanceFromTop(){
        return fromTopOfStack;
    }
    string getTerminal(){
        return terminal;
    }

    void setTerminal(string tr){
        terminal=tr;
    }

    string getName()
    {
        return name;
    }
    string getType()
    {
        return type;
    }
    SymbolInfo *getNextSymbolPointer()
    {
        return nextSymbolPointer;
    }
    vector<pair<string,string>> getParams(){
        return parametersForFunction;
    }
    vector<pair<pair<string,string>,int>> getVars(){
        return varNameTypeSz;
    }
     void setVars(vector<pair<pair<string,string>,int>> vars){
        varNameTypeSz=vars;
    }
    int getArraySize(){
        return arraySize;
    }
    string getInherentType(){
        return inherentType;
    }
    string getRettypeOrArrayType(){
        return rettypeORarrType;
    }
    void addParam(pair<string,string>tp){
        parametersForFunction.push_back(tp);
    }
    void addVar(pair<pair<string,string>,int> pr){
        varNameTypeSz.push_back(pr);
    }
    void setName(string nm)
    {
        name = nm;
    }
    void setType(string tp)
    {
        type = tp;
    }
    void setNextSymbolPointer(SymbolInfo *ptr)
    {
        nextSymbolPointer = ptr;
    }
    void setParams(vector<pair<string,string>> p){
        parametersForFunction=p;
    }
    void setArraySize(int sz){
        arraySize=sz;
    }
    void setInherentType(string tp){
        inherentType=tp;
    }
    void setRettypeOrArrayType(string tp){
        rettypeORarrType=tp;
    }
    bool funcComp(SymbolInfo *sinfo){
        if(!(this->name==sinfo->getName() && this->rettypeORarrType==sinfo->getRettypeOrArrayType() && this->parametersForFunction.size()==sinfo->getParams().size()))
        {
            // cout<<this->getRettypeOrArrayType()<<" "<<sinfo->getRettypeOrArrayType()<<"\n";
            // cout<<this->name<<" "<<sinfo->getName()<<"\n";
            // cout<<this->getParams().size()<<" "<<sinfo->getParams().size()<<"\n";
            return false;
        }
        for(int i=0;i<sinfo->getParams().size();i++){
            if(this->parametersForFunction[i].second!=sinfo->getParams()[i].second){
                //cout<<"nanana\n";
                return false;
            }
        }
        return true;
    }
    bool operator==(const SymbolInfo &sInfo)
    {
        if ((this->name) == (sInfo.name))
            return true;

        return false;
    }
};