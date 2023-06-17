#ifndef INITGAME_H_
#define INITGAME_H_

#define ButtonNum 30
// ���еİ�ť
enum BUTTON
{
	StartNewGame,	  // ��ʼ����Ϸ
	BuildMapAuto,	  // �Զ����ɵ�ͼ
	BuildMapManu,	  // �ֶ����ɵ�ͼ
//	EmptyMap,		  // �հ׵�ͼ
//	UseTemp,		  // ʹ��ģ��
//	TempFromSys,	  // ϵͳģ��
//	TempFromFile,	  // �浵ģ��
	ReadFiles,		  // ��ȡ�浵
	ExitGame,		  // �˳�
	Menu,			  // �˵�
	CrtNewMap,		  // �½���ͼ��Ctrl+c��
	OpenMap,		  // �򿪵�ͼ��Ctrl+o��
	SaveGame,		  // �浵��Ctrl+s��
//	SaveAsTemp,		  // ����Ϊģ�壨Ctrl+m��
	BackToMP,		  // ���������棨Ctrl+b��
	Tools,			  // ����
//	EditMap,		  // �༭��ͼ��Ctrl+e��
	PromptNextStep,	  // ��ʾ��һ����Shift+p��
	ShowShortestPath, // ��ʾ���·����Shift+r��
	ShowAllPath,	  // ��ʾȫ��·����Shift+q��

	Instruction,	  // ʹ��˵��
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


//��ʼ����Ϸ���ݣ�����״̬������״̬��
void InitGame(void);

//�л���Ŀ��ҳ��
void ShiftPageTo(int PageTo);
#endif
