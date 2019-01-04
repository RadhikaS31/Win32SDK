#include<windows.h>
#include"PhysicsDLL.h"
#include<math.h>

int gx1, gy1, gr1, gd1; // x, y, radius and direction for circle1
int gx2, gy2, gr2, gd2; // x, y, radius and direction for circle2
int gcollision;
BOOL Collision = FALSE;
BOOL C1OutofBound = FALSE;
BOOL C2OutofBound = FALSE;

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

HMODULE hDll;

BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)// Entry point function

{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	break;

	case DLL_THREAD_ATTACH:
	break;

	case DLL_PROCESS_DETACH:
	break;

	case DLL_THREAD_DETACH:
	break;
	}
	return(true);
}



extern "C" BOOL ValidateCollision(int gx1, int gy1, int gx2, int gy2,int r1,int r2,int d1,int d2)
{
	
	static HANDLE hThreadOne = NULL, hThreadTwo = NULL;

	hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hDll, 0, NULL);
	hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hDll, 0, NULL);

	while (1)
	{
		if(C1OutofBound == TRUE && C2OutofBound == TRUE)
		{
			Collision = FALSE;
			break;
		}
		if((sqrt((gx2 - gx1)*(gx2 - gx1) + (gy2 - gy1)*(gy2 - gy1))) < (gr1 + gr2))
		{
			Collision = TRUE;
			break;
		}
	}
	return (gcollision);

}

DWORD WINAPI ThreadProcOne(LPVOID param)
{
	while (1)
	{
		if (gx1 < 0 || gx1 > 1366 || gy1 < 0 || gy1 > 768)
		{
			C1OutofBound = TRUE;
			break;
		}

		switch (gd1)
		{
		case 0:gy1--; //up
			break;

		case 1:gy1++; //down
			break;

		case 2: gx1--; //left
			break;

		case 3:gx1++; //right
			break;

		case 4:(gx2-- && gy2--); //up left
			break;

		case 5:(gx2-- && gy2++); //downleft
			break;

		case 6:(gx2++ && gy2--); //up right
			break;

		case 7:(gx2++ && gy2++); //down right
			break;
		}
	}
	return (0);
}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	while (1)
	{
		if (gx2 < 0 || gx2 > 1366 || gy2 < 0 || gy2 > 768)
		{
			C2OutofBound = TRUE;
			break;
		}

		switch (gd2)
		{
		case 0:gy2--; //up
			break;

		case 1:gy2++; //down
			break;
			
		case 2:gx2--; //left
			break;

		case 3:gx2++; //right
			break;

		case 4:(gx2-- && gy2--); //up left
			break;

		case 5:(gx2-- && gy2++); //downleft
			break;

		case 6:(gx2++ && gy2--); //up right
			break;

		case 7:(gx2++ && gy2++); //down right
			break;
		}
	}
	return(0);
}
