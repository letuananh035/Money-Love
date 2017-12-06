// GiuaKi.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GiuaKi.h"
#include "Global.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	InputMoney(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	InputNote(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GIUAKI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GIUAKI));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GIUAKI));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_GIUAKI);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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


	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN,
		CW_USEDEFAULT, 0, Global::sizeMain.cx, Global::sizeMain.cy, NULL, NULL, hInstance, NULL);

	Global::hWndMain = hWnd;



	if (!hWnd)
	{
		return FALSE;
	}



	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		//HANDLE_MSG(hWnd, WM_LBUTTONDBLCLK, OnLButtonDown);
		//HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
		//HANDLE_MSG(hWnd, WM_NOTIFY, OnNotify);
		//HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		//HANDLE_MSG(hWnd, WM_VSCROLL, OnVScroll);
		//HANDLE_MSG(hWnd, WM_HSCROLL, OnHScroll);
		HANDLE_MSG(hWnd, WM_MOUSEWHEEL, OnMouseWheel);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


FButton* buttonSet = NULL;
HDC bufferInput;
// Message handler for about box.
INT_PTR CALLBACK InputMoney(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	RECT rect;
	int width;
	int height;
	switch (message)
	{
	case WM_INITDIALOG:{
		LOGFONT lf;
		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFont = CreateFont(lf.lfHeight - 5, lf.lfWidth,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight + 4,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, lf.lfFaceName);
		//
		HWND hwnd = GetDlgItem(hDlg, IDC_EDIT1);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
		std::wstring str = std::to_wstring(Global::TempChiTieu.tien);
		SendMessage(hwnd, WM_SETTEXT, NULL, LPARAM(str.c_str()));
		return (INT_PTR)TRUE;
	}

	case WM_PAINT:{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hDlg, &ps);

		GetWindowRect(hDlg, &rect);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;

		DeleteDC(bufferInput);
		bufferInput = GetParentHDC(hDlg);

		Graphics grBuffer(bufferInput);
		SolidBrush backgroudHeader(Color(255, 236, 240, 241));
		grBuffer.FillRectangle(&backgroudHeader, 0, 0, width, height);


		if (buttonSet == NULL){
			RECT rect = { 10, 80, width - 25, 120 };
			//button1 = new FButton(L"Thống kê", Global::font_Arial_15, rect, LEFT, Color(255, 0, 76, 60));
			buttonSet = new FButton(L"Set", Global::font_Arial_20, rect, CENTER, Color(255, 0, 76, 60));
		}
		if (buttonSet->MoseEnter){
			buttonSet->color = Color(255, 189, 195, 199);
		}
		else{
			buttonSet->color = Color(255, 236, 240, 241);
		}
		buttonSet->colorText = Color(255, 44, 62, 80);
		buttonSet->Draw(bufferInput);

		FText::SetColor(Color(255, 44, 62, 80));
		FText::DrawTextFont(bufferInput, PointF(width / 2, 25), L"Nhập số tiền", Global::font_Arial_15, CENTER);

		if (!BitBlt(hdc, 0, 0, width,
			height, bufferInput, 0, 0, SRCCOPY)){
			MessageBox(hDlg, L"", L"", 0);
		}
		EndPaint(hDlg, &ps);
	}
				  break;
	case WM_LBUTTONDOWN:{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		if (buttonSet != NULL && buttonSet->IsEnter(x, y)){
			HWND hwnd = GetDlgItem(hDlg, IDC_EDIT1);
			int nLength = GetWindowTextLength(hwnd);
			if (nLength > 0)
			{
				TCHAR *sText = new TCHAR[nLength + 1];
				GetWindowText(hwnd, sText, nLength + 1);
				int num = _ttoi(sText);
				Global::TempChiTieu.tien = num;
				InvalidateRect(Global::hWndMain, NULL, false);
				delete[] sText;

			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	case WM_MOUSEMOVE:{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		buttonSet->OnMove(xPos, yPos);
		InvalidateRect(hDlg, NULL, false);
	}
					  break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			HWND hwnd = GetDlgItem(hDlg, IDC_EDIT1);
			int nLength = GetWindowTextLength(hwnd);
			if (nLength > 0)
			{
				TCHAR *sText = new TCHAR[nLength + 1];
				GetWindowText(hwnd, sText, nLength + 1);
				int num = _ttoi(sText);
				Global::TempChiTieu.tien = num;
				InvalidateRect(Global::hWndMain, NULL, false);
				delete[] sText;

			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

FButton* buttonSet2 = NULL;
HDC bufferInput2;
// Message handler for about box.
INT_PTR CALLBACK InputNote(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	RECT rect;
	int width;
	int height;
	switch (message)
	{
	case WM_INITDIALOG:{
		LOGFONT lf;
		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFont = CreateFont(lf.lfHeight - 5, lf.lfWidth,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight + 4,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, lf.lfFaceName);
		//
		HWND hwnd = GetDlgItem(hDlg, IDC_EDIT2);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
		SendMessage(hwnd, WM_SETTEXT, NULL, LPARAM(Global::TempChiTieu.chuthich));
		return (INT_PTR)TRUE;
	}

	case WM_PAINT:{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hDlg, &ps);

		GetWindowRect(hDlg, &rect);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;

		DeleteDC(bufferInput2);
		bufferInput2 = GetParentHDC(hDlg);

		Graphics grBuffer(bufferInput2);
		SolidBrush backgroudHeader(Color(255, 236, 240, 241));
		grBuffer.FillRectangle(&backgroudHeader, 0, 0, width, height);


		if (buttonSet2 == NULL){
			RECT rect = { 10, 80, width - 25, 120 };
			//button1 = new FButton(L"Thống kê", Global::font_Arial_15, rect, LEFT, Color(255, 0, 76, 60));
			buttonSet2 = new FButton(L"Set", Global::font_Arial_20, rect, CENTER, Color(255, 0, 76, 60));
		}
		if (buttonSet2->MoseEnter){
			buttonSet2->color = Color(255, 189, 195, 199);
		}
		else{
			buttonSet2->color = Color(255, 236, 240, 241);
		}
		buttonSet2->colorText = Color(255, 44, 62, 80);
		buttonSet2->Draw(bufferInput2);

		FText::SetColor(Color(255, 44, 62, 80));
		FText::DrawTextFont(bufferInput2, PointF(width / 2, 25), L"Nhập ghi chú(200 kí tự)", Global::font_Arial_15, CENTER);

		if (!BitBlt(hdc, 0, 0, width,
			height, bufferInput2, 0, 0, SRCCOPY)){
			MessageBox(hDlg, L"", L"", 0);
		}
		EndPaint(hDlg, &ps);
	}
				  break;
	case WM_LBUTTONDOWN:{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		if (buttonSet2 != NULL && buttonSet2->IsEnter(x, y)){
			HWND hwnd = GetDlgItem(hDlg, IDC_EDIT2);
			int nLength = GetWindowTextLength(hwnd);
			if (nLength > 0)
			{
				TCHAR *sText = new TCHAR[nLength + 1];
				GetWindowText(hwnd, sText, nLength + 1);
				int num = _ttoi(sText);
				_tcscpy(Global::TempChiTieu.chuthich, sText);
				InvalidateRect(Global::hWndMain, NULL, false);
				delete[] sText;
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	case WM_MOUSEMOVE:{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		buttonSet2->OnMove(xPos, yPos);
		InvalidateRect(hDlg, NULL, false);
		break;
	}
	case WM_COMMAND:{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			HWND hwnd = GetDlgItem(hDlg, IDC_EDIT2);
			int nLength = GetWindowTextLength(hwnd);
			if (nLength > 0)
			{
				TCHAR *sText = new TCHAR[nLength + 1];
				GetWindowText(hwnd, sText, nLength + 1);
				int num = _ttoi(sText);
				_tcscpy(Global::TempChiTieu.chuthich, sText);
				InvalidateRect(Global::hWndMain, NULL, false);
				delete[] sText;
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
					break;
	}
	return (INT_PTR)FALSE;
}



void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify){
	switch (id)
	{
	case IDM_ABOUT:
		//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
		//default:
		//return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

FButton* button1 = NULL;
FButton* button2 = NULL;
FButton* button3 = NULL;
FButton* button4 = NULL;

int SumThu = 0;
int SumChi = 0;

int SumAn = 0;
int SumDiChuyen = 0;
int SumNha = 0;
int SumCho = 0;
int SumDichVu = 0;
int SumLuong = 0;
int SumKhoanThuKhac = 0;

int posTab = 0;
int posAdd = Global::sizeMain.cx;
int posDraw = 0;
int posCirle = 0;


TypeChiTieu typeShow;


FButtonImage* buttonEditNote;
FButtonImage* buttonEditMoney;
//FFont* font_Arial_9;
//FFont* font_Arial_11;
/*
AN,
DICHUYEN,
NHA,
CHO,
DICHVU,
LUONG,
KHOANTHUKHAC
*/
FButtonImage* buttonTypeAN;
FButtonImage* buttonTypeDICHUYEN;
FButtonImage* buttonTypeNHA;
FButtonImage* buttonTypeCHO;
FButtonImage* buttonTypeDICHVU;
FButtonImage* buttonTypeLUONG;
FButtonImage* buttonTypeKHOANTHUKHAC;


void OnPaint(HWND hWnd){


	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	int width = Global::sizeMain.cx;
	int height = Global::sizeMain.cy;

	/*Xóa và tạo lại buffer*/
	DeleteDC(Global::hdcBuffer);
	Global::hdcBuffer = GetParentHDC(hWnd);
	Graphics grBuffer(Global::hdcBuffer);
	if (posAdd == width && posTab == 0 && posDraw == 0){
		DrawMain();
	}
	else{
		if (posAdd != 0 && posDraw != width){
			if (!BitBlt(Global::hdcBuffer, 0, 0, width,
				height, Global::bufferApp, 0, 0, SRCCOPY)){
				MessageBox(hWnd, L"", L"", 0);
			}
		}
	}
	//Button Home
	if (Global::buttonAdd == NULL)
		Global::buttonAdd = new FButtonImage(L"Data/add.png", width - 50, 8);
	Global::buttonAdd->Draw(Global::hdcBuffer);

	if (Global::isShowAdd){
		DrawAdd();
	}
	else{
		if (posAdd < width){
			posAdd += 20;
			InvalidateRect(Global::hWndMain, NULL, false);
			SolidBrush backgroudHeader(Color(255, 236, 240, 241));
			grBuffer.FillRectangle(&backgroudHeader, posAdd, 0, width, height);
		}
	}
	/*Home*/
	DrawTabHome();
	//Button Home
	if (!Global::isShowAdd && !Global::isShowDraw){
		if (Global::buttonHome == NULL)
			Global::buttonHome = new FButtonImage(L"Data/home.png", 0, 0);
		if (posTab > 50){
			Global::buttonHome->SetPosition(posTab - 50, 8);
			Global::buttonHome->Draw(Global::hdcBuffer);
		}
		else{
			Global::buttonHome->SetPosition(0, 8);
			Global::buttonHome->Draw(Global::hdcBuffer);
		}
	}


	//Vẽ Thống Kê

	if (Global::isShowDraw){
		//Vẽ khung thống kê
		SolidBrush blackBrush(Color(255, 236, 240, 241));
		grBuffer.FillRectangle(&blackBrush, 0, 0, posDraw, height);
		//Vẽ Khung Title
		SolidBrush titleBrush(Color(255, 46, 204, 113));
		grBuffer.FillRectangle(&titleBrush, 0, 0, posDraw, 50);
		//Vẽ Title
		//FText::SetColor(Color(255, 231, 76, 60));
		FText::DrawTextFont(Global::hdcBuffer, PointF(posDraw - width + 50, 25), L"Thống kê", Global::font_Arial_15, LEFT);
		if (Global::buttonClose == NULL){
			Global::buttonClose = new FButtonImage(L"Data/close.png", 0, 8);
		}
		Global::buttonClose->SetPosition(posDraw - width, 8);
		Global::buttonClose->Draw(Global::hdcBuffer);
		grBuffer.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
		//grBuffer.SetInterpolationMode(InterpolationModeHighQualityBicubic);
		//Vẽ biểu đồ
		int chartY = 120;

		SolidBrush whiteCircle(Color(150, 0, 0, 0));
		SolidBrush blackalphaCircle(Color(150, 52, 73, 94)); // Xanh đen mờ
		grBuffer.FillPie(&whiteCircle, (posDraw - 200) / 2, chartY, 200, 200, 0, 360);
		if (Global::ShowType == 0 && SumChi != 0){
			//
			REAL DoHienTai = 0;
			int sum = 0;
			int posSize = 0;
			//Sum AN
			DrawPie(AN, SumAn, SumChi, DoHienTai, L"Data/restaurant.png", grBuffer, Color(255, 46, 204, 113));
			//Sum Cho
			DrawPie(CHO, SumCho, SumChi, DoHienTai, L"Data/cart.png", grBuffer, Color(255, 52, 152, 219));
			//Sum Di Chuyen
			DrawPie(DICHUYEN, SumDiChuyen, SumChi, DoHienTai, L"Data/taxi.png", grBuffer, Color(255, 155, 89, 182));
			//Sum Dich Vu
			DrawPie(DICHVU, SumDichVu, SumChi, DoHienTai, L"Data/navigation.png", grBuffer, Color(255, 230, 126, 34));
			//Sum Nha
			DrawPie(NHA, SumNha, SumChi, DoHienTai, L"Data/house.png", grBuffer, Color(255, 44, 62, 80));
		
			if (Global::isShowType){
				SolidBrush BGBrush(Color(255, 236, 240, 241));
				SolidBrush BGLINEBrush(Color(255, 44, 62, 80));
				grBuffer.FillRectangle(&BGLINEBrush, Global::mouse_x - 1, Global::mouse_y - 1 - 40, 120 + 2, 40 + 2);
				grBuffer.FillRectangle(&BGBrush, Global::mouse_x, Global::mouse_y - 40, 120, 40);
				
				TCHAR per[50]; // where you put result
				if (typeShow == AN){
					_stprintf(per, TEXT("Tiền Ăn:\n%s"), MakeMoney(SumAn));
				}
				else if (typeShow == DICHUYEN){
					_stprintf(per, TEXT("Tiền Di Chuyển:\n%s"), MakeMoney(SumDiChuyen));
				}
				else if (typeShow == DICHVU){
					_stprintf(per, TEXT("Tiền Dịch Vụ:\n%s"), MakeMoney(SumDichVu));
				}
				else if (typeShow == CHO){
					_stprintf(per, TEXT("Tiền Mua Sắm:\n%s"), MakeMoney(SumCho));
				}
				else if (typeShow == NHA){
					_stprintf(per, TEXT("Tiền Nhà:\n%s"), MakeMoney(SumNha));
				}
				FText::DrawTextFont(Global::hdcBuffer, PointF(Global::mouse_x + 5, Global::mouse_y - 40 + 20), per, Global::font_Arial_10, LEFT);
			}
			TCHAR per[30]; // where you put result
			_stprintf(per, TEXT("Tổng Chi: %s"), MakeMoney(SumChi));
			FText::DrawTextFont(Global::hdcBuffer, PointF(width / 2, height - 200), per, Global::font_Arial_20, CENTER);
		}
		if (Global::ShowType == 1 && SumThu != 0){
			//
			REAL DoHienTai = 0;
			int sum = 0;
			int posSize = 0;
			//Sum LUONG
			DrawPie(LUONG, SumLuong, SumThu, DoHienTai, L"Data/money-bag.png", grBuffer, Color(255, 46, 204, 113));
			//Sum KHOANTHUKHAC
			DrawPie(KHOANTHUKHAC, SumKhoanThuKhac, SumThu, DoHienTai, L"Data/coin.png", grBuffer, Color(255, 52, 152, 219));

			if (Global::isShowType){
				SolidBrush BGBrush(Color(255, 236, 240, 241));
				SolidBrush BGLINEBrush(Color(255, 44, 62, 80));
				grBuffer.FillRectangle(&BGLINEBrush, Global::mouse_x - 1, Global::mouse_y - 1 - 40, 120 + 2, 40 + 2);
				grBuffer.FillRectangle(&BGBrush, Global::mouse_x, Global::mouse_y - 40, 120, 40);

				TCHAR per[50]; // where you put result
				if (typeShow == KHOANTHUKHAC){
					_stprintf(per, TEXT("Khoảng Thu Khác:\n%s"), MakeMoney(SumKhoanThuKhac));
				}
				else if (typeShow == LUONG){
					_stprintf(per, TEXT("Tiền Lương:\n%s"), MakeMoney(SumLuong));
				}
				FText::DrawTextFont(Global::hdcBuffer, PointF(Global::mouse_x + 5, Global::mouse_y - 40 + 20), per, Global::font_Arial_10, LEFT);
			}
			TCHAR per[50]; // where you put result
			_stprintf(per, TEXT("Tổng Thu: %s"), MakeMoney(SumThu));
			FText::DrawTextFont(Global::hdcBuffer, PointF(width / 2, height - 200), per, Global::font_Arial_20, CENTER);
		}
		if (Global::ShowType == 2 && SumThu + SumChi != 0){
			//
			REAL DoHienTai = 0;
			int sum = 0;
			int posSize = 0;
			//Sum THU
			DrawPie(THU, SumThu, SumThu + SumChi, DoHienTai, L"Data/get-money.png", grBuffer, Color(255, 46, 204, 113));
			//Sum CHI
			DrawPie(CHI, SumChi, SumThu + SumChi, DoHienTai, L"Data/money.png", grBuffer, Color(255, 52, 152, 219));

			if (Global::isShowType){
				SolidBrush BGBrush(Color(255, 236, 240, 241));
				SolidBrush BGLINEBrush(Color(255, 44, 62, 80));
				grBuffer.FillRectangle(&BGLINEBrush, Global::mouse_x - 1, Global::mouse_y - 1 - 40, 120 + 2, 40 + 2);
				grBuffer.FillRectangle(&BGBrush, Global::mouse_x, Global::mouse_y - 40, 120, 40);

				TCHAR per[50]; // where you put result
				if (typeShow == THU){
					_stprintf(per, TEXT("Tổng Thu:\n%s"), MakeMoney(SumThu));
				}
				else if (typeShow == CHI){
					_stprintf(per, TEXT("Tổng Chi:\n%s"), MakeMoney(SumChi));
				}
				FText::DrawTextFont(Global::hdcBuffer, PointF(Global::mouse_x + 5, Global::mouse_y - 40 + 20), per, Global::font_Arial_10, LEFT);
			}
			TCHAR per[50]; // where you put result
			_stprintf(per, TEXT("Số dư: %s"), MakeMoney(SumThu - SumChi));
			FText::DrawTextFont(Global::hdcBuffer, PointF(width / 2, height - 200), per, Global::font_Arial_20, CENTER);
		}
		//--------
		if (posCirle <= 360){
			posCirle += 3;
			InvalidateRect(Global::hWndMain, NULL, false);
		}
		//Di chuyển
		if (posDraw < width){
			posDraw += 20;
			InvalidateRect(Global::hWndMain, NULL, false);
		}
	}
	else{
		if (posDraw > 0){
			posDraw -= 20;
			InvalidateRect(Global::hWndMain, NULL, false);
			SolidBrush backgroudHeader(Color(255, 236, 240, 241));
			grBuffer.FillRectangle(&backgroudHeader, 0, 0, posDraw, height);
		}
		else{
			posCirle = 0;
		}
	}



	//Button Add
	//
	if (!BitBlt(hdc, 0, 0, width,
		height, Global::hdcBuffer, 0, 0, SRCCOPY)){
		MessageBox(hWnd, L"", L"", 0);
	}
	// TODO: Add any drawing code here...
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hwnd){


	delete  Global::font_Arial_30;
	delete  Global::font_Arial_12;
	delete  Global::font_Arial_15;
	delete  Global::font_Arial_20;
	delete  Global::font_Arial_25;
	//delete font_Arial_9;
	delete  Global::font_Arial_10;
	//delete font_Arial_11;
	GdiplusShutdown(Global::gdiplusToken);
	PostQuitMessage(0);
}

void AddItem(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	Date date;
	date.day = ltm->tm_mday;
	date.month = 1 + ltm->tm_mon;
	date.year = 1900 + ltm->tm_year;
	date.thu = ltm->tm_wday;

	if (Global::listData.size() > 0 && Global::listData[Global::listData.size() - 1].date == date){
		Global::listData[Global::listData.size() - 1].listChiTieu.push_back(Global::TempChiTieu);
	}
	else{
		DataManager temp;
		temp.MakeDate();
		temp.listChiTieu.push_back(Global::TempChiTieu);
		Global::listData.push_back(temp);
	}
	Global::TempChiTieu.tien = 0;
	Global::TempChiTieu.type = AN;
	_tcscpy(Global::TempChiTieu.chuthich, L"");

	MakeListItem(Global::listData);
	InvalidateRect(Global::hWndMain, NULL, false);
}


BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){
	int width = Global::sizeMain.cx;
	int height = Global::sizeMain.cy;
	Global::bufferApp = GetParentHDC(hwnd);
	GdiplusStartup(&Global::gdiplusToken, &Global::gdiplusStartupInput, NULL);

	_tcscpy(Global::TempChiTieu.chuthich, L"");
	Global::TempChiTieu.tien = 0;
	Global::TempChiTieu.type = AN;

	Global::font_Arial_30 = new FFont(L"Arial", 30, FontStyle::FontStyleBold);
	Global::font_Arial_12 = new FFont(L"Arial", 12, FontStyle::FontStyleBold);
	Global::font_Arial_15 = new FFont(L"Arial", 15, FontStyle::FontStyleBold);
	Global::font_Arial_20 = new FFont(L"Arial", 20, FontStyle::FontStyleBold);
	Global::font_Arial_25 = new FFont(L"Arial", 25, FontStyle::FontStyleBold);
	//font_Arial_9  = new FFont(L"Arial", 9, FontStyle::FontStyleBold);
	Global::font_Arial_10 = new FFont(L"Arial", 10, FontStyle::FontStyleBold);
	//font_Arial_11 = new FFont(L"Arial", 11, FontStyle::FontStyleBold);

	//Lấy dữ liêu
	GetData();
	MakeListItem(Global::listData);
	return true;
}
HDC GetParentHDC(HWND hWnd){
	HDC resultHDC = NULL;
	HBITMAP hBitmap = NULL;
	int width = Global::sizeMain.cx;
	int height = Global::sizeMain.cy;

	HDC hDc = ::GetDC(hWnd);

	resultHDC = ::CreateCompatibleDC(hDc);

	hBitmap = ::CreateCompatibleBitmap(hDc, width, height);

	::SelectObject(resultHDC, hBitmap);
	::DeleteObject(hBitmap);
	::DeleteDC(hDc);
	return resultHDC;
}

HDC MakeHDC(int width, int height){
	HDC resultHDC = NULL;
	HBITMAP hBitmap = NULL;

	HDC hDc = ::GetDC(NULL);

	resultHDC = ::CreateCompatibleDC(hDc);

	hBitmap = ::CreateCompatibleBitmap(hDc, width, height);

	::SelectObject(resultHDC, hBitmap);
	::DeleteObject(hBitmap);
	::DeleteDC(hDc);
	return resultHDC;
}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags){
	int width = Global::sizeMain.cx;
	int height = Global::sizeMain.cy;

	if (Global::buttonHome != NULL && Global::buttonHome->IsEnter(x, y) == true && Global::isShowAdd == false && posAdd == width  && !Global::isShowDraw){
		if (Global::isShowTab == true){
			Global::isShowTab = false;
			InvalidateRect(Global::hWndMain, NULL, false);
			return;
		}
		else{
			Global::isShowTab = true;
			if (!BitBlt(Global::bufferApp, 0, 0, width,
				height, Global::hdcBuffer, 0, 0, SRCCOPY)){
				MessageBox(hwnd, L"", L"", 0);
			}
			InvalidateRect(Global::hWndMain, NULL, false);
			return;
		}
	}
	if (Global::buttonAdd != NULL && Global::buttonAdd->IsEnter(x, y) == true && posAdd == width){
		if (Global::isShowTab == false && !Global::isShowDraw){
			//MessageBox(hwnd, L"Add button", 0, 0);
			Global::isShowAdd = true;
			if (!BitBlt(Global::bufferApp, 0, 0, width,
				height, Global::hdcBuffer, 0, 0, SRCCOPY)){
				MessageBox(hwnd, L"", L"", 0);
			}
			InvalidateRect(Global::hWndMain, NULL, false);
			return;
		}
	}

	if (Global::buttonLuu != NULL && Global::buttonLuu->IsEnter(x, y) && Global::isShowAdd == true && Global::isShowTab == false && !Global::isShowDraw){
		if (Global::TempChiTieu.tien > 0){
			if (Global::isShowItem != true){
				AddItem();
				SaveData();
				Global::isShowAdd = false;
				InvalidateRect(Global::hWndMain, NULL, false);
			}
			else{
				_tcscpy(Global::listData[Global::indexManager].listChiTieu[Global::indexItem].chuthich, Global::TempChiTieu.chuthich);
				Global::listData[Global::indexManager].listChiTieu[Global::indexItem].tien = Global::TempChiTieu.tien;
				Global::listData[Global::indexManager].listChiTieu[Global::indexItem].type = Global::TempChiTieu.type;
				SaveData();

				Global::isShowItem = false;
				Global::isShowAdd = false;

				Global::TempChiTieu.tien = 0;
				Global::TempChiTieu.type = AN;
				_tcscpy(Global::TempChiTieu.chuthich, L"");

				MakeListItem(Global::listData);
				InvalidateRect(Global::hWndMain, NULL, false);

			}
		}
		return;
	}
	if (button1 != NULL && button1->IsEnter(x, y) && Global::isShowTab == true && posTab == width - 180){
		//MessageBox(hwnd, L"Menu 1", 0, 0);
		Global::isShowDraw = true;
		Global::isShowTab = false;
		Global::ShowType = 0;
		posTab = 0;
		return;
	}
	if (button2 != NULL && button2->IsEnter(x, y) && Global::isShowTab == true && posTab == width - 180){
		//MessageBox(hwnd, L"Menu 2", 0, 0);
		Global::isShowDraw = true;
		Global::isShowTab = false;
		Global::ShowType = 1;
		posTab = 0;
		return;
	}
	if (button3 != NULL && button3->IsEnter(x, y) && Global::isShowTab == true && posTab == width - 180){
		//MessageBox(hwnd, L"Menu 2", 0, 0);
		Global::isShowDraw = true;
		Global::isShowTab = false;
		Global::ShowType = 2;
		posTab = 0;
		return;
	}
	if (button4 != NULL && button4->IsEnter(x, y) && Global::isShowTab == true && posTab == width - 180){
		//MessageBox(hwnd, L"Menu 4", 0, 0);
		if (Global::listData.size() > 0){
			SaveCSV();
		}
		Global::isShowTab = false;
		InvalidateRect(Global::hWndMain, NULL, false);
		return;
	}
	if (Global::buttonClose != NULL && Global::buttonClose->IsEnter(x, y) && Global::isShowTab == false){
		if (Global::isShowAdd == true){
			Global::isShowAdd = false;
			_tcscpy(Global::TempChiTieu.chuthich, L"");
			Global::TempChiTieu.tien = 0;
			Global::TempChiTieu.type = AN;
			Global::isShowItem = false;
			return;
		}
		if (Global::isShowDraw == true){
			Global::isShowDraw = false;
			return;
		}
	}
	if (buttonEditMoney != NULL && buttonEditMoney->IsEnter(x, y) && Global::isShowAdd == true && Global::isShowTab == false){
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), Global::hWndMain, InputMoney);
	}
	if (buttonTypeAN != NULL && buttonTypeAN->IsEnter(x, y) && Global::isShowAdd == true && Global::isShowTab == false){
		Global::TempChiTieu.type = AN;
		InvalidateRect(Global::hWndMain, NULL, false);
		return;
	}
	if (buttonTypeCHO != NULL && buttonTypeCHO->IsEnter(x, y) && Global::isShowAdd == true && Global::isShowTab == false){
		Global::TempChiTieu.type = CHO;
		InvalidateRect(Global::hWndMain, NULL, false);
		return;
	}
	if (buttonTypeDICHUYEN != NULL && buttonTypeDICHUYEN->IsEnter(x, y) && Global::isShowAdd == true && Global::isShowTab == false){
		Global::TempChiTieu.type = DICHUYEN;
		InvalidateRect(Global::hWndMain, NULL, false);
		return;
	}
	if (buttonTypeDICHVU != NULL && buttonTypeDICHVU->IsEnter(x, y) && Global::isShowAdd == true && Global::isShowTab == false){
		Global::TempChiTieu.type = DICHVU;
		InvalidateRect(Global::hWndMain, NULL, false);
		return;
	}
	if (buttonTypeKHOANTHUKHAC != NULL && buttonTypeKHOANTHUKHAC->IsEnter(x, y) && Global::isShowAdd == true && Global::isShowTab == false){
		Global::TempChiTieu.type = KHOANTHUKHAC;
		InvalidateRect(Global::hWndMain, NULL, false);
		return;
	}
	if (buttonTypeLUONG != NULL && buttonTypeLUONG->IsEnter(x, y) && Global::isShowAdd == true && Global::isShowTab == false){
		Global::TempChiTieu.type = LUONG;
		InvalidateRect(Global::hWndMain, NULL, false);
		return;
	}
	if (buttonTypeNHA != NULL && buttonTypeNHA->IsEnter(x, y) && Global::isShowAdd == true && Global::isShowTab == false){
		Global::TempChiTieu.type = NHA;
		InvalidateRect(Global::hWndMain, NULL, false);
		return;
	}
	if (buttonEditNote != NULL && buttonEditNote->IsEnter(x, y) && Global::isShowAdd == true && Global::isShowTab == false){
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), Global::hWndMain, InputNote);
	}
	if (Global::isShowTab == false && y >= 150 && Global::isShowAdd == false && !Global::isShowDraw){
		int posy = 10;//170
		for (int i = Global::listData.size() - 1; i >= 0; i--){
			for (int j = Global::listData[i].listChiTieu.size() - 1; j >= 0; --j){
				int nPos = (Global::listData[i].listChiTieu.size() - 1) - j;
				if (y >= posy + 40 + 70 * nPos - Global::yPosItem + 150 && y <= posy + 40 + 70 * nPos + 60 - Global::yPosItem + 150){
					TCHAR date[20]; // where you put result
					_stprintf(date, TEXT("Item %d, %d"), i, j);
					Global::indexManager = i;
					Global::indexItem = j;
					Global::isShowItem = true;
					Global::isShowAdd = true;
					// Set Temp
					_tcscpy(Global::TempChiTieu.chuthich, Global::listData[i].listChiTieu[j].chuthich);
					Global::TempChiTieu.tien = Global::listData[i].listChiTieu[j].tien;
					Global::TempChiTieu.type = Global::listData[i].listChiTieu[j].type;
					//Make buffer
					if (!BitBlt(Global::bufferApp, 0, 0, width,
						height, Global::hdcBuffer, 0, 0, SRCCOPY)){
						MessageBox(hwnd, L"", L"", 0);
					}
					InvalidateRect(Global::hWndMain, NULL, false);
					//MessageBox(hwnd, date, 0, 0);
					return;
				}
			}
			posy += 40 + 70 * Global::listData[i].listChiTieu.size();
		}
	}
}

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags){
	int width = Global::sizeMain.cx;
	int height = Global::sizeMain.cy;
	Global::isShowType = false;
	Global::mouse_x = x;
	Global::mouse_y = y;
	if (Global::isShowDraw){
		if (posDraw == width){
			int x1 = 100;
			int y1 = 0;
			int x2 = x - (width / 2);
			int y2 = y - (120 + 100);
			int dot = x1*x2 + y1*y2;       // dot product between[x1, y1] and[x2, y2]
			float mau = sqrt(x1*x1 + y1*y1) * sqrt(x2*x2 + y2*y2);
			int det = x1*y2 - y1*x2;	   // determinant
			REAL angle = acos(dot / mau) * 180 / 3.14159265358979f;///atan2(det, dot);  // atan2(y, x) or atan2(sin, cos)
			if (y2 < 0) angle = 360 - angle;
			if (sqrt(x2*x2 + y2*y2) <= 100){
				REAL DoHienTai = 0;
				REAL DoVe = 0;
				if (Global::ShowType == 0){
					//Sum AN
					DoVe = REAL(SumAn) / SumChi * 360;
					if (angle >= DoHienTai && angle <= DoVe){
						typeShow = AN;
						Global::isShowType = true;
					}
					DoHienTai += DoVe;
					//Sum Cho
					DoVe = REAL(SumCho) / SumChi * 360;
					if (angle >= DoHienTai && angle <= DoHienTai + DoVe){
						typeShow = CHO;
						Global::isShowType = true;
					}
					DoHienTai += DoVe;
					//Sum Di Chuyen
					DoVe = REAL(SumDiChuyen) / SumChi * 360;
					if (angle >= DoHienTai && angle <= DoHienTai + DoVe){
						typeShow = DICHUYEN;
						Global::isShowType = true;
					}
					DoHienTai += DoVe;
					//Sum Dich Vu
					DoVe = REAL(SumDichVu) / SumChi * 360;
					if (angle >= DoHienTai && angle <= DoHienTai + DoVe){
						typeShow = DICHVU;
						Global::isShowType = true;
					}
					DoHienTai += DoVe;
					//Sum Nha
					DoVe = REAL(SumNha) / SumChi * 360;
					if (angle >= DoHienTai && angle <= DoHienTai + DoVe){
						typeShow = NHA;
						Global::isShowType = true;
					}
				}
				else if (Global::ShowType == 1){
					DoVe = REAL(SumLuong) / SumThu * 360;
					if (angle >= DoHienTai && angle <= DoHienTai + DoVe){
						typeShow = LUONG;
						Global::isShowType = true;
					}
					DoHienTai += DoVe;
					DoVe = REAL(SumKhoanThuKhac) / SumChi * 360;
					if (angle >= DoHienTai && angle <= DoHienTai + DoVe){
						typeShow = KHOANTHUKHAC;
						Global::isShowType = true;
					}
				}
				else{
					DoVe = REAL(SumThu) / (SumThu + SumChi) * 360;
					if (angle >= DoHienTai && angle <= DoHienTai + DoVe){
						typeShow = THU;
						Global::isShowType = true;
					}
					DoHienTai += DoVe;
					DoVe = REAL(SumChi) / (SumThu + SumChi) * 360;
					if (angle >= DoHienTai && angle <= DoHienTai +  DoVe){
						typeShow = CHI;
						Global::isShowType = true;
					}
				}
			}
		}
	}

	/*if (button1 != NULL && button1->IsEnter(x, y) && isShowTab == true && pos == width - 180){
		button1->MoseEnter = true;
		}
		else{
		button1->MoseEnter = true;
		}*/
	if (button1 != NULL){
		button1->OnMove(x, y);
	}
	if (button2 != NULL){
		button2->OnMove(x, y);
	}
	if (button3 != NULL){
		button3->OnMove(x, y);
	}
	if (button4 != NULL){
		button4->OnMove(x, y);
	}
	if (Global::buttonLuu != NULL){
		Global::buttonLuu->OnMove(x, y);
	}
	InvalidateRect(Global::hWndMain, NULL, false);
}


void DrawTabHome(){
	Graphics grBuffer(Global::hdcBuffer);
	int width = Global::sizeMain.cx;
	int height = Global::sizeMain.cy;
	//FFont fontTilte(L"Arial", Color(255, 231, 76, 60), 25, FontStyle::FontStyleBold);
	if (Global::isShowTab){
		//Vẽ background mờ đen
		SolidBrush backgroudBrush(Color(200, 127, 140, 141));
		grBuffer.FillRectangle(&backgroudBrush, 0, 0, width, height);
		//Vẽ khung tab
		SolidBrush blackBrush(Color(255, 236, 240, 241));
		grBuffer.FillRectangle(&blackBrush, 0, 0, posTab, height);
		//Vẽ Title
		FText::SetColor(Color(255, 231, 76, 60));
		FText::DrawTextFont(Global::hdcBuffer, PointF(0, 25), L"Công cụ", Global::font_Arial_25, LEFT);
		//Di chuyển
		if (posTab < width - 180){
			posTab += 20;
			InvalidateRect(Global::hWndMain, NULL, false);
		}
		//vẽ Line
		Pen pen(Color(255, 149, 165, 166), 2.0);
		grBuffer.DrawLine(&pen, Point(posTab - (width - 180), 50), Point(posTab, 50));
		//Button
		//FFont font(L"Arial", Color(255, 44, 62, 80), 15, FontStyle::FontStyleBold);
		//1
		if (button1 == NULL){
			RECT rect = { posTab - (width - 180), 52, posTab, 102 };
			button1 = new FButton(L"Thống kê chi", Global::font_Arial_15, rect, LEFT, Color(255, 0, 76, 60));
		}
		if (button1->MoseEnter){
			button1->color = Color(255, 189, 195, 199);
		}
		else{
			button1->color = Color(255, 236, 240, 241);
		}
		button1->SetPosition(posTab - (width - 180), 52);
		button1->colorText = Color(255, 44, 62, 80);
		button1->Draw(Global::hdcBuffer);
		//2
		if (button2 == NULL){
			RECT rect = { posTab - (width - 180), 103, posTab, 153 };
			button2 = new FButton(L"Thống kê thu", Global::font_Arial_15, rect, LEFT, Color(255, 0, 76, 60));
		}
		if (button2->MoseEnter){
			button2->color = Color(255, 189, 195, 199);
		}
		else{
			button2->color = Color(255, 236, 240, 241);
		}
		button2->SetPosition(posTab - (width - 180), 103);
		button2->colorText = Color(255, 44, 62, 80);
		button2->Draw(Global::hdcBuffer);
		//3
		if (button3 == NULL){
			RECT rect = { posTab - (width - 180), 154, posTab, 204 };
			button3 = new FButton(L"Thống kê thu chi", Global::font_Arial_15, rect, LEFT, Color(255, 0, 76, 60));
		}
		if (button3->MoseEnter){
			button3->color = Color(255, 189, 195, 199);
		}
		else{
			button3->color = Color(255, 236, 240, 241);
		}
		button3->SetPosition(posTab - (width - 180), 154);
		button3->colorText = Color(255, 44, 62, 80);
		button3->Draw(Global::hdcBuffer);
		//4
		if (button4 == NULL){
			RECT rect = { posTab - (width - 180), 205, posTab, 255 };
			button4 = new FButton(L"Xuất file excel", Global::font_Arial_15, rect, LEFT, Color(255, 0, 76, 60));
		}
		if (button4->MoseEnter){
			button4->color = Color(255, 189, 195, 199);
		}
		else{
			button4->color = Color(255, 236, 240, 241);
		}
		button4->SetPosition(posTab - (width - 180), 205);
		button4->colorText = Color(255, 44, 62, 80);
		button4->Draw(Global::hdcBuffer);
	}
	else{
		SolidBrush blackBrush(Color(255, 236, 240, 241));
		grBuffer.FillRectangle(&blackBrush, 0, 0, posTab, height);
		if (posTab > 0){
			posTab -= 20;
			InvalidateRect(Global::hWndMain, NULL, false);
		}
	}
}

void OnMouseWheel(HWND hwnd, int xPos, int yPos, int zDelta, UINT fwKeys){
	int sizeHeight = 0;
	for (int i = Global::listData.size() - 1; i >= 0; i--){
		sizeHeight += 40 + 70 * Global::listData[i].listChiTieu.size();
	}
	if (Global::yPosItem - zDelta <= 0){
		Global::yPosItem = 0;
	}
	else{
		if (sizeHeight - (Global::yPosItem - zDelta) >= 300)
			Global::yPosItem -= zDelta;
	}

	InvalidateRect(Global::hWndMain, NULL, false);
}



void MakeListItem(vector<DataManager> list){
	int width = Global::sizeMain.cx;
	int height = Global::sizeMain.cy;
	//Tính toán độ cao
	int sizeHeight = 100;
	for (int i = Global::listData.size() - 1; i >= 0; i--){
		sizeHeight += 40 + 70 * Global::listData[i].listChiTieu.size();
	}
	if (Global::bufferItem != NULL){
		DeleteDC(Global::bufferItem);
	}
	Global::bufferItem = MakeHDC(Global::sizeMain.cx, sizeHeight + 500);

	Graphics grBuffer(Global::bufferItem);
	//Tạo background
	SolidBrush backgroudBrush(Color(255, 189, 195, 199));
	//
	grBuffer.FillRectangle(&backgroudBrush, 0, 0, width, sizeHeight + 400);
	int posy = 10;//170
	// Set tổng thu và chi
	SumThu = 0;
	SumChi = 0;
	SumAn = 0;
	SumDiChuyen = 0;
	SumNha = 0;
	SumCho = 0;
	SumDichVu = 0;
	SumLuong = 0;
	SumKhoanThuKhac = 0;
	for (int i = Global::listData.size() - 1; i >= 0; i--)
	{
		SolidBrush backgroudItem(Color(255, 236, 240, 241));
		grBuffer.FillRectangle(&backgroudItem, 0, posy, width, 40 + 70 * Global::listData[i].listChiTieu.size() - 10);
		//Line
		Pen pen(Color(255, 149, 165, 166), 1.5);
		grBuffer.DrawLine(&pen, Point(0, posy + 40), Point(width, posy + 40));
		//Font
		//FFont fontHeader(L"Arial", Color(255, 44, 62, 80), 20, FontStyle::FontStyleBold);
		//Make day
		TCHAR day[3]; // where you put result
		_stprintf(day, TEXT("%02d"), Global::listData[i].date.day);
		FText::SetColor(Color(255, 44, 62, 80));
		FText::DrawTextFont(Global::bufferItem, PointF(10, posy + 22), day, Global::font_Arial_20, LEFT);
		//Make thu
		//fontHeader.size = 9;
		FText::DrawTextFont(Global::bufferItem, PointF(50, posy + 12), Global::Thu[Global::listData[i].date.thu], Global::font_Arial_10, LEFT);
		//Make date
		//fontHeader.color = Color(190, 44, 62, 80);
		TCHAR date[20]; // where you put result
		_stprintf(date, TEXT("tháng %d, %d"), Global::listData[i].date.month, Global::listData[i].date.year);
		FText::SetColor(Color(190, 44, 62, 80));
		FText::DrawTextFont(Global::bufferItem, PointF(50, posy + 27), date, Global::font_Arial_10, LEFT);
		//Draw tien
		TCHAR* strMoneySum = Global::listData[i].getMoney();
		FText::SetColor(Color(255, 44, 62, 80));
		FText::DrawTextFont(Global::bufferItem, PointF(width - 50, posy + 20), strMoneySum, Global::font_Arial_12, RIGHT);
		delete[] strMoneySum;
		for (int j = Global::listData[i].listChiTieu.size() - 1; j >= 0; --j){
			TypeChiTieu type = Global::listData[i].listChiTieu[j].type;
			if (type == LUONG || type == KHOANTHUKHAC){
				SumThu += Global::listData[i].listChiTieu[j].tien;
			}
			else{
				SumChi += Global::listData[i].listChiTieu[j].tien;
			}

			if (type == TypeChiTieu::AN){
				SumAn += Global::listData[i].listChiTieu[j].tien;
			}
			else if (type == TypeChiTieu::CHO){
				SumCho += Global::listData[i].listChiTieu[j].tien;
			}
			else if (type == TypeChiTieu::DICHUYEN){
				SumDiChuyen += Global::listData[i].listChiTieu[j].tien;
			}
			else if (type == TypeChiTieu::DICHVU){
				SumDichVu += Global::listData[i].listChiTieu[j].tien;
			}
			else if (type == TypeChiTieu::KHOANTHUKHAC){
				SumKhoanThuKhac += Global::listData[i].listChiTieu[j].tien;
			}
			else if (type == TypeChiTieu::LUONG){
				SumLuong += Global::listData[i].listChiTieu[j].tien;
			}
			else if (type == TypeChiTieu::NHA){
				SumNha += Global::listData[i].listChiTieu[j].tien;
			}
			int nPos = (Global::listData[i].listChiTieu.size() - 1) - j;
			Image image(Global::listData[i].listChiTieu[j].getImage());
			grBuffer.DrawImage(&image, 15, posy + 55 + 70 * nPos, 32, 32);

			//fontHeader.size = 11;
			FText::SetColor(Color(255, 44, 62, 80));
			FText::DrawTextFont(Global::bufferItem, PointF(60, posy + 60 + 70 * nPos), Global::listData[i].listChiTieu[j].getStringType(), Global::font_Arial_12, LEFT);
			//fontHeader.style = FontStyle::FontStyleRegular;
			FText::SetColor(Color(200, 44, 62, 80));
			FText::DrawTextFont(Global::bufferItem, PointF(60, posy + 80 + 70 * nPos), Global::listData[i].listChiTieu[j].chuthich, Global::font_Arial_10, LEFT);
			//fontHeader.size = 11;
			//fontHeader.style = FontStyle::FontStyleBold;
			TCHAR* strMoney = Global::listData[i].listChiTieu[j].getMoney();
			FText::SetColor(Global::listData[i].listChiTieu[j].getColor());
			FText::DrawTextFont(Global::bufferItem, PointF(width - 50, posy + 60 + 70 * nPos), strMoney, Global::font_Arial_12, RIGHT);
			delete[] strMoney;
		}
		posy += 40 + 70 * Global::listData[i].listChiTieu.size();
	}
}

void DrawMain(){

	Graphics grBuffer(Global::hdcBuffer);
	/*Vẽ backgroud trắng*/
	SolidBrush backgroudBrush(Color(255, 189, 195, 199));
	grBuffer.FillRectangle(&backgroudBrush, 0, 0, Global::sizeMain.cx, Global::sizeMain.cy);
	/*Vẽ thanh tiêu đề*/

	SolidBrush blackBrush(Color(255, 46, 204, 113));
	grBuffer.FillRectangle(&blackBrush, 0, 0, Global::sizeMain.cx, 50);

	/*Vẽ tiêu đề*/
	//FText::DrawTextFont(Global::hdcBuffer, PointF(width / 2, 25), L"Money Love", font, CENTER);
	{
		grBuffer.SetSmoothingMode(SmoothingModeAntiAlias);
		grBuffer.SetInterpolationMode(InterpolationModeHighQualityBicubic);
		FontFamily fontFamily(L"Arial");
		StringFormat strformat;
		strformat.SetAlignment(StringAlignmentCenter);
		strformat.SetLineAlignment(StringAlignmentCenter);
		wchar_t pszbuf[] = L"Money Love";
		GraphicsPath path;
		path.AddString(pszbuf, wcslen(pszbuf), &fontFamily,
			FontStyleRegular, 30, Gdiplus::Point(Global::sizeMain.cx / 2, 25), &strformat);
		for (int i = 1; i < 6; ++i)
		{
			Pen pen(Color(100, 231, 76, 60), i);
			pen.SetLineJoin(LineJoinRound);
			grBuffer.DrawPath(&pen, &path);
		}
		SolidBrush brush(Color(255, 255, 255));
		grBuffer.FillPath(&brush, &path);
		grBuffer.SetSmoothingMode(SmoothingModeDefault);
		grBuffer.SetInterpolationMode(InterpolationModeDefault);
	}

	/*Vẽ Hearder*/
		{
			SolidBrush backgroudHeader(Color(255, 236, 240, 241));
			grBuffer.FillRectangle(&backgroudHeader, 0, 50, Global::sizeMain.cx, 100);
			//Title
			FText::SetColor(Color(255, 44, 62, 80));
			FText::DrawTextFont(Global::hdcBuffer, PointF(15, 75), L"Tổng tiền thu:", Global::font_Arial_12, LEFT);
			FText::DrawTextFont(Global::hdcBuffer, PointF(15, 100), L"Tổng tiền chi:", Global::font_Arial_12, LEFT);
			//Tien thu
			FText::SetColor(Color(255, 52, 152, 219));
			TCHAR *Thu = MakeMoney(SumThu);
			FText::DrawTextFont(Global::hdcBuffer, PointF(Global::sizeMain.cx - 50, 75), Thu, Global::font_Arial_12, RIGHT);
			delete[]Thu;
			//Tien chi
			FText::SetColor(Color(255, 231, 76, 60));
			TCHAR *Chi = MakeMoney(SumChi);
			FText::DrawTextFont(Global::hdcBuffer, PointF(Global::sizeMain.cx - 50, 100), Chi, Global::font_Arial_12, RIGHT);
			delete[]Chi;
			//Line
			Pen pen(Color(255, 149, 165, 166), 1.5);
			grBuffer.DrawLine(&pen, Point(Global::sizeMain.cx - 200, 115), Point(Global::sizeMain.cx, 115));
			//Tong
			FText::SetColor(Color(255, 44, 62, 80));
			TCHAR *Sum = MakeMoney(SumThu - SumChi);
			FText::DrawTextFont(Global::hdcBuffer, PointF(Global::sizeMain.cx - 50, 135), Sum, Global::font_Arial_15, RIGHT);
			delete[]Sum;
			//Line
			grBuffer.DrawLine(&pen, Point(0, 149), Point(Global::sizeMain.cx, 149));

		}
		/*Vẽ Item*/
		if (!BitBlt(Global::hdcBuffer, 0, 150, Global::sizeMain.cx,
			Global::sizeMain.cy, Global::bufferItem, 0, Global::yPosItem, SRCCOPY)){
			MessageBox(Global::hWndMain, L"", L"", 0);
		}
}


void DrawAdd(){
	Graphics grBuffer(Global::hdcBuffer);
	SolidBrush backgroudHeader(Color(255, 236, 240, 241));
	grBuffer.FillRectangle(&backgroudHeader, posAdd, 0, Global::sizeMain.cx, Global::sizeMain.cy);
	//Vẽ Khung Title
	SolidBrush titleBrush(Color(255, 46, 204, 113));
	grBuffer.FillRectangle(&titleBrush, posAdd, 0, Global::sizeMain.cx, 50);
	//FFont fontHeader(L"Arial", Color(255, 44, 62, 80), 15, FontStyle::FontStyleBold);
	FText::SetColor(Color(255, 44, 62, 80));
	//Set title
	if (!Global::isShowItem)
		FText::DrawTextFont(Global::hdcBuffer, PointF(posAdd + 50, 25), L"Thêm giao dịch", Global::font_Arial_15, LEFT);
	else
		FText::DrawTextFont(Global::hdcBuffer, PointF(posAdd + 50, 25), L"Xem giao dịch", Global::font_Arial_15, LEFT);

	if (Global::buttonClose == NULL){
		Global::buttonClose = new FButtonImage(L"Data/close.png", 0, 8);
	}
	Global::buttonClose->SetPosition(posAdd, 8);
	Global::buttonClose->Draw(Global::hdcBuffer);
	{
		SolidBrush backgroudHeader(Color(255, 255, 255, 255));
		grBuffer.FillRectangle(&backgroudHeader, posAdd, 50, Global::sizeMain.cx, 300);
	}
	//1
	if (Global::buttonLuu == NULL){
		RECT rect = { 0, 0, 50, 50 };
		Global::buttonLuu = new FButton(L"Lưu", Global::font_Arial_15, rect, CENTER, Color(255, 0, 76, 60));
	}
	if (Global::buttonLuu->MoseEnter){
		Global::buttonLuu->color = Color(255, 39, 174, 96);
	}
	else{
		Global::buttonLuu->color = Color(255, 46, 204, 113);
	}
	Global::buttonLuu->SetPosition(Global::sizeMain.cx - 70, 0);
	Global::buttonLuu->colorText = Color(255, 44, 62, 80);
	Global::buttonLuu->Draw(Global::hdcBuffer);

	//FFont fontMoney(L"Arial", Temp.getColor(), 20, FontStyle::FontStyleBold);
	TCHAR* strMoney = Global::TempChiTieu.getMoney();
	FText::SetColor(Global::TempChiTieu.getColor());
	FText::DrawTextFont(Global::hdcBuffer, PointF(posAdd + 65, 85), strMoney, Global::font_Arial_20, LEFT);
	delete[] strMoney;

	if (buttonEditMoney == NULL){
		buttonEditMoney = new FButtonImage(L"Data/edit.png", 0, 8);
	}
	buttonEditMoney->SetPosition(posAdd + Global::sizeMain.cx - 50, 65);
	buttonEditMoney->Draw(Global::hdcBuffer);

	Pen pen(Color(150, 149, 165, 166), 2);
	grBuffer.DrawLine(&pen, Point(posAdd, 115), Point(posAdd + Global::sizeMain.cx, 115));


	Image image(Global::TempChiTieu.getImage());
	grBuffer.DrawImage(&image, posAdd + 20, 125, 32, 32);

	FText::SetColor(Color(255, 52, 73, 94));
	FText::DrawTextFont(Global::hdcBuffer, PointF(posAdd + 25 + 40, 125 + 16), Global::TempChiTieu.getStringType(), Global::font_Arial_15, LEFT);

	if (buttonEditNote == NULL){
		buttonEditNote = new FButtonImage(L"Data/edit.png", 0, 8);
	}
	buttonEditNote->SetPosition(posAdd + Global::sizeMain.cx - 50, 170);
	buttonEditNote->Draw(Global::hdcBuffer);

	grBuffer.DrawLine(&pen, Point(posAdd + 65, 160), Point(posAdd + Global::sizeMain.cx, 160));


	grBuffer.DrawImage(&Global::imageNote, posAdd + 20, 170, 32, 32);

	FText::DrawTextBox(Global::hdcBuffer, RectF(posAdd + 25 + 40, 180, Global::sizeMain.cx - 65 - 50, 150), Global::TempChiTieu.chuthich, Global::font_Arial_15, LEFT);

	grBuffer.DrawLine(&pen, Point(posAdd + 65, 330), Point(posAdd + Global::sizeMain.cx, 330));

	FText::SetColor(Color(255, 52, 152, 219));
	FText::DrawTextFont(Global::hdcBuffer, PointF(posAdd + 25, Global::sizeMain.cy - 270), L"Chi tiêu:", Global::font_Arial_15, LEFT);


	FText::SetColor(Color(255, 231, 76, 60));
	FText::DrawTextFont(Global::hdcBuffer, PointF(posAdd + 25, Global::sizeMain.cy - 170), L"Thu nhập:", Global::font_Arial_15, LEFT);


	//
	if (buttonTypeAN == NULL){
		buttonTypeAN = new FButtonImage(L"Data/restaurant.png", posAdd + 25 + 15, Global::sizeMain.cy - 250);
	}
	buttonTypeAN->SetPosition(posAdd + 25 + 15, Global::sizeMain.cy - 250);
	buttonTypeAN->Draw(Global::hdcBuffer);
	if (Global::TempChiTieu.type == AN){
		Pen backgroudHeader(Color(255, 46, 204, 113), 2);
		grBuffer.DrawRectangle(&backgroudHeader, posAdd + 25 + 15 - 2, Global::sizeMain.cy - 250 - 2, 32 + 4, 32 + 4);
	}
	//
	if (buttonTypeDICHUYEN == NULL){
		buttonTypeDICHUYEN = new FButtonImage(L"Data/taxi.png", posAdd + 25 + 15 + 45, Global::sizeMain.cy - 250);
	}
	buttonTypeDICHUYEN->SetPosition(posAdd + 25 + 15 + 45, Global::sizeMain.cy - 250);
	buttonTypeDICHUYEN->Draw(Global::hdcBuffer);

	if (Global::TempChiTieu.type == DICHUYEN){
		Pen backgroudHeader(Color(255, 46, 204, 113), 2);
		grBuffer.DrawRectangle(&backgroudHeader, posAdd + 25 + 15 + 45 - 2, Global::sizeMain.cy - 250 - 2, 32 + 4, 32 + 4);
	}
	//
	if (buttonTypeNHA == NULL){
		buttonTypeNHA = new FButtonImage(L"Data/house.png", posAdd + 25 + 15 + 45 * 2, Global::sizeMain.cy - 250);
	}
	buttonTypeNHA->SetPosition(posAdd + 25 + 15 + 45 * 2, Global::sizeMain.cy - 250);
	buttonTypeNHA->Draw(Global::hdcBuffer);

	if (Global::TempChiTieu.type == NHA){
		Pen backgroudHeader(Color(255, 46, 204, 113), 2);
		grBuffer.DrawRectangle(&backgroudHeader, posAdd + 25 + 15 + 45 * 2 - 2, Global::sizeMain.cy - 250 - 2, 32 + 4, 32 + 4);
	}
	//
	if (buttonTypeCHO == NULL){
		buttonTypeCHO = new FButtonImage(L"Data/cart.png", posAdd + 25 + 15 + 45 * 3, Global::sizeMain.cy - 250);
	}
	buttonTypeCHO->SetPosition(posAdd + 25 + 15 + 45 * 3, Global::sizeMain.cy - 250);
	buttonTypeCHO->Draw(Global::hdcBuffer);
	if (Global::TempChiTieu.type == CHO){
		Pen backgroudHeader(Color(255, 46, 204, 113), 2);
		grBuffer.DrawRectangle(&backgroudHeader, posAdd + 25 + 15 + 45 * 3 - 2, Global::sizeMain.cy - 250 - 2, 32 + 4, 32 + 4);
	}
	//
	if (buttonTypeDICHVU == NULL){
		buttonTypeDICHVU = new FButtonImage(L"Data/navigation.png", posAdd + 25 + 15 + 45 * 4, Global::sizeMain.cy - 250);
	}
	buttonTypeDICHVU->SetPosition(posAdd + 25 + 15 + 45 * 4, Global::sizeMain.cy - 250);
	buttonTypeDICHVU->Draw(Global::hdcBuffer);
	if (Global::TempChiTieu.type == DICHVU){
		Pen backgroudHeader(Color(255, 46, 204, 113), 2);
		grBuffer.DrawRectangle(&backgroudHeader, posAdd + 25 + 15 + 45 * 4 - 2, Global::sizeMain.cy - 250 - 2, 32 + 4, 32 + 4);
	}
	//
	if (buttonTypeLUONG == NULL){
		buttonTypeLUONG = new FButtonImage(L"Data/money-bag.png", posAdd + 25 + 15, Global::sizeMain.cy - 150);
	}
	buttonTypeLUONG->SetPosition(posAdd + 25 + 15, Global::sizeMain.cy - 150);
	buttonTypeLUONG->Draw(Global::hdcBuffer);
	if (Global::TempChiTieu.type == LUONG){
		Pen backgroudHeader(Color(255, 46, 204, 113), 2);
		grBuffer.DrawRectangle(&backgroudHeader, posAdd + 25 + 15 - 2, Global::sizeMain.cy - 150 - 2, 32 + 4, 32 + 4);
	}
	//
	if (buttonTypeKHOANTHUKHAC == NULL){
		buttonTypeKHOANTHUKHAC = new FButtonImage(L"Data/coin.png", posAdd + 25 + 15 + 45, Global::sizeMain.cy - 150);
	}
	buttonTypeKHOANTHUKHAC->SetPosition(posAdd + 25 + 15 + 45, Global::sizeMain.cy - 150);
	buttonTypeKHOANTHUKHAC->Draw(Global::hdcBuffer);

	if (Global::TempChiTieu.type == KHOANTHUKHAC){
		Pen backgroudHeader(Color(255, 46, 204, 113), 2);
		grBuffer.DrawRectangle(&backgroudHeader, posAdd + 25 + 15 + 45 - 2, Global::sizeMain.cy - 150 - 2, 32 + 4, 32 + 4);
	}
	//

	if (posAdd > 0){
		posAdd -= 20;
		InvalidateRect(Global::hWndMain, NULL, false);
	}
}

void SaveData(){
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	std::basic_ofstream<wchar_t> ofs("data.his");
	ofs.imbue(loc);
	ofs << (wchar_t)0xfeff;// BOM
	int length = Global::listData.size();
	if (length > 0){
		ofs << length << endl;
		for (int i = 0; i < length; ++i){
			ofs << Global::listData[i].date.thu << endl;
			ofs << Global::listData[i].date.day << endl;
			ofs << Global::listData[i].date.month << endl;
			ofs << Global::listData[i].date.year << endl;
			int lengthData = Global::listData[i].listChiTieu.size();
			ofs << lengthData << endl;
			for (int j = 0; j < lengthData; ++j){
				ofs << Global::listData[i].listChiTieu[j].tien << endl;
				ofs << Global::listData[i].listChiTieu[j].type << endl;
				ofs << Global::listData[i].listChiTieu[j].chuthich << endl;
			}
		}
	}
	ofs.close();
}

void GetData(){
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	std::basic_ifstream<wchar_t> ifs("data.his");
	if (ifs.is_open() == false) return;
	ifs.imbue(loc);
	int length;
	ifs >> length;
	for (int i = 0; i < length; ++i){
		DataManager data;
		ifs >> data.date.thu;
		ifs >> data.date.day;
		ifs >> data.date.month;
		ifs >> data.date.year;
		int lengthData;
		ifs >> lengthData;
		for (int j = 0; j < lengthData; ++j){
			ChiTieu chitieu;
			ifs >> chitieu.tien;
			int type;
			ifs >> type;
			chitieu.type = (TypeChiTieu)type;
			ifs.getline(chitieu.chuthich, 200); // Get \n
			ifs.getline(chitieu.chuthich, 200);
			//ifs >> chitieu.chuthich;
			data.listChiTieu.push_back(chitieu);
		}
		Global::listData.push_back(data);
	}
	ifs.close();
}

void SaveCSV(){
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	std::basic_ofstream<wchar_t> ofs("data.csv");
	ofs.imbue(loc);
	ofs << (wchar_t)0xfeff;// BOM
	int length = Global::listData.size();
	ofs << L"Tổng tiền thu:," << SumThu << endl;
	ofs << L"Tổng tiền chi:," << SumChi << endl;
	ofs << L"Tổng số dư:," << SumThu - SumChi << endl;
	ofs << L"\"Thứ,Ngày/tháng/năm\",Loại,Tiền,Ghi chú\n";
	if (length > 0){
		for (int i = 0; i < length; ++i){
			int lengthData = Global::listData[i].listChiTieu.size();
			for (int j = 0; j < lengthData; ++j){
				ofs << "\"" << Global::Thu[Global::listData[i].date.thu] << "," << Global::listData[i].date.day << "/" << Global::listData[i].date.month << "/" << Global::listData[i].date.year << "\", ";
				ofs << Global::listData[i].listChiTieu[j].getStringType() << ",";
				ofs << "\"" << Global::listData[i].listChiTieu[j].getMoney() << "\",";
				ofs << "\"" << Global::listData[i].listChiTieu[j].chuthich << "\"" << endl;
			}
		}
	}
	ofs.close();
	ShellExecute(NULL, L"open", L"data.csv", NULL, NULL, SW_SHOWDEFAULT);
}


float lengthdir_x(float Length, float Direction) {
	return (std::cos(-Direction*(3.14159265 / 180)) * Length);
}
float lengthdir_y(float Length, float Direction) {
	return (std::sin(-Direction*(3.14159265 / 180)) * Length);
}


void DrawPie(TypeChiTieu type, int Sum, int SumTong, REAL &DoHienTai, TCHAR* path, Graphics &grBuffer, Color color){
	int chartY = 120;
	REAL DoVe = REAL(Sum) / SumTong * 360;
	SolidBrush brush(color); // Xanh đen
	//Set size
	if (Sum > 0){
		if (DoHienTai + DoVe > posCirle){
			grBuffer.FillPie(&brush, (posDraw - 200) / 2, chartY, 200, 200, DoHienTai, posCirle - DoHienTai);
			DoHienTai = posCirle;
		}
		else{
			REAL x = 0;
			REAL y = 0;
			int Move = 0;
			if (typeShow == type && Global::isShowType){
				x = lengthdir_x(10, (360 - (DoVe / 2 + DoHienTai)));
				y = lengthdir_y(10, (360 - (DoVe / 2 + DoHienTai)));
				Move = 10;
			}
			REAL x_1 = lengthdir_x(140 + Move, (360 - (DoVe / 2 + DoHienTai))) + posDraw / 2;
			REAL y_1 = lengthdir_y(140 + Move, (360 - (DoVe / 2 + DoHienTai))) + 100 + chartY;
			REAL x_2 = lengthdir_x(100 + Move, (360 - (DoVe / 2 + DoHienTai))) + posDraw / 2;
			REAL y_2 = lengthdir_y(100 + Move, (360 - (DoVe / 2 + DoHienTai))) + 100 + chartY;
			Pen pen(Color(255, 0, 0, 0), 1.5);
			grBuffer.DrawLine(&pen, PointF(x_2, y_2), PointF(x_1, y_1));
			Image image(path);
			grBuffer.DrawImage(&image, x_1 - 16, y_1 - 16, (REAL)32, (REAL)32);

			TCHAR per[20]; // where you put result
			_stprintf(per, TEXT("%.2f\%%"), Sum * 100.0 / SumTong);

			if (x_1 >= Global::sizeMain.cx / 2){
				FText::DrawTextFont(Global::hdcBuffer, PointF(x_1 + 20, y_1 + 8), per, Global::font_Arial_12, LEFT);
			}
			else{
				FText::DrawTextFont(Global::hdcBuffer, PointF(x_1 - 20, y_1 + 8), per, Global::font_Arial_12, RIGHT);
			}

			grBuffer.FillPie(&brush, (posDraw - 200) / 2 + x, chartY + y, (REAL)200, (REAL)200, DoHienTai, DoVe);
			DoHienTai += DoVe;
		}
	}
}