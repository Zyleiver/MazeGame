#ifndef SETUP_H_
#define SETUP_H_

//��ʱ��������ƶ�ʱ�������ٶȣ�Ϊ1000 ms
#define MONSTERSPEED 1000 

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

//����һ��������µ�ͼ
void CreateNewMap(void);

//�ֶ�������ͼ/��ͼ�༭
void BuildMap(void);

//ʹ��ģ��
void UseTemplate(void);
//OpenTemp

//��Ϸ��ʼ����������ޡ���ҳ�ʼ����
void InitMap(void);

extern int Map[100][100];
#endif
