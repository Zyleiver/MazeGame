#ifndef MYHEADER_H_
#define MYHEADER_H_

// inc from lib
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <file.h>
#include <stdlib.h>
#include <windows.h>
#include <stddef.h>

// inc from teacher
#include "boolean.h"
// #include "exception.h"
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
#include "initgame.h"

//*************************setup**************************

// 界面相关—————————————————————————————————————————————————

#define WINDOWS_WIDTH (double)300
#define WINDOWS_HEIGHT (double)200

// 界面状态
enum Page_Stage
{
    MAIN_PAGE = 0, // 主界面
    CHOSEMAP_PAGE, // 选择生成地图方式界面
    GAME_PAGE,     // 游戏界面
    EDIT_PAGE,     // 地图编辑界面
    MENU_PAGE,     // 菜单界面
    TOOL_PAGE,     // 工具界面
    END_PAGE,      // 结束界面
};

extern int page_stage;

// 按钮相关——————————————————————————————————————————————————

// 按钮结构，name为按钮名字，stage为按钮状态,x、y为按钮左上角横纵坐标，lx、ly为按钮x、y方向长度,visible为按钮是否可见
typedef struct
{
    char *name;
    int stage;
    double x;
    double y;
    double lx;
    double ly;
    int visible;
} Button;
typedef Button *PButton;

extern Button ButtonEnum[25];
// 按钮状态，Button_UP为松开，Button_DOWN为按下
enum Button_stage
{
    Button_UP = 0, // 松开
    Button_DOWN,   // 按下
};

// 按钮可视状态，VISIBLE为可视，UNVISIBLE为不可视
enum Button_visible
{
    UNVISIBLE = 0, // 不可视
    VISIBLE,       // 可视
};

// 按钮
/*
// 所有的按钮
extern Button StartNewGame;     // 开始新游戏
extern Button BuildMapAuto;     // 自动生成地图
extern Button BuildMapManu;     // 手动生成地图
extern Button EmptyMap;         // 空白地图
extern Button UseTemp;          // 使用模板
extern Button TempFromSys;      // 系统模板
extern Button TempFromFile;     // 存档模板
extern Button ReadFiles;        // 读取存档
extern Button ExitGame;         // 退出
extern Button Menu;             // 菜单
extern Button CrtNewMap;        // 新建地图（Ctrl+c）
extern Button OpenMap;          // 打开地图（Ctrl+o）
extern Button SaveGame;         // 存档（Ctrl+s）
extern Button SaveAsTemp;       // 保存为模板（Ctrl+m）
extern Button BackToMP;         // 返回主界面（Ctrl+b）
extern Button Tools;            // 工具
extern Button EditMap;          // 编辑地图（Ctrl+e）
extern Button PromptNextStep;   // 提示下一步（Shift+p）
extern Button ShowShortestPath; // 显示最短路径（Shift+r）
extern Button ShowAllPath;      // 显示全部路径（Shift+a）
extern Button LeftShiftPath;    // 显示全部路径时左切
extern Button RightShiftPath;   // 显示全部路径时右切
extern Button Instruction;      // 使用说明
extern Button About_Game;       // 关于
extern Button Back;             // 回退
*/
// 元素相关——————————————————————————————————————————————————————

// 方块元素，ROAD为路，WALL为墙，COIN为金币
typedef enum
{
    ROAD,
    START,
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
Charactor Monster[3];   // 怪兽

// 路线相关————————————————————————————————————————————————————————

// 地图规格 MAP_LENGTH=map_length
#define MAP_LENGTH map_length
extern int map_xlength;
extern int map_ylength;
extern int Map[100][100];

// 提示下一步的方向
enum nextway
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
};

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
extern Pallway AllHead;

#endif
