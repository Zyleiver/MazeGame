#include "MyHeader.h"


/*
Button StartNewGame;	 // ��ʼ����Ϸ
Button BuildMapAuto;	 // �Զ����ɵ�ͼ
Button BuildMapManu;	 // �ֶ����ɵ�ͼ




Button ReadFiles;		 // ��ȡ�浵
Button ExitGame;		 // �˳�
Button Menu;			 // �˵�
Button CrtNewMap;		 // �½���ͼ��Ctrl+c��
Button OpenMap;			 // �򿪵�ͼ��Ctrl+o��
Button SaveGame;		 // �浵��Ctrl+s��

Button BackToMP;		 // ���������棨Ctrl+b��
Button Tools;			 // ����
Button EditMap;			 // �༭��ͼ��Ctrl+e��
Button PromptNextStep;	 // ��ʾ��һ����Alt+p��
Button ShowShortestPath; // ��ʾ���·����Alt+r��
Button ShowAllPath;		 // ��ʾȫ��·����Alt+a��
Button LeftShiftPath;	 // ��ʾȫ��·��ʱ����
Button RightShiftPath;	 // ��ʾȫ��·��ʱ����
Button Instruction;		 // ʹ��˵��
Button About_Game;		 // ����
Button Back;			 // ����
*/

Button ButtonEnum[ButtonNum] = {
	{"��ʼ����Ϸ"				,Button_UP	,120,120,60,20	,UNVISIBLE}, 
	{"�Զ����ɵ�ͼ"				,Button_UP	,45,130,60,20	,UNVISIBLE},
	{"�ֶ����ɵ�ͼ"				,Button_UP	,45,60,60,20	,UNVISIBLE},
//	{"�հ׵�ͼ"					,Button_UP	,45,100,15,20	,UNVISIBLE},
//	{"ʹ��ģ��"					,Button_UP	,60,100,15,20	,UNVISIBLE},
//	{"ϵͳģ��"					,Button_UP	,75,100,15,20	,UNVISIBLE},
//	{"�浵ģ��"					,Button_UP	,90,100,15,20	,UNVISIBLE},
	{"��ȡ�浵"					,Button_UP	,120,90,60,20	,UNVISIBLE},
	{"�˳�"						,Button_UP	,120,60,60,20	,UNVISIBLE},
	{"�˵�"						,Button_UP	,0,185,20,15	,UNVISIBLE},
	{"�½���ͼ  Ctrl+c"					,Button_UP	,0,172,40,13	,UNVISIBLE},
	{"�򿪵�ͼ  Ctrl+o"					,Button_UP	,0,159,40,13	,UNVISIBLE},
	{"�浵  Ctrl+s"						,Button_UP	,0,146,40,13	,UNVISIBLE},
//	{"����Ϊģ��"				,Button_UP	,35,60,15,20	,UNVISIBLE},
	{"������ҳ��  Ctrl+b"		,Button_UP	,0,133,40,13	,UNVISIBLE},
	{"����"						,Button_UP	,20,185,20,15	,UNVISIBLE},
//	{"�༭��ͼ  Shift+e"		,Button_UP	,20,172,30,13	,UNVISIBLE},
	{"��ʾ��һ��  Shift+p"		,Button_UP	,0,172,40,13	,UNVISIBLE},
	{"��ʾ���·��  Shift+r"	,Button_UP	,0,159,40,13	,UNVISIBLE},
	{"��ʾȫ��·��  Shift+a"	,Button_UP	,0,146,40,13	,UNVISIBLE},
	{"<-"						,Button_UP	,20,20,15,15	,UNVISIBLE},
	{"->"						,Button_UP	,35,20,15,15	,UNVISIBLE},
	{"ʹ��˵��"					,Button_UP	,260,185,20,15	,VISIBLE},
	{"����"						,Button_UP	,280,185,20,15	,VISIBLE},
	{"����"						,Button_UP	,20,175,20,15	,UNVISIBLE},
	{"ǽ"						,Button_UP	,10,150,20,15	,UNVISIBLE},
	{"���"						,Button_UP	,10,130,20,15	,UNVISIBLE},
	{"�յ�"						,Button_UP	,10,110,20,15	,UNVISIBLE},
	{"���"						,Button_UP	,10,90,20,15	,UNVISIBLE},
	{"��Ƥ"						,Button_UP	,10,70,20,15	,UNVISIBLE},
	{"���"						,Button_UP	,10,50,20,15	,UNVISIBLE},
	{"�˳�"						,Button_UP	,10,30,20,15	,UNVISIBLE},
};
void InitGame(void)
{
	DefineColor("Light Light Gray", .86, .86, .86);
	DefineColor("Light Brown",.4,.23,.057);
	DefineColor("FaceColor",(double)238/(double)255,(double)210/(double)255,(double)189/(double)255);
	setTextBoxColors("Black","Black","Black","Blue",0);
	ShiftPageTo(MAIN_PAGE);

	return;
}


