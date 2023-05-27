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

//����״̬��MAIN_PAGEΪ��ҳ�棬GAME_PAGEΪ��Ϸ����
typedef enum{
	MAIN_PAGE = 0,
	GAME_PAGE,
}page_stage;

//��ť״̬��OFFΪ�ɿ���ONΪ����
typedef enum{
	OFF = 0 ,
	ON,
}button_stage;

//��ť�ṹ��nameΪ��ť���֣�stageΪ��ť״̬,x��yΪ��ť���ϽǺ������꣬lx��lyΪ��ťx��y���򳤶�,visibleΪ��ť�Ƿ�ɼ�
struct button{
	char* name;
	int stage;
    int x;
    int y;
    int lx;
    int ly;
    int visible;
};

//����Ԫ�أ�ROADΪ·��WALLΪǽ��COINΪ���
typedef enum{
    START,
    ROAD ,
    WALL,
    COIN,
    END,
}element;

//��ʾ��һ���ķ���
typedef enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
}nextway;

//��ɫ�ṹ��hpΪ����ֵ��xΪ�����꣬yΪ������
struct Charactor
{
    int hp;
    int x;
    int y;
};

//�յ�·����x��yΪ�ڵ�����꣬nextΪ��һ���ڵ�ĵ�ַ
struct Way{
    int x;
    int y;
    struct Way* next;
};

//��ͼ��16*16
int Map[16][16]={ROAD};




#endif

