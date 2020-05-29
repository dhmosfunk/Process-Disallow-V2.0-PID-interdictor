/* 
	Author : Dhmosthenhs Xama
	File: pr_Functions.cpp
*/

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>
#include <TlHelp32.h>
#include <thread>

#include "pr_Functions.h"

using namespace std;

void hideConsole(){ //Hide console under programs
	FreeConsole();
}

void writeLogs(string pid_name) {

	auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
	auto ti = ctime(&timenow);

	ofstream logfile;
	logfile.open("logs.log", ios::out | ios::app | ios::binary);//open [logs.log] for append or create it.
	logfile << "A forbidden process was opened as [ NULL ] PID Name [ " + pid_name + " ] on [ " + ti + " ]\n";
												/*USERNAME*/
	logfile.close();
}

void errorMsgBox(LPCTSTR boxTitle, LPCTSTR message) {
	LPCTSTR Caption = boxTitle;
	MessageBox(NULL,
		message,
		Caption,
		MB_OK | MB_ICONERROR);
}

BOOL killProcesses(vector <string> banned_pids) {
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return(FALSE);
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);  // clean the snapshot object
		return(FALSE);
	}

	// Now walk the snapshot of processes 
	
	do {
		string str(pe32.szExeFile);
		for (int i = 0; i < banned_pids.size(); i++) {
			if (str == banned_pids[i])
			{
				thread terminatePR(TerminateMyProcess, pe32.th32ProcessID, 1);
				if (terminatePR.joinable()) {
					terminatePR.detach();
				}
				writeLogs(banned_pids[i]);
				thread therrormsgBox(errorMsgBox, "Forbidden proccess.", "A wrong process was opened.\n\nYou have opened a forbidden process by the system,\nplease press [OK] to continue.");
				if (therrormsgBox.joinable()) {
					therrormsgBox.detach();
				}
				thRestart();
			}
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return(TRUE);
}

BOOL TerminateMyProcess(DWORD dwProcessId, UINT uExitCode) {
	DWORD dwDesiredAccess = PROCESS_TERMINATE;
	BOOL  bInheritHandle = FALSE;
	HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	if (hProcess == NULL)
		return FALSE;

	BOOL result = TerminateProcess(hProcess, uExitCode);

	CloseHandle(hProcess);

	return result;
}

/*
string readLogs(string filename){
	string line;
	ifstream myfile(filename);
	
	if (myfile.is_open()){
    	while(getline(myfile,line)){
			cout << line << endl;
		}
    myfile.close();
	}

  else cout << "Unable to open file";
	
	
}
*/

void thRestart() {
	system("shutdown -t 3 -r -f"); //restart system command.
}




