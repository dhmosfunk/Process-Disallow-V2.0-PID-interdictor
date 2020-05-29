/* 
	Author : Dhmosthenhs Xama
	File: main.cpp
*/
 
#include <iostream>

#include "pr_Functions.h"

using namespace std;

vector <string> banned_pids={"example.exe","example.exe","example.exe","example.exe","example.exe"};//Update from here banned pids.

int main(){
	hideConsole();

	while(true){
		if (GetAsyncKeyState(VK_NUMPAD0) && GetAsyncKeyState(VK_NUMPAD1)){
				while (true){
					if (GetAsyncKeyState(VK_NUMPAD9) && GetAsyncKeyState(VK_NUMPAD8)){
						break;
					}
					else continue;
				}
			}
			else killProcesses(banned_pids);
	}

	return 0;
}
