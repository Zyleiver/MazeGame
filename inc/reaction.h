#ifndef REACTION_H_
#define REACTION_H_

// ����¼����жϴ�����ʲô�¼�
void myMouseEvent(int x, int y, int button, int event);

// ���������¼�����ݼ�
void myKeyboardEvent(int key, int event);

// ʱ���¼�
void myTimerEvent(int timerID);

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
