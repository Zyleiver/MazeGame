#include "MyHeader.h"

//按钮定义
Button ButtonEnum[ButtonNum] = {
	{"开始新游戏"				,Button_UP	,20,100,100,20	,UNVISIBLE}, 
	{"自动生成地图"				,Button_UP	,45,130,60,20	,UNVISIBLE},
	{"手动生成地图"				,Button_UP	,45,60,60,20	,UNVISIBLE},
	{"读取存档"					,Button_UP	,120,90,60,20	,UNVISIBLE},
	{"退出"						,Button_UP	,120,60,60,20	,UNVISIBLE},
	{"菜单"						,Button_UP	,0,185,20,15	,UNVISIBLE},
	{"新建地图  Ctrl+c"			,Button_UP	,0,172,40,13	,UNVISIBLE},
	{"打开地图  Ctrl+x"			,Button_UP	,0,159,40,13	,UNVISIBLE},
	{"保存地图  Ctrl+v"			,Button_UP	,0,146,40,13	,UNVISIBLE},
	{"返回主页面  Ctrl+q"		,Button_UP	,0,133,40,13	,UNVISIBLE},
	{"工具"						,Button_UP	,20,185,20,15	,UNVISIBLE},
	{"提示下一步  Shift+p"		,Button_UP	,0,172,40,13	,UNVISIBLE},
	{"显示最短路径  Shift+r"	,Button_UP	,0,159,40,13	,UNVISIBLE},
	{"显示全部路径  Shift+m"	,Button_UP	,0,146,40,13	,UNVISIBLE},
	{"游戏说明"					,Button_UP	,260,185,20,15	,VISIBLE},
	{"关于"						,Button_UP	,280,185,20,15	,VISIBLE},
	{"回退"						,Button_UP	,20,175,20,15	,UNVISIBLE},
	{"墙"						,Button_UP	,10,150,20,15	,UNVISIBLE},
	{"起点"						,Button_UP	,10,130,20,15	,UNVISIBLE},
	{"终点"						,Button_UP	,10,110,20,15	,UNVISIBLE},
	{"金币"						,Button_UP	,10,90,20,15	,UNVISIBLE},
	{"橡皮"						,Button_UP	,10,70,20,15	,UNVISIBLE},
	{"完成"						,Button_UP	,10,50,20,15	,UNVISIBLE},
	{"退出"						,Button_UP	,10,30,20,15	,UNVISIBLE},
	{"<-"						,Button_UP	,20,20,15,15	,UNVISIBLE},
	{"->"						,Button_UP	,35,20,15,15	,UNVISIBLE},
};

//游戏初始化
void InitGame(void)
{
	DefineColor("Light Light Gray", .86, .86, .86);
	DefineColor("Light Brown",.4,.23,.057);
	DefineColor("FaceColor",(double)238/(double)255,(double)210/(double)255,(double)189/(double)255);
	DefineColor("Pakistan Green",0,(double)102/(double)255,0);
	DefineColor("SafeWayGreen",0,(double)180/(double)255,(double)80/(double)255);
	setTextBoxColors("Black","Black","Black","Blue",0);
	ShiftPageTo(MAIN_PAGE);

	return;
}

//切换界面，各界面状态设置
void ShiftPageTo(int PageTo)
{
	switch (PageTo)
	{
		case MAIN_PAGE://主界面
			page_stage=MAIN_PAGE;
			AllUnvisible();
			ButtonEnum[StartNewGame].visible=VISIBLE;
			ButtonEnum[ReadFiles].visible=VISIBLE;
			ButtonEnum[ExitGame].visible=VISIBLE;
			ButtonEnum[LeftShiftPath].visible=UNVISIBLE;
			ButtonEnum[RightShiftPath].visible=UNVISIBLE;

			break;

		case CHOSEMAP_PAGE://地图参数选择界面
			page_stage=CHOSEMAP_PAGE;
			AllUnvisible();
			ButtonEnum[BuildMapAuto].visible=VISIBLE;
			ButtonEnum[BuildMapManu].visible=VISIBLE;
			ButtonEnum[Back].visible=VISIBLE;
			ButtonEnum[LeftShiftPath].visible=UNVISIBLE;
			ButtonEnum[RightShiftPath].visible=UNVISIBLE;
			
			break;

		case GAME_PAGE://游戏界面
			page_stage=GAME_PAGE;
			AllUnvisible();
			ButtonEnum[Menu].visible=VISIBLE;
			ButtonEnum[Tools].visible=VISIBLE;

			break;

		case EDIT_PAGE://编辑界面
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
			ButtonEnum[LeftShiftPath].visible=UNVISIBLE;
			ButtonEnum[RightShiftPath].visible=UNVISIBLE;

			break;

		case MENU_PAGE://菜单界面
			page_stage=MENU_PAGE;
			AllUnvisible();
			ButtonEnum[Menu].visible=VISIBLE;
			ButtonEnum[Tools].visible=VISIBLE;
			ButtonEnum[CrtNewMap].visible=VISIBLE;
			ButtonEnum[OpenMap].visible=VISIBLE;
			ButtonEnum[SaveGame].visible=VISIBLE;
			ButtonEnum[BackToMP].visible=VISIBLE;
		
			break;

		case TOOL_PAGE://工具界面
			page_stage=TOOL_PAGE;
			AllUnvisible();
			ButtonEnum[Menu].visible=VISIBLE;
			ButtonEnum[Tools].visible=VISIBLE;
			ButtonEnum[PromptNextStep].visible=VISIBLE;
			ButtonEnum[ShowShortestPath].visible=VISIBLE;
			ButtonEnum[ShowAllPath].visible=VISIBLE;
			
			break;

		case END_PAGE://结束界面
			page_stage=END_PAGE;
			break;
			
		case INSTRUCT_PAGE://关于界面
			AllUnvisible();
			ButtonEnum[Back].visible=VISIBLE;
			page_stage=INSTRUCT_PAGE;
			break;
	}
	
	return;
}
