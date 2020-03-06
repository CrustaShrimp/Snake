// Snake.cpp : Defines the entry point for the application.
//

#include "MainGame.h"
#include "Snake.h"
#include "resource.h"
#include "framework.h"
#include <cassert>          // assert
#include <algorithm>        // std::for_each
#include <mmsystem.h>       // PlaySound()

#define MAX_LOADSTRING 100
#define LINETHICKNESS 4     // For drawing the border of snakefield

// Global Variables:
HINSTANCE   g_hInst;                        // Current instance
HWND        g_hWnd = NULL;                  // Handle of the main window
WCHAR       szTitle[MAX_LOADSTRING];        // The title bar text
WCHAR       szWindowClass[MAX_LOADSTRING];  // The main window class name

Game        TheGame;                        // Instance of the game
DIFFICULTY  g_eDifficulty = DIFFICULTY::UNINIT;         


static int iStart = 30;                                         // Start offset of the snake playing field
static int iEnd = iStart + TranslateGameToDisplay(GRIDSIZE);    // End of the snake playing field

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);

// Callback for main window
// Processes keys (arrows = controls, escape = pause)
// Processes menu buttons (Restart, difficulty settings, sound, about, exit)
// Processes timer (timer set using difficulty settings)
// Processes paint (to paint the window, only paints the snake when not gameover, draws pause symbol when paused)
// Processes destroy
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// Callback for the About popup window.
// Sets icon
// Processes OK and Cancel buttons
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Callback for Startup window
// Sets icon
// Processes radiobuttons (difficulty)
// Processes start button
// Initialises game
INT_PTR CALLBACK    Startup(HWND, UINT, WPARAM, LPARAM);

// Callback for GameOver window
// Sets icon
// Processes score for display
// Processes restart button
INT_PTR CALLBACK    GameOver(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE /*hPrevInstance*/,
                     _In_ LPWSTR    /*lpCmdLine*/,
                     _In_ int       nCmdShow)
{
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROUNDSNAKE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BACKGROUND);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SNAKE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_BLOCKSNAKE));

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
   g_hInst = hInstance; // Store instance handle in our global variable

   const DWORD dwStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU); // Not resizable, minimisable or maximisable
   const int iScreenSizeX = GetSystemMetrics(SM_CXSCREEN);
   const int iScreenSizeY = GetSystemMetrics(SM_CYSCREEN);
   
   const int iWindowWidth  = 480;   // Defined width of the main window
   const int iWindowHeight = 520;   // Defined height of the main window 
   g_hWnd = CreateWindowW(szWindowClass, szTitle, dwStyle,
      (iScreenSizeX - iWindowWidth)/2 , (iScreenSizeY - iWindowHeight)/2, iWindowWidth, iWindowHeight, 
      nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }
   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);
   // Open startup configuration window at startup
   DialogBox(g_hInst, MAKEINTRESOURCE(IDD_START), g_hWnd, Startup);
   return TRUE;
}

//************************************
// Draws the GridElement on the HDC
// with HBRUSH, translating the 
// game coordinates to squares
// in screen coordinates
//
// Method:    DrawGivenGEWithColor
// FullName:  DrawGivenGEWithColor
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const GridElement & GE
// Parameter: HDC hdc
// Parameter: const HBRUSH hbrBrush
//************************************
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

//************************************
// Returns a CString containing the 
// last score of the player
//
// Method:    GetScoreString
// FullName:  GetScoreString
// Access:    public 
// Returns:   CString
// Qualifier:
//************************************
CString GetScoreString()
{
    //Get score and make it into a string
    // formatting example: 00005
    const int iScore = TheGame.GetScore();
    CString strScore;
    strScore.Format(_T("%05d\0"), iScore);
    return strScore;
}

//************************************
// Draws the snake and food, using
// DrawGivenGEWithColor
// Also draws the current score
//
// Method:    DrawSnake
// FullName:  DrawSnake
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: HWND hWnd
// Parameter: HDC hdc
//************************************
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
    if (GEFood.GetActive())
    {
        DrawGivenGEWithColor(GEFood,hdc,hbrOrange);
    }

    // Draw score:
    CString strScore = GetScoreString();
    
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

//************************************
// Draws pause symbol (rotated =)
// on the screen, on top of the rest
// in the main window
// Method:    DrawPause
// FullName:  DrawPause
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: HWND hWnd
// Parameter: HDC hdc
//************************************
void DrawPause(HWND hWnd, HDC hdc)
{
    const HBRUSH hbrGrey  = CreateSolidBrush(RGB( 150, 150, 150));
    // Get window rect
    RECT rcWindow;
    GetClientRect(hWnd,&rcWindow);
    const int iMiddleLR = (rcWindow.right - rcWindow.left) / 2;
    const int iMiddleUD = (rcWindow.bottom - rcWindow.top) / 2;
    const int iOffset = 10;
    const int iHeight = 50;
    const int iWidth  = 20; 
    RECT rcLeftBar;
    SetRect(&rcLeftBar, iMiddleLR - iOffset - iWidth, iMiddleUD - iHeight, iMiddleLR - iOffset, iMiddleUD + iHeight);
    RECT rcRightBar;
    SetRect(&rcRightBar, iMiddleLR + iOffset, iMiddleUD - iHeight, iMiddleLR + iOffset + iWidth, iMiddleUD + iHeight);
  
    FillRect(hdc, &rcLeftBar, hbrGrey);
    FillRect(hdc, &rcRightBar, hbrGrey);
}

