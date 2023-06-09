#include "MyHeader.h"

/*对象声明*/
int map_xlength; 			// 地图规格
int map_ylength;
int page_stage;			 	// 页面状态
int Map[100][100] = {0}; 	// 地图数组，最大为100*100

void Main()
{
	SetWindowTitle("MazeGame");
	SetWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
	InitGraphics();
	InitGame();

	registerKeyboardEvent(myKeyboardEvent);
	registerMouseEvent(myMouseEvent);
	registerTimerEvent(myTimerEvent);
	registerCharEvent(mycharEvent);
	startTimer(MonsterTimer, 500);
	startTimer(FlashTimer, 10);
	startTimer(GameTouchTimer, 20);
}
