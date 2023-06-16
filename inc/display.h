#ifndef DISPLAY_H_
#define DISPLAY_H_

extern int xscale, yscale;
extern int CoinGet;

void display(void);


void DrawCoin(double mx, double my, double l, int InMap);    //»­½ð±Ò
void DrawMonster(double mx,double my,double l);      //»­¹ÖÊÞ
void DrawRole(double mx,double my,double l);         //»­½ÇÉ«
#endif