//************************************
// Toggles the music (Snake Jazz)
// Should be called when mute button pressed
// or when the sound menu option is toggled
// Method:    ToggleSound
// FullName:  ToggleSound
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: HWND hWnd
// Parameter: const bool bEnable
//************************************
void ToggleSound(const HWND& hWnd, const bool bEnable)
{
    HMENU hmenu = GetMenu(hWnd);
    if (bEnable) // Go to enabled mode
    {
        TheGame.SetSoundEnabled(true);
        // Play snakejazz when playing, not paused, not game over
        PlaySnakeJazz(TheGame.IsPlaying());
        CheckMenuItem(hmenu, IDM_OPTIONS_SOUND, MF_CHECKED);
    }
    else // Go to disabled mode
    {
        TheGame.SetSoundEnabled(false);
        PlaySnakeJazz(false);
        CheckMenuItem(hmenu, IDM_OPTIONS_SOUND, MF_UNCHECKED);
    }
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
            TheGame.TogglePause(false);
            break;

        case 0x4D: // "M" key
        {
            // Process the M key
            const bool bSoundEnabled = TheGame.GetSoundEnabled();
            ToggleSound(hWnd, bSoundEnabled);
            break;
        }
            // Process other non-character keystrokes. 
        default:
            return -1;
            break;
        }
    case WM_COMMAND:
        {
            HMENU hmenu = GetMenu(hWnd);
            const int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_RESTART:
            {
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_START), hWnd, Startup);
                break;
            }
            case IDM_DIFFICULTY_EASY:
            {
                UINT state = GetMenuState(hmenu,IDM_DIFFICULTY_EASY, MF_BYCOMMAND);
                if (state == MF_UNCHECKED)
                {
                    g_eDifficulty = DIFFICULTY::EASY;
                    CheckMenuItem(hmenu,   IDM_DIFFICULTY_EASY,   MF_CHECKED);
                    CheckMenuItem(hmenu, IDM_DIFFICULTY_MEDIUM, MF_UNCHECKED);
                    CheckMenuItem(hmenu,   IDM_DIFFICULTY_HARD, MF_UNCHECKED);
                }
                SetTimer(hWnd, IDS_TIMER, (int)g_eDifficulty, (TIMERPROC)NULL);     // no timer callback 
                break;
            }
            case IDM_DIFFICULTY_MEDIUM:
            {
                UINT state = GetMenuState(hmenu,IDM_DIFFICULTY_MEDIUM, MF_BYCOMMAND);
                if (state == MF_UNCHECKED)
                {
                    g_eDifficulty = DIFFICULTY::MEDIUM;
                    CheckMenuItem(hmenu,   IDM_DIFFICULTY_EASY, MF_UNCHECKED);
                    CheckMenuItem(hmenu, IDM_DIFFICULTY_MEDIUM,   MF_CHECKED);
                    CheckMenuItem(hmenu,   IDM_DIFFICULTY_HARD, MF_UNCHECKED);
                }
                SetTimer(hWnd, IDS_TIMER, (int)g_eDifficulty, (TIMERPROC)NULL);     // no timer callback 
                break;
            }
            case IDM_DIFFICULTY_HARD:
            {
                UINT state = GetMenuState(hmenu,IDM_DIFFICULTY_HARD, MF_BYCOMMAND);
                if (state == MF_UNCHECKED)
                {
                    g_eDifficulty = DIFFICULTY::HARD;
                    CheckMenuItem(hmenu,   IDM_DIFFICULTY_EASY, MF_UNCHECKED);
                    CheckMenuItem(hmenu, IDM_DIFFICULTY_MEDIUM, MF_UNCHECKED);
                    CheckMenuItem(hmenu,   IDM_DIFFICULTY_HARD,   MF_CHECKED);
                }
                SetTimer(hWnd, IDS_TIMER, (int)g_eDifficulty, (TIMERPROC)NULL);     // no timer callback 
                break;
            }
            case IDM_OPTIONS_SOUND:
            {
                const UINT uiState = GetMenuState(hmenu, IDM_OPTIONS_SOUND, MF_BYCOMMAND);
                const bool bEnable = uiState == MF_CHECKED;
                ToggleSound(hWnd, bEnable);
                break;
            }
            case IDM_ABOUT:
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
        if(TheGame.IsGameOver())
        {
            DialogBox(g_hInst, MAKEINTRESOURCE(IDD_GAMEOVER), hWnd, GameOver);
        }
        InvalidateRect(hWnd, NULL, FALSE);
        UpdateWindow(hWnd);
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // Add any drawing code that uses hdc here...
            HPEN hpen;
            hpen = CreatePen(PS_SOLID, LINETHICKNESS, RGB(0, 0, 0));
            SelectObject(hdc, hpen);
            Rectangle(hdc, iStart - LINETHICKNESS/2, iStart - LINETHICKNESS/2, iEnd, iEnd);
            if (!TheGame.IsGameOver())
            {
                DrawSnake(hWnd, hdc);
                if (TheGame.GetPaused())
                {
                    DrawPause(hWnd,hdc);
                }
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
    {
        TheGame.TogglePause(true);
        HICON hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_BLOCKSNAKE));
        SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        return (INT_PTR)TRUE;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            TheGame.TogglePause(false);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Message handler for Startup box.
