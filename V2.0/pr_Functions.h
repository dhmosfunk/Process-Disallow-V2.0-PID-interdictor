/* 
	Author : Dhmosthenhs Xama
	File: pr_Functions.h
*/

#include <windows.h>
#include <vector>

using namespace std;

void hideConsole();
void writeLogs(string pid_name);
void errorMsgBox(LPCTSTR boxTitle, LPCTSTR message);
BOOL killProcesses(vector <string> banned_pids);
BOOL TerminateMyProcess(DWORD dwProcessId, UINT uExitCode);
//string readLogs(string filename);
void thRestart();
