#include <iostream>
#include <Windows.h>
using namespace std;
int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Incorrect number of arguments\n");
		return 0;
	}
	int num = atoi(argv[1]);
	PCHAR N1 = (PCHAR)malloc(9);
	sprintf_s(N1, 9, "String %d", num);
	PCHAR N2 = (PCHAR)malloc(9);
	sprintf_s(N2, 9, "String %d", num % 5);
	HANDLE MTX[2];
	for (int i = 0; i < 2; i++)
		MTX[i] = CreateMutexA(NULL, FALSE, N1);
	int eating = 0;
	while (eating != 1000000) {
		WaitForSingleObject(MTX[0], INFINITE);
		DWORD WR = WaitForSingleObject(MTX[1], 0);
		if (WR == WAIT_OBJECT_0)
		{
			eating++;
			ReleaseMutex(MTX[1]);
		}
		ReleaseMutex(MTX[0]);
	}
	printf("Philosopher %d ate and satiated \n", (num + 1));
	for (int i = 0; i < 2; i++)
		CloseHandle(MTX[i]);
	return 1;
}