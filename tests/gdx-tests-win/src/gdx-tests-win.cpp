#include "stdafx.h"
#include "gdx-tests-win.h"
#include "resource.h"

HINSTANCE TheInstance = 0;

Controller::Controller (HWND hwnd)
{
    // Attach icon to main dialog
    HICON hIcon = LoadIcon (TheInstance, MAKEINTRESOURCE (DLG_ICON));
    SendMessage (hwnd, WM_SETICON, WPARAM (TRUE), LPARAM (hIcon));
    hIcon = LoadIcon (TheInstance, MAKEINTRESOURCE (DLG_ICON_S));
    SendMessage (hwnd, WM_SETICON, WPARAM (FALSE), LPARAM (hIcon));

	int idx = ::SendDlgItemMessage(hwnd, IDC_TESTS_LIST, LB_ADDSTRING, 0, (LPARAM)L"Test3");
	SendDlgItemMessage(hwnd, IDC_TESTS_LIST, LB_SETITEMDATA, (WPARAM)idx, (LPARAM)3);

	idx = ::SendDlgItemMessage(hwnd, IDC_TESTS_LIST, LB_ADDSTRING, 0, (LPARAM)L"Test1");
	SendDlgItemMessage(hwnd, IDC_TESTS_LIST, LB_SETITEMDATA, (WPARAM)idx, (LPARAM)1);
	
	idx = ::SendDlgItemMessage(hwnd, IDC_TESTS_LIST, LB_ADDSTRING, 0, (LPARAM)L"Test2");
	SendDlgItemMessage(hwnd, IDC_TESTS_LIST, LB_SETITEMDATA, (WPARAM)idx, (LPARAM)2);
	
	idx = ::SendDlgItemMessage(hwnd, IDC_TESTS_LIST, LB_ADDSTRING, 0, (LPARAM)L"Test5");
	SendDlgItemMessage(hwnd, IDC_TESTS_LIST, LB_SETITEMDATA, (WPARAM)idx, (LPARAM)5);
}

void Controller::Command (HWND hwnd, int controlID, int command)
{
    TCHAR statusMessage[64];

    switch (controlID)
    {
		case IDC_BUTTON_RUN:
			if (command == BN_CLICKED)
			{
				HWND hList = GetDlgItem(hwnd, IDC_TESTS_LIST);
                int index = ::SendMessage(hList, LB_GETCURSEL, 0, 0);
				int data = SendMessage(hList, LB_GETITEMDATA, (WPARAM)index, 0);
			}
			break;
    }
}

BOOL CALLBACK DialogProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static Controller* control = 0;
    switch (message)
    {
    case WM_INITDIALOG:
		control = new Controller (hwnd);
        return TRUE;
    case WM_COMMAND:
        control->Command(hwnd, LOWORD(wParam), HIWORD (wParam));
        return TRUE;
    case WM_DESTROY:
        PostQuitMessage(0);
        return TRUE;
    case WM_CLOSE:
        delete control;
        DestroyWindow (hwnd);
        return TRUE;
    }
    return FALSE;
}

int WINAPI WinMain
   (HINSTANCE hInst, HINSTANCE hPrevInst, char * cmdParam, int cmdShow)
{
    TheInstance = hInst;

    HWND hDialog = 0;

    hDialog = CreateDialog (hInst, MAKEINTRESOURCE (DLG_MAIN), 0, (DLGPROC)DialogProc);
    if (!hDialog)
    {
        TCHAR buf [100];
        wsprintf (buf, L"Error x%x", GetLastError ());
        MessageBox (0, buf, L"CreateDialog", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    MSG  msg;
    int status;
    while ((status = GetMessage (&msg, 0, 0, 0)) != 0)
    {
        if (status == -1)
            return -1;
        if (!IsDialogMessage (hDialog, &msg))
        {
            TranslateMessage ( &msg );
            DispatchMessage ( &msg );
        }
    }

    return msg.wParam;
}