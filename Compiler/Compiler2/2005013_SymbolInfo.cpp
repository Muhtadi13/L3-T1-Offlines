#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define lli long long
#define plli pair<lli, lli>
#define MAX 5000006
//#define cin in
//#define cout out



using namespace std;
lli MOD = 1000000007LL;


class SymbolInfo
{
private:
    string name;
    string type;
    SymbolInfo *nextSymbolPointer;

public:
    SymbolInfo(){
        nextSymbolPointer=NULL;
    }
    SymbolInfo(const SymbolInfo &s)
    {
        name = s.name;
        type = s.type;
        nextSymbolPointer = NULL;
    }
    ~SymbolInfo()
    {
        nextSymbolPointer = NULL; 
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
    bool operator==(const SymbolInfo &sInfo)
    {
        if ((this->name) == (sInfo.name))
            return true;

        return false;
    }
};