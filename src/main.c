#include"MyHeader.h"

void Main()
{
	SetWindowTitle("画些什么东西");
	InitGraphics();
	display();
	int a;
	registerMouseEvent(myMouseEvent);
}
