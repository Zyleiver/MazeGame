#ifndef REACTION_H_
#define REACTION_H_

extern int ifctrl;
extern int ifshift;

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

//��ҳ�水ť�����¼�
void MainPageTell(double mouse_x, double mouse_y);

// ��Ϸ���水ť�����¼�
void GamePageTell(double mouse_x, double mouse_y);

//ѡ��ģʽ���水ť�����¼� 
void ChoseMapPageTell(double mouse_x,double mouse_y);

//�˵����水ť�����¼�
void MenuPageTell(double mouse_x, double mouse_y);

//���߽��水ť�����¼�
void ToolPageTell(double mouse_x,double mouse_y);

//�༭���水ť�¼�
void EditPageTell (double mouse_x,double mouse_y);

//ȫ����ť���ɼ�
void AllUnvisible(void);

// ��ɫ�����ƶ�
void Moveup(void);
// ��ɫ�����˶�
void Moveleft(void);
// ��ɫ�����˶�
void Moveright(void);
// ��ɫ�����˶�
void Movedown(void);
#endif
