#ifndef DISPLAY_H_
#define DISPLAY_H_

extern int xscale, yscale;
extern int CoinGet;

void display(void);


void DrawCoin(double mx, double my, double l, int InMap);    //�����
void DrawMonster(double mx,double my,double l);      //������
void DrawRole(double mx,double my,double l);         //����ɫ
#endif
