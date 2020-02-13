// Snake.cpp : Defines the entry point for the application.
//

#include "MainGame.h"
#include "Snake.h"
#include "framework.h"
#include <algorithm>
#include <atlstr.h>

#define MAX_LOADSTRING 100
#define LINETHICKNESS 4
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
Game TheGame;									// Instance of the game

DIFFICULTY g_eDifficulty = EASY;

static int iStart = 20;
static int iEnd = iStart + TranslateGameToDisplay(GRIDSIZE);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	TheGame.InitialiseGame();

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SNAKE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SNAKE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SNAKE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BACKGROUND);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SNAKE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   DWORD dwStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
   HWND  hWnd = CreateWindowW(szWindowClass, szTitle, dwStyle,
      0, 0, 460, 500, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   // handle to main window 
   // timer identifier 
   // 10-second interval 

   SetTimer(hWnd, IDS_TIMER, g_eDifficulty, (TIMERPROC)NULL);     // no timer callback 
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

void DrawGivenGEWithColor(const GridElement& GE, HDC hdc, const HBRUSH hbrBrush)
{
	// Get XY pair in game coordinates
	const IntPair XYPair = GE.GetXY();
	// Translate to display coordinates
	const IntPair DisplayPair = TranslateGameToDisplay(XYPair);
	// Get XY values of the pixel (note: pixel is translated to square of size TranslateGameToDisplay())
	const int iLeft = iStart + DisplayPair.first;
	const int iRight = iLeft + TranslateGameToDisplay(1);
	const int iTop = iStart + DisplayPair.second;
	const int iBottom = iTop + TranslateGameToDisplay(1);
	RECT rPixel;
	SetRect(&rPixel, iLeft, iTop, iRight, iBottom);
	FillRect(hdc, &rPixel, hbrBrush);
}

void DrawSnake(HWND hWnd, HDC hdc)
{
	// Define the brushes
	const HBRUSH hbrBlack  = CreateSolidBrush(RGB(  0,   0,   0));
	const HBRUSH hbrOrange = CreateSolidBrush(RGB(255, 180,   0));

	// Get snake vector
	const std::vector<GridElement>* const pSnakeVector = TheGame.GetSnake();
	// Draw each element of the snake
	std::for_each(pSnakeVector->begin(), pSnakeVector->end(), [&](const GridElement& GE){DrawGivenGEWithColor(GE, hdc, hbrBlack);});

	//Get the food point
	const GridElement& GEFood = TheGame.GetFoodRef();
	DrawGivenGEWithColor(GEFood,hdc,hbrOrange);

	// Draw score:
	//Get score and make it into a string
	// 00000
	const int iScore = TheGame.GetScore();
	CString strScore;
	strScore.Format(_T("%05d\0"),iScore);
	
	// Determine window rect
	RECT rcWindow;
	GetClientRect(hWnd,&rcWindow);
	rcWindow.top++;
	rcWindow.bottom--;
	rcWindow.left+=iStart;
	rcWindow.right--;
	SetTextColor(hdc, RGB(0,0,0));

	DrawText(hdc, strScore, -1, &rcWindow, DT_LEFT | DT_TOP | DT_SINGLELINE);
	DeleteObject(hbrBlack);
	DeleteObject(hbrOrange);
}

void DrawGameOver(HWND hWnd, HDC hdc)
{
	RECT rcWindow;
	GetClientRect(hWnd,&rcWindow);

	DrawText(hdc, _T("GAME OVER"), -1, &rcWindow, DT_CENTER | DT_SINGLELINE);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_KEYDOWN  - process keys pressed
//  WM_COMMAND  - process the application menu
//	WM_TIMER	- every X seconds
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
HMENU hmenu = GetMenu(hWnd);
    switch (message)
    {
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:

			// Process the LEFT ARROW key. 
			TheGame.SetDirection(Game::DIRECTION::LEFT);
			break;

		case VK_RIGHT:

			// Process the RIGHT ARROW key. 
			TheGame.SetDirection(Game::DIRECTION::RIGHT);
			break;

		case VK_UP:

			// Process the UP ARROW key. 
			TheGame.SetDirection(Game::DIRECTION::UP);
			break;

		case VK_DOWN:

			// Process the DOWN ARROW key. 
			TheGame.SetDirection(Game::DIRECTION::DOWN);
			break;

		case VK_ESCAPE:

			// Process the ESC key. 
			// TODO
			break;

		case VK_RETURN:

			// Process the RETURN/ENTER key. 
			// TODO
			break;

			// Process other non-character keystrokes. 
		default:
			return -1;
			break;
		}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case IDM_RESTART:
			{
				TheGame.InitialiseGame();
				break;
			}
			case IDM_DIFFICULTY_EASY:
			{
				UINT state = GetMenuState(hmenu,IDM_DIFFICULTY_EASY, MF_BYCOMMAND);
				if (state == MF_UNCHECKED)
				{
					g_eDifficulty = EASY;
					CheckMenuItem(hmenu,   IDM_DIFFICULTY_EASY,   MF_CHECKED);
					CheckMenuItem(hmenu, IDM_DIFFICULTY_MEDIUM, MF_UNCHECKED);
					CheckMenuItem(hmenu,   IDM_DIFFICULTY_HARD, MF_UNCHECKED);
				}
				SetTimer(hWnd, IDS_TIMER, g_eDifficulty, (TIMERPROC)NULL);     // no timer callback 
				break;
			}
			case IDM_DIFFICULTY_MEDIUM:
			{
				UINT state = GetMenuState(hmenu,IDM_DIFFICULTY_MEDIUM, MF_BYCOMMAND);
				if (state == MF_UNCHECKED)
				{
					g_eDifficulty = MEDIUM;
					CheckMenuItem(hmenu,   IDM_DIFFICULTY_EASY, MF_UNCHECKED);
					CheckMenuItem(hmenu, IDM_DIFFICULTY_MEDIUM,   MF_CHECKED);
					CheckMenuItem(hmenu,   IDM_DIFFICULTY_HARD, MF_UNCHECKED);
				}
				SetTimer(hWnd, IDS_TIMER, g_eDifficulty, (TIMERPROC)NULL);     // no timer callback 
				break;
			}
			case IDM_DIFFICULTY_HARD:
			{
				UINT state = GetMenuState(hmenu,IDM_DIFFICULTY_HARD, MF_BYCOMMAND);
				if (state == MF_UNCHECKED)
				{
					g_eDifficulty = HARD;
					CheckMenuItem(hmenu,   IDM_DIFFICULTY_EASY, MF_UNCHECKED);
					CheckMenuItem(hmenu, IDM_DIFFICULTY_MEDIUM, MF_UNCHECKED);
					CheckMenuItem(hmenu,   IDM_DIFFICULTY_HARD,   MF_CHECKED);
				}
				SetTimer(hWnd, IDS_TIMER, g_eDifficulty, (TIMERPROC)NULL);     // no timer callback 
				break;
			}
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
				return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_TIMER:
		TheGame.Play();
		InvalidateRect(hWnd, NULL, FALSE);
		UpdateWindow(hWnd);
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			HPEN hpen;
			hpen = CreatePen(PS_SOLID, LINETHICKNESS, RGB(0, 0, 0));
			SelectObject(hdc, hpen);
			Rectangle(hdc, iStart - LINETHICKNESS/2, iStart - LINETHICKNESS/2, iEnd, iEnd);
			if (TheGame.IsGameOver())
			{
				DrawGameOver(hWnd,hdc);
			}
			else
			{
				DrawSnake(hWnd, hdc);
			}
			DeleteObject(hpen);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return -1;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

IntPair TranslateGameToDisplay(const IntPair Coordinates)
{
	const int iX = TranslateGameToDisplay(Coordinates.first);
	const int iY = TranslateGameToDisplay(Coordinates.second);
	return std::make_pair(iX, iY);
}