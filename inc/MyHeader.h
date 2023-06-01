#ifndef MYHEADER_H_
#define MYHEADER_H_

//inc from lib
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<file.h>
#include<stdlib.h>

//inc from teacher
#include"boolean.h"
#include"exception.h"
#include"extgraph.h"
#include"gcalloc.h"
#include"genlib.h"
#include"graphics.h"
#include"imgui.h"
#include"linkedlist.h"
#include"random.h"
#include"simpio.h"
#include"strlib.h"

//my own inc
#include"clue.h"
#include"display.h"
#include"file.h"
#include"reaction.h"
#include"setup.h"

//setup

//界面状态，MAIN_PAGE为主页面，GAME_PAGE为游戏界面
typedef enum{
	MAIN_PAGE = 0,
	GAME_PAGE,
}page_stage;

//按钮状态，OFF为松开，ON为按下
typedef enum{
	OFF = 0 ,
	ON,
}button_stage;

//按钮结构，name为按钮名字，stage为按钮状态,x、y为按钮左上角横纵坐标，lx、ly为按钮x、y方向长度,visible为按钮是否可见
struct button{
	char* name;
	int stage;
    int x;
    int y;
    int lx;
    int ly;
    int visible;
};

//方块元素，ROAD为路，WALL为墙，COIN为金币
typedef enum{
    START,
    ROAD ,
    WALL,
    COIN,
    END,
}element;

//提示下一步的方向
typedef enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
}nextway;

//角色结构，hp为生命值，x为横坐标，y为纵坐标
struct Charactor
{
    int hp;
    int x;
    int y;
};

//终点路径，x、y为节点的坐标，next为下一个节点的地址
struct Way{
    int x;
    int y;
    struct Way* next;
};

//地图，16*16
int Map[16][16]={ROAD};




#endif

