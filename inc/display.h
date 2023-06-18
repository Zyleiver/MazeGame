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
void DrawGoal(double mx, double my, double l);		 //画终点 

void DrawPreCoin(double mx, double my, double l); 	 //画预览金币 
void DrawPreGoal(double mx,double my,double l);		 //画预览终点 
void DrawPreRole(double mx,double my,double l);		 //画预览角色 
void drawhat(double mx,double my,double l);          //画下一步的帽子

void DrawWayArrow (double mx,double my,double length,int stage);//画最短路径和全部路径的一格图像

void drawsway(void);//绘制最短路径
void drawaway(void);//绘制全部路径的一条
void drawbutton (int j);//画按钮
void drawpreimage(void);//画预览图

void draw_win_image(void);//画胜利界面
void draw_lose_image(void);//画失败界面


void draw_getdata_box(void);//绘制地图参数输入框
#endif
