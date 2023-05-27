#ifndef REACTION_H_
#define REACTION_H_

//鼠标事件，判断触发了什么事件
void myMouseEvent (int x, int y, int button, int event);

//按键触发事件，快捷键
void myKeyboardEvent(void);

//退出程序
void Exit(void);

//新建地图
void CreateMap_ingame(void);

//打开地图
void OpenMap_ingame(void);

//返回主菜单
void BackToMainPage(void);

//判断游戏事件（碰到怪兽、金币、终点）
void TellStuff(void);

#endif
