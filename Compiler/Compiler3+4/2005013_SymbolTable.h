#pragma once
#include "2005013_ScopeTable.h"
using namespace std;

class SymbolTable
{

    ScopeTable *currentScopeTable;
    int allTableSize;
    int tot=1;
    

public:
    SymbolTable(int sz)
    {
        
        allTableSize = sz;
        currentScopeTable = new ScopeTable(allTableSize);
        currentScopeTable->setID("1");
        currentScopeTable->setParentScope(NULL);
    }
    ScopeTable *getCurrentScopeTable()
    {
        return currentScopeTable;
    }

    void enterScope()
    {
        
        ScopeTable *nw = new ScopeTable(allTableSize);
        int prev = currentScopeTable->getChildCnt();
        nw->setID(to_string(++tot));
        nw->setParentScope(currentScopeTable);
        nw->setChildCount(0);
        currentScopeTable->setChildCount(prev + 1);
        currentScopeTable = nw;
        cout<<"Scope "<<currentScopeTable->getID()<<" created\n";
    }
    void exitScope()
    {
        // if(currentScopeTable==NULL)
        // return;
         cout<<"Scope "<<currentScopeTable->getID()<<" deleted\n";
        ScopeTable *temp = currentScopeTable;
        currentScopeTable = currentScopeTable->getParentScope();
        delete temp;
    }
    bool Insert(string name, string type)
    {
        if (currentScopeTable == NULL)
        {
            enterScope();
        }
        return currentScopeTable->Insert(name, type);
    }
    bool Insert(SymbolInfo *sinfo)
    {
        if (currentScopeTable == NULL)
        {
            enterScope();
        }
        return currentScopeTable->Insert(sinfo);
    }
    bool Remove(string name)
    {
        if (currentScopeTable == NULL)
            return false;

        return currentScopeTable->Delete(name);
    }
    SymbolInfo *LookUp(string el)
    {
        //cout<<"NULL\n";

        ScopeTable *itr = currentScopeTable;
        while (itr != NULL)
        {
            SymbolInfo *ret = itr->Lookup(el);
            if (ret != NULL)
                return ret;

            itr = itr->getParentScope();
        }
        
        return NULL;
    }
    pair<plli, string> LookUpPositon(string el)
    {
        ScopeTable *itr = currentScopeTable;
        while (itr != NULL)
        {
            plli ret = itr->insertionLocation(el);

            if (ret.first != -1)
                return {ret, itr->getID()};

            itr = itr->getParentScope();
        }
        return {{-1, -1}, " "};
    }

    void printCurrentTable(ofstream &out)
    {
        out << "\tScopeTable# " << currentScopeTable->getID() << "\n";
        currentScopeTable->Print(out);
    }
    void printAllTables(ofstream &out)
    {
        ScopeTable *itr = currentScopeTable;
        while (itr != NULL)
        {
            out << "\tScopeTable# " << itr->getID() << "\n";
            itr->Print(out);
            itr = itr->getParentScope();
        }
    }
    void clear()
    {
        while (currentScopeTable != NULL)
        {
            ScopeTable *tmp = currentScopeTable;
            currentScopeTable = currentScopeTable->getParentScope();
            delete tmp;
        }
    }
};
