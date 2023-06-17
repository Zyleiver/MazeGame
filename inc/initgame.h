#ifndef INITGAME_H_
#define INITGAME_H_

#define ButtonNum 30
// 所有的按钮
enum BUTTON
{
	StartNewGame,	  // 开始新游戏
	BuildMapAuto,	  // 自动生成地图
	BuildMapManu,	  // 手动生成地图
//	EmptyMap,		  // 空白地图
//	UseTemp,		  // 使用模板
//	TempFromSys,	  // 系统模板
//	TempFromFile,	  // 存档模板
	ReadFiles,		  // 读取存档
	ExitGame,		  // 退出
	Menu,			  // 菜单
	CrtNewMap,		  // 新建地图（Ctrl+c）
	OpenMap,		  // 打开地图（Ctrl+o）
	SaveGame,		  // 存档（Ctrl+s）
//	SaveAsTemp,		  // 保存为模板（Ctrl+m）
	BackToMP,		  // 返回主界面（Ctrl+b）
	Tools,			  // 工具
//	EditMap,		  // 编辑地图（Ctrl+e）
	PromptNextStep,	  // 提示下一步（Shift+p）
	ShowShortestPath, // 显示最短路径（Shift+r）
	ShowAllPath,	  // 显示全部路径（Shift+q）

	Instruction,	  // 使用说明
	About_Game,		  // 关于
	Back,			  // 回退
	PutWall,		  //放置墙
	PutRole, 		  //放置起点
	PutGoal,		  //放置终点
	PutCoin, 		  //放置金币
	Erase, 			  //橡皮
	Complete, 		  //完成编辑
	Cancel,			  //退出编辑
	LeftShiftPath,	  // 显示全部路径时左切
	RightShiftPath	  // 显示全部路径时右切
};


//初始化游戏数据（界面状态、按键状态）
void InitGame(void);

//切换到目标页面
void ShiftPageTo(int PageTo);
#endif
