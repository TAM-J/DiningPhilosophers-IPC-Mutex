#include<iostream>
#include<Windows.h>
using namespace std;
#define EXE_FILENAME "C:\\Users\\repos\\Debug\\mtx.exe"
#define NUM_PROCESSES 5
int main()
{
	for (int i = 0; i < 5; i++) {
		PCHAR tmp = (PCHAR)malloc(9);
		sprintf_s(tmp, 9, "String %d", i);
		CreateMutexA(NULL, FALSE, tmp);
	}
	INT size = strlen(EXE_FILENAME) + 3;
	PCHAR param = (PCHAR)malloc(size * sizeof(CHAR));
	STARTUPINFOA si;
	PROCESS_INFORMATION pi[NUM_PROCESSES];
	for (int i = 0; i < NUM_PROCESSES; i++)
	{
		sprintf_s(param, size, "%s %d", EXE_FILENAME, i + 1);
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi[i], sizeof(pi[i]));
		CreateProcessA(
			NULL,
			param,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi[i]);
	}
	for (int i = 0; i < 5; i++) {
		WaitForSingleObject(pi[i].hProcess, INFINITE);
	}

}