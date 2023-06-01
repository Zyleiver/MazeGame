#ifndef MYHEADER_H_
#define MYHEADER_H_

// inc from lib
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <file.h>
#include <stdlib.h>

// inc from teacher
#include "boolean.h"
#include "exception.h"
#include "extgraph.h"
#include "gcalloc.h"
#include "genlib.h"
#include "graphics.h"
#include "imgui.h"
#include "linkedlist.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"

// my own inc
#include "clue.h"
#include "display.h"
#include "file.h"
#include "reaction.h"
#include "setup.h"

//*************************setup**************************

// 界面相关—————————————————————————————————————————————————

#define WINDOWS_WIDTH (double)100
#define WINDOWS_HEIGHT (double)100

// 界面状态，MAIN_PAGE为主页面，GAME_PAGE为游戏界面
typedef enum
{
    MAIN_PAGE = 0,
    GAME_PAGE,
} page_stage;



// 按钮相关——————————————————————————————————————————————————

// 按钮结构，name为按钮名字，stage为按钮状态,x、y为按钮左上角横纵坐标，lx、ly为按钮x、y方向长度,visible为按钮是否可见
typedef struct
{
    char *name;
    int stage;
    int x;
    int y;
    int lx;
    int ly;
    int visible;
} Button;

// 按钮状态，OFF为松开，ON为按下
typedef enum
{
    OFF = 0,
    ON,
} Button_stage;

// 所有的按钮
Button StartNewGame;     // 开始新游戏
Button BuildMapAuto;     // 自动生成地图
Button BuildMapManu;     // 手动生成地图
Button EmptyMap;         // 空白地图
Button UseTemp;          // 使用模板
Button TempFromSys;      // 系统模板
Button TempFromFile;     // 存档模板
Button ReadFiles;        // 读取存档
Button ExitGame;         // 退出
Button Menu;             // 菜单
Button CrtNewMap;        // 新建地图（Ctrl+c）
Button OpenMap;          // 打开地图（Ctrl+o）
Button SaveGame;         // 存档（Ctrl+s）
Button SaveAsTemp;       // 保存为模板（Ctrl+m）
Button BackToMP;         // 返回主界面（Ctrl+b）
Button Tools;            // 工具
Button EditMap;          // 编辑地图（Ctrl+e）
Button PromptNextStep;   // 提示下一步（Alt+p）
Button ShowShortestPath; // 显示最短路径（Alt+r）
Button ShowAllPath;      // 显示全部路径（Alt+a）
Button LeftShiftPath;    // 显示全部路径时左切
Button RightShiftPath;   // 显示全部路径时右切
Button Instruction;      // 使用说明
Button About_Game;       // 关于

// 元素相关——————————————————————————————————————————————————————

// 方块元素，ROAD为路，WALL为墙，COIN为金币
typedef enum
{
    START,
    ROAD,
    WALL,
    COIN,
    END,
} element;

// 角色结构，hp为生命值，x为横坐标，y为纵坐标
typedef struct
{
    int hp;
    int x;
    int y;
} Charactor;

// 所有角色
Charactor MajorRole; // 主角
Charactor Monster;   // 怪兽

// 路线相关————————————————————————————————————————————————————————

// 提示下一步的方向
typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
} nextway;

// 终点路径，x、y为节点的坐标，next为下一个节点的地址
struct Way
{
    int x;
    int y;
    struct Way *next;
};
typedef struct Way *pWay; // 路径结构的指针

// 全部路径的链表
struct AllWay
{
    pWay ThisWay;
    struct AllWay *Next;
};
typedef struct AllWay *Pallway; // 路径链表的指针

#endif
