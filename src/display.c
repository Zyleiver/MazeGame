#include"MyHeader.h"

void display(void)
{
	double x = 1.0; 
	double y = 1.0; 
	double w = 1.0;
	double h = GetFontHeight() * 2; 
	// draw a square
	SetPenColor("Blue");
	drawLabel(x, y, "Blue Lable is Here");

	drawRectangle(x, y += h*1.2, w, h, 0);
	SetPenColor("Red"); drawBox(x, y += h*1.2, w, h, 0, "Box is here", 'C', "Green");
	SetPenColor("Red"); drawBox(x, y += h*1.2, w, h, 1, "Filled Box is here", 'L', "Green");
}
