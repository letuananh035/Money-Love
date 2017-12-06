#include "FButton.h"


FButton::FButton()
{
	text = NULL;
}


FButton::~FButton()
{
}


bool FButton::IsEnter(int x_, int y_){
	return x_ >= x && x_ <= x + cx  && y_ >= y && y_ <= y + cy;
}

FButton::FButton(TCHAR* text, FFont* font, RECT rect, FormatText format, Color color){
	this->text = text;
	this->font = font;
	this->x = rect.left;
	this->y = rect.top;
	this->cx = rect.right - rect.left;
	this->cy = rect.bottom - rect.top;
	this->format = format;
	this->color = color;
}

void FButton::Draw(HDC hdc){
	Graphics graphics(hdc);
	Font* fontText = this->font->getFont(); //fontText(&FontFamily(this->font.font), this->font.size);
	SolidBrush brushText(this->colorText);
	SolidBrush BrushBG(this->color);
	//Draw BG
	graphics.FillRectangle(&BrushBG, this->x, this->y, this->cx, this->cy);
	//Draw text
	if (this->format == CENTER){
		StringFormat stringFormat = new StringFormat();
		stringFormat.SetAlignment(StringAlignment::StringAlignmentCenter);
		stringFormat.SetLineAlignment(StringAlignment::StringAlignmentCenter);
		Status st = graphics.DrawString(text, -1, fontText, PointF(this->x + this->cx / 2, this->y + this->cy / 2), &stringFormat, &brushText);
	}
	else{
		StringFormat stringFormat = new StringFormat();
		stringFormat.SetLineAlignment(StringAlignment::StringAlignmentCenter);
		Status st = graphics.DrawString(text, -1, fontText, PointF(this->x, this->y + this->cy / 2), &stringFormat, &brushText);
	}
}

void FButton::SetPosition(int x, int y){
	this->x = x;
	this->y = y;
}

void FButton::OnMove(int x_, int y_){
	if (this->IsEnter(x_, y_)){
		this->MoseEnter = true;
	}
	else{
		this->MoseEnter = false;
	}
}