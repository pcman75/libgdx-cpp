///////////////////////////////////////////////////////////////////////////////
// Window.cpp
// ==========
// A class of Window for MS Windows
// It registers window class(WNDCLASSEX) with RegisterClassEx() and creates a 
// window with CreateWindowEx() API call.
//
//  AUTHOR: Song Ho Ahn
// CREATED: 2005-03-16
// UPDATED: 2006-09-20
///////////////////////////////////////////////////////////////////////////////

#pragma warning(disable : 4996)

#include "stdafx.h"

#include "Window.h"
#include "procedure.h"
using std::stringstream;
using std::cout;
using std::endl;
using namespace Win;




///////////////////////////////////////////////////////////////////////////////
// constructor with params
// NOTE: Windows does not clip a child window from the parent client's area.
// To prevent the parent window from drawing over its child window area, the
// parent window must have WS_CLIPCHILDREN flag.
///////////////////////////////////////////////////////////////////////////////
Window::Window(HINSTANCE hInst, const char* name, HWND hParent, Controller* ctrl) : handle(0), instance(hInst), controller(ctrl), winStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN),
                                                                                       winStyleEx(WS_EX_CLIENTEDGE), x(CW_USEDEFAULT), y(CW_USEDEFAULT),
                                                                                       width(CW_USEDEFAULT), height(CW_USEDEFAULT),
                                                                                       parentHandle(hParent), menuHandle(0)
{
    // copy string
    strncpy(this->title, name, MAX_STRING-1);
    strncpy(this->className, name, MAX_STRING-1);

    // populate window class struct
    winClass.cbSize        = sizeof(WNDCLASSEX);
    winClass.style         = 0;                             // class styles: CS_OWNDC, CS_PARENTDC, CS_CLASSDC, CS_GLOBALCLASS, ...
    winClass.lpfnWndProc   = Win::windowProcedure;          // pointer to window procedure
    winClass.cbClsExtra    = 0;
    winClass.cbWndExtra    = 0;
    winClass.hInstance     = instance;                      // owner of this class
    winClass.hIcon         = LoadIcon(0, IDI_APPLICATION);  // default icon
    winClass.hCursor       = LoadCursor(0, IDC_ARROW);      // default arrow cursor
    winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // default white brush
    winClass.lpszMenuName  = 0;
    winClass.lpszClassName = className;
    winClass.hIconSm       = LoadIcon(0, IDI_APPLICATION);  // default small icon
}



///////////////////////////////////////////////////////////////////////////////
// destructor
///////////////////////////////////////////////////////////////////////////////
Window::~Window()
{
    ::UnregisterClass(className, instance);
}



///////////////////////////////////////////////////////////////////////////////
// create a window
///////////////////////////////////////////////////////////////////////////////
HWND Window::create()
{
    // register a window class
    if(!::RegisterClassEx(&winClass)) return 0;

    handle = ::CreateWindowEx(winStyleEx,           // window border with a sunken edge
                              className,            // name of a registered window class
                              title,                // caption of window
                              winStyle,             // window style
                              x,                    // x position
                              y,                    // y position
                              width,                // witdh
                              height,               // height
                              parentHandle,         // handle to parent window
                              menuHandle,           // handle to menu
                              instance,             // application instance
                              (LPVOID)controller);  // window creation data

    //this->show(SW_SHOWDEFAULT);                     // make it visible

    return handle;
}



///////////////////////////////////////////////////////////////////////////////
// show the window on the screen
///////////////////////////////////////////////////////////////////////////////
void Window::show(int cmdShow)
{
    ::ShowWindow(handle, cmdShow);
    ::UpdateWindow(handle);
}



///////////////////////////////////////////////////////////////////////////////
// print itself
///////////////////////////////////////////////////////////////////////////////
void Window::printSelf() const
{
    stringstream wss;                          // wide char output string stream buffer

    // build output string
    wss << "=== Win::Window object ===\n"
        << "Name: " << title << "\n"
        << "Position: (" << x << ", " << y << ")\n"
        << "Width: " << width << "\n"
        << "Height: " << height << "\n"
        << "Handle: " << handle << "\n"
        << "Parent Handle: " << parentHandle << "\n"
        << "Menu Handle: " << menuHandle << "\n"
        << "Instance: " << instance << "\n"
        << "Controller: " << std::hex << controller << "\n"
        << endl;

    cout << wss.str();                         // print the string to the console
}



///////////////////////////////////////////////////////////////////////////////
// load an icon using resource ID and convert it to HICON
///////////////////////////////////////////////////////////////////////////////
HICON Window::loadIcon(int id)
{
    return (HICON)::LoadImage(instance, MAKEINTRESOURCE(id), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
}



///////////////////////////////////////////////////////////////////////////////
// load an icon using resource ID and convert it to HICON
///////////////////////////////////////////////////////////////////////////////
HICON Window::loadCursor(int id)
{
    return (HCURSOR)::LoadImage(instance, MAKEINTRESOURCE(id), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE);
}
