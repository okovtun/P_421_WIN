#include<Windows.h>
#include<iostream>
#include"resource.h"

CONST CHAR* ITEMS[] = { "This", "is", "my", "first", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		//https://stackoverflow.com/questions/15543571/allocconsole-not-displaying-cout
		for (int i = 0; i < sizeof(ITEMS)/sizeof(ITEMS[0]) ; i++)
		{
			//std::cout << ITEMS[i] << std::endl;
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)ITEMS[i]);
		}
	}
	break;
	case WM_COMMAND:
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}