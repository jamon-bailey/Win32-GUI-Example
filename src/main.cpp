
#include <Windows.h>
#include "window_proc.hpp"

// Application Entry Point:
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point
//
// GUI Window Creation:
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/creating-a-window
//
// Composing Windows GUI Program:
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program

/*!
 * @brief
 * Main application window class name.
 */
static constexpr LPCSTR APP_CLASS_NAME = "Win32 Demo";
static constexpr LPCSTR WINDOW_TITLE_TEXT = "Demo Win32 Application";

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // ---> Register Window Class <----------------------------------------------------------
    WNDCLASSEX windowClass{}; ///< Window class description
    windowClass.cbSize = sizeof(WNDCLASSEX);                    ///< Window class structure version indicator
    windowClass.hInstance = hInstance;                          ///< Handle to module registering window class
    windowClass.lpszClassName = APP_CLASS_NAME;                 ///< Window family (class) name
    windowClass.lpfnWndProc = &windowProcedure;                 ///< Window class procedure function
    windowClass.style = CS_HREDRAW | CS_VREDRAW;                ///< Window class property (style) flags
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);          ///< Window class cursor shape
    windowClass.hbrBackground = GetSysColorBrush(COLOR_WINDOW); ///< Delegate minimum window repaint to Win32 API
    
    auto windowClassId = RegisterClassEx(&windowClass);
    // ----------------------------------------------------------> Register Window Class <---

    // Check that window class registration did not fail
    if (!windowClassId)
        return 1;

    // ---> Create Window From Class <-------------------------------------------------------
    HWND windowHandle = CreateWindowEx( ///< Handle to main application window
        NULL,                ///< Extended window property (style) flags
        APP_CLASS_NAME,      ///< Window family (class) name
        WINDOW_TITLE_TEXT,   ///< Window titlebar text
        WS_OVERLAPPEDWINDOW, ///< Window property (style) flags
        CW_USEDEFAULT,       ///< Window x-coordinate
        CW_USEDEFAULT,       ///< Window y-coordinate
        800,                 ///< Window width
        500,                 ///< Window height
        NULL,                ///< Parent window handle
        NULL,                ///< Handle to window menu
        hInstance,           ///< Handle to module that registered window class
        nullptr              ///< Optional data passed on window startup (WM_CREATE)
    );
    // -------------------------------------------------------> Create Window From Class <---

    // Check that window creation did not fail
    if (windowHandle == NULL)
        return 100;

    // Make newly created window visible on screen
    ShowWindow(windowHandle, nCmdShow);

    // ---> Run Window Event Loop <----------------------------------------------------------
    MSG msg{};
    BOOL run;

    do {
        // Block until next message is received from queue
        run = GetMessage(&msg, NULL, 0, 0);

        // Check for event loop end signal
        if (run == FALSE) {
            run = static_cast<BOOL>(msg.wParam);
            break; // Terminate window event loop
        }

        TranslateMessage(&msg); // Translates keystrokes into characters
        DispatchMessage(&msg);  // Call target window procedure function
    } while (true);
    // ----------------------------------------------------------> Run Window Event Loop <---

    return 0; // End of application
}
