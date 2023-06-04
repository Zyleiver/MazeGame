#include "MyHeader.h"

/*对象声明*/
int map_length;											//地图规格
int page_stage=MAIN_PAGE;								//页面状态 1、MAIN_PAGE 2、GAME_PAGE 3、END_PAGE
int Map[100][100];										//地图数组，最大为100*100

void Main()
{
	SetWindowTitle("MazeGame");
	SetWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
	InitGraphics();
	InitGame();
	display();
	registerKeyboardEvent(myKeyboardEvent);
	registerMouseEvent(myMouseEvent);
	registerTimerEvent(myTimerEvent);
}
