#ifndef REACTION_H_
#define REACTION_H_

extern int ifctrl;  // �Ƿ���Ctrl��
extern int ifshift; // �Ƿ���Shift��

extern int putting; // ���ڱ༭��ģ��
extern int ifpre;   // �Ƿ���ʾԤ��
extern int editx;   // �༭��ͼ��x����
extern int edity;   // �༭��ͼ��y����

extern int aboutstage; // �洢�򿪹���ǰ��ҳ��״̬

/***************************************************************************************/

void myMouseEvent(int x, int y, int button, int event); // ����¼����жϴ�����ʲô�¼�
void myKeyboardEvent(int key, int event);               // ���ư��������¼�����ݼ�
void mycharEvent(char ch);                              // ��ͨ���������¼�

/***************************************************************************************/

void MainPageTell(double mouse_x, double mouse_y);     // ��ҳ�水ť�����¼�
void GamePageTell(double mouse_x, double mouse_y);     // ��Ϸ���水ť�����¼�
void ChoseMapPageTell(double mouse_x, double mouse_y); // ѡ��ģʽ���水ť�����¼�
void MenuPageTell(double mouse_x, double mouse_y);     // �˵����水ť�����¼�
void ToolPageTell(double mouse_x, double mouse_y);     // ���߽��水ť�����¼�
void EditPageTell(double mouse_x, double mouse_y);     // �༭���水ť�¼�

/***************************************************************************************/

void TellLeftButtonDown(double mouse_x, double mouse_y); // �������¼�
void TellMouseMove(double mouse_x, double mouse_y);      // ����ƶ��¼�

/***************************************************************************************/

int TellRoad(double x, double y); // �жϱ༭ʱ�Ƿ��ո�λ��
int TellWall(double x, double y); // �жϱ༭ʱ�Ƿ��ǽ
void AllEditButtonUp(void);       // ���б༭��ť����

/***************************************************************************************/

void Moveup(void);    // ��ɫ�����ƶ�
void Moveleft(void);  // ��ɫ�����˶�
void Moveright(void); // ��ɫ�����˶�
void Movedown(void);  // ��ɫ�����˶�

/***************************************************************************************/

void AllUnvisible(void);                                    // ȫ����ť���ɼ�
void AllButtonUp(void);                                     // ȫ����ť�ɿ�
int TellPress(double mouse_x, double mouse_y, Button Butt); // �ж����޴�����ť
int TellOn(double mouse_x, double mouse_y, Button Butt);    // �ж�����Ƿ��ڰ�ť��
void setMouseCursorHand(void);                              // �������ָ
void setMouseCursorArrow(void);                             // ����ɼ�ͷ

/***************************************************************************************/

void build_map_auto(void); // ����Զ����ɵ�ͼ
void build_map_manu(void); // ����ֶ����ɵ�ͼ

#endif
