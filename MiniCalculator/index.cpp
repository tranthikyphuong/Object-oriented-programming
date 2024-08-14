#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <atlstr.h>
#include "Expression.h"

#define IDI_ICON1 101

string GetWindowStringText(HWND hwnd)
{
    int len = GetWindowTextLength(hwnd) + 1;
    vector<wchar_t> buf(len);
    GetWindowText(hwnd, &buf[0], len);
    wstring wide = &buf[0];
    string s(wide.begin(), wide.end());
    return s;
}

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Mini Calculator");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 400: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application

    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 400,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Show window center screen
    RECT rc;
    GetWindowRect(hWnd, &rc);
    int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
    int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;
    SetWindowPos(hWnd, 0, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

    // Set app icon
    HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return

HWND expressInput, submitBtn, expressResult;
TCHAR greeting[] = _T("Enter your expression below:");
TCHAR resultLabel[] = _T("Result:");

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        // Here your application is laid out.
        // For this introduction, we just print out "Hello, Windows desktop!"
        // in the top left corner.
        TextOut(hdc,
            150, 60,
            greeting, _tcslen(greeting));

        expressInput = CreateWindow(_T("EDIT"), _T(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_WANTRETURN,
            90, 100, 300, 22, hWnd, NULL, hInst, 0);

        TextOut(hdc,
            90, 140,
            resultLabel, _tcslen(resultLabel));

        expressResult = CreateWindow(_T("STATIC"), _T(""),
            WS_VISIBLE | WS_CHILD,
            150, 140, 240, 22, hWnd, NULL, hInst, 0);

        submitBtn = CreateWindow(_T("BUTTON"), _T("Calculate"),
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            190, 190, 100, 40, hWnd, NULL, hInst, 0);

        // End application-specific layout section.

        EndPaint(hWnd, &ps);
        break;
    case WM_COMMAND:
        if ((HIWORD(wParam) == BN_CLICKED) && (lParam != 0))
        {
            string e = GetWindowStringText(expressInput);
            
            try {
                Expression* expression = new Expression(e);
                double calcResult = expression->calculate();
                std::wstringstream sss(L"");
                sss << calcResult;
                SetWindowText(expressResult, sss.str().c_str());
            }
            catch (const char* err) {
                MessageBox(hWnd, CA2CT(err), _T("Error"), MB_OK);
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}