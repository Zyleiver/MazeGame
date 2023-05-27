#ifndef CLUE_H_
#define CLUE_H_

//路径寻找，输入curx、cury（当前横纵坐标），将路径存在链表里，返回0为未找到，返回1为找到
int find_way(int curx,int cury);

//提示下一步,输入curx、cury（当前横纵坐标），返回下一步的方向
nextway next_move(int curx,int cury);

#endif
