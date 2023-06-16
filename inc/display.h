#ifndef DISPLAY_H_
#define DISPLAY_H_

extern int xscale, yscale;
extern int CoinGet;
extern char mapx[4];
extern char mapy[4];
extern char monsnum[5];
extern char coinnum[5];

void display(void);


void DrawCoin(double mx, double my, double l, int InMap);    //»­½ð±Ò
void DrawMonster(double mx,double my,double l);      //»­¹ÖÊÞ
void DrawRole(double mx,double my,double l);         //»­½ÇÉ«
#endif
