#include "MyHeader.h"

/*��������*/
int map_length;											//��ͼ���
int page_stage=MAIN_PAGE;								//ҳ��״̬ 1��MAIN_PAGE 2��GAME_PAGE 3��END_PAGE
int Map[100][100];										//��ͼ���飬���Ϊ100*100

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
