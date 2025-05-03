
#include "2005013_SymbolInfo.cpp"
using namespace std;
class ScopeTable
{
    ScopeTable *parentScope;
    SymbolInfo **headList;
    SymbolInfo **tailList;
    int childcnt;

    int tableSize;
    string ID;

public:
    ScopeTable(int sz)
    {

        // sieve();
        tableSize = sz;
        // for (int i = tableSize; i <= 2 * tableSize; i++)
        // {
        //     if (smallestprimedivisor[i] == i)
        //     {
        //         tableSize = i;
        //         break;
        //     }
        // }
        childcnt=0;
        parentScope = NULL;
        tailList = new SymbolInfo *[tableSize];
        headList = new SymbolInfo *[tableSize];
        for (int i = 0; i < tableSize; i++)
        {
            headList[i] = NULL;
            tailList[i] = NULL;
        }
    }
    ~ScopeTable()
    {
        for (int i = 0; i < tableSize; i++)
        {
            clear(headList[i]);
        }
        delete headList;
        delete tailList;
    }

    int getTableSize()
    {
        return tableSize;
    }
    string getID()
    {
        return ID;
    }
    void setID(string s)
    {
        ID = s;
    }
    ScopeTable *getParentScope()
    {
        return parentScope;
    }
    void setParentScope(ScopeTable *st)
    {
        parentScope = st;
    }

    unsigned long sdbmhash(string s)
    {
        // unsigned char *str = reinterpret_cast<unsigned char *>(const_cast<char *>(s.c_str()));
         unsigned long hash = 0;
        // lli c = 0;

        for(int i=0;i<s.size();i++)
        {
            hash = s[i] + (hash << 6) + (hash << 16) - hash;
        }

        return hash % tableSize;
    }

    bool Insert(string name, string type)
    {

        unsigned long ind;
        SymbolInfo *el = new SymbolInfo;
        el->setName(name);
        el->setType(type);
        el->setNextSymbolPointer(NULL);
        ind = sdbmhash(name);

        if (Lookup(name) != NULL)
        {
            return false;
        }

        if (headList[ind] == NULL)
        {
            headList[ind] = el;
            tailList[ind] = headList[ind];
        }
        else
        {
            tailList[ind]->setNextSymbolPointer(el);
            tailList[ind] = el;
        }
        // out << ind << headList[ind]->getName() << "inserted\n";
        return true;
    }

    bool Delete(string el)
    {

        // int elind = headList[ind].find(el);
        if (Lookup(el) == NULL)
        {
            // out << "not found\n";

            return false;
        }

        unsigned long ind;
        ind = sdbmhash(el);

        SymbolInfo *temp = new SymbolInfo;
        SymbolInfo *prev = new SymbolInfo;
        temp = headList[ind];
        prev = NULL;

        while (temp->getName() != el)
        {
            prev = temp;
            temp = temp->getNextSymbolPointer();
        }
        if (prev != NULL)
        {
            prev->setNextSymbolPointer(temp->getNextSymbolPointer());
            temp->setNextSymbolPointer(NULL);
        }
        else
        {
            headList[ind] = temp->getNextSymbolPointer();
            temp->setNextSymbolPointer(NULL);
        }
        if (tailList[ind]->getName() == temp->getName())
        {
            tailList[ind] = prev;
        }

        delete temp;
        // out << el << "deleted\n";
        return true;
    }

    SymbolInfo *Lookup(string el)
    {
        unsigned long ind;
        ind = sdbmhash(el);
        // int elind = headList[ind].find(el);

        SymbolInfo *sInfo = headList[ind];
        while (sInfo != NULL)
        {
            if (sInfo->getName() == el)
                return sInfo;

            sInfo = sInfo->getNextSymbolPointer();
        }
        return NULL;
    }
    plli insertionLocation(string el)
    {
        unsigned long ind;
        ind = sdbmhash(el);
        // int elind = headList[ind].find(el);

        SymbolInfo *sInfo = headList[ind];
        int cnt = 0;
        while (sInfo != NULL)
        {
            cnt++;
            if (sInfo->getName() == el)
                return {ind, cnt};

            sInfo = sInfo->getNextSymbolPointer();
        }
        return {-1, -1};
    }
    void Print(ofstream &out)
    {
        SymbolInfo *stemp;
        for (int i = 0; i < tableSize; i++)
        {
            out<<"\t"<<i+1;
            
            stemp = headList[i];
            while (stemp != NULL)
            {
                out << " --> (" << stemp->getName() << "," << stemp->getType() << ")";
                stemp = stemp->getNextSymbolPointer();
            }
            out << "\n";
        }
    }
    void clear(SymbolInfo *start)
    {

        while (start != NULL)
        {
            SymbolInfo *tmp = start;
            start = start->getNextSymbolPointer();
            delete tmp;
        }
    }
    void setChildCount(int x){
        childcnt=x;
    }
    int getChildCnt(){
        return childcnt;
    }
};
