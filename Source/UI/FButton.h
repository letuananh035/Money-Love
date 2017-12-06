#pragma once
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
using namespace Gdiplus;
#include "FFont.h"
#ifndef FBUTTON_H

#define UIDLL __declspec(dllexport)
#else
#define UIDLL __declspec(dllimport)
#endif
class UIDLL FButton
{
public:
	int x, y;
	int cx, cy;
	TCHAR* text;
	FFont* font;
	int size;
	FormatText format;
	Color color;
	Color colorText;
	bool MoseEnter;
	FButton(TCHAR* text, FFont* font, RECT rect, FormatText format, Color color);
	void SetPosition(int x, int y);
	void Draw(HDC hdc);
	FButton();
	~FButton();
	bool IsEnter(int x_, int y_);
	void OnMove(int x_, int y_);
};

