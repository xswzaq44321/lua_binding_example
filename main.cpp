#include <iostream>
#include <string>
#include "LuaScript.h"
using namespace std;

int main(){
	LuaScript script("Player.lua");
	float posX = script.get<float>("player.position.x");
	cout << posX;
}
