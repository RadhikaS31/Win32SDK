
#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include"PhysicsDLL.h"
#include"DialogBox.h"
#include"MatPC.h"
#include"ChemistryDLL.h"

#import"Math.tlb" no_namespace, raw_interfaces_only
#include"Debug\math.tlh"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogProcM(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{

	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My Dialog");
	HRESULT hr;
	hr = CoInitialize(NULL);

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.cbClsExtra = 0;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hIconSm = LoadIcon(hInstance, TEXT("MY_ICON"));
	wndClass.hIcon = LoadIcon(hInstance, TEXT("MY_ICON"));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;


	RegisterClassEx(&wndClass);
	hwnd = CreateWindow(szAppName,
		TEXT("PhyChemMathBio"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		0);

	ShowWindow(hwnd, SW_MAXIMIZE);

	//	Update window
	UpdateWindow(hwnd);

	//	Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CoUninitialize();
	return ((int)msg.wParam);
}

//	Callback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP	hBitmap = NULL;
	HDC				hdcWnd = NULL;
	HDC				hdcBmp = NULL;
	RECT			rcWnd;
	BOOL			bRet = FALSE;
	HDC			hdc;
	PAINTSTRUCT	ps;
	TCHAR		str[] = TEXT("Press any key to continue .. !!!");
	RECT		rc;
	static HINSTANCE hInstance = NULL;
	static HINSTANCE hInstance1 = NULL;

	switch (iMsg)
	{
	case WM_CREATE:
		//	Load Bitmap
		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(SPLASHSCREEN));
		if (hBitmap == NULL)
		{
			MessageBox(hwnd, TEXT("Failed to load bitmap."), TEXT("Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}
	
		hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
		break;

	case WM_KEYDOWN:
		int id;
		switch (wParam)
		{
		case VK_SPACE:

			hInstance1 = (HINSTANCE)GetWindowLong(hwnd, -6);
			DialogBox(hInstance1, "MYDIALOG", hwnd, DialogProcM);
			break;

		case VK_ESCAPE:
			id = MessageBox(hwnd, "DO YOU WANT TO EXIT?", "MESSAGE", MB_YESNO | MB_ICONQUESTION);
			switch (id)
			{
			case IDYES:
				DestroyWindow(hwnd);
				break;
			case IDNO:
				break;
			}

		}
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rcWnd);
		hdcWnd = BeginPaint(hwnd, &ps);
		hdcBmp = CreateCompatibleDC(hdcWnd);
		SelectObject(hdcBmp, (HGDIOBJ)hBitmap);
		bRet = StretchBlt(hdcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top, hdcBmp, 0, 0, 1100, 650, SRCCOPY);
		if (bRet == FALSE)
		{
			MessageBox(hwnd, TEXT("Failed to bitmap on screen."), TEXT("Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		DeleteObject(hdcBmp);

		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, str, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		id = MessageBox(hwnd, "DO YOU WANT TO EXIT?", "MESSAGE", MB_YESNO | MB_ICONQUESTION);
		switch (id)
		{
		case IDYES:
			DestroyWindow(hwnd);
			break;
		case IDNO:
			break;
		}

		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

//	Dialog Procedure
BOOL CALLBACK DialogProcM(HWND hDlgM, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	//char StrSprintf[20];
	static char str[10];

	//CCW Math Specific
	CLSID clsidMath;
	long iMultiply = 0;
	void ComErrorDescriptionString(HWND, HRESULT);
	HRESULT hr;
	static _Math *app;
	int distance, constant, force;

	//Chemistry Specific
	ISearch *pISearch = NULL;
	HRESULT hrClassFactory;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		{
		//ID_RBPHYSICS
		SendDlgItemMessage(hDlgM, ID_RBMATH, BM_SETCHECK, 1, 0);

		SendDlgItemMessage(hDlgM, ID_CBDIRECTION1, CB_ADDSTRING, 0, (LPARAM)"Up");
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION1, CB_ADDSTRING, 0, (LPARAM)"Down");
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION1, CB_ADDSTRING, 0, (LPARAM)"Left");
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION1, CB_ADDSTRING, 0, (LPARAM)"Right");
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION1, CB_ADDSTRING, 0, (LPARAM)"UpLeft");
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION1, CB_ADDSTRING, 0, (LPARAM)"DownLeft");
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION1, CB_ADDSTRING, 0, (LPARAM)"UpRight");
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION1, CB_ADDSTRING, 0, (LPARAM)"DownRight");
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION1, CB_ADDSTRING, 0, (LPARAM)TEXT("TowardsWindow"));
	
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION1, CB_SETCURSEL, 3, 0);

		EnableWindow(GetDlgItem(hDlgM, ID_ETX1), TRUE);
		EnableWindow(GetDlgItem(hDlgM, ID_ETY1), TRUE);
		EnableWindow(GetDlgItem(hDlgM, ID_ETRADIUS1), TRUE);
		EnableWindow(GetDlgItem(hDlgM, ID_CBDIRECTION1), TRUE);


		SendDlgItemMessage(hDlgM, ID_CBDIRECTION2, CB_ADDSTRING , 0,(LPARAM)TEXT("Up"));
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION2, CB_ADDSTRING, 0, (LPARAM)TEXT("Down"));
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION2, CB_ADDSTRING, 0, (LPARAM)TEXT("Left"));
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION2, CB_ADDSTRING, 0, (LPARAM)TEXT("Right"));
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION2, CB_ADDSTRING, 0, (LPARAM)TEXT("UpLeft"));
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION2, CB_ADDSTRING, 0, (LPARAM)TEXT("DownLeft"));
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION2, CB_ADDSTRING, 0, (LPARAM)TEXT("UpRight"));
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION2, CB_ADDSTRING, 0, (LPARAM)TEXT("DownRight"));
		SendDlgItemMessage(hDlgM, ID_CBDIRECTION2, CB_ADDSTRING, 0, (LPARAM)TEXT("TowardsWindow"));

		SendDlgItemMessage(hDlgM, ID_CBDIRECTION2, CB_SETCURSEL, 3, 0);

		EnableWindow(GetDlgItem(hDlgM, ID_ETX2), TRUE);
		EnableWindow(GetDlgItem(hDlgM, ID_ETY2), TRUE);
		EnableWindow(GetDlgItem(hDlgM, ID_ETRADIUS2), TRUE);
		EnableWindow(GetDlgItem(hDlgM, ID_CBDIRECTION2), TRUE);

		/*********************************Chemistry*************************************/
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Hydrogen"));//1
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Helium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Lithium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Beryllium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Boron"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Carbon"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Nitrogen"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Oxygen"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Fluorine"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Neon"));//10

		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Sodium"));//11
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Magnesium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Aluminium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Silicon"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Phosphorus"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Sulfur"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Chlorine"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Argon"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Potassium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Calcium"));//20

		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Scandium"));//21
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Titanium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Vanadium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Chromium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Manganese"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Iron"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Cobalt"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Nickel"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Copper"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Zinc"));//30

		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Gallium"));//31
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Germanium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Arsenic"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Selenium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Bromine"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Krypton"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Rubidium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Strontium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Yttrium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Zirconium"));//40

		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Niobium"));//41
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Molybdenum"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Technetium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Ruthenium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Rhodium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Palladium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Silver"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Cadmium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Indium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Tin"));//50

		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Antimony"));//51
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Tellurium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Iodine"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Xenon"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Caesium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Barium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Lanthanum"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Cerium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Praseodymium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Neodymium"));//60

		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Promethium"));//61
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Samarium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Europium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Gadolinium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Terbium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Dysprosium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Holmium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Erbium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Thulium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Ytterbium"));//70

		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Lutetium"));//71
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Hafnium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Tantalum"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Tungsten"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Rhenium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Osmium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Iridium	"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Platinum"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Gold"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Mercury"));//80

		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Thallium"));//81
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Lead"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Bismuth"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Polonium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Astatine"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Radon"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Francium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Radium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Actinium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Thorium"));//90

		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Protactinium"));//91
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Uranium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Neptunium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Plutonium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Americium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Curium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Berkelium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Californium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Einsteinium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Fermium"));//100

		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Mendelevium"));//101
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Nobelium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Lawrencium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Rutherfordium"));
		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_ADDSTRING, 0, (LPARAM)TEXT("Dubnium"));//105

		SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_SETCURSEL, 3, 0);

		/*******************************************************************************/

		//CCW Math Specific
		
		hr = CLSIDFromProgID(L"Math.Math", &clsidMath);//

		if (FAILED(hr))
		{
			ComErrorDescriptionString(hDlgM, hr);
			DestroyWindow(hDlgM);
		}

		hr = CoCreateInstance(clsidMath, NULL, CLSCTX_INPROC_SERVER, __uuidof(_Math), (VOID **)&app);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(hDlgM, hr);
			exit(0);
		}

		}
		return TRUE;


	case WM_COMMAND:
		{
		BOOL CollisionResult;
		HMODULE hLib = NULL;
		typedef int(*pfnValidateCollision)(int, int, int, int,int,int,int,int);
		pfnValidateCollision pfn = NULL;
		int x1, x2, y1, y2, r1, r2, d1, d2, xy, ab;

		switch (LOWORD(wParam))
			{
		case ID_CANCEL:
			EndDialog(hDlgM, 0);
			break;

		case ID_ValidateCollision:

			x1 = GetDlgItemInt(hDlgM, ID_ETX1, NULL, TRUE);
			y1 = GetDlgItemInt(hDlgM, ID_ETY1, NULL, TRUE);
			r1 = GetDlgItemInt(hDlgM, ID_ETRADIUS1, NULL, TRUE);
			d1 = GetDlgItemInt(hDlgM, ID_CBDIRECTION1, NULL, TRUE);
			xy = SendDlgItemMessage(hDlgM, ID_CBDIRECTION1, CB_GETCURSEL, d1, 0);

			x2 = GetDlgItemInt(hDlgM, ID_ETX2, NULL, TRUE);
			y2 = GetDlgItemInt(hDlgM, ID_ETY2, NULL, TRUE);
			r2 = GetDlgItemInt(hDlgM, ID_ETRADIUS2, NULL, TRUE);
			d2 = GetDlgItemInt(hDlgM, ID_CBDIRECTION2, NULL, TRUE);
			ab = SendDlgItemMessage(hDlgM, ID_CBDIRECTION2, CB_GETCURSEL, d2, 0);

			hLib = LoadLibrary(TEXT("PhysicsDLL.dll"));

			if (hLib == NULL)
			{
				MessageBox(hDlgM, "Dll could not be loaded!", "Messages", MB_OK);
				DestroyWindow(hDlgM);

			}
		
			GetProcAddress(hLib, "ValidateCollision");
			pfn = (pfnValidateCollision)GetProcAddress(hLib, "ValidateCollision");
		

			CollisionResult = pfn(x1, y1, x2, y2,r1,r2,xy,ab);
			if (CollisionResult == TRUE)
			{
				MessageBox(hDlgM, "congrats!! Collision Detected, BOOM ", "Message", MB_OK);
			}
			else
			{
				MessageBox(hDlgM, "oops!!! No Collision Detected, SORRY ", "Message", MB_OK);
			}
			break;

		case ID_RBMATH:
			EnableWindow(GetDlgItem(hDlgM, ID_ETX1), TRUE);
			EnableWindow(GetDlgItem(hDlgM, ID_ETY1), TRUE);
			EnableWindow(GetDlgItem(hDlgM, ID_ETRADIUS1), TRUE);
			EnableWindow(GetDlgItem(hDlgM, ID_CBDIRECTION1), TRUE);

			break;
			
		case IDB_FORCE:
	
			distance = GetDlgItemInt(hDlgM, ID_DISTANCE, NULL, TRUE);
			constant = GetDlgItemInt(hDlgM, ID_CONSTANT, NULL, TRUE);

			hr = app->Force(constant,distance, &iMultiply);

			if (FAILED(hr))
			{
				ComErrorDescriptionString(hDlgM, hr);
				exit(0);
			}

			SetDlgItemInt(hDlgM, ID_FORCE, iMultiply, TRUE);
				break;

		case IDB_CONSTANT:
			force = GetDlgItemInt(hDlgM, ID_FORCE, NULL, TRUE);
			distance= GetDlgItemInt(hDlgM, ID_DISTANCE, NULL, TRUE);

			hr = app->Constant(force, distance, &iMultiply);

			if (FAILED(hr))
			{
				ComErrorDescriptionString(hDlgM, hr);
				exit(0);
			}

			SetDlgItemInt(hDlgM, ID_CONSTANT, iMultiply, TRUE);
			break;
			
		case IDB_DISTANCE:
			force = GetDlgItemInt(hDlgM, ID_FORCE, NULL, TRUE);
			constant = GetDlgItemInt(hDlgM, ID_CONSTANT, NULL, TRUE);

			hr = app->Distance(force, constant, &iMultiply);

			if (FAILED(hr))
			{
				ComErrorDescriptionString(hDlgM, hr);
				exit(0);
			}

			SetDlgItemInt(hDlgM, ID_DISTANCE, iMultiply, TRUE);
			break;

		case IDB_SEARCHELEMENT:
		//Chemistry Item
		int DataDlg,DataDlg2;
		DataDlg = GetDlgItemInt(hDlgM, ID_ETNUMBER, NULL, TRUE);
		DataDlg2 = SendDlgItemMessage(hDlgM, ID_ETNUMBER, CB_GETCURSEL, DataDlg, 0);
		hrClassFactory = CoCreateInstance(CLSID_Chemistry, NULL, CLSCTX_INPROC_SERVER, IID_ISearch, (void **)&pISearch);
		if (FAILED(hrClassFactory))
		{
			MessageBox(hDlgM, TEXT("ISum Interface Can not be found"), TEXT("Error"), MB_OK);
			exit(0);
			DestroyWindow(hDlgM);
		}
		DataDlg2 = DataDlg2 + 1;
		pISearch->ElementSearch(DataDlg2);
		pISearch->Release();
		pISearch = NULL;

			break;
			}
		}
		return(TRUE);
	}
	return (FALSE);
}


BOOL CALLBACK DialogProcC(HWND hDlgC, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}



void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		sprintf_s(str, TEXT("%s"), szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
		sprintf_s(str, TEXT("[Colud not find a description for error # %#x.]\n"), hr);
	MessageBox(hwnd, str, TEXT("Com Error 1 "), MB_OK);
}



