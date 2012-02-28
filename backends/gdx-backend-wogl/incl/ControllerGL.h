///////////////////////////////////////////////////////////////////////////////
// ControllerGL.h
// ==============
// Derived Controller class for OpenGL window
// It is the controller of OpenGL rendering window. It initializes DC and RC,
// when WM_CREATE called, then, start new thread for OpenGL rendering loop.
//
// When this class is constructed, it gets the pointers to model and view
// components.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gamil.com)
// CREATED: 2006-07-09
// UPDATED: 2007-07-21
///////////////////////////////////////////////////////////////////////////////

#ifndef WIN_CONTROLLER_GL_H
#define WIN_CONTROLLER_GL_H

#include "Controller.h"
#include "ViewGL.h"
#include "WoglGraphics.h"
#include "ViewGL.h"
#include "WindowsInput.h"


namespace Win
{
    class ControllerGL : public Controller
    {
    public:
        ControllerGL(WoglGraphics* graphics, WindowsInput* input, ViewGL* view); // ctor with params
        ~ControllerGL() {};                         // dtor

        int close();                                // close the RC and destroy OpenGL window
        int command(int id, int cmd, LPARAM msg);   // for WM_COMMAND
        int create();                               // create RC for OpenGL window and start new thread for rendering
        int paint();
        int lButtonDown(WPARAM state, int x, int y);
        int lButtonUp(WPARAM state, int x, int y);
        int rButtonDown(WPARAM state, int x, int y);
        int rButtonUp(WPARAM state, int x, int y);
        int mouseMove(WPARAM state, int x, int y);
        int keyDown(int key, LPARAM lParam);
        int size(int width, int height, WPARAM type);

    private:
        static void threadFunction(void* arg);      // static thread function, it will route to member function, runThread()
        void runThread();                           // thread for OpenGL rendering

        WoglGraphics* m_pGraphics;                           //
		WindowsInput* m_pInput;
        ViewGL* viewGL;                             //
        HANDLE threadHandle;
        unsigned int threadId;
        volatile bool loopFlag;                     // rendering loop flag
        bool resizeFlag;
        int clientWidth;                            // width of client area
        int clientHeight;                           // height of client area
    };
}

#endif
