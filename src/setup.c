#include "MyHeader.h"

int MZX;			//地图算法横向总长 
int MZY;			//地图算法纵向总长 

int coinNum;		//金币数量 
int monsternum;		//怪兽数量 
int endtime;		//胜利结算动画显示时间 
int dietime;		//失利结算动画显示时间 
int iscracked = 0;	//无敌时间变量 
int ender = 0;		//判断胜利还是失利 
int bubuhat = 0;	//成就使用变量 

double Xlength;		//Xlength=地图横向总长 
double Ylength;		//Ylength=地图纵向总长
double length;		//格子大小 
double X0;			//地图左下角横坐标
double Y0;			//地图右下角纵坐标


//循环变量群 
int i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i17;
//用于随机选择未访问方格的过程中存放随机方格 
int rnum;
int rnumx, rnumy;
//用于在迷宫生成算法中判断方格是否被访问过
typedef enum
{
    NO,
    YES
} visitYorN;
//未访问表 
struct nonvisit
{
    int x;
    int y;
    struct nonvisit *next;
};


//****************************自动生成迷宫模块*********************************//

//自动生成基图函数 
void CreateNewMap(void)
{
   
     if(170/yscale>=230/xscale)
    {
    	length=230/xscale;
	}else
	{
		length=170/yscale;
	}
	

    Xlength = (double)xscale * length;
    Ylength = (double)yscale * length;
    X0 = 150 - Xlength / 2;
    Y0 = 90 - Ylength / 2;
    
    CoinGet = 0;
    MajorRole.hp = 12;
    MajorRole.x = -10;
    MajorRole.y = -10;
    for (i12 = 0; i12 < 1000; i12++)
    {
        Monster[i12].hp = 0;
        Monster[i12].x = -10;
        Monster[i12].y = -10;
    }

    // 地图恢复原始状态为建立作准备
    for (i12 = 0; i12 < 100; i12++)
    {
        for (i13 = 0; i13 < 100; i13++)
        {
            Map[i12][i13] = ROAD;
        }
    }
    AllButtonUp();

    // 全图最外层一圈设置为墙，但在前端不显示出来，只是便于算法实现，免去讨论边界情况
    for (i1 = 0; i1 <= 99; i1++)
    {
        Map[i1][0] = WALL;
        Map[i1][99] = WALL;
    }

    for (i1 = 0; i1 <= 99; i1++)
    {
        Map[0][i1] = WALL;
        Map[99][i1] = WALL;
    }

    //给迷宫隔列设置WALL
    for (i2 = 2; i2 <= 97; i2 = i2 + 2)
    {
        for (i3 = 1; i3 <= 98; i3++)
        {
            Map[i2][i3] = WALL; 
        }
    }
	//给迷宫隔行设置WALL
    for (i4 = 2; i4 <= 97; i4 = i4 + 2)
    {
        for (i5 = 1; i5 <= 98; i5++)
        {
            Map[i5][i4] = WALL; 
        }
    }

    // 初始化将所有方格设为未访问
    int visit[100 + 4][100 + 4];
    for (i10 = 0; i10 <= 103; i10++)
    {
        for (i11 = 0; i11 <= 103; i11++)
        {
            visit[i10][i11] = NO;
        }
    }

    //随机生成迷宫时选择起点，终点 
    Map[1][1] = START;
    Map[MZX][MZY] = END;
	
	//建立一个链表用来维护未访问的方格
    struct nonvisit *head;
    struct nonvisit *p;
    struct nonvisit *tail;
    head = tail = NULL;

    for (i7 = 1; i7 <= MZX; i7 = i7 + 2)
    {
        for (i8 = 1; i8 <= MZY; i8 = i8 + 2)
        {
            p = (struct nonvisit *)malloc(sizeof(struct nonvisit));
            p->x = i7;
            p->y = i8;
            p->next = NULL;
            if (head == NULL)
            {
                head = p;
            }
            else
            {
                tail->next = p;
            }
            tail = p;
        }
    }
    p = head;
    
    //vnum即visitnumber,记录访问过的方格数，roadnum为地图总共需要访问的方格数 
    int vnum = 0;
    int roadnum = (MZX + 1) * (MZY + 1) / 4;

    //首先将起点入队 
    visit[1 + 1][1 + 1] = YES;
    vnum++;
    head = head->next;
    p = head;

    // prim算法生成迷宫基础地图
    srand(time(0));
    while (vnum < roadnum)
    {     
        while (1)
        {
        	//随机抽取一个未放问队中的新方格
            p = head;
            rnum = rand() % (roadnum - vnum);
            if (rnum == 0)
            {
                rnumx = p->x;
                rnumy = p->y;
            }

            while (rnum > 1)
            {
                p = p->next;
                rnum--;
            }

            if (rnum != 0)
            {
                rnumx = p->next->x;
                rnumy = p->next->y;
            }
            

            //判断新方格是否与当前通路相连，若相连则入队 
            if (visit[rnumx + 1][rnumy + 2 + 1] == YES)
            {
                vnum++;
                Map[rnumx][rnumy + 1] = ROAD;
                visit[rnumx + 1][rnumy + 1] = YES;

                if (rnum != 0)
                    p->next = p->next->next;
                else
                    head = head->next;
                break;
            }
            else if (visit[rnumx - 2 + 1][rnumy + 1] == YES)
            {
                vnum++;
                Map[rnumx - 1][rnumy] = ROAD;
                visit[rnumx + 1][rnumy + 1] = YES;

                if (rnum != 0)
                    p->next = p->next->next;
                else
                    head = head->next;
                break;
            }
            else if (visit[rnumx + 2 + 1][rnumy + 1] == YES)
            {
                vnum++;
                visit[rnumx + 1][rnumy + 1] = YES;
                Map[rnumx + 1][rnumy] = ROAD;

                if (rnum != 0)
                    p->next = p->next->next;
                else
                    head = head->next;
                break;
            }
            else if (visit[rnumx + 1][rnumy - 2 + 1] == YES)
            {
                vnum++;
                Map[rnumx][rnumy - 1] = ROAD;
                visit[rnumx + 1][rnumy + 1] = YES;

                if (rnum != 0)
                    p->next = p->next->next;
                else
                    head = head->next;
                break;
            }
        }

        p = head;
    }

    // 随机凿墙程序优化迷宫生成算法
    int randwallbreakx, randwallbreaky, randwallbreaknum;
    srand(time(0));
    for (randwallbreaknum = 0; (randwallbreaknum <= MZX/2 && randwallbreaknum <= MZY/2) && xscale + yscale > 9;)
    {
        randwallbreakx = rand() % (MZX) + 1;
        randwallbreaky = rand() % (MZY) + 1;

        if (Map[randwallbreakx][randwallbreaky] == WALL && randwallbreakx <= 2*MZX/3 && randwallbreaky <= 2*MZY/3)
        {
        	if(randwallbreakx > MZX/4 && randwallbreaky > MZY/4)
            Map[randwallbreakx][randwallbreaky] = ROAD;
            randwallbreaknum++;
        }
    }
    for (randwallbreaknum = 0; randwallbreaknum <= 8 && xscale > 9 && yscale > 9;)
    {
        randwallbreakx = rand() % (MZX) + 1;
        randwallbreaky = rand() % (MZY) + 1;

        if (Map[randwallbreakx][randwallbreaky] == WALL && randwallbreakx > MZX-15 && randwallbreaky > MZY-15)
        {
        	if(randwallbreakx < MZX-5 && randwallbreaky < MZY-5)
            {
            	randwallbreaknum++;
            	Map[randwallbreakx][randwallbreaky] = ROAD;
			}
        }
    }
    //至此迷宫基础部分WALL、ROAD生成完成，存放于二维数组Map中

    //金币生成在距离合适的ROAD上
    int coinx, coiny;
    srand(time(0));
    i6 = 0;
    while (i6 < coinNum)
    {
        coinx = rand() % (MZX) + 1;
        coiny = rand() % (MZY) + 1;
        
            if (coinx % 2 != 0 && coiny % 2 != 0)
            {
            	if(Map[coinx][coiny] == ROAD && coinx < MZX && coiny < MZY)
                {
                	Map[coinx][coiny] = COIN;
                	i6++;
				}
            }
        
    }
	
	//人物怪兽填充 
    GameInit();
}

