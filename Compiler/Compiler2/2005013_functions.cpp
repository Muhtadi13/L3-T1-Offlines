#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;
ofstream outtoken;
ofstream outlog;
int linecount = 1;
int errorcount = 0;
int warningcount = 0;
int tabcount = 0;
int cntf = 0;
int cntw = 0;
int cntt = 0;
int cntv = 0;
bool islinestart = true;

void replaceString(string &source, string const &tofind, string const &target)
{
    for (string::size_type i = 0; (i = source.find(tofind, i)) != string::npos;)
    {
        source.replace(i, tofind.length(), target);
        i += target.length();
    }
}

void replaceBegin(string &source, string const &tofind, string const &target)
{
    string::size_type i = source.find(tofind, 0);
    if (i != string::npos)
    {
        source.replace(i, tofind.length(), target);
    }
}

void replaceEnd(string &source, string const &tofind, string const &target)
{
    string::size_type i = source.rfind(tofind);
    if (i != string::npos)
    {
        source.replace(i, tofind.length(), target);
    }
}

string replaceAllSpecialCharacter(string &source)
{
    string tmp = source;

    replaceString(tmp, "\\n", "\n");
    replaceString(tmp, "\\t", "\t");
    replaceString(tmp, "\\\'", "\'");
    replaceString(tmp, "\\\"", "\"");
    replaceString(tmp, "\\a", "\a");
    replaceString(tmp, "\\0", "\0");
    replaceString(tmp, "\\f", "\f");
    replaceString(tmp, "\\r", "\r");
    replaceString(tmp, "\\b", "\b");
    replaceString(tmp, "\\v", "\v");
    replaceString(tmp, "\\\\", "\\");
    
    
    return tmp;
}

string fromLast(string &source, string const &tofind)
{
    int i = source.rfind(tofind);
    string ret = "";
    if (i < source.size() - 1)
    {
        ret = source.substr(i + 1);
    }
    return ret;
}
void showWarning()
{
    if (islinestart)
    {
        if (!(cntt == tabcount && cntw == 0))
        {
            warningcount++;

            if (cntt != tabcount)
            {
                outlog << "Line# " << linecount << ": warning, " << tabcount << " of tabs needed but got " << cntt << " tabs.\n";
            }
            else
            {
                outlog << "Line# " << linecount << ": Warning, tab requrired but got space.\n";
            }
        }
        islinestart=false;
    }
}

string makeUpperString(string &str)
{
    string ret = str;
    for (int i = 0; i < ret.size(); i++)
    {
        ret[i] = toupper(ret[i]);
    }
    return ret;
}
