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

// Handle to the "1" button
HWND btnOne;

// Handle to the "2" button
HWND btnTwo;

// Handle to the "3" button
HWND btnThree;

// Handle to the "+" button
HWND btnPlus;

// Handle to the "4" button
HWND btnFour;

// Handle to the "5" button
HWND btnFive;

// Handle to the "6" button
HWND btnSix;

// Handle to the "7" button
HWND btnSeven;

// Handle to the "8" button
HWND btnEight;

// Handle to the "9" button
HWND btnNine;

// Handle to the "Neg" button
HWND btnNeg;

// Handle to the "/" button
HWND btnDiv;

// Handle to the "*" button
HWND btnTimes;

// Handle to the "-" button
HWND btnMinus;

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
    SetWindowPos(btnOne, HWND_TOP, 0, mainClientRect.bottom - 200, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnTwo, HWND_TOP, mainClientRect.right / 4, mainClientRect.bottom - 200, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnThree, HWND_TOP, mainClientRect.right / 2, mainClientRect.bottom - 200, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnFour, HWND_TOP, 0, mainClientRect.bottom - 300, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnFive, HWND_TOP, mainClientRect.right / 4, mainClientRect.bottom - 300, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnSix, HWND_TOP, mainClientRect.right / 2, mainClientRect.bottom - 300, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnPlus, HWND_TOP, 3 * mainClientRect.right / 4, mainClientRect.bottom - 400, mainClientRect.right / 4, 200, 0);
    SetWindowPos(btnSeven, HWND_TOP, 0, mainClientRect.bottom - 400, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnEight, HWND_TOP, mainClientRect.right / 4, mainClientRect.bottom - 400, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnNine, HWND_TOP, mainClientRect.right / 2, mainClientRect.bottom - 400, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnNeg, HWND_TOP, 0, mainClientRect.bottom - 500, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnDiv, HWND_TOP, mainClientRect.right / 4, mainClientRect.bottom - 500, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnTimes, HWND_TOP, mainClientRect.right / 2, mainClientRect.bottom - 500, mainClientRect.right / 4, 100, 0);
    SetWindowPos(btnMinus, HWND_TOP, 3 * mainClientRect.right / 4, mainClientRect.bottom - 500, mainClientRect.right / 4, 100, 0);

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
                displayError(L"Unable to create 0 button");
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

            // Create "1" button
            HWND one = CreateWindowW(
                L"BUTTON",
                L"1",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                0,
                600,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (one == NULL) {
                displayError(L"Unable to create 1 button");
            }

            btnOne = one;

            // Create "2" button
            HWND two = CreateWindowW(
                L"BUTTON",
                L"2",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                100,
                600,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (two == NULL) {
                displayError(L"Unable to create 2 button");
            }

            btnTwo = two;

            // Create "3" button
            HWND three = CreateWindowW(
                L"BUTTON",
                L"3",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                200,
                600,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (three == NULL) {
                displayError(L"Unable to create 3 button");
            }

            btnThree = three;

            // Create "4" button
            HWND four = CreateWindowW(
                L"BUTTON",
                L"4",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                0,
                500,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (four == NULL) {
                displayError(L"Unable to create 4 button");
            }

            btnFour = four;

            // Create "5" button
            HWND five = CreateWindowW(
                L"BUTTON",
                L"5",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                100,
                500,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (five == NULL) {
                displayError(L"Unable to create 5 button");
            }

            btnFive = five;

            // Create "6" button
            HWND six = CreateWindowW(
                L"BUTTON",
                L"6",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                200,
                500,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (six == NULL) {
                displayError(L"Unable to create 6 button");
            }

            btnSix = six;

            // Create "+" button
            HWND plus = CreateWindowW(
                L"BUTTON",
                L"+",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                300,
                400,
                100,
                200,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (plus == NULL) {
                displayError(L"Unable to create + button");
            }

            btnPlus = plus;

            // Create "7" button
            HWND seven = CreateWindowW(
                L"BUTTON",
                L"7",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                0,
                400,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (seven == NULL) {
                displayError(L"Unable to create 7 button");
            }

            btnSeven = seven;

            // Create "8" button
            HWND eight = CreateWindowW(
                L"BUTTON",
                L"8",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                100,
                400,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (eight == NULL) {
                displayError(L"Unable to create 8 button");
            }

            btnEight = eight;

            // Create "9" button
            HWND nine = CreateWindowW(
                L"BUTTON",
                L"9",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                200,
                400,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (nine == NULL) {
                displayError(L"Unable to create 9 button");
            }

            btnNine = nine;

            // Create "Neg" button
            HWND neg = CreateWindowW(
                L"BUTTON",
                L"Neg",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                0,
                300,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (neg == NULL) {
                displayError(L"Unable to create neg button");
            }

            btnNeg = neg;

            // Create "/" button
            HWND div = CreateWindowW(
                L"BUTTON",
                L"/",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                100,
                300,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (div == NULL) {
                displayError(L"Unable to create / button");
            }

            btnDiv = div;

            // Create "*" button
            HWND times = CreateWindowW(
                L"BUTTON",
                L"*",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                200,
                300,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (times == NULL) {
                displayError(L"Unable to create * button");
            }

            btnTimes = times;

            // Create "-" button
            HWND minus = CreateWindowW(
                L"BUTTON",
                L"-",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                300,
                300,
                100,
                100,
                hwnd,
                NULL,
                glblInstance,
                NULL
            );

            if (minus == NULL) {
                displayError(L"Unable to create - button");
            }

            btnMinus = minus;

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
                    } else if (btn == btnOne) {
                        MessageBox(NULL, L"Clicked one!", L"Alright!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnTwo) {
                        MessageBox(NULL, L"Clicked two!", L"Ayyy!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnThree) {
                        MessageBox(NULL, L"Clicked three!", L"Yes yes yes!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnFour) {
                        MessageBox(NULL, L"Clicked four!", L"Hooray!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnFive) {
                        MessageBox(NULL, L"Clicked five!", L"Woohoo!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnSix) {
                        MessageBox(NULL, L"Clicked six!", L"Tubular!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnPlus) {
                        MessageBox(NULL, L"Clicked plus!", L"Wowzers!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnSeven) {
                        MessageBox(NULL, L"Clicked seven!", L"Whoa!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnEight) {
                        MessageBox(NULL, L"Clicked eight!", L"Hey hey hey!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnNine) {
                        MessageBox(NULL, L"Clicked nine!", L"Oh baby!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnNeg) {
                        MessageBox(NULL, L"Clicked neg!", L"W00t!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnDiv) {
                        MessageBox(NULL, L"Clicked div!", L"Radical!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnTimes) {
                        MessageBox(NULL, L"Clicked times!", L"Awesome!", MB_OK | MB_ICONINFORMATION);
                    } else if (btn == btnMinus) {
                        MessageBox(NULL, L"Clicked minus!", L"Wow, incredible!", MB_OK | MB_ICONINFORMATION);
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

                case '1':
                case VK_NUMPAD1: {
                    // Simulate a click on the "1" button
                    SendMessage(btnOne, BM_CLICK, NULL, NULL);
                    break;
                }

                case '2':
                case VK_NUMPAD2: {
                    // Simulate a click on the "2" button
                    SendMessage(btnTwo, BM_CLICK, NULL, NULL);
                    break;
                }

                case '3':
                case VK_NUMPAD3: {
                    // Simulate a click on the "3" button
                    SendMessage(btnThree, BM_CLICK, NULL, NULL);
                    break;
                }

                case '4':
                case VK_NUMPAD4: {
                    // Simulate a click on the "4" button
                    SendMessage(btnFour, BM_CLICK, NULL, NULL);
                    break;
                }

                case '5':
                case VK_NUMPAD5: {
                    // Simulate a click on the "5" button
                    SendMessage(btnFive, BM_CLICK, NULL, NULL);
                    break;
                }

                case '6':
                case VK_NUMPAD6: {
                    // Simulate a click on the "6" button
                    SendMessage(btnSix, BM_CLICK, NULL, NULL);
                    break;
                }

                case VK_OEM_PLUS:
                case VK_ADD: {
                    // Simulate a click on the "+" button
                    SendMessage(btnPlus, BM_CLICK, NULL, NULL);
                    break;
                }
                
                case '7':
                case VK_NUMPAD7: {
                    // Simulate a click on the "7" button
                    SendMessage(btnSeven, BM_CLICK, NULL, NULL);
                    break;
                }

                case '8':
                case VK_NUMPAD8: {
                    // Simulate a click on the "8" button
                    SendMessage(btnEight, BM_CLICK, NULL, NULL);
                    break;
                }

                case '9':
                case VK_NUMPAD9: {
                    // Simulate a click on the "9" button
                    SendMessage(btnNine, BM_CLICK, NULL, NULL);
                    break;
                }

                case 'N': {
                    // Simulate a click on the "Neg" button
                    SendMessage(btnNeg, BM_CLICK, NULL, NULL);
                    break;
                }

                case VK_OEM_2:
                case VK_DIVIDE: {
                    // Simulate a click on the "/" button
                    SendMessage(btnDiv, BM_CLICK, NULL, NULL);
                    break;
                }

                // TODO shift + 8
                case VK_MULTIPLY: {
                    SendMessage(btnTimes, BM_CLICK, NULL, NULL);
                    break;
                }

                case VK_OEM_MINUS:
                case VK_SUBTRACT: {
                    SendMessage(btnMinus, BM_CLICK, NULL, NULL);
                    break;
                }
            }
            return 0;
        }

        // case WM_PAINT: {
        //     // TODO fill client area with grey/white
        // }

        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        
        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
}
