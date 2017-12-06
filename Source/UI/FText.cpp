#include "FText.h"




void FText::SetColor(Color color){
	FText::color = color;
}

void FText::DrawTextFont(HDC hdc, PointF point, TCHAR* text, FFont* ffont, FormatText format){
	Graphics graphics(hdc);
	Font* fontText = ffont->getFont();
	SolidBrush brush(FText::color);
	if (format == CENTER){
		StringFormat stringFormat = new StringFormat();
		stringFormat.SetAlignment(StringAlignment::StringAlignmentCenter);
		stringFormat.SetLineAlignment(StringAlignment::StringAlignmentCenter);
		Status st = graphics.DrawString(text, -1, fontText, point, &stringFormat, &brush);
	}
	else if(format == LEFT){
		StringFormat stringFormat = new StringFormat();
		stringFormat.SetLineAlignment(StringAlignment::StringAlignmentCenter);
		stringFormat.SetAlignment(StringAlignment::StringAlignmentNear);
		Status st = graphics.DrawString(text, -1, fontText, point, &stringFormat, &brush);
	}
	else {
		StringFormat stringFormat = new StringFormat();
		stringFormat.SetLineAlignment(StringAlignment::StringAlignmentCenter);
		stringFormat.SetAlignment(StringAlignment::StringAlignmentFar);
		Status st = graphics.DrawString(text, -1, fontText, point, &stringFormat, &brush);
	}

}

void FText::DrawTextBox(HDC hdc, RectF rect, TCHAR* text, FFont* ffont, FormatText format){
	Graphics graphics(hdc);
	Font* fontText = ffont->getFont(); //fontText(&FontFamily(ffont.font), ffont.size, ffont.style);
	SolidBrush brush(FText::color);
	if (format == CENTER){
		StringFormat stringFormat = new StringFormat();
		stringFormat.SetAlignment(StringAlignment::StringAlignmentNear);
		stringFormat.SetLineAlignment(StringAlignment::StringAlignmentCenter);
		Status st = graphics.DrawString(text, -1, fontText, rect, &stringFormat, &brush);
	}
	else if (format == LEFT){
		StringFormat stringFormat = new StringFormat();
		stringFormat.SetLineAlignment(StringAlignment::StringAlignmentNear);
		stringFormat.SetAlignment(StringAlignment::StringAlignmentNear);
		Status st = graphics.DrawString(text, -1, fontText, rect, &stringFormat, &brush);
	}
	else {
		StringFormat stringFormat = new StringFormat();
		stringFormat.SetLineAlignment(StringAlignment::StringAlignmentNear);
		stringFormat.SetAlignment(StringAlignment::StringAlignmentFar);
		Status st = graphics.DrawString(text, -1, fontText, rect, &stringFormat, &brush);
	}
}

