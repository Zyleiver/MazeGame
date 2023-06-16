#include "MyHeader.h"


/*
Button StartNewGame;	 // 开始新游戏
Button BuildMapAuto;	 // 自动生成地图
Button BuildMapManu;	 // 手动生成地图




Button ReadFiles;		 // 读取存档
Button ExitGame;		 // 退出
Button Menu;			 // 菜单
Button CrtNewMap;		 // 新建地图（Ctrl+c）
Button OpenMap;			 // 打开地图（Ctrl+o）
Button SaveGame;		 // 存档（Ctrl+s）

Button BackToMP;		 // 返回主界面（Ctrl+b）
Button Tools;			 // 工具
Button EditMap;			 // 编辑地图（Ctrl+e）
Button PromptNextStep;	 // 提示下一步（Alt+p）
Button ShowShortestPath; // 显示最短路径（Alt+r）
Button ShowAllPath;		 // 显示全部路径（Alt+a）
Button LeftShiftPath;	 // 显示全部路径时左切
Button RightShiftPath;	 // 显示全部路径时右切
Button Instruction;		 // 使用说明
Button About_Game;		 // 关于
Button Back;			 // 回退
*/

Button ButtonEnum[ButtonNum] = {
	{"开始新游戏"				,Button_UP	,120,120,60,20	,UNVISIBLE}, 
	{"自动生成地图"				,Button_UP	,45,130,60,20	,UNVISIBLE},
	{"手动生成地图"				,Button_UP	,45,60,60,20	,UNVISIBLE},
//	{"空白地图"					,Button_UP	,45,100,15,20	,UNVISIBLE},
//	{"使用模板"					,Button_UP	,60,100,15,20	,UNVISIBLE},
//	{"系统模板"					,Button_UP	,75,100,15,20	,UNVISIBLE},
//	{"存档模板"					,Button_UP	,90,100,15,20	,UNVISIBLE},
	{"读取存档"					,Button_UP	,120,90,60,20	,UNVISIBLE},
	{"退出"						,Button_UP	,120,60,60,20	,UNVISIBLE},
	{"菜单"						,Button_UP	,0,185,20,15	,UNVISIBLE},
	{"新建地图  Ctrl+c"					,Button_UP	,0,172,40,13	,UNVISIBLE},
	{"打开地图  Ctrl+o"					,Button_UP	,0,159,40,13	,UNVISIBLE},
	{"存档  Ctrl+s"						,Button_UP	,0,146,40,13	,UNVISIBLE},
//	{"保存为模板"				,Button_UP	,35,60,15,20	,UNVISIBLE},
	{"返回主页面  Ctrl+b"		,Button_UP	,0,133,40,13	,UNVISIBLE},
	{"工具"						,Button_UP	,20,185,20,15	,UNVISIBLE},
//	{"编辑地图  Shift+e"		,Button_UP	,20,172,30,13	,UNVISIBLE},
	{"提示下一步  Shift+p"		,Button_UP	,0,172,40,13	,UNVISIBLE},
	{"显示最短路径  Shift+r"	,Button_UP	,0,159,40,13	,UNVISIBLE},
	{"显示全部路径  Shift+a"	,Button_UP	,0,146,40,13	,UNVISIBLE},
	{"<-"						,Button_UP	,20,20,15,15	,UNVISIBLE},
	{"->"						,Button_UP	,35,20,15,15	,UNVISIBLE},
	{"使用说明"					,Button_UP	,260,185,20,15	,VISIBLE},
	{"关于"						,Button_UP	,280,185,20,15	,VISIBLE},
	{"回退"						,Button_UP	,20,175,20,15	,UNVISIBLE},
	{"墙"						,Button_UP	,10,150,20,15	,UNVISIBLE},
	{"起点"						,Button_UP	,10,130,20,15	,UNVISIBLE},
	{"终点"						,Button_UP	,10,110,20,15	,UNVISIBLE},
	{"金币"						,Button_UP	,10,90,20,15	,UNVISIBLE},
	{"橡皮"						,Button_UP	,10,70,20,15	,UNVISIBLE},
	{"完成"						,Button_UP	,10,50,20,15	,UNVISIBLE},
	{"退出"						,Button_UP	,10,30,20,15	,UNVISIBLE},
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
