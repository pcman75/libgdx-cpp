#include "StdAfx.h"
#include "WoglApplication.h"
#include "WoglGraphics.h"
#include "WoglInput.h"
#include "WoglFiles.h"

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[256];					// The title bar text
TCHAR szWindowClass[20];			// the main window class name

HDC hDC;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


void ResizeGraphics(HWND hWnd);
void InitGraphics(HWND hWnd);
void DrawGraphics();


WoglApplication::WoglApplication (const ApplicationListener& listener, const wchar_t* title, int width, int height, bool useGL20IfAvailable)
{
	logLevel = LOG_INFO;
	m_pGraphics = new WoglGraphics();
	m_pInput = new WoglInput();
	m_pFiles = new WoglFiles();

	hDC = NULL;
	// Initialize global strings

	wcscpy_s(szTitle, title);
	wcscpy_s( szWindowClass, L"OpenGLTest");

	//get instance of current program (self)
	HINSTANCE hInst= GetModuleHandle (0);	
	MyRegisterClass(hInst);

	// Perform application initialization:
	InitInstance (hInst, SW_SHOWNORMAL);
	
	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		DrawGraphics();
	}

	//wglDeleteContext(hRC);
    //ReleaseDC(hWnd, hDC);
}

WoglApplication::~WoglApplication(void)
{
	delete m_pGraphics;
	delete m_pInput;
	delete m_pFiles;
	//delete m_pAudio;
}

const Graphics& WoglApplication::getGraphics ()
{
	return *m_pGraphics;
}


/*
const Audio& WoglApplication::getAudio ()
{
	return *m_pAudio;
}
*/

const Input& WoglApplication::getInput ()
{
	return *m_pInput;
}


const Files& WoglApplication::getFiles ()
{
	return *m_pFiles;
}


void WoglApplication::log(const wchar_t* tag, const wchar_t* message)
{
}

/* TODO imlement it only iof it's the case i.e u used C++ throw exceptions or gdx throws exceptions
void WoglApplication::log (const wchar_t* tag, const wchar_t* message, std::exception ex)
{
	if (logLevel >= LOG_INFO)
	{
		log(tag, message + ex.what());
	}
}
*/
void WoglApplication::error (const wchar_t* tag, const wchar_t* message)
{
}

//void WoglApplication::error (const wchar_t* tag, const wchar_t* message, std::exception ex)
//{
//}

void WoglApplication::debug (const wchar_t* tag, const wchar_t* message)
{
}

//void WoglApplication::debug (const wchar_t* tag, const wchar_t* message, std::exception ex)
//{
//}


void WoglApplication::setLogLevel (int logLevel)
{
}

 WoglApplication::ApplicationType WoglApplication::getType ()
{
	return Windows;
}


int WoglApplication::getVersion ()
{
	return 0;
}

//TODO: possible?
/** @return the heap memory use in bytes */
//long getHeap ();

//const Preferences& WoglApplication::getPreferences (const wchar_t* name)
//{
//	return 
//}

void WoglApplication::exit()
{
	//TODO: send WM_CLOSE
	exit();
}







//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OPENGLTEST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_OPENGLTEST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   // Initialize OpenGL
   InitGraphics(hWnd);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		ResizeGraphics(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//open GL


// Set up pixel format for graphics initialization
void SetupPixelFormat()
{
    PIXELFORMATDESCRIPTOR pfd, *ppfd;
    int pixelformat;

    ppfd = &pfd;

    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_COLORINDEX;
    ppfd->cColorBits = 16;
    ppfd->cDepthBits = 16;
    ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 0;

    pixelformat = ChoosePixelFormat(hDC, ppfd);
    SetPixelFormat(hDC, pixelformat, ppfd);
}

// Initialize OpenGL graphics
void InitGraphics(HWND hWnd)
{
    hDC = GetDC(hWnd);

    SetupPixelFormat();

    HGLRC hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

    glClearColor(0, 0, 0, 0.5);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}

// Resize graphics to fit window
void ResizeGraphics(HWND hWnd)
{
    // Get new window size
    RECT rect;
	int width, height;
	GLfloat aspect;

    GetClientRect(hWnd, &rect);
    width = rect.right;
    height = rect.bottom;
    aspect = (GLfloat)width / height;

    // Adjust graphics to window size
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Draw frame
void DrawGraphics()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set location in front of camera
    glLoadIdentity();
    glTranslated(0, 0, -10);

    // Draw a square
    glBegin(GL_QUADS);
    glColor3d(1, 1, 0);
    glVertex3d(-2, 2, 0);
    glVertex3d(2, 2, 0);
    glVertex3d(2, -2, 0);
    glVertex3d(-2, -2, 0);
    glEnd();

    // Show the new scene
    SwapBuffers(hDC);
}
