// WindowsProject1.cpp: 응용 프로그램의 진입점을 정의합니다.
//
#include "stdafx.h"

#include <list>
#include<Windows.h>
#include<ObjIdl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#include "WindowsProject1.h"
#include "resource.h"
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

WCHAR lpszText[10] = L"TEXT";

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HDC DC = NULL;
HDC DC2 = NULL;

void DrawFlip(Image* image, int x, int y, int cx, int cy, int px, int py, HDC DC, bool isFlip);

class Avatar {
public:
	int x;
	int y;
	int frame;
	int DIR;
	bool isMove;
	Image*	image;
	int width;
	int height;
	Avatar(int _x, int _y) {
		x = _x;
		y = _y;
		frame = 0;
		DIR = 1;
		isMove = false;
		image = new Image(L"pngresource.png");
		width = 30;
	}
	void Flip() {
		image->RotateFlip(RotateNoneFlipX);
	}
	void Render() {
		

		if (DIR == 2) {
			//image->RotateFlip(RotateNoneFlipX);
		}
		if (!isMove)
		{

			frame %= 3;
			if (frame == 0) {
				DrawFlip(image, x, y, 0, 0, 34, 40, DC, DIR == 2);
				//graphics.DrawImage(&image, x, y, 0, 0, 34, 40, Gdiplus::UnitPixel);
			}
			else if (frame == 1) {
				DrawFlip(image, x + 3, y, 34, 0, 30, 40, DC, DIR == 2);
				//graphics.DrawImage(&image, x+3, y, 34, 0, 30, 40, Gdiplus::UnitPixel);
			}
			else if (frame == 2) {
				DrawFlip(image, x + 4, y, 64, 0, 32, 40, DC, DIR == 2);
				//graphics.DrawImage(&image, x+4, y, 64, 0, 32, 40, Gdiplus::UnitPixel);
			}
		}
		else {
			frame %= 8;
			switch (frame)
			{
			case 0:DrawFlip(image, x, y, 137, 0, 31, 43, DC, DIR == 2); break;
			case 1:DrawFlip(image, x, y, 168, 0, 32, 43, DC, DIR == 2); break;
			case 2:DrawFlip(image, x, y, 200, 0, 32, 43, DC, DIR == 2); break;
			case 3:DrawFlip(image, x, y, 234, 0, 34, 43, DC, DIR == 2); break;
			case 4:DrawFlip(image, x, y, 266, 0, 32, 43, DC, DIR == 2); break;
			case 5:DrawFlip(image, x, y, 298, 0, 32, 43, DC, DIR == 2); break;
			case 6:DrawFlip(image, x, y, 331, 0, 33, 43, DC, DIR == 2); break;
			case 7:DrawFlip(image, x, y, 367, 0, 36, 43, DC, DIR == 2); break;
			case 8:DrawFlip(image, x, y, 403, 0, 36, 43, DC, DIR == 2); break;
			}
		}
	}
	void Move(int v) {
		x += v;
	}
	void Updste() {
		frame += 1;
	}
};

Avatar* avatar;

