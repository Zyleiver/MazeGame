#ifndef CLUE_H_
#define CLUE_H_

extern Map[100][100];	//地图 

//****************************求最优解模块*********************************//
int find_way_shortest(int curx,int cury);

//****************************求全部解模块*********************************//
int find_way_all(int curx, int cury);

//****************************求下一步模块*********************************//
int next_move(void);

#endif
