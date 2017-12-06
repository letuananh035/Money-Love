#pragma once
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
using namespace Gdiplus;
#include "FFont.h"
#ifndef FTEXT_H
#define UIDLL __declspec(dllexport)
#else
#define UIDLL __declspec(dllimport)
#endif
class UIDLL FText{
	static Color color;
public:
	static void DrawTextFont(HDC hdc, PointF point, TCHAR* text, FFont* font, FormatText format = LEFT);
	static void DrawTextBox(HDC hdc, RectF rect, TCHAR* text, FFont* font, FormatText format = LEFT);
	static void SetColor(Color color);
};

Color FText::color = Color(255, 255, 255);