//人物、怪兽自动初始化函数 
void GameInit(void)
{
	//生成地图规模 
	 if(170/yscale>=230/xscale)
    {
    	length=230/xscale;
	}else
	{
		length=170/yscale;
	}

    Xlength = (double)xscale * length;
    Ylength = (double)yscale * length;
    X0 = 150 - Xlength / 2;
    Y0 = 90 - Ylength / 2;
    MZX = xscale * 2 - 1;
    MZY = yscale * 2 - 1;
	i6 = 0;

    CoinGet = 0;
    // 主角状态初始化
    MajorRole.hp = 12;
    int i, j;
    for (i = MZX + 1; i >= 0; i--)
    {
        for (j = 0; j <= MZY + 1; j++)
        {
            if (Map[i][j] == START)
            {
                MajorRole.x = i;
                MajorRole.y = j;
            }
        }
    }

    // 怪兽状态初始化
    for (i12 = 1; i12 <= monsternum; i12++)
    {
        if (monsternum > i12)
            Monster[i12].hp = 100;

    	while (1)
    	{
        	Monster[i12].x = rand()%(MZX-1)+1;
        	Monster[i12].y = rand()%(MZY-1)+1;
        	if((Monster[i12].x>=MZX/3 && Monster[i12].y>=MZY/3) && (Monster[i12].x<=4*MZX/5 || Monster[i12].y<=4*MZY/5) && (Map[Monster[i12].x][Monster[i12].y] == ROAD || Map[Monster[i12].x][Monster[i12].y] == COIN))
        	{
     	       if(Monster[i12].x%2!=0 && Monster[i12].y%2!=0)
     	       break;
     	    }
    	}
	}
	
	//怪兽0用于判断准备工作是否完成 
	Monster[0].hp = 100;
    
}


