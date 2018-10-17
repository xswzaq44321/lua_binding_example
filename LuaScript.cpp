#include <string>
#include <iostream>
#include "LuaScript.h"

LuaScript::LuaScript(const std::string& filename){
	L = luaL_newstate();
	if(luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)){
		std::cout << "Error: script not loaded (" << filename << ")" << std::endl;
		L = 0;
	}
}

LuaScript::~LuaScript(){
	if(L) lua_close(L);
}

void LuaScript::printError(const std::string& variableName, const std::string& reason){
	std::cout << "Error: can't get [" << variableName << "]. " << reason << std::endl;
}

template<>
inline std::string LuaScript::lua_getdefault(){
	return "null";
}

bool LuaScript::lua_gettostack(const std::string& variableName){
	level = 0;
	std::string var = "";
	for(unsigned int i = 0; i < variableName.size(); ++i){
		if(variableName.at(i) == '.'){
			if(level == 0){
				lua_getglobal(L, var.c_str());
			}else{
				lua_getfield(L, -1, var.c_str());
			}

			if(lua_isnil(L, -1)){
				printError(variableName, var + " is not defined");
				return false;
			}else{
				var = "";
				level++;
			}
			lua_getglobal(L, var.c_str());
		}else{
			var += variableName.at(i);
		}
	}
	if(level == 0){
		lua_getglobal(L, var.c_str());
	}else{
		lua_getfield(L, -1, var.c_str());
	}
	if(lua_isnil(L, -1)){
		printError(variableName, var + " is not defined");
		return false;
	}

	return true;
}

template<>
inline bool LuaScript::lua_get(const std::string& variableName){
	return (bool)lua_toboolean(L, -1);
}

template<>
inline float LuaScript::lua_get(const std::string& variableName){
	if(!lua_isnumber(L, -1)){
		printError(variableName, "Not a number");
	}
	return (float)lua_tonumber(L, -1);
}

template<>
inline int LuaScript::lua_get(const std::string& variableName){
	if(!lua_isnumber(L, -1)){
		printError(variableName, "Not a number");
	}
	return (int)lua_tonumber(L, -1);
}

template<>
inline std::string LuaScript::lua_get(const std::string& variableName){
	std::string s = "null";
	if(lua_isstring(L, -1)){
		s = std::string(lua_tostring(L, -1));
	}else{
		printError(variableName, "Not a string");
	}
	return s;
}
