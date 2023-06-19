#ifndef SETUP_H_
#define SETUP_H_

extern int Map[100][100]; 	//地图数组 
extern int MZX;				//地图算法横向总长 
extern int MZY;				//地图算法纵向总长 

extern int coinNum;		//金币数量 
extern int monsternum;	//怪兽数量 
extern int endtime;		//胜利结算动画变量 
extern int dietime;		//失利结算动画变量 
extern int iscracked;	//碰撞时间变量 
extern int ender;		//判断胜利还是失利 
extern int bubuhat;		//成就使用变量 

extern double Xlength;  //Xlength=地图横向总长
extern double Ylength;  //Ylength=地图纵向总长
extern double length;   //格子大小
extern double X0;       //地图左下角横坐标
extern double Y0;       //地图右下角纵坐标


//****************************自动生成迷宫模块*********************************//

void CreateNewMap(void);	//自动生成基图函数
void GameInit(void);		//人物、怪兽自动初始化函数


//****************************手动生成迷宫模块*********************************//

void BuildMap(void);						//地图基图初始化
void EditMap(int x, int y, int buttonusing);//迷宫编辑函数


//****************************游戏动态构建模块*********************************//

//时间回调函数 
void myTimerEvent(int timerID); 
#endif
