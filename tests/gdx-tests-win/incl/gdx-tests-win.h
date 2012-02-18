#pragma once

class Controller
{
public:
    Controller(HWND hwnd);
    ~Controller ()
    {}
    void Command (HWND hwnd, int controlID, int command);
};
