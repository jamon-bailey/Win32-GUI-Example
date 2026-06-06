
#include "window_proc.hpp"

LRESULT CALLBACK windowProcedure(HWND windowHandle, UINT signal, WPARAM wParam, LPARAM lParam)
{
	switch (signal) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(windowHandle, signal, wParam, lParam);
	}
}
