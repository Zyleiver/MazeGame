#ifndef SETUP_H_
#define SETUP_H_

//暂时先令怪兽移动时间间隔（速度）为1000 ms
#define MONSTERSPEED 1000 

extern int monsternum;
//暂时先令地图为18*18，宏定义数值计算公式
//用户输入地图尺寸X、Y.  MZX = X*2 - 1; MZY = Y*2 - 1
//这就意味着生成的地图不将墙算进用户指定的格数中
//可以画细奇数列偶数行的方格（——）和偶数列奇数行的方格（|）————即墙
//并且将偶数列偶数行的方格画成（.）————这个位置永远都是墙
//奇数列奇数行则一定是ROAD或COIN或START或END
//而且在主角和怪兽移动时，需要在程序上跨越两个ROAD，这样前端显示才是跨越了一个“方格”
//来保持整体方形且满足用户要求
extern int MZX;
extern int MZY;

//创建一个随机的新地图
void CreateNewMap(void);

//手动创建地图/地图编辑
void BuildMap(void);

//使用模板
void UseTemplate(void);
//OpenTemp

//游戏初始化（人物、怪兽、金币初始化）
void InitMap(void);

extern int Map[100][100];
#endif
