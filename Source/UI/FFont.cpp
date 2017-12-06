#include "FFont.h"


FFont::FFont()
{
	//font = L"Arial";
	//size = 12;
	//this->color = Color(255, 0, 0, 0);
	//style = FontStyle::FontStyleRegular;
	this->font = NULL;
}


FFont::~FFont()
{
	delete font;
}


FFont::FFont(TCHAR* font, int size){
	//wcscpy(this->font, font);
	//this->size = size;
	//this->color = Color(255, 0, 0, 0);
	this->font = new Font(&FontFamily(font), size, FontStyle::FontStyleRegular);
}

FFont::FFont(TCHAR* font, int size, FontStyle style){
	//this->font = font;
	//this->size = size;
	//this->color = color;
	//this->style = style;
	this->font = new Font(&FontFamily(font), size, style);
}

Font* FFont::getFont(){
	return this->font;
}