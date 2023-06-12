#ifndef CLUE_H_
#define CLUE_H_

#define MZX 35
#define MZY 35

extern Map[100][100];

//最短路径寻找，输入curx、cury（当前横纵坐标），将路径存在链表里，返回0为未找到，返回1为找到
int find_way_shortest(int curx,int cury);

//所有路径寻找，返回0无解
int find_way_all(int curx, int cury);

//提示下一步,输入curx、cury（当前横纵坐标），返回下一步的方向，返回0无解
int next_move(void);

#endif
