#ifndef UNICODE
    #define UNICODE
#endif
#ifndef _UNICODE
    #define _UNICODE
#endif

#include "rpn_stack.hpp"

#include <windows.h>

// Handle to main window
HWND mainWnd;

// Rect containing dimensions of main window's client area
RECT mainClientRect;

// Handle to the "0" button
HWND btnZero;

// Handle to the "." button
HWND btnDot;

// Handle to the "Enter" button
HWND btnEnter;

// Global storage of runtime instance handle
HINSTANCE glblInstance;

// Displays a message box with a given unicode error string
void displayError(const wchar_t*);

// Window procedure for main window
LRESULT CALLBACK mainWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR pCmdLine,
    int nCmdShow
) {
    // Main window class
    WNDCLASS mainWc = { };
    mainWc.lpfnWndProc = mainWndProc;
    mainWc.hInstance = hInstance;
    mainWc.lpszClassName = L"RPN Main";

    RegisterClass(&mainWc);

    glblInstance = hInstance;

    // Show main window
    HWND hwnd = CreateWindowW(
        L"RPN Main",
        L"RPN Calculator",
        // WS_OVERLAPPEDWINDOW,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        400,
        800,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        displayError(L"Could not create main RPN window");
        return -1;
    }

    if (!GetClientRect(hwnd, &mainClientRect)) {
        displayError(L"Unable to fetch client dimensions");
    }

    mainWnd = hwnd;

    // Set button sizes relative to main window
    SetWindowPos(btnZero, HWND_TOP, 0, mainClientRect.bottom - 100, mainClientRect.right / 2, 100, 0);
    SetWindowPos(btnDot, HWND_TOP, mainClientRect.right / 2, mainClientRect.bottom - 100, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnEnter, HWND_TOP, 3 * mainClientRect.right / 4, mainClientRect.bottom - 200, mainClientRect.right / 4, 200, 0);

    ShowWindow(hwnd, nCmdShow);

    // Setup message loop
    MSG msg = { };

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void displayError(const wchar_t* msg) {
    MessageBox(NULL, msg, L"Error", MB_OK | MB_ICONERROR);
}

LRESULT CALLBACK mainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // Create "0" button
            HWND zero = CreateWindowW(
                L"BUTTON",
                L"0",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                0,
                700,
                200,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (zero == NULL) {
                displayError(L"Unable to create zero button");
            }

            btnZero = zero;

            // Create "." button
            HWND dot = CreateWindowW(
                L"BUTTON",
                L".",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                200,
                700,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (dot == NULL) {
                displayError(L"Unable to create dot button");
            }

            btnDot = dot;

            // Create "Enter" button
            HWND enter = CreateWindowW(
                L"BUTTON",
                L"Enter",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                300,
                700,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (enter == NULL) {
                displayError(L"Unable to create enter button");
            }

            btnEnter = enter;

            return 0;
        }

        case WM_COMMAND: {
            switch (HIWORD(wParam)) {
                case BN_CLICKED: {
                    HWND btn = (HWND) lParam;
                    if (btn == btnZero) {
                        MessageBox(NULL, L"Clicked zero!", L"Yippee!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnDot) {
                        MessageBox(NULL, L"Clicked dot!", L"Yahoo!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnEnter) {
                        MessageBox(NULL, L"Clicked Enter!", L"Whoopee!", MB_OK | MB_ICONINFORMATION);
                    }
                    break;
                }
            }
            SetFocus(hwnd); // return focus to main window
            return 0;
        }

        case WM_KEYDOWN: {
            switch (wParam) {
                case '0':
                case VK_NUMPAD0: {
                    // Simulate a click on the "0" button
                    SendMessage(btnZero, BM_CLICK, NULL, NULL);
                    break;
                }

                case VK_OEM_PERIOD:
                case VK_DECIMAL: {
                    // Simulate a click on the "." button
                    SendMessage(btnDot, BM_CLICK, NULL, NULL);
                    break;
                }

                case VK_RETURN: {
                    // Simulate a click on the "Enter" button
                    SendMessage(btnEnter, BM_CLICK, NULL, NULL);
                    break;
                }
            }
            return 0;
        }

        case WM_PAINT: {
            // TODO fill client area with grey/white
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        
        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
}
