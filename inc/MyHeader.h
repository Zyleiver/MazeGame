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

// ������ء�������������������������������������������������������������������������������������������������

#define WINDOWS_WIDTH (double)300
#define WINDOWS_HEIGHT (double)200

// ����״̬
enum Page_Stage
{
    MAIN_PAGE = 0, // ������
    CHOSEMAP_PAGE, // ѡ�����ɵ�ͼ��ʽ����
    GAME_PAGE,     // ��Ϸ����
    EDIT_PAGE,     // ��ͼ�༭����
    MENU_PAGE,     // �˵�����
    TOOL_PAGE,     // ���߽���
    END_PAGE,      // ��������
};

extern int page_stage;

// ��ť��ء���������������������������������������������������������������������������������������������������

// ��ť�ṹ��nameΪ��ť���֣�stageΪ��ť״̬,x��yΪ��ť���ϽǺ������꣬lx��lyΪ��ťx��y���򳤶�,visibleΪ��ť�Ƿ�ɼ�
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
// ��ť״̬��Button_UPΪ�ɿ���Button_DOWNΪ����
enum Button_stage
{
    Button_UP = 0, // �ɿ�
    Button_DOWN,   // ����
};

// ��ť����״̬��VISIBLEΪ���ӣ�UNVISIBLEΪ������
enum Button_visible
{
    UNVISIBLE = 0, // ������
    VISIBLE,       // ����
};

// ��ť
/*
// ���еİ�ť
extern Button StartNewGame;     // ��ʼ����Ϸ
extern Button BuildMapAuto;     // �Զ����ɵ�ͼ
extern Button BuildMapManu;     // �ֶ����ɵ�ͼ
extern Button EmptyMap;         // �հ׵�ͼ
extern Button UseTemp;          // ʹ��ģ��
extern Button TempFromSys;      // ϵͳģ��
extern Button TempFromFile;     // �浵ģ��
extern Button ReadFiles;        // ��ȡ�浵
extern Button ExitGame;         // �˳�
extern Button Menu;             // �˵�
extern Button CrtNewMap;        // �½���ͼ��Ctrl+c��
extern Button OpenMap;          // �򿪵�ͼ��Ctrl+o��
extern Button SaveGame;         // �浵��Ctrl+s��
extern Button SaveAsTemp;       // ����Ϊģ�壨Ctrl+m��
extern Button BackToMP;         // ���������棨Ctrl+b��
extern Button Tools;            // ����
extern Button EditMap;          // �༭��ͼ��Ctrl+e��
extern Button PromptNextStep;   // ��ʾ��һ����Shift+p��
extern Button ShowShortestPath; // ��ʾ���·����Shift+r��
extern Button ShowAllPath;      // ��ʾȫ��·����Shift+a��
extern Button LeftShiftPath;    // ��ʾȫ��·��ʱ����
extern Button RightShiftPath;   // ��ʾȫ��·��ʱ����
extern Button Instruction;      // ʹ��˵��
extern Button About_Game;       // ����
extern Button Back;             // ����
*/
// Ԫ����ء�����������������������������������������������������������������������������������������������������������

// ����Ԫ�أ�ROADΪ·��WALLΪǽ��COINΪ���
typedef enum
{
    ROAD,
    START,
    WALL,
    COIN,
    END,
} element;

// ��ɫ�ṹ��hpΪ����ֵ��xΪ�����꣬yΪ������
typedef struct
{
    int hp;
    int x;
    int y;
} Charactor;

// ���н�ɫ
Charactor MajorRole; // ����
Charactor Monster[3];   // ����

// ·����ء���������������������������������������������������������������������������������������������������������������

// ��ͼ��� MAP_LENGTH=map_length
#define MAP_LENGTH map_length
extern int map_xlength;
extern int map_ylength;
extern int Map[100][100];

// ��ʾ��һ���ķ���
enum nextway
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
};

// �յ�·����x��yΪ�ڵ�����꣬nextΪ��һ���ڵ�ĵ�ַ
struct Way
{
    int x;
    int y;
    struct Way *next;
};
typedef struct Way *pWay; // ·���ṹ��ָ��

// ȫ��·��������
struct AllWay
{
    pWay ThisWay;
    struct AllWay *Next;
};
typedef struct AllWay *Pallway; // ·�������ָ��
extern Pallway AllHead;

#endif
