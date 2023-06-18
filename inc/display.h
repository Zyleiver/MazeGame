#ifndef DISPLAY_H_
#define DISPLAY_H_

extern int xscale, yscale;
extern int CoinGet;
extern char mapx[4];
extern char mapy[4];
extern char monsnum[5];
extern char coinnum[5];

void display(void);


void DrawCoin(double mx, double my, double l, int InMap);    //�����
void DrawMonster(double mx,double my,double l);      //������
void DrawRole(double mx,double my,double l);         //����ɫ
void DrawGoal(double mx, double my, double l);		 //���յ� 

void DrawPreCoin(double mx, double my, double l); 	 //��Ԥ����� 
void DrawPreGoal(double mx,double my,double l);		 //��Ԥ���յ� 
void DrawPreRole(double mx,double my,double l);		 //��Ԥ����ɫ 
void drawhat(double mx,double my,double l);          //����һ����ñ��

void DrawWayArrow (double mx,double my,double length,int stage);//�����·����ȫ��·����һ��ͼ��

void drawsway(void);//�������·��
void drawaway(void);//����ȫ��·����һ��
void drawbutton (int j);//����ť
void drawpreimage(void);//��Ԥ��ͼ

void draw_win_image(void);//��ʤ������
void draw_lose_image(void);//��ʧ�ܽ���


void draw_getdata_box(void);//���Ƶ�ͼ���������
#endif
