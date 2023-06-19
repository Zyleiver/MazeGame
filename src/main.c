#include "MyHeader.h"

/*��������*/
int map_xlength; 			// ��ͼ���
int map_ylength;
int page_stage;			 	// ҳ��״̬
int Map[100][100] = {0}; 	// ��ͼ���飬���Ϊ100*100

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
