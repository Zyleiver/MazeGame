#ifndef SETUP_H_
#define SETUP_H_

extern int Map[100][100]; 	//��ͼ���� 
extern int MZX;				//��ͼ�㷨�����ܳ� 
extern int MZY;				//��ͼ�㷨�����ܳ� 

extern int coinNum;		//������� 
extern int monsternum;	//�������� 
extern int endtime;		//ʤ�����㶯������ 
extern int dietime;		//ʧ�����㶯������ 
extern int iscracked;	//��ײʱ����� 
extern int ender;		//�ж�ʤ������ʧ�� 
extern int bubuhat;		//�ɾ�ʹ�ñ��� 

extern double Xlength;  //Xlength=��ͼ�����ܳ�
extern double Ylength;  //Ylength=��ͼ�����ܳ�
extern double length;   //���Ӵ�С
extern double X0;       //��ͼ���½Ǻ�����
extern double Y0;       //��ͼ���½�������


//****************************�Զ������Թ�ģ��*********************************//

void CreateNewMap(void);	//�Զ����ɻ�ͼ����
void GameInit(void);		//��������Զ���ʼ������


//****************************�ֶ������Թ�ģ��*********************************//

void BuildMap(void);						//��ͼ��ͼ��ʼ��
void EditMap(int x, int y, int buttonusing);//�Թ��༭����


//****************************��Ϸ��̬����ģ��*********************************//

//ʱ��ص����� 
void myTimerEvent(int timerID); 
#endif
