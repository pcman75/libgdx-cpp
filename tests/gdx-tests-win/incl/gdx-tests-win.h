#pragma once
#include "GdxTest.h"

class Controller
{
public:
    Controller(HWND hwnd);
    ~Controller ()
    {}
    void Command (HWND hwnd, int controlID, int command);

private:
	void addTestToList(HWND hwnd, const char* testName);
	GdxTest* getSelectedTest(HWND hwnd);
};
