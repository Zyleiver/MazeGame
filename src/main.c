#include<stdio.h>
#include"MyHeader.h"

void display()
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


void myMouseEvent (int x, int y, int button, int event)
{
	double mx = ScaleXInches(x);
	double my = ScaleYInches(y);
	switch (event)
	{
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON)
		{
			MovePen(mx,my);
			DrawArc(1,0,180);
		}
			
		display();
		break;
	}
	display();
}

void Main()
{
	SetWindowTitle("画些什么东西");
	InitGraphics();

	display();
	registerMouseEvent(myMouseEvent);
}