//****************************手动生成迷宫模块*********************************//

//地图基图初始化 
void BuildMap(void)
{
    
    if(170/yscale>=230/xscale)
    {
    	length=230/xscale;
	}else
	{
		length=170/yscale;
	}

    Xlength = (double)xscale * length;
    Ylength = (double)yscale * length;
    X0 = 150 - Xlength / 2;
    Y0 = 90 - Ylength / 2;

    putting = 0;
    CoinGet = 0;
    MajorRole.hp = 12;
    MajorRole.x = -110;
    MajorRole.y = -110;
    for (i12 = 0; i12 < 1000; i12++)
    {
        Monster[i12].hp = 0;
        Monster[i12].x = -100;
        Monster[i12].y = -100;
    }

    // 地图恢复原始状态为建立作准备
    for (i12 = 0; i12 < 100; i12++)
    {
        for (i13 = 0; i13 < 100; i13++)
        {
            Map[i12][i13] = ROAD;
        }
    }
    AllButtonUp();

    // 全图最外层一圈设置为墙
    for (i1 = 0; i1 <= 99; i1++)
    {
        Map[i1][0] = WALL;
        Map[i1][99] = WALL;
    }

    for (i1 = 0; i1 <= 99; i1++)
    {
        Map[0][i1] = WALL;
        Map[99][i1] = WALL;
    }

    // 初始化ROAD和WALL，交错排列，保证每个ROAD上下左右四个方向都是WALL
    // 给迷宫隔列设置WALL
    for (i2 = 2; i2 <= 97; i2 = i2 + 2)
    {
        for (i3 = 1; i3 <= 98; i3++)
        {
            Map[i2][i3] = WALL; 
        }
    }
	
	// 给迷宫隔行设置WALL
    for (i4 = 2; i4 <= 97; i4 = i4 + 2)
    {
        for (i5 = 1; i5 <= 98; i5++)
        {
            Map[i5][i4] = WALL;
        }
    }
    
}

//迷宫编辑函数 
void EditMap(int x, int y, int buttonusing)
{
    switch (buttonusing)
    {
    //放置金币 
  	case PutCoin:
        if (x % 2 != 0 && y % 2 != 0)
        {
            if(Map[x][y]==ROAD)
            {
                Map[x][y] = COIN;
            }
            
        }

        break;

	//放置角色 
    case PutRole:
    	if(Map[x][y]==ROAD)
    	{
    		if (x % 2 != 0 && y % 2 != 0)
        	{
            	for (i12 = 0; i12 < 100; i12++)
            	{
                for (i13 = 0; i13 < 100; i13++)
                {
                    if (Map[i12][i13] == START)
                        Map[i12][i13] = ROAD;
                }
            }

            Map[x][y] = START;
            MajorRole.x = x;
            MajorRole.y = y;
        }	
		}
        
        break;
	
	//放置终点 
    case PutGoal:
    	if(Map[x][y]==ROAD)
    	{
    		if (x % 2 != 0 && y % 2 != 0)
        {
            for (i12 = 0; i12 < 100; i12++)
            {
                for (i13 = 0; i13 < 100; i13++)
                {
                    if (Map[i12][i13] == END)
                        Map[i12][i13] = ROAD;
                }
            }

            Map[x][y] = END;
        }
		}
        
        break;

	//使用橡皮擦除元素 
    case Erase:
        if (Map[x][y] != ROAD && x >= 1 && y >= 1 && x <= MZX + 1 && y <= MZY + 1)
        {
            if (Map[x][y] == START)
            {
                MajorRole.hp = 12;
                MajorRole.x = -10;
                MajorRole.y = -10;
            }

            Map[x][y] = ROAD;
    	}
        break;

	//放置墙 
    case PutWall:
        if (x % 2 == 1 || y % 2 == 1)
        {
            Map[x][y] = WALL;
        }
        break;

	//完成编辑开始游玩 
    case Complete:
        Monster[0].hp = 100;
        ShiftPageTo(GAME_PAGE);
        break;
    }
}


