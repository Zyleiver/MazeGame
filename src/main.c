#include "MyHeader.h"

// 地图，16*16
int Map[16][16] = {ROAD};

void Main()
{
	SetWindowTitle("MazeGame");
	SetWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
	InitGraphics();
	display();
	registerKeyboardEvent(myKeyboardEvent);
	registerMouseEvent(myMouseEvent);
	registerTimerEvent(myTimerEvent);
}
