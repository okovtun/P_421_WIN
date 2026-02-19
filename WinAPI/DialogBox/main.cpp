#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_INVITE[] = "Введите имя пользователя";
//g_ - Global (глобальная переменная или константа)
//sz_ - String Zero (строка, заканчивающаяся нулем - NULL Terminated Line)

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//HWND - Handler to Window. 
	//Это указатель, при помощи которого можно обратиться к окну.
	//(указатель, на который можно отправить сообщение - SendMessage)
	//Focus - это часть окна, которая принимает команды с клавиатуры.
	//Фокус переключается клавишей 'Tab' и стрелками.
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_INVITE);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			//WPARAM - это DWORD
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_INVITE) == 0)
				//https://legacy.cplusplus.com/reference/cstring/strcmp/
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_INVITE);

		}
		break;
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;		//Размер буфера 256 Байт
			CHAR sz_buffer[SIZE] = {};	//Текстовый буфер
			//Получаем текстовые поля, чтобы к ним можно было обращаться:
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			//Для того чтобы обратиться к какому-либо элементу окна,
			//ему нужно отправить сообщение:
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);	//считываем текст из поля 'Login'
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);	//загружаем текст из буфера в поле 'Password'
		}
		break;
		case IDOK:
			MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}