class Enemy {
public:
	int x;
	int y;
	int frame;
	int DIR;
	bool isMove;
	Image*	image;
	int width;
	bool isActive = true;
	Enemy(int _x, int _y) {

		image = new Image(L"pngresource.png");
		int size = image->GetPaletteSize();
		ColorPalette* tmp = (ColorPalette*)malloc(size);
		Status st = image->GetPalette(tmp, size);
		
		x = _x;
		y = _y;
		frame = 0;
		DIR = 1;
		isMove = false;
		width = 30;
	}
	void Render() {
		if (!isActive) return;

		if (DIR == 2) {
			image->RotateFlip(RotateNoneFlipX);
		}
		if (!isMove)
		{

			frame %= 3;
			if (frame == 0) {
				DrawFlip(image, x, y, 0, 0, 34, 40, DC, DIR == 2);
				//graphics.DrawImage(&image, x, y, 0, 0, 34, 40, Gdiplus::UnitPixel);
			}
			else if (frame == 1) {
				DrawFlip(image, x + 3, y, 34, 0, 30, 40, DC, DIR == 2);
				//graphics.DrawImage(&image, x+3, y, 34, 0, 30, 40, Gdiplus::UnitPixel);
			}
			else if (frame == 2) {
				DrawFlip(image, x + 4, y, 64, 0, 32, 40, DC, DIR == 2);
				//graphics.DrawImage(&image, x+4, y, 64, 0, 32, 40, Gdiplus::UnitPixel);
			}
		}
		else {
			frame %= 8;
			switch (frame)
			{
			case 0:DrawFlip(image, x, y, 137, 0, 31, 43, DC, DIR == 2); break;
			case 1:DrawFlip(image, x, y, 168, 0, 32, 43, DC, DIR == 2); break;
			case 2:DrawFlip(image, x, y, 200, 0, 32, 43, DC, DIR == 2); break;
			case 3:DrawFlip(image, x, y, 234, 0, 34, 43, DC, DIR == 2); break;
			case 4:DrawFlip(image, x, y, 266, 0, 32, 43, DC, DIR == 2); break;
			case 5:DrawFlip(image, x, y, 298, 0, 32, 43, DC, DIR == 2); break;
			case 6:DrawFlip(image, x, y, 331, 0, 33, 43, DC, DIR == 2); break;
			case 7:DrawFlip(image, x, y, 367, 0, 36, 43, DC, DIR == 2); break;
			case 8:DrawFlip(image, x, y, 403, 0, 36, 43, DC, DIR == 2); break;
			}
		}
	}
	void Move(int v) {
		x += v;
	}
	void Updste() {
		if (!isActive) return;
		frame += 1;
	}
};

std::list<Enemy*> enumLst;


class Background {
public:
	int term = 0;
	Image* img_bg;
	Background() {
		img_bg = new Image(L"sky.png");
	}
	void Update() {
		if (avatar->isMove) {
			if (avatar->x < 300) {
				term += 300 - avatar->x;
				avatar->x = 300;
			}
			else if (avatar->x > 700) {
				term += 700 - avatar->x;
				avatar->x = 700;
			}
		}


		if (term > 824) {
			term -= 824;
		}
		else if (term < -824) {
			term += 824;
		}
	}
	void Render(HDC hdc) {
		Graphics graphics(hdc);
		graphics.DrawImage(img_bg, -824 + term, 0, 0, 0, 824, 206, Gdiplus::UnitPixel);
		graphics.DrawImage(img_bg, 0 + term, 0, 0, 0, 824, 206, Gdiplus::UnitPixel);
		graphics.DrawImage(img_bg, 824 + term, 0, 0, 0, 824, 206, Gdiplus::UnitPixel);
		graphics.DrawImage(img_bg, 824 * 2 + term, 0, 0, 0, 824, 206, Gdiplus::UnitPixel);
	}
};


Background* bg;

class Missile {
public:
	int posX;
	int posY;
	int DIR;
	int speed;
	bool isActive;
	int updateCount;
	int width;
	Missile(int x, int y, int dir, int spd) {
		posX = x;
		posY = y;
		DIR = dir;
		speed = spd;
		isActive = false;
		updateCount = 0;
		width = 5;
	}
	void Active(bool isActive) {
		this->isActive = isActive;
	}
	void Update() {
		if (!isActive)
		{
			return;
		}
		updateCount += 1;
		posX += speed * (DIR == 2 ? -1 : 1);

		if (updateCount == 20) {
			updateCount = 0;
			isActive = false;
		}

		//로직 추가 해서 off상태로 바꾼다
	}
	void Render(HDC hdc) {
		if (!isActive) return;
		HBRUSH hbr = CreateSolidBrush(RGB(0, 0, 200));
		SelectObject(hdc, hbr);
		RoundRect(hdc, posX, posY, posX + 10, posY + 10, 5, 5);
		HBRUSH hbr2 = CreateSolidBrush(RGB(0, 0, 200));
		SelectObject(hdc, hbr2);
		DeleteObject(hbr);
	}
};

std::list<Missile*> mslLst;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);


	ULONG_PTR gdiToken;
	GdiplusStartupInput gidplusStartupInput;
	GdiplusStartup(&gdiToken, &gidplusStartupInput, NULL);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	GdiplusShutdown(gdiToken);
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	//wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, L"TEST", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

//BOOL isDown = FALSE;
//WORD x = 300; //케릭터의 상대좌표가 300~700 허용됨
//WORD y = 160;
BOOL isRnder = FALSE;
//int frame = 0;
//BOOL isMove = FALSE;
//WORD DIR = 0; // 0 : NONE , 1: RIGHT, 2 : LEFT, 3: DOWN, 4 : UP



void DrawFlip(Image* image, int x, int y, int cx, int cy, int px, int py, HDC DC, bool isFlip)
{
	Graphics graphics(DC);
	if (isFlip) {
		x;
		y;
		cx = 400 - cx - px;
		cy;
		px;
		py;
	}
	graphics.DrawImage(image, x, y, cx, cy, px, py, Gdiplus::UnitPixel);
}

// 적 10마리 정도 생성
// 배경 클래스화

//int term = 0;

void OnPaint(HDC hdc)
{
	if(DC == NULL) DC = CreateCompatibleDC(hdc);
	if (DC2 == NULL) DC2 = CreateCompatibleDC(hdc);
	
	//Image img_bg(L"sky.png");
	

	HBITMAP newBitmap, preBitmap;
	
	newBitmap = CreateCompatibleBitmap(hdc,2000, 2000);// 비트맵을 실제로 읽어온다 - 이미지를 만든다
	//newBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(DC));// 비트맵을 실제로 읽어온다 - 값을 복사해온다
	preBitmap = (HBITMAP)SelectObject(DC, (HGDIOBJ)newBitmap);  // 새로만든 dc에 읽어온 비트맵을 장착
	(HBITMAP)SelectObject(DC2, (HGDIOBJ)preBitmap);
	//Graphics graphics(DC);
	//Graphics graphics(hdc);
	PatBlt(DC, 0, 0, 1000, 1000, BLACKNESS);
	
	/*if (avatar->isMove) {
		if (avatar->x < 300) {
			term += 300 - avatar->x;
			avatar->x = 300;
		}
		else if (avatar->x > 700) {
			term += 700 - avatar->x;
			avatar->x = 700;
		}
	}


	if (term > 824) {
		term -= 824;
	}
	else if (term < -824) {
		term += 824;
	}

	graphics.DrawImage(&img_bg, -824 + term, 0, 0, 0, 824, 206, Gdiplus::UnitPixel);
	graphics.DrawImage(&img_bg, 0 + term, 0, 0, 0, 824, 206, Gdiplus::UnitPixel);
	graphics.DrawImage(&img_bg, 824 + term, 0, 0, 0, 824, 206, Gdiplus::UnitPixel);
	graphics.DrawImage(&img_bg, 824 * 2 + term, 0, 0, 0, 824, 206, Gdiplus::UnitPixel);*/
	
	bg->Render(DC);
	avatar->Render();
	auto iter = enumLst.begin();

	for (iter; iter != enumLst.end(); iter++) {
		(*iter)->Render();
	}

	auto iter2 = mslLst.begin();

	for (iter2; iter2 != mslLst.end(); iter2++) {
		(*iter2)->Render(DC);
	}
	


	// 케릭터의 상대 좌표가 300보다 작으면 상대좌표가 300이 되는 위치에 카메라를 위치시킴
	// 케릭터의 상대좌표가 700보다 크면 상대좌표가 700이 되는 위치에 카메라를 위치시킴
	

	//BitBlt(hdc, camPosX, 0, 1000, 1000, DC2, 0, 0, SRCCOPY); // 여기 앞에 좌표를 카메라 좌표로 사용

	//케릭터의 상대 좌표값은 camPosX + x

	BitBlt(hdc, 0, 0, 2000, 2000, DC2, 0, 0, SRCCOPY); // 여기 앞에 좌표를 카메라 좌표로 사용
	//SelectObject(DC, (HGDIOBJ)preBitmap);  // 새로만든 dc에 읽어온 비트맵을 장착
	
}

