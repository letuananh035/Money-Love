#pragma once
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
using namespace Gdiplus;
enum FormatText{
	LEFT,
	CENTER,
	RIGHT
};
#ifndef FFONT_H
#define UIDLL __declspec(dllexport)
#else
#define UIDLL __declspec(dllimport)
#endif
class UIDLL FFont
{
	Font* font;
public:
	//int size;
	//TCHAR* font;
	//FontStyle style;
	FFont(TCHAR* font, int size);
	FFont(TCHAR* font, int size, FontStyle style);
	Font* getFont();
	FFont();
	~FFont();
};

