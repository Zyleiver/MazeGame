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

// ������ء�������������������������������������������������������������������������������������������������

#define WINDOWS_WIDTH (double)100
#define WINDOWS_HEIGHT (double)100

// ����״̬��MAIN_PAGEΪ��ҳ�棬GAME_PAGEΪ��Ϸ����
typedef enum
{
    MAIN_PAGE = 0,
    GAME_PAGE,
} page_stage;

// ��ť��ء���������������������������������������������������������������������������������������������������

// ��ť�ṹ��nameΪ��ť���֣�stageΪ��ť״̬,x��yΪ��ť���ϽǺ������꣬lx��lyΪ��ťx��y���򳤶�,visibleΪ��ť�Ƿ�ɼ�
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

// ��ť״̬��OFFΪ�ɿ���ONΪ����
typedef enum
{
    OFF = 0,
    ON,
} Button_stage;

// ���еİ�ť
Button StartNewGame;     // ��ʼ����Ϸ
Button BuildMapAuto;     // �Զ����ɵ�ͼ
Button BuildMapManu;     // �ֶ����ɵ�ͼ
Button EmptyMap;         // �հ׵�ͼ
Button UseTemp;          // ʹ��ģ��
Button TempFromSys;      // ϵͳģ��
Button TempFromFile;     // �浵ģ��
Button ReadFiles;        // ��ȡ�浵
Button ExitGame;         // �˳�
Button Menu;             // �˵�
Button CrtNewMap;        // �½���ͼ��Ctrl+c��
Button OpenMap;          // �򿪵�ͼ��Ctrl+o��
Button SaveGame;         // �浵��Ctrl+s��
Button SaveAsTemp;       // ����Ϊģ�壨Ctrl+m��
Button BackToMP;         // ���������棨Ctrl+b��
Button Tools;            // ����
Button EditMap;          // �༭��ͼ��Ctrl+e��
Button PromptNextStep;   // ��ʾ��һ����Alt+p��
Button ShowShortestPath; // ��ʾ���·����Alt+r��
Button ShowAllPath;      // ��ʾȫ��·����Alt+a��
Button LeftShiftPath;    // ��ʾȫ��·��ʱ����
Button RightShiftPath;   // ��ʾȫ��·��ʱ����
Button Instruction;      // ʹ��˵��
Button About_Game;       // ����

// Ԫ����ء�����������������������������������������������������������������������������������������������������������

// ����Ԫ�أ�ROADΪ·��WALLΪǽ��COINΪ���
typedef enum
{
    START,
    ROAD,
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
Charactor Monster;   // ����

// ·����ء���������������������������������������������������������������������������������������������������������������

// ��ʾ��һ���ķ���
typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
} nextway;

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

#endif