//배경만 움직일 시 적이 움직이지 않는 현상 수정
// 적이 속도를 가지고 움직이게 수정
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int factor = 1;
	//GetDC(hWnd);
    switch (message)
    {
	/*case WM_KEYDOWN:
	{
		HDC hdc = GetDC(hWnd);
		
		
		if (wCharLst.size() >= 10)
		{
			wCharLst.pop_front();
		}
		WCHAR input = L'a';
		wCharLst.push_back(input);
		auto iter = wCharLst.begin();
		int idx = 0;
		for (iter; iter != wCharLst.end(); ++iter)
		{
			TextOut(hdc, x + idx*10, y, &(*iter), 1);
			idx++;
		}
		
		ReleaseDC(hWnd, hdc);
	}
	case WM_LBUTTONDOWN:
	{
		isDown = TRUE;
	}
	break;
	case WM_LBUTTONUP:
	{
		isDown = FALSE;
	}
		break;
	case WM_MOUSEMOVE:
	{
		y = HIWORD(lParam);
		x = LOWORD(lParam);
		break;
	}*/
	case WM_KEYDOWN:
	{
		// avatar관련 처리
		// 눌렸다는거 인지
		//if (wParam == VK_LEFT || wParam == VK_UP || wParam == VK_DOWN || wParam == VK_RIGHT)
		{
			switch (wParam)
			{
			case VK_LEFT:	avatar->DIR = 2;	break;
			case VK_RIGHT:	avatar->DIR = 1;	break;
			/*case VK_UP:		DIR = 4;	break;
			case VK_DOWN:	DIR = 3;	break;*/
			//case VK_END:		camPosX -= 10; break;
			//case VK_HOME:		camPosX += 10; break;
			case VK_SPACE:
				auto iter = mslLst.begin();
				for (iter; iter != mslLst.end(); iter++) {
					if (!((*iter)->isActive)) {
						(*iter)->Active(true);
						(*iter)->posX = avatar->x;
						(*iter)->posY = avatar->y;
						(*iter)->DIR = avatar->DIR;
						if (avatar->DIR == 2) {
							(*iter)->posX -= 3;
						} else if (avatar->DIR == 1) {
							(*iter)->posX += 17;
						}
						(*iter)->posY += 15;
						break;
					}
				}
				break;
			}
			
			avatar->isMove = TRUE;
		}
	}
	break;
	case WM_KEYUP:
	{
		//풀렸다는 것 인지
		//DIR = 0;
		avatar->isMove = FALSE;
		factor = 0;
	}
	break;
	case WM_CREATE:
	{
		static HANDLE hTimer = (HANDLE)SetTimer(hWnd, 0, 80, NULL);
		avatar = new Avatar(300, 160);
		bg = new Background();
		for (int i = 0; i < 10; i++)
		{
			enumLst.push_back(new Enemy(150 * i + 350 , 160));
		}
		for (int i = 0; i < 10; i++)
		{
			mslLst.push_back(new Missile(0, 0, 1, 10));
		}
		
		
	}
		break;
	case WM_TIMER:
	{
		// avatar의 업데이트 호출
		bg->Update();
		avatar->Updste();
		auto iter = enumLst.begin();

		for (iter; iter != enumLst.end(); iter++) {
			(*iter)->Updste();
		}

		auto iter2 = mslLst.begin();

		for (iter2; iter2 != mslLst.end(); iter2++) {
			(*iter2)->Update();
		}

		if (avatar->isMove) {
			factor += 1;
			if (factor > 100) factor = 100;
			switch (avatar->DIR)
			{
				// avatar의 방향을 참고해서  move호출
			case 1:
				//x += 10; 
				avatar->Move(factor);
				break;
			case 2:
				//x -= 10; 
				avatar->Move(factor * -1);
				break;
				/*case 3:	y += 10; break;
				case 4: y -= 10; break;*/
			}
		}
		else {
			factor = 0;
		}
		
		// avatar vs enemy

		iter = enumLst.begin();

		for (iter; iter != enumLst.end(); iter++) {
			avatar->x;
			avatar->width;
			(*iter)->x;
			(*iter)->width;

			if ((*iter)->x >= avatar->x && (*iter)->x <= avatar->x + avatar->width)
			{
				//충돌
				enumLst.erase(iter);
				break;
			}
			if ((*iter)->x + (*iter)->width >= avatar->x 
				&& (*iter)->x + (*iter)->width <= avatar->x + avatar->width)
			{
				//충돌
				enumLst.erase(iter);
				break;
			}
		}

		iter2 = mslLst.begin();

		for (iter2; iter2 != mslLst.end(); iter2++) {
			if (!(*iter2)->isActive) continue;
			iter = enumLst.begin();
			for (iter; iter != enumLst.end(); iter++) {
				if (!(*iter)->isActive) continue;
				if ((*iter)->x >= (*iter2)->posX && (*iter)->x <= (*iter2)->posX + (*iter2)->width)
				{
					//충돌
					//enumLst.erase(iter);
					(*iter)->isActive = false;
					(*iter2)->isActive = false;
					continue;
				}
				if ((*iter)->x + (*iter)->width >= (*iter2)->posX
					&& (*iter)->x + (*iter)->width <= (*iter2)->posX + (*iter2)->width)
				{
					//충돌
					//enumLst.erase(iter);
					(*iter)->isActive = false;
					(*iter2)->isActive = false;
					continue;
				}
			}
		}


		//coll check

		//frame += 1;
		
		//InvalidateRect// WM_PAINT
		//InvalidateRect(hWnd, NULL, TRUE);
		//InvalidateRect((HWND)DC, NULL, TRUE); 
		HDC hdc = GetDC(hWnd);
		OnPaint(hdc);
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
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
    case WM_PAINT:
        {
		// 펜
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
			/*HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			HBRUSH bruch = CreateSolidBrush(RGB(0, 0, 255));

			SelectObject(hdc, pen);
			SelectObject(hdc, bruch);
			Rectangle(hdc, x, y, x+50, y+50);

			if (isRnder) {
				Rectangle(hdc, 0, 0, 10, 10);
			}
			
			DeleteObject(pen);
			DeleteObject(bruch);*/

			OnPaint(hdc);





			//HBITMAP newBitmap, preBitmap;

			//HDC DC = CreateCompatibleDC(hdc);

			//newBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));// 비트맵을 실제로 읽어온다
			//preBitmap = (HBITMAP)SelectObject(DC, (HGDIOBJ)newBitmap);  // 새로만든 dc에 읽어온 비트맵을 장착
			//if (!isMove)
			//{
			//	frame %= 3;
			//	if (frame == 0) {
			//		BitBlt(hdc, x, y, 34, 40, DC, 0, 0, SRCCOPY);
			//	}
			//	else if (frame == 1) {
			//		BitBlt(hdc, x+3, y, 30, 40, DC, 34, 0, SRCCOPY);
			//	}
			//	else if (frame == 2) {
			//		BitBlt(hdc, x+4, y, 32, 40, DC, 64, 0, SRCCOPY);
			//	}
			//}
			//else {
			//	frame %= 9;
			//	switch (frame)
			//	{
			//	case 0:BitBlt(hdc, x, y, 36, 43, DC, 102, 0, SRCCOPY); break;
			//	case 1:BitBlt(hdc, x, y, 31, 43, DC, 137, 0, SRCCOPY); break;
			//	case 2:BitBlt(hdc, x, y, 32, 43, DC, 168, 0, SRCCOPY); break;
			//	case 3:BitBlt(hdc, x, y, 34, 43, DC, 200, 0, SRCCOPY); break;
			//	case 4:BitBlt(hdc, x, y, 32, 43, DC, 234, 0, SRCCOPY); break;
			//	case 5:BitBlt(hdc, x, y, 32, 43, DC, 265, 0, SRCCOPY); break;
			//	case 6:BitBlt(hdc, x, y, 33, 43, DC, 297, 0, SRCCOPY); break;
			//	case 7:BitBlt(hdc, x, y, 36, 43, DC, 330, 0, SRCCOPY); break;
			//	case 8:BitBlt(hdc, x, y, 36, 43, DC, 366, 0, SRCCOPY); break;
			//	}
			//}
			//
			//

			//SelectObject(DC, preBitmap);
			//DeleteObject(newBitmap);
			//DeleteObject(DC);


            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
