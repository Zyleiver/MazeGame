#ifndef REACTION_H_
#define REACTION_H_

int ifctrl=0;
int ifshift=0;

// ����¼����жϴ�����ʲô�¼�
void myMouseEvent(int x, int y, int button, int event);

// ���ư��������¼�����ݼ�
void myKeyboardEvent(int key, int event);

//��ͨ���������¼�
void mycharEvent(char ch);

// �˳�����
void Exit(void);

// �½���ͼ
void CreateMap_ingame(void);

// �򿪵�ͼ
void OpenMap_ingame(void);

// �������˵�
void BackToMainPage(void);

// �ж���Ϸ�¼�������ǽ�����ޡ���ҡ��յ㣩
void TellStuff(void);

#endif
