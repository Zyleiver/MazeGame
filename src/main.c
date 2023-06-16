#include "MyHeader.h"
void myTimerEvent(int timerID);
/*对象声明*/
int map_xlength;											//地图规格
int map_ylength;
int page_stage;								//页面状态 1、MAIN_PAGE 2、GAME_PAGE 3、END_PAGE
int Map[100][100] = {0};										//地图数组，最大为100*100

void Main()
{
	SetWindowTitle("MazeGame");
	SetWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
	page_stage=MAIN_PAGE;
	InitConsole(); 
	InitGraphics();
	InitGame();
    
	
	iscracked=200;
	xscale=48;
	yscale=48;
	MZX=xscale*2-1;
	MZY=yscale*2-1;
	monsternum=100;
	registerKeyboardEvent(myKeyboardEvent);
	registerMouseEvent(myMouseEvent);
	registerTimerEvent(myTimerEvent);
	registerCharEvent(mycharEvent);
	startTimer(MonsterTimer,500);
	startTimer(FlashTimer,10);
	startTimer(GameTouchTimer,20);
}


