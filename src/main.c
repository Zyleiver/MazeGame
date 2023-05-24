#include"MyHeader.h"

void Main()
{
	SetWindowTitle("画些什么东西");
	InitGraphics();
	display();
	registerMouseEvent(myMouseEvent);
}