//****************************游戏动态构建模块*********************************//

//时间回调函数 
void myTimerEvent(int timerID)
{
    switch (timerID)
    {
    //怪兽移动时间回调 
    case MonsterTimer:
    	//保证怪兽只在游戏时移动
        if (Monster[0].hp != 100 || page_stage != GAME_PAGE) 
        {
        	break;
		}
            
		//分别对每只游戏中怪兽的路径进行判断 
       for(i14 = 1;i14 <= monsternum;i14 ++)
        {
       			int ifforwardplayer = rand()%10;
       			int monstermoverand = rand()%2;
       			
    	        if(ifforwardplayer<8)//朝向主角走，4/5的概率 
                {
                    if(monstermoverand)//走x
                    {
                        if(MajorRole.x>Monster[i14].x)//走正
                        {
                            
							if(Map[Monster[i14].x+1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x++;
                                Monster[i14].x++;
                            }else{
                            	//走x走不通就尝试走y 
								if(MajorRole.y>Monster[i14].y)
                        		{
                            		if(Map[Monster[i14].x][Monster[i14].y+1]!=WALL)
                                	{   
                                    	Monster[i14].y++;
                                    	Monster[i14].y++;
                                	}
                        		}
                        		else
                        		{
                            		if(Map[Monster[i14].x][Monster[i14].y-1]!=WALL)
                            		{
                                		Monster[i14].y--;
                                		Monster[i14].y--;
                            		}
                        		}
							}
                        }
                        else//走负 
                        {	
                        	
                            if(Map[Monster[i14].x-1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x--;
                                Monster[i14].x--;
                            }else{
                            	//走x走不通就尝试走y 
                            		if(MajorRole.y>Monster[i14].y)
                       		 		{
                            			if(Map[Monster[i14].x][Monster[i14].y+1]!=WALL)
                                		{   
                                  	  		Monster[i14].y++;
                                    		Monster[i14].y++;
                                		}
                        			}
                        			else
                        			{
                            			if(Map[Monster[i14].x][Monster[i14].y-1]!=WALL)
                            			{
                               	 			Monster[i14].y--;
                                			Monster[i14].y--;
                            			}
                        			}
							}
							
                    	}
                    }
                    else//走y 
                    {	
                        if(MajorRole.y>Monster[i14].y)//走正 
                        {
                            if(Map[Monster[i14].x][Monster[i14].y+1]!=WALL)
                            {   
                                Monster[i14].y++;
                                Monster[i14].y++;
                            }
                        	else{
                        		//走y走不通尝试走x 
                        			if(MajorRole.x>Monster[i14].x)
                        		{
                            		if(Map[Monster[i14].x+1][Monster[i14].y]!=WALL)
                                	{   
                                    	Monster[i14].x++;
                                    	Monster[i14].x++;
                                	}
                        		}
                        		else
                        		{
                            		if(Map[Monster[i14].x-1][Monster[i14].y-1]!=WALL)
                            		{
                                		Monster[i14].x--;
                                		Monster[i14].x--;
                            		}
                        		}
							}
                        }
                        else//走负 
                        {
                            if(Map[Monster[i14].x][Monster[i14].y-1]!=WALL)
                            {
                                Monster[i14].y--;
                                Monster[i14].y--;
                            }
                            else{
                            	//走y走不通尝试走x 
                        			if(MajorRole.x>Monster[i14].x)
                        		{
                            		if(Map[Monster[i14].x+1][Monster[i14].y]!=WALL)
                                	{   
                                    	Monster[i14].x++;
                                    	Monster[i14].x++;
                                	}
                        		}
                        		else
                        		{
                            		if(Map[Monster[i14].x-1][Monster[i14].y-1]!=WALL)
                            		{
                                		Monster[i14].x--;
                                		Monster[i14].x--;
                            		}
                        		}
							}
                        }
                    }
                }
                else//不朝主角走 
                {
        
					if(monstermoverand)//走x
                    {
                        if(MajorRole.x>Monster[i14].x)//走负
                        {
                            if(Map[Monster[i14].x-1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x--;
                                Monster[i14].x--;
                            }
                            else//走x不通就尝试走y 
                            {
                            	if(MajorRole.y>Monster[i14].y)
                        		{
                            		if(Map[Monster[i14].x][Monster[i14].y-1]!=WALL)
                                	{   
                                    	Monster[i14].y--;
                                    	Monster[i14].y--;
                                	}
                        		}
                        		else
                        		{
                            		if(Map[Monster[i14].x][Monster[i14].y+1]!=WALL)
                            		{
                                		Monster[i14].y++;
                                		Monster[i14].y++;
                            		}
                        		}
                        	}
                        }
                        else//走正 
                        {
                            if(Map[Monster[i14].x+1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x++;
                                Monster[i14].x++;
                            }
                            else//走x不通就尝试走y 
                            {
                            	if(MajorRole.y>Monster[i14].y)
                        		{
                            		if(Map[Monster[i14].x][Monster[i14].y-1]!=WALL)
                                	{   
                                    	Monster[i14].y--;
                                    	Monster[i14].y--;
                                	}
                        		}
                        		else
                        		{
                            		if(Map[Monster[i14].x][Monster[i14].y+1]!=WALL)
                            		{
                                		Monster[i14].y++;
                                		Monster[i14].y++;
                            		}
                        		}
                        	}
                        }
                    }
                    else//走y 
                    {
                        if(MajorRole.y>Monster[i14].y)//走负 
                        {
                            if(Map[Monster[i14].x][Monster[i14].y-1]!=WALL)
                            {   
                                Monster[i14].y--;
                                Monster[i14].y--;
                            }
                            else//走y不通就尝试走x 
                            {
                            	if(MajorRole.x>Monster[i14].x)
                        		{
                            		if(Map[Monster[i14].x-1][Monster[i14].y]!=WALL)
                                	{   
                                    	Monster[i14].x--;
                                    	Monster[i14].x--;
                                	}
                        		}
                        		else
                        		{
                            		if(Map[Monster[i14].x+1][Monster[i14].y]!=WALL)
                            		{
                                		Monster[i14].x++;
                                		Monster[i14].x++;
                            		}
                        		}
							}
                        }
                        else//走正 
                        {
                            if(Map[Monster[i14].x][Monster[i14].y+1]!=WALL)
                            {
                                Monster[i14].y++;
                                Monster[i14].y++;
                            }
                            else//走y不通就尝试走x 
                            {
                            	if(MajorRole.x>Monster[i14].x)
                        		{
                            		if(Map[Monster[i14].x-1][Monster[i14].y]!=WALL)
                                	{   
                                    	Monster[i14].x--;
                                    	Monster[i14].x--;
                                	}
                        		}
                        		else
                        		{
                            		if(Map[Monster[i14].x+1][Monster[i14].y]!=WALL)
                            		{
                                		Monster[i14].x++;
                                		Monster[i14].x++;
                            		}
                        		}
							}
                        }
                    }
                }       
        }
        break;
    
	//刷新时间回调    
    case FlashTimer:
    		if(iscracked>0)
				iscracked--;
			if(endtime > 0)
				endtime--;
			if(dietime > 0)
				dietime--;
            display();
            break;
            
    //游戏触碰时间回调 
    case GameTouchTimer:
    	    
    	    //怪兽碰撞事件 
    		for(i15 = 1; i15 <= monsternum; i15++ )
    		{
    			if(MajorRole.x == Monster[i15].x && MajorRole.y == Monster[i15].y &&page_stage==GAME_PAGE)
    			{
    				if(MajorRole.hp != 0 && iscracked == 0 && page_stage == GAME_PAGE && endtime == 0)
    				{
    					if(MajorRole.hp <= 3)
    					{
    						MajorRole.hp = 0;	
						}
    					else
    					{
    						MajorRole.hp = MajorRole.hp - 3;
						}
    						
    					iscracked = 200;
					}
				}
			}
			
				//到达终点 
				if(page_stage==GAME_PAGE && Map[MajorRole.x][MajorRole.y] == END)
				{
					if(ButtonEnum[PromptNextStep].stage == Button_DOWN)
						bubuhat = 1;
					ShiftPageTo(END_PAGE);
					endtime = 200;
					ender = 1;	
				}
				//角色失利 
				if(page_stage==GAME_PAGE && MajorRole.hp == 0)
				{
					ShiftPageTo(END_PAGE);
					dietime = 100;
					ender = 2;
				}
				
				//胜利成就判断和保存询问 
				if(page_stage==END_PAGE && endtime == 0 && ender == 1)
				{		
                        int result;
						if(CoinGet < coinNum || coinNum == 0)
						{
							ender = 0;
							if(MajorRole.hp == 12)
							{
								if(CoinGet == 0)
									result = MessageBox(NULL, "\t获 得 成 就 ：无 瑕 ：金 币 是 什 么？ \n\n\t是 否 保 存 地 图 ", "胜利", MB_YESNO);
								else if(bubuhat == 0)
									result = MessageBox(NULL, "\t获 得 成 就 ：无 瑕 ：完 好 如 初\n\n\t是 否 保 存 地 图 ", "胜利", MB_YESNO);
								else
								{
									bubuhat = 0;
									result = MessageBox(NULL, "\t获 得 成 就 ：好 像 掉 了 什 么？\n\n\t是 否 保 存 地 图 ", "胜利", MB_YESNO);
								}
							
							}
							else if(bubuhat == 1)
							{
								bubuhat = 0;
								result = MessageBox(NULL, "\t获 得 成 就 ：好 像 掉 了 什 么？\n\n\t是 否 保 存 地 图 ", "胜利", MB_YESNO);
							}
							else
								result = MessageBox(NULL, "\t是 否 保 存 地 图 ", "胜利", MB_YESNO);
							
						}
    					else 
    					{
    						ender = 0;
    						if(MajorRole.hp != 12)
    							result = MessageBox(NULL, "\t获 得 成 就 ：收 藏 家\n\n\t是 否 保 存 地 图 ", "胜利", MB_YESNO);
							else 
								result = MessageBox(NULL, "\t获 得 成 就 ：无 瑕 ：杰 出 的 收 藏 家\n\n\t是 否 保 存 地 图 ", "胜利", MB_YESNO);
						}
    					
    					//保存结果 
						if (result == IDYES)
    					{
        						if(saveMap())
        						{
        							int re = MessageBox(NULL, "\n\t保存成功 ", "成功", MB_OK);
								}
								else
								{
									int re1 = MessageBox(NULL, "\n\t保存失败", "重试", MB_OK);
								}
								
								ShiftPageTo(MAIN_PAGE);
							
    					}
    					else if (result == IDNO)
    					{
        					ShiftPageTo(MAIN_PAGE);
    					}
					
					
				}
				
				//失利成就判断和保存时间 
				if(page_stage==END_PAGE && dietime == 0 && ender == 2)
				{		
						
                        int result1;
						if(CoinGet < coinNum || coinNum == 0)
						{
							ender = 0;
							if(monsternum >= 200)
								result1 = MessageBox(NULL, "\t获 得 成 就 ：怪 兽 爱 好 者\n\n\t是 否 保 存 地 图 ", "失利", MB_YESNO);
							else
								result1 = MessageBox(NULL, "\t再 接 再 厉 !\n\n\t是 否 保 存 地 图 ", "失利", MB_YESNO);
						}
    					else 
    					{
    						ender = 0;
    						result1 = MessageBox(NULL, "\t获 得 成 就 ：金 币 导 致 的\n\n\t是 否 保 存 地 图 ", "失利", MB_YESNO);
						}
    					
    					//保存结果 
    					if (result1 == IDYES)
    					{
        					if(saveMap())
        					{
        						int re = MessageBox(NULL, "\n\t保存成功 ", "成功", MB_OK);
        						
							}
							else
							{
								int re1 = MessageBox(NULL, "\n\t保存失败", "重试", MB_OK);
							}
							ShiftPageTo(MAIN_PAGE);
        					
    					}
    					else if (result1 == IDNO)
    					{
        					ShiftPageTo(MAIN_PAGE);
    					}
    				
				}
				
			//金币碰撞事件
			if(Map[MajorRole.x][MajorRole.y] == COIN && page_stage==GAME_PAGE)
			{
				Map[MajorRole.x][MajorRole.y] = COINGOT;
				CoinGet++;
				if(MajorRole.hp < 12)
					MajorRole.hp ++;
			}	
    break;   
    }	 
}
