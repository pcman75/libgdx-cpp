#include "stdafx.h"
#include "gdx-tests-win.h"
#include "resource.h"

#include "GdxTests.h"
#include "WoglApplication.h"
#include "GlfwApplication.h"

HINSTANCE TheInstance = 0;

Controller::Controller(HWND hwnd)
{
    // Attach icon to main dialog
    HICON hIcon = LoadIcon (TheInstance, MAKEINTRESOURCE (DLG_ICON));
    SendMessage (hwnd, WM_SETICON, WPARAM (TRUE), LPARAM (hIcon));
    hIcon = LoadIcon (TheInstance, MAKEINTRESOURCE (DLG_ICON_S));
    SendMessage (hwnd, WM_SETICON, WPARAM (FALSE), LPARAM (hIcon));

	for(GdxTests::TestsMapIterator it = GdxTests::tests.begin(); it != GdxTests::tests.end(); it++)
		addTestToList(hwnd, it->first.c_str());
}

void Controller::addTestToList(HWND hwnd, const char* testName)
{
	::SendDlgItemMessage(hwnd, IDC_TESTS_LIST, LB_ADDSTRING, 0, (LPARAM)testName);
}

void Controller::Command (HWND hwnd, int controlID, int command)
{
    switch (controlID)
    {
		case IDC_BUTTON_RUN:
			if (command == BN_CLICKED)
			{
				GdxTest* test = NULL;
				HWND hList = ::GetDlgItem(hwnd, IDC_TESTS_LIST);

					// Get current selection index in listbox
				int itemIndex = (int) ::SendMessage(hList, LB_GETCURSEL, (WPARAM)0, (LPARAM) 0);
				if (itemIndex != LB_ERR)
				{
						// Get length of text in listbox
					int textLen = (int) SendMessage(hList, LB_GETTEXTLEN, (WPARAM) itemIndex, 0);
		
					// Allocate buffer to store text (consider +1 for end of string)
					TCHAR * textBuffer = new TCHAR[textLen + 1];

					// Get actual text in buffer
					SendMessage(hList, LB_GETTEXT, (WPARAM) itemIndex, (LPARAM) textBuffer );

					test = GdxTests::newTest(textBuffer);
					if(test)
					{
						GlfwApplication(*test, textBuffer, 400, 300, test->needsGL20());
						delete test;
					}
					delete[] textBuffer;
				}
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
        wsprintf (buf, "Error x%x", GetLastError ());
        MessageBox (0, buf, "CreateDialog", MB_ICONEXCLAMATION | MB_OK);
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