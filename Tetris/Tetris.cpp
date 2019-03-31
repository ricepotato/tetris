#include "stdafx.h"
#include"Tet.h"
#include"resource.h"
#include<commctrl.h>

#define LEFT_SPACE 10 // 55
#define TOP_SPACE 10

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

VOID CALLBACK Proc_DropDown(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

int Msg_PAINT(HWND hWnd, WPARAM wParam, LPARAM lParam);
int Msg_CREATE(HWND hWnd, WPARAM wParam, LPARAM lParam);
int Msg_KEYDOWN(HWND hWnd, WPARAM wParam, LPARAM lParam);
int Msg_DESTROY(HWND hWnd, WPARAM wParam, LPARAM lParam);

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);
void DoubleBufferingDraw(void);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("테트리스");

HWND hMainWnd;

TETRIS Tet;

TCHAR str[256];
int arBlockOrder[MAX_NUM_OF_BLOCK_ORDER];
int nBlockOrderCtr = 0;
HBITMAP BlockImageList[8];
HBITMAP NumberList[11];
POINT arTetPoint[240];
RECT rtTet;

HBITMAP hBit;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG Message;
	HWND hWnd;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	/*
		hWnd = CreateWindowEx(NULL ,lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, (HMENU)NULL, hInstance, NULL);
	*/

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);

	}

	return (int)Message.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hMainWnd = hWnd;
		return Msg_CREATE(hWnd, wParam, lParam);
	case WM_PAINT:
		return Msg_PAINT(hWnd, wParam, lParam);
	case WM_KEYDOWN:
		return Msg_KEYDOWN(hWnd, wParam, lParam);
	case WM_DESTROY:
		return Msg_DESTROY(hWnd, wParam, lParam);
	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("%d %d"), LOWORD(lParam), HIWORD(lParam));
		SetWindowText(hWnd, str);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

int Msg_PAINT(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	hdc = BeginPaint(hWnd, &ps);

	if (hBit)
		DrawBitmap(hdc, 0, 0, hBit);

	EndPaint(hWnd, &ps);
	return 0;
}

int Msg_CREATE(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int i;
	int j;

	srand(GetTickCount());

	rtTet.left = LEFT_SPACE;
	rtTet.top = TOP_SPACE;
	rtTet.right = LEFT_SPACE + 16 * 10;
	rtTet.bottom = TOP_SPACE + 16 * 24;

	InflateRect(&rtTet, 2, 2);

	for (i = 0; i < 8; i++)
	{
		BlockImageList[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(109 + i));
	}
	for (i = 0; i < 11; i++)
	{
		NumberList[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(120 + i));
	}

	for (i = 0; i < 24; i++)
	{
		for (j = 0; j < 10; j++)
		{
			arTetPoint[j + i * 10].x = LEFT_SPACE + j * 16;
			arTetPoint[j + i * 10].y = TOP_SPACE + i * 16;
		}
	}


	MakeBlockOrder(arBlockOrder);

	for (i = 140; i < 150; i++)
	{
		Tet.arTet[i] = 26;
	}
	Tet.arTet[142] = 0;
	Tet.arTet[125] = 25;
	Tet.arTet[127] = 22;

	//SetTimer(hWnd, 1, 1000, Proc_DropDown );

	PutBlockInTET(&Tet, NEMO);
	Tet.nCurrentBlockShape = NEMO;

	MakeTransparentBlocks(&Tet);

	DoubleBufferingDraw();
	return 0;
}

void MakeSolidBlocksStraight(TETRIS *Tet)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		Tet->arTet[Tet->Moving[i]] = 0;
	}
	for (i = 0; i < 4; i++)
	{
		Tet->arTet[Tet->Transparent[i]] = Tet->nCurrentBlockShape + 20;
	}

	Tet->nCurrentBlockShape = 0;
	Tet->nCurrentBlockState = 0;
	Tet->nXpos = 0;
	Tet->nYpos = 0;
}
void EraseLine(TETRIS *Tet)
{
	int i;
	int j;

	for (i = 0; i < 24; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (Tet->arTet[i * 10 + j] < 20)
				break;
		}
		if (j == 10)
		{
			memcpy(Tet->arTet + 10, Tet->arTet, sizeof(int) * i * 10);
			Tet->nScore += 123; // 점수가 더해집니다.
			i--;
		}
	}
}

