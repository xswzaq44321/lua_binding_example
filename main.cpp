#include <iostream>
#include <string>
#include "LuaScript.h"
using namespace std;

int main(){
	LuaScript script("player.lua");
	float posX = script.get<float>("player.position.x");
	float posY = script.get<float>("player.position.y");
	cout << "posX, posY = " << posX << "," << posY;
}
