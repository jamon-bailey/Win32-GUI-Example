
#include <Windows.h>
#include "window_proc.hpp"

static constexpr LPCSTR WINDOW_CLASS_NAME = "MainAppWindow";

// Application Entry Point:
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point
//
// GUI Window Creation:
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/creating-a-window
//
// Composing Windows GUI Program:
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // ---> Register Window Class <----------------------------------------------------------
    WNDCLASSEX windowClass{};

    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.lpszClassName = WINDOW_CLASS_NAME;
    windowClass.lpfnWndProc = &windowProcedure;
    windowClass.hInstance = hInstance;
    
    auto windowClassId = RegisterClassEx(&windowClass);
    // ----------------------------------------------------------> Register Window Class <---

    // ---> Create Window From Class <-------------------------------------------------------
    HWND windowHandle = CreateWindowEx(
        NULL,                                    ///< Optional window style
        WINDOW_CLASS_NAME,                       ///< Window class name
        "Demo Win32 Application",                ///< Window titlebar text
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, ///< Window style
        CW_USEDEFAULT,                           ///< Window x-coordinate
        CW_USEDEFAULT,                           ///< Window y-coordinate
        800,                                     ///< Window width
        500,                                     ///< Window height
        NULL,                                    ///< Parent window handle
        NULL,                                    ///< Window menu handle
        hInstance,                               ///< Instance handle???
        nullptr                                  ///< Additional application data???
    );
    // -------------------------------------------------------> Create Window From Class <---

    if (windowHandle == NULL)
        return 100;

    ShowWindow(windowHandle, nCmdShow);

    // ---> Run Window Event Loop <----------------------------------------------------------
    MSG msg{};

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // ----------------------------------------------------------> Run Window Event Loop <---

    return 0;
}