void ShiftPageTo(int PageTo)
{
	switch (PageTo)
	{
		case MAIN_PAGE:
			page_stage=MAIN_PAGE;
			AllUnvisible();
			ButtonEnum[StartNewGame].visible=VISIBLE;
			ButtonEnum[ReadFiles].visible=VISIBLE;
			ButtonEnum[ExitGame].visible=VISIBLE;

			break;

		case CHOSEMAP_PAGE:
			page_stage=CHOSEMAP_PAGE;
			AllUnvisible();
			ButtonEnum[BuildMapAuto].visible=VISIBLE;
			ButtonEnum[BuildMapManu].visible=VISIBLE;
			ButtonEnum[Back].visible=VISIBLE;
			break;

		case GAME_PAGE:
			page_stage=GAME_PAGE;
			AllUnvisible();
			ButtonEnum[Menu].visible=VISIBLE;
			ButtonEnum[Tools].visible=VISIBLE;
			if(ButtonEnum[ShowAllPath].stage==Button_DOWN){
				ButtonEnum[LeftShiftPath].visible=VISIBLE;
				ButtonEnum[RightShiftPath].visible=VISIBLE;
			}
			break;

		case EDIT_PAGE:
			page_stage=EDIT_PAGE;
			AllUnvisible();
			ButtonEnum[Menu].visible=VISIBLE;
			ButtonEnum[Tools].visible=VISIBLE;
			ButtonEnum[PutWall].visible=VISIBLE;
			ButtonEnum[PutRole].visible=VISIBLE;
			ButtonEnum[PutGoal].visible=VISIBLE;
			ButtonEnum[PutCoin].visible=VISIBLE;
			ButtonEnum[Erase].visible=VISIBLE;
			ButtonEnum[Complete].visible=VISIBLE;
			ButtonEnum[Cancel].visible=VISIBLE;


			break;

		case MENU_PAGE:
			page_stage=MENU_PAGE;
			AllUnvisible();
			ButtonEnum[Menu].visible=VISIBLE;
			ButtonEnum[Tools].visible=VISIBLE;
			ButtonEnum[CrtNewMap].visible=VISIBLE;
			ButtonEnum[OpenMap].visible=VISIBLE;
			ButtonEnum[SaveGame].visible=VISIBLE;
			ButtonEnum[BackToMP].visible=VISIBLE;
			if(ButtonEnum[ShowAllPath].stage==Button_DOWN)
			{
				ButtonEnum[LeftShiftPath].visible=VISIBLE;
				ButtonEnum[RightShiftPath].visible=VISIBLE;
			}
			break;

		case TOOL_PAGE:
			page_stage=TOOL_PAGE;
			AllUnvisible();
			ButtonEnum[Menu].visible=VISIBLE;
			ButtonEnum[Tools].visible=VISIBLE;
			ButtonEnum[PromptNextStep].visible=VISIBLE;
			ButtonEnum[ShowShortestPath].visible=VISIBLE;
			ButtonEnum[ShowAllPath].visible=VISIBLE;
			if(ButtonEnum[ShowAllPath].stage==Button_DOWN){
				ButtonEnum[LeftShiftPath].visible=VISIBLE;
				ButtonEnum[RightShiftPath].visible=VISIBLE;
			}
			break;

		case END_PAGE:
			page_stage=END_PAGE;
			break;
	}
	
	return;
}
