#ifndef DISPLAY_H_
#define DISPLAY_H_

extern int xscale, yscale;
extern int CoinGet;
extern char mapx[4];
extern char mapy[4];
extern char monsnum[5];
extern char coinnum[5];

void display(void);


void DrawCoin(double mx, double my, double l, int InMap);    //画金币
void DrawMonster(double mx,double my,double l);      //画怪兽
void DrawRole(double mx,double my,double l);         //画角色

void DrawPreCoin(double mx, double my, double l); 	 //画预览金币 
void DrawPreGoal(double mx,double my,double l);		 //画预览终点 
void DrawPreRole(double mx,double my,double l);		 //画预览角色 
void drawhat(double mx,double my,double l);          //画下一步的帽子
#endif
