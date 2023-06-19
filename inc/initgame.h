#ifndef INITGAME_H_
#define INITGAME_H_

#define ButtonNum 30
// ���еİ�ť
enum BUTTON
{
	StartNewGame,	  // ��ʼ����Ϸ
	BuildMapAuto,	  // �Զ����ɵ�ͼ
	BuildMapManu,	  // �ֶ����ɵ�ͼ
	ReadFiles,		  // ��ȡ�浵
	ExitGame,		  // �˳�
	Menu,			  // �˵�
	CrtNewMap,		  // �½���ͼ��Ctrl+c��
	OpenMap,		  // �򿪵�ͼ��Ctrl+x��
	SaveGame,		  // �����ͼ��Ctrl+v��
	BackToMP,		  // ���������棨Ctrl+q��
	Tools,			  // ����
	PromptNextStep,	  // ��ʾ��һ����Shift+p��
	ShowShortestPath, // ��ʾ���·����Shift+r��
	ShowAllPath,	  // ��ʾȫ��·����Shift+m��
	Instruction,	  // ��Ϸ˵��
	About_Game,		  // ����
	Back,			  // ����
	PutWall,		  //����ǽ
	PutRole, 		  //�������
	PutGoal,		  //�����յ�
	PutCoin, 		  //���ý��
	Erase, 			  //��Ƥ
	Complete, 		  //��ɱ༭
	Cancel,			  //�˳��༭
	LeftShiftPath,	  // ��ʾȫ��·��ʱ����
	RightShiftPath	  // ��ʾȫ��·��ʱ����
};

extern Button ButtonEnum[ButtonNum];

void InitGame(void);//��ʼ����Ϸ���ݣ�����״̬������״̬��
void ShiftPageTo(int PageTo);//�л���Ŀ��ҳ��
#endif