VOID CALLBACK Proc_DropDown(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	int nResult;

	nResult = MoveBlocks(&Tet, VK_DOWN);

	if (nResult == -1)
	{
		MakeSolidBlocks(&Tet);
		EraseLine(&Tet);
		ScoreBoard(&Tet);
		PutBlockInTET(&Tet, arBlockOrder[++nBlockOrderCtr]);
		MakeTransparentBlocks(&Tet);
	}
	DoubleBufferingDraw();
	//InvalidateRect(hWnd, NULL, TRUE );
}
int Msg_KEYDOWN(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int nResult;

	nResult = MoveBlocks(&Tet, (int)wParam);
	if (nResult == 0)
		MakeTransparentBlocks(&Tet);

	switch (wParam)
	{
	case VK_F1:
		MakeBlockOrder(arBlockOrder);
		InitializeTET(&Tet);
		SetTimer(hWnd, 1, 1000, Proc_DropDown);
		Tet.nCurrentBlockState = 1;
		PutBlockInTET(&Tet, arBlockOrder[nBlockOrderCtr]);
		MakeTransparentBlocks(&Tet);

		break;
	case VK_SPACE:
		MakeSolidBlocksStraight(&Tet);
		EraseLine(&Tet);
		ScoreBoard(&Tet);
		PutBlockInTET(&Tet, arBlockOrder[++nBlockOrderCtr]);
		MakeTransparentBlocks(&Tet);
		break;
	case VK_DOWN:
		if (nResult == -1)
		{
			MakeSolidBlocks(&Tet);
			EraseLine(&Tet);
			ScoreBoard(&Tet);
			PutBlockInTET(&Tet, arBlockOrder[++nBlockOrderCtr]);
			MakeTransparentBlocks(&Tet);
		}
		break;
	case VK_UP:
		RotateBlocks(&Tet);
		MakeTransparentBlocks(&Tet);
		break;
	}
	DoubleBufferingDraw();
	return 0;
}
int Msg_DESTROY(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int i;
	for (i = 0; i < 8; i++)
	{
		DeleteObject(BlockImageList[i]);
	}
	for (i = 0; i < 11; i++)
	{
		DeleteObject(NumberList[i]);
	}
	PostQuitMessage(0);
	return 0;
}

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}
void DoubleBufferingDraw(void)
{
	RECT crt;
	HDC hdc, hMemDC;
	HBITMAP OldBit;

	int i, j;

	GetClientRect(hMainWnd, &crt);
	hdc = GetDC(hMainWnd);

	if (hBit == NULL)
		hBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);

	hMemDC = CreateCompatibleDC(hdc);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	//FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW) );
	FillRect(hMemDC, &crt, (HBRUSH)GetStockObject(BLACK_BRUSH)); // 검정색 배경 브러시 입니다.
	////

	for (i = 0; i < 240; i++) // 블록이 출력될 위치를 점으로 표시합니다.
	{
		SetPixel(hMemDC, arTetPoint[i].x, arTetPoint[i].y, RGB(0, 0, 0));
	}

	//FillRect(hMemDC, &rtTet, (HBRUSH)GetStockObject( BLACK_BRUSH ) );
	FrameRect(hMemDC, &rtTet, (HBRUSH)GetStockObject(WHITE_BRUSH)); // 하얀색 겉라인을 그립니다.


	for (i = 0; i < 24; i++) // 배열의 상태를 보여주는 출력입니다.
	{
		for (j = 0; j < 10; j++)
		{
			wsprintf(str, TEXT("%2d"), Tet.arTet[i * 10 + j]);
			TextOut(hMemDC, 200 + j * 20, 10 + i * 18, str, lstrlen(str));
		}
	}

	wsprintf(str, TEXT("%d %d %d %d"), Tet.Moving[0], Tet.Moving[1], Tet.Moving[2], Tet.Moving[3]); // 움직이는 블록의 상태를 보여줍니다.
	TextOut(hMemDC, 450, 200, str, lstrlen(str));
	wsprintf(str, TEXT("%d %d %d %d"), Tet.Transparent[0], Tet.Transparent[1], Tet.Transparent[2], Tet.Transparent[3]); // 투명블록의 상태를 보여줍니다.
	TextOut(hMemDC, 450, 230, str, lstrlen(str));

	for (i = 0; i < 8; i++)
	{
		DrawBitmap(hMemDC, 415 + i * 16, 45, BlockImageList[i]); // 블록의 이미지를 출력합니다.
	}

	for (i = 0; i < 24; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (Tet.arTet[j + i * 10] > 0)
				DrawBitmap(hMemDC, arTetPoint[j + i * 10].x, arTetPoint[j + i * 10].y, BlockImageList[(Tet.arTet[j + i * 10] - 1) % 10]);

			if (Tet.arTet[j + i * 10] == -1)
				DrawBitmap(hMemDC, arTetPoint[j + i * 10].x, arTetPoint[j + i * 10].y, BlockImageList[7]);

		}
	}

	for (i = 0; i < 11; i++)
	{
		DrawBitmap(hMemDC, 415 + i * 16, 10, NumberList[i]);
	}

	for (i = 0; i < 10; i++)
	{
		DrawBitmap(hMemDC, 10 + i * 16, 405, NumberList[Tet.arScore[i]]);
	}

	////
	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);

	ReleaseDC(hMainWnd, hdc);
	InvalidateRect(hMainWnd, NULL, FALSE);
}

