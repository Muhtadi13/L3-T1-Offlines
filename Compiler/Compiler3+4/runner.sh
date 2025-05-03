yacc --yacc -Wcounterexample -d 2005013.y -o y.tab.cpp
flex -o 2005013.cpp 2005013.l
g++ -w *.
rm 2005013.cpp y.tab.cpp y.tab.hpp
./a.out input.txt