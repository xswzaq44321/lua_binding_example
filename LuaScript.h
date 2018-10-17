#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <vector>
#include <iostream>

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class LuaScript{
	public:
		LuaScript(const std::string& filename);
		~LuaScript();
		void printError(const std::string &variableName, const std::string& reason);

		template<typename T>
			T get(const std::string& variableName){
				if(!L){
					printError(variableName, "Script is not loaded");
					return lua_getdefault<T>();
				}

				T result;
				if(lua_gettostack(variableName)){
					result = lua_get<T>(variableName);
				}else{
					result = lua_getdefault<T>();
				}

				lua_pop(L, level + 1);
				return result;
			}
		bool lua_gettostack(const std::string& variableName);

		//generic get
		template<typename T>
			T lua_get(const std::string& variableName){
				return 0;
			}
		//generic default get
		template<typename T>
			T lua_getdefault(){
				return 0;
			}
	private:
		lua_State* L;
		std::string filename;
		int level;
};

#endif