INT_PTR CALLBACK Startup(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        TheGame.TogglePause(true);
        const BOOL SoundEnabled = TheGame.GetSoundEnabled();
        UINT DefaultDifficulty = IDC_SETEASY;
        switch (g_eDifficulty)
        {
        case DIFFICULTY::UNINIT:
        case DIFFICULTY::EASY:
            DefaultDifficulty = IDC_SETEASY;
            break;
        case DIFFICULTY::MEDIUM:
            DefaultDifficulty = IDC_SETMEDIUM;
            break;
        case DIFFICULTY::HARD:
            DefaultDifficulty = IDC_SETHARD;
            break;
        default:
            break;
        }
         
        HICON hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_BLOCKSNAKE));
        SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        CheckDlgButton(hDlg,IDC_SOUND,SoundEnabled);
        CheckRadioButton(hDlg,IDC_SETEASY , IDC_SETHARD, DefaultDifficulty);
        return (INT_PTR)TRUE;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            case IDC_SETEASY:
                g_eDifficulty = DIFFICULTY::EASY;
                break;
            
            case IDC_SETMEDIUM:
                g_eDifficulty = DIFFICULTY::MEDIUM;
                break;
            
            case IDC_SETHARD:
                g_eDifficulty = DIFFICULTY::HARD;
                break;
            case IDSTART:
            {
                // Get menu from main window:
                HMENU hmenu = GetMenu(g_hWnd);
                switch (g_eDifficulty)
                {
                    default: // Easy is the default setting
                    case DIFFICULTY::EASY:
                        CheckMenuItem(hmenu,   IDM_DIFFICULTY_EASY,   MF_CHECKED);
                        CheckMenuItem(hmenu, IDM_DIFFICULTY_MEDIUM, MF_UNCHECKED);
                        CheckMenuItem(hmenu,   IDM_DIFFICULTY_HARD, MF_UNCHECKED);
                        break;
                    case DIFFICULTY::MEDIUM:
                        CheckMenuItem(hmenu,   IDM_DIFFICULTY_EASY, MF_UNCHECKED);
                        CheckMenuItem(hmenu, IDM_DIFFICULTY_MEDIUM,   MF_CHECKED);
                        CheckMenuItem(hmenu,   IDM_DIFFICULTY_HARD, MF_UNCHECKED);
                        break;
                    case DIFFICULTY::HARD:
                        CheckMenuItem(hmenu,   IDM_DIFFICULTY_EASY, MF_UNCHECKED);
                        CheckMenuItem(hmenu, IDM_DIFFICULTY_MEDIUM, MF_UNCHECKED);
                        CheckMenuItem(hmenu,   IDM_DIFFICULTY_HARD,   MF_CHECKED);
                        break;
                }
                UINT SoundEnabled = IsDlgButtonChecked(hDlg,IDC_SOUND);
                const bool bSoundEnabled = SoundEnabled;
                ToggleSound(hDlg,bSoundEnabled);
                SetTimer(g_hWnd, IDS_TIMER, (int)g_eDifficulty, (TIMERPROC)NULL);     // no timer callback 
                EndDialog(hDlg, LOWORD(wParam));
                TheGame.InitialiseGame();
                return (INT_PTR)TRUE;
            }
            case IDCANCEL:
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
        }
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK GameOver(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        HICON hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_BLOCKSNAKE));
        SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        HWND hWndScoreTextBox = GetDlgItem(hDlg,IDC_SCORE);
        CString strScore = GetScoreString();
        SendMessage(hWndScoreTextBox, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)strScore);
        return (INT_PTR) TRUE;
        break;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == IDRESTART)
        {
            EndDialog(hDlg, LOWORD(wParam));
            DialogBox(g_hInst, MAKEINTRESOURCE(IDD_START), g_hWnd, Startup);
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void PlaySnakeJazz(const bool bPlay)
{
    if (bPlay && TheGame.GetSoundEnabled())
    {
        PlaySound(MAKEINTRESOURCE(IDA_SNAKEJAZZ),NULL,SND_ASYNC | SND_LOOP | SND_RESOURCE);
    }
    else
    {
        PlaySound(NULL,NULL,NULL);
    }
}

IntPair TranslateGameToDisplay(const IntPair Coordinates)
{
    const int iX = TranslateGameToDisplay(Coordinates.first);
    const int iY = TranslateGameToDisplay(Coordinates.second);
    return std::make_pair(iX, iY);
}