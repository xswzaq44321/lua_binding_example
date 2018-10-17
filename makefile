main: main.o LuaScript.o
	g++ main.o LuaScript.o -o main -llua
main.o: main.cpp LuaScript.h
	g++ -c main.cpp
LuaScript.o: LuaScript.cpp LuaScript.h
	g++ -c LuaScript.cpp
clean:
	rm *.o
