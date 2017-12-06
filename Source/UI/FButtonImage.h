#pragma once
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
using namespace Gdiplus;
#include "FFont.h"
#ifndef FBUTTONIMAGE_H
#define UIDLL __declspec(dllexport)
#else
#define UIDLL __declspec(dllimport)
#endif
class UIDLL FButtonImage
{
	int x, y;
	TCHAR* path;
	Image* image;
public:
	bool MoseEnter;
	FButtonImage(TCHAR* path,int x,int y);
	FButtonImage();
	~FButtonImage();
	void Draw(HDC hdc);
	bool IsEnter(int x_, int y_);
	void SetPosition(int x, int y);
	void OnMove(int x_, int y_);
};

