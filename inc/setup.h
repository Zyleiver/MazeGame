#ifndef SETUP_H_
#define SETUP_H_

extern int coinNum;

extern int monsternum;
//��ʱ�����ͼΪ18*18���궨����ֵ���㹫ʽ
//�û������ͼ�ߴ�X��Y.  MZX = X*2 - 1; MZY = Y*2 - 1
//�����ζ�����ɵĵ�ͼ����ǽ����û�ָ���ĸ�����
//���Ի�ϸ������ż���еķ��񣨡�������ż���������еķ���|������������ǽ
//���ҽ�ż����ż���еķ��񻭳ɣ�.�������������λ����Զ����ǽ
//��������������һ����ROAD��COIN��START��END
//���������Ǻ͹����ƶ�ʱ����Ҫ�ڳ����Ͽ�Խ����ROAD������ǰ����ʾ���ǿ�Խ��һ��������
//���������巽���������û�Ҫ��
extern int MZX;
extern int MZY;


extern double Xlength;  //Xlength=��ͼ�����ܳ�
extern double Ylength;  //Ylength=��ͼ�����ܳ�
extern double length;   //���Ӵ�С
extern double X0;       //��ͼ���½Ǻ�����
extern double Y0;       //��ͼ���½�������

//����һ��������µ�ͼ
void CreateNewMap(void);

//�ֶ�������ͼ/��ͼ�༭
void BuildMap(void);

//������޳�ʼ�� 
void GameInit(void);

//��Ϸ��ʼ����������ޡ���ҳ�ʼ����
void InitMap(void);

//
void EditMap(int x, int y, int buttonusing);

extern int Map[100][100];

extern int iscracked;
#endif
