#ifndef REACTION_H_
#define REACTION_H_

extern int ifctrl;  // 是否按下Ctrl键
extern int ifshift; // 是否按下Shift键

extern int putting; // 正在编辑的模块
extern int ifpre;   // 是否显示预览
extern int editx;   // 编辑地图的x坐标
extern int edity;   // 编辑地图的y坐标

extern int aboutstage; // 存储打开关于前的页面状态

/***************************************************************************************/

void myMouseEvent(int x, int y, int button, int event); // 鼠标事件，判断触发了什么事件
void myKeyboardEvent(int key, int event);               // 控制按键触发事件，快捷键
void mycharEvent(char ch);                              // 普通按键触发事件

/***************************************************************************************/

void MainPageTell(double mouse_x, double mouse_y);     // 主页面按钮触发事件
void GamePageTell(double mouse_x, double mouse_y);     // 游戏界面按钮触发事件
void ChoseMapPageTell(double mouse_x, double mouse_y); // 选择模式界面按钮触发事件
void MenuPageTell(double mouse_x, double mouse_y);     // 菜单界面按钮触发事件
void ToolPageTell(double mouse_x, double mouse_y);     // 工具界面按钮触发事件
void EditPageTell(double mouse_x, double mouse_y);     // 编辑界面按钮事件

/***************************************************************************************/

void TellLeftButtonDown(double mouse_x, double mouse_y); // 左键点击事件
void TellMouseMove(double mouse_x, double mouse_y);      // 鼠标移动事件

/***************************************************************************************/

int TellRoad(double x, double y); // 判断编辑时是否点空格位置
int TellWall(double x, double y); // 判断编辑时是否点墙
void AllEditButtonUp(void);       // 所有编辑按钮弹起

/***************************************************************************************/

void Moveup(void);    // 角色向上移动
void Moveleft(void);  // 角色向左运动
void Moveright(void); // 角色向右运动
void Movedown(void);  // 角色向下运动

/***************************************************************************************/

void AllUnvisible(void);                                    // 全部按钮不可见
void AllButtonUp(void);                                     // 全部按钮松开
int TellPress(double mouse_x, double mouse_y, Button Butt); // 判断有无触发按钮
int TellOn(double mouse_x, double mouse_y, Button Butt);    // 判断鼠标是否在按钮上
void setMouseCursorHand(void);                              // 鼠标变成手指
void setMouseCursorArrow(void);                             // 鼠标变成箭头

/***************************************************************************************/

void build_map_auto(void); // 点击自动生成地图
void build_map_manu(void); // 点击手动生成地图

#endif
