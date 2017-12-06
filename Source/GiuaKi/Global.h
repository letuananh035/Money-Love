#pragma once

#include <windowsX.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
#include <objidl.h>
#include <gdiplus.h>
#include <locale>
#include <fstream>
#include <codecvt>
#include <iomanip>
#include <Windows.h>
#include <Shellapi.h>
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "gdiplus.lib")
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
using namespace Gdiplus;
#include <vector>
using namespace std;
//
#include "FText.h"
#include "FButton.h"
#include "FButtonImage.h"
#include "DataManager.h"
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnMouseMove(HWND, int, int, UINT);
void OnLButtonUp(HWND, int, int, UINT);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnSize(HWND hwnd, UINT state, int cx, int cy);
void OnPaint(HWND);
LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm);
void OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos);
void OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos);
void OnMouseWheel(HWND hwnd, int xPos, int yPos, int zDelta, UINT fwKeys);


//
HDC GetParentHDC(HWND hWnd);
void DrawTabHome();
HDC MakeHDC(int width, int height);
void MakeListItem(vector<DataManager> list);
void DrawMain();
void DrawAdd();
void AddItem();
void SaveData();
void GetData();
void SaveCSV();
float lengthdir_x(float len, float dir);
float lengthdir_y(float len, float dir);

void DrawPie(TypeChiTieu type, int Sum, int SumTong, REAL &DoHienTai, TCHAR* path, Graphics &grBuffer, Color color);
namespace Global{
	SIZE sizeMain = { 480, 640 };
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	HWND hWndMain = NULL;
	HDC hdcBuffer = NULL;
	bool isShowTab = false;
	bool isShowAdd = false;
	bool isShowItem = false;
	bool isShowDraw = false;
	bool isShowType = false;
	int ShowType = 0;
	TCHAR* Thu[7] = { L"C.Nhật", L"Thứ 2", L"Thứ 3", L"Thứ 4", L"Thứ 5", L"Thứ 6", L"Thứ 7" };
	HDC bufferItem = NULL;
	FButtonImage *buttonHome = NULL;
	FButtonImage *buttonAdd = NULL;
	vector<DataManager> listData;
	Image imageNote(L"Data/note.png");
	FButtonImage* buttonClose = NULL;
	FButton* buttonLuu = NULL;
	FFont* font_Arial_30;
	FFont* font_Arial_12;
	FFont* font_Arial_15;
	FFont* font_Arial_20;
	FFont* font_Arial_25;
	FFont* font_Arial_10;
	HDC bufferApp; // buffer lưu lại màn hình 
	int yPosItem = 0;// Vị list list item
	ChiTieu TempChiTieu;
	int indexManager = -1;
	int indexItem = -1;
	int mouse_x = 0;
	int mouse_y = 0;
}

