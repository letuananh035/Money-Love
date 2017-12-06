#include "FButtonImage.h"



FButtonImage::~FButtonImage()
{
}

FButtonImage::FButtonImage(){
	path = NULL;
}

FButtonImage::FButtonImage(TCHAR* path, int x, int y){
	this->path = path;
	this->x = x;
	this->y = y;
	image = new Image(this->path);
}

void FButtonImage::Draw(HDC hdc){
	Graphics graphics(hdc);
	RectF boundsRect;
	Unit unit;
	image->GetBounds(&boundsRect, &unit);
	graphics.DrawImage(image, this->x, this->y, int(boundsRect.Width), int(boundsRect.Height));
}
bool FButtonImage::IsEnter(int x_, int y_){
	Image image(this->path);
	RectF boundsRect;
	Unit unit;
	image.GetBounds(&boundsRect, &unit);
	return x_ >= this->x && x_ <= this->x + int(boundsRect.Width) && y_ >= this->y && y_ <= this->y + int(boundsRect.Height);
}

void FButtonImage::SetPosition(int x, int y){
	this->x = x;
	this->y = y;
}

void FButtonImage::OnMove(int x_, int y_){
	if (this->IsEnter(x_, y_)){
		this->MoseEnter = true;
	}
	else{
		this->MoseEnter = false;
	}
}