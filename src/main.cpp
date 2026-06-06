
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
static constexpr LPCSTR WINDOW_CLASS_NAME = "MainAppWindow";

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // ---> Register Window Class <----------------------------------------------------------
    WNDCLASSEX windowClass{}; ///< Window class description
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = WINDOW_CLASS_NAME;
    windowClass.lpfnWndProc = &windowProcedure;
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    auto windowClassId = RegisterClassEx(&windowClass);
    // ----------------------------------------------------------> Register Window Class <---

    // ---> Create Window From Class <-------------------------------------------------------
    HWND windowHandle = CreateWindowEx( ///< Handle to main application window
        NULL,                     ///< Optional window style
        WINDOW_CLASS_NAME,        ///< Window class name
        "Demo Win32 Application", ///< Window titlebar text
        WS_OVERLAPPEDWINDOW,      ///< Window style
        CW_USEDEFAULT,            ///< Window x-coordinate
        CW_USEDEFAULT,            ///< Window y-coordinate
        800,                      ///< Window width
        500,                      ///< Window height
        NULL,                     ///< Parent window handle
        NULL,                     ///< Window menu handle
        hInstance,                ///< Instance handle???
        nullptr                   ///< Additional application data???
    );
    // -------------------------------------------------------> Create Window From Class <---

    // Check that window creation did not fail
    if (windowHandle == NULL)
        return 100;

    // Set visibility of newly created window
    ShowWindow(windowHandle, nCmdShow);

    // ---> Run Window Event Loop <----------------------------------------------------------
    MSG msg{};
    BOOL run;

    do {
        // Block until next message is recieved from queue
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
