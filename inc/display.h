#ifndef DISPLAY_H_
#define DISPLAY_H_

extern int xscale, yscale;
extern int CoinGet;

void display(void);

void DrawAvatar(double mx, double my, double length);       //����ɫ
void DrawCoin(double mx, double my, double l, int InMap);    //�����


#endif
