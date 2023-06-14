#ifndef INITGAME_H_
#define INITGAME_H_

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
	PromptNextStep,	  // ��ʾ��һ����Alt+p��
	ShowShortestPath, // ��ʾ���·����Alt+r��
	ShowAllPath,	  // ��ʾȫ��·����Alt+a��
	LeftShiftPath,	  // ��ʾȫ��·��ʱ����
	RightShiftPath,	  // ��ʾȫ��·��ʱ����
	Instruction,	  // ʹ��˵��
	About_Game,		  // ����
	Back			  // ����
};


//��ʼ����Ϸ���ݣ�����״̬������״̬��
void InitGame(void);

//�л���Ŀ��ҳ��
void ShiftPageTo(int PageTo);
#endif
