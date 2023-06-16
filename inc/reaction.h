#ifndef REACTION_H_
#define REACTION_H_

extern int ifctrl;
extern int ifshift;

// 鼠标事件，判断触发了什么事件
void myMouseEvent(int x, int y, int button, int event);

// 控制按键触发事件，快捷键
void myKeyboardEvent(int key, int event);

//普通按键触发事件
void mycharEvent(char ch);

// 退出程序
void Exit(void);

// 新建地图
void CreateMap_ingame(void);

// 打开地图
void OpenMap_ingame(void);

// 返回主菜单
void BackToMainPage(void);

//主页面按钮触发事件
void MainPageTell(double mouse_x, double mouse_y);

// 游戏界面按钮触发事件
void GamePageTell(double mouse_x, double mouse_y);

//选择模式界面按钮触发事件 
void ChoseMapPageTell(double mouse_x,double mouse_y);

//菜单界面按钮触发事件
void MenuPageTell(double mouse_x, double mouse_y);

//工具界面按钮触发事件
void ToolPageTell(double mouse_x,double mouse_y);

//编辑界面按钮事件
void EditPageTell (double mouse_x,double mouse_y);

//全部按钮不可见
void AllUnvisible(void);

// 角色向上移动
void Moveup(void);
// 角色向左运动
void Moveleft(void);
// 角色向右运动
void Moveright(void);
// 角色向下运动
void Movedown(void);
#endif
