#include "MyHeader.h"

int MZX;
int MZY;
	
//循环变量群 ,
int i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i17;

//用于随机选择未访问方格的过程中，存放随机序号
int rnum;
//用于随机选择未访问方格的过程中，存放对应随机序号方格的坐标
int rnumx,rnumy;

int monsternum;

//用于在迷宫生成算法中判断方格是否被访问过
typedef enum
{
    NO,
    YES
}visitYorN;

struct nonvisit
{
    int x;
    int y;
    struct nonvisit *next;
};


//******自动生成迷宫函数******//
void CreateNewMap(void)
{
	MajorRole.hp = 3;
	MajorRole.x = -10;
	MajorRole.y = -10;
	for(i12 = 0; i12 < 1000; i12++)
	{
		Monster[i12].hp = 0;
		Monster[i12].x = -10;
		Monster[i12].y = -10;
	}
	
    //地图恢复原始状态为建立作准备
    for (i12 = 0; i12 < 100; i12++)
    {
        for(i13 = 0; i13 < 100; i13++)
        {
            Map[i12][i13] = ROAD;
        }
    }
    

    //全图最外层一圈设置为墙，但在前端不显示出来，只是便于算法实现，免去讨论边界情况
    for(i1 = 0; i1<=99; i1++)
    {
        Map[i1][0] = WALL;
        Map[i1][99] = WALL;
    }
    
    for(i1 = 0; i1<=99; i1++)
    {
        Map[0][i1] = WALL;
        Map[99][i1] = WALL;
    }


    //初始化ROAD和WALL，交错排列，保证每个ROAD上下左右四个方向都是WALL
    for(i2 = 2; i2<=97; i2=i2 + 2)
    {
        for(i3 = 1; i3<=98; i3++)
        {
            Map[i2][i3] = WALL; //给迷宫隔列设置WALL
        }
    }

    for(i4 = 2; i4<=97; i4=i4 + 2)
    {
        for(i5 = 1; i5<=98; i5++)
        {
            Map[i5][i4] = WALL; //给迷宫隔行设置WALL
        }
    }
    //迷宫最开始时设置了都为ROAD，所以只需要设置初始WALL即可

    //初始化将所有方格设为未访问
    int visit[100+4][100+4];
    for(i10 = 0;i10<=103;i10++)
    {
    	for(i11 = 0;i11<=103;i11++)
    	{
    		visit[i10][i11] = NO;
		}
	}
    //visit[x+1][y+1]是用于判断ROAD方格是否被访问过的数组，x和y为横纵坐标
    //+1是防止下方visit判断过程边界击穿




    //迷宫从（1，1）开始，（MZX，MZY）结束
    Map[1][1] = START;
    Map[MZX][MZY] = END;

    //vnum 即visitnumber,记录访问过的ROAD(包括END和START)方格数目，达到初始的ROAD数目roadnum时，maze生成完成
    int vnum = 0; 
    int roadnum = (MZX+1)*(MZY+1)/4;
    
    
    struct nonvisit *head;
    struct nonvisit *p;
    struct nonvisit *tail;
    head = tail = NULL;

    //建立一个链表，用来维护未访问方格的表
    for(i7 = 1; i7<=MZX ; i7 = i7+2)
    {
        for(i8 = 1; i8<=MZY ; i8 = i8+2)
        {
            p = (struct nonvisit*)malloc(sizeof(struct nonvisit));
            p->x = i7;
            p->y = i8;
            p->next = NULL;
            if(head==NULL)
            {
                head = p;
            }else{
                tail->next = p;
            }
            tail = p;
        }
    }
    p = head;

	printf("t\n");

    //首先访问起点（1，1）
    visit[1+1][1+1]=YES;
    printf("%d",visit[2][2]);
    vnum++;
    head = head->next;
    p = head;
    //删除未访问表中的起点方格

	srand(time(0));
    //prim算法生成迷宫基础地图
    while (vnum<roadnum)
    {
        //随机选择一个未访问过的且与现有通路相接的方格并连入现有通路
        while(1)
        {
        	p = head;
            rnum = rand()%(roadnum-vnum);
            if(rnum == 0)
            {
                rnumx = p->x;
                rnumy = p->y;
            }

            while(rnum>1)
            {
                p = p->next;
                rnum--;
            }

            if(rnum != 0)
            {   
                rnumx = p->next->x;
                rnumy = p->next->y;
            }
                //上方程序随机从未访问表中抽取了一个方格
                //不直接令p移动到随机序号位置是为了便于之后删除操作

                //下方程序判断该方格是否与当前通路相连，若相连则打通墙并记录，并将其从未访问表中删去
                if(visit[rnumx+1][rnumy+2+1] == YES)
                {
                	vnum++;
                    Map[rnumx][rnumy+1] = ROAD;
                    visit[rnumx+1][rnumy+1] = YES;

                    if(rnum != 0)
                    p->next = p->next->next;
                    else 
                    head = head->next;
                    break;
                }else if(visit[rnumx-2+1][rnumy+1] == YES){
                    vnum++;
                    Map[rnumx-1][rnumy] = ROAD;
                    visit[rnumx+1][rnumy+1] = YES;

                    if(rnum != 0)
                    p->next = p->next->next;
                    else 
                    head = head->next;
                    break;
                }else if(visit[rnumx+2+1][rnumy+1] == YES){
                    vnum++;
                    visit[rnumx+1][rnumy+1] = YES;
                    Map[rnumx+1][rnumy] = ROAD;

                    if(rnum != 0)
                    p->next = p->next->next;
                    else 
                    head = head->next;
                    break;
                }else if(visit[rnumx+1][rnumy-2+1] == YES){
                    vnum++;
                    Map[rnumx][rnumy-1] = ROAD;
                    visit[rnumx+1][rnumy+1] = YES;

                    if(rnum != 0)
                    p->next = p->next->next;
                    else 
                    head = head->next;
                    break;
                }
        }
        
        p = head;   //成功将通路扩展，为p移到表头为下一次循环作准备

        //当vnum等于roadnum时，说明所有初始化的ROAD都已经被访问过了，也即意味着迷宫基础地图生成完成
    }//退出循环

	//随机凿墙优化迷宫生成算法 
	int randwallbreakx, randwallbreaky, randwallbreaknum;
	srand(time(0));
	for(randwallbreaknum = 0; (randwallbreaknum <= MZX && randwallbreaknum <= MZY) && xscale+yscale>12;)
	{
		randwallbreakx = rand()%(MZX) + 1;
		randwallbreaky = rand()%(MZY) + 1;
		
		if(Map[randwallbreakx][randwallbreaky] == WALL)
		{
			Map[randwallbreakx][randwallbreaky] = ROAD;
			 randwallbreaknum++;
		}	
	}
	for(randwallbreaknum = 0; randwallbreaknum <= 3 && xscale+yscale>12; )
	{
		randwallbreakx = rand()%(MZX) + 1; 
		randwallbreaky = rand()%(MZY) + 1;
		
		if(Map[randwallbreakx][randwallbreaky] == WALL && randwallbreakx>MZX-5 && randwallbreaky>MZY-5)
		{
			randwallbreaknum ++;
			Map[randwallbreakx][randwallbreaky] = ROAD;
		}
	}
	
	
    //至此迷宫基础部分生成完成，存放于二维数组Map中，只有WALL和ROAD
    //但注意Map数组实际要画出的内容仅为[1][1]到[MZX][MZY]
    //终点位于[MZX][MZY],起点位于[1][1]，如有需要可以更改其位置或者地图大小


    //以下为人物、怪兽、金币初始化
    
    //三个金币状态初始化
    int coinx, coiny;
    
    srand(time(0));
    while(i6<3)
    {
        coinx = rand()%(MZX)+1;
        coiny = rand()%(MZY)+1;
        if((coinx>=MZX/3 || coiny>=MZY/3) && (coinx<=4*MZX/5 || coiny<=4*MZY/5) && (Map[coinx][coiny] == ROAD))
        {
            if(coinx%2!=0 && coiny%2!=0)
            {
                Map[coinx][coiny] = COIN;
                i6++;
            }
        }
    }//金币生成在距离合适的ROAD上
    
    //人物、怪兽初始化 
    GameInit();
    
    	//测试点 
    	int i,j;
    	for(i = MZX+1;i>=0;i--)
    	{
    		for(j = 0;j<=MZY+1;j++)
    		{
    			if(Map[j][i]==ROAD)
    			printf("   ");
    			if(Map[j][i]==WALL)
    			printf(" # ");
    			if(Map[j][i]==COIN)
    			printf(" O ");
    			if(Map[j][i]==END)
    			printf(" w ");
    			if(Map[j][i]==START)
    			printf(" S ");
			}
			printf("\n");
		}
		//测试结束 
}



//******人物、怪兽自动初始化******//
void GameInit(void)
{
    i6=0;
	
	CoinGet=0; 
    //主角状态初始化
    MajorRole.hp = 3;
    int i,j;
    for(i = MZX+1;i>=0;i--)
    {
    	for(j = 0;j<=MZY+1;j++)
    	{
			if(Map[i][j] == START)
    		{
    			MajorRole.x = i;
    			MajorRole.y = j;
			}	
		}
	}


    //怪兽状态初始化
    for(i12 = 1; i12 <= monsternum; i12++)
    {
    	if(monsternum > i12)
  		Monster[i12].hp = 100;

    	while (1)
    	{
        	Monster[i12].x = rand()%(MZX)+1;
        	Monster[i12].y = rand()%(MZY)+1;
        	if((Monster[i12].x>=MZX/3 || Monster[i12].y>=MZY/3) && (Monster[i12].x<=4*MZX/5 || Monster[i12].y<=4*MZY/5) && (Map[Monster[i12].x][Monster[i12].y] == ROAD))
        	{
     	       if(Monster[i12].x%2!=0 && Monster[i12].y%2!=0)
     	       break;
     	    }
    	}
	}
	Monster[0].hp = 100;
    //下来令怪兽在适当范围内移动
    
    
}


//******手动生成地图******//
void BuildMap(void)
{
	MajorRole.hp = 3;
	MajorRole.x = -10;
	MajorRole.y = -10;
	for(i12 = 0; i12 < 1000; i12++)
	{
		Monster[i12].hp = 0;
		Monster[i12].x = -20;
		Monster[i12].y = -20;
	}
	
	//地图恢复原始状态为建立作准备
    for (i12 = 0; i12 < 100; i12++)
    {
        for(i13 = 0; i13 < 100; i13++)
        {
            Map[i12][i13] = ROAD;
        }
    }
    

    //全图最外层一圈设置为墙，但在前端不显示出来，只是便于算法实现，免去讨论边界情况
    for(i1 = 0; i1<=99; i1++)
    {
        Map[i1][0] = WALL;
        Map[i1][99] = WALL;
    }
    
    for(i1 = 0; i1<=99; i1++)
    {
        Map[0][i1] = WALL;
        Map[99][i1] = WALL;
    }


    //初始化ROAD和WALL，交错排列，保证每个ROAD上下左右四个方向都是WALL
    for(i2 = 2; i2<=97; i2=i2 + 2)
    {
        for(i3 = 1; i3<=98; i3++)
        {
            Map[i2][i3] = WALL; //给迷宫隔列设置WALL
        }
    }

    for(i4 = 2; i4<=97; i4=i4 + 2)
    {
        for(i5 = 1; i5<=98; i5++)
        {
            Map[i5][i4] = WALL; //给迷宫隔行设置WALL
        }
    }
    //迷宫最开始时设置了都为ROAD，所以只需要设置初始WALL即可
    
}

void EditMap(int x,int y,int buttonusing)
{
	static int i18 = 0;
	
	switch (buttonusing)
	{
		case PutCoin:
			if(x%2 != 0 && y%2 != 0)
			{
				for (i12 = 0; i12 < 100; i12++)
    			{
        			for(i13 = 0; i13 < 100; i13++)
       				{
       					if(Map[i12][i13] == COIN)
            			Map[i12][i13] = ROAD;
        			}
    			}
    			
    			Map[x][y] = COIN;
			}
				
		break;
		
		case PutRole:
			if(x%2 != 0 && y%2 != 0)
			{
				for (i12 = 0; i12 < 100; i12++)
    			{
        			for(i13 = 0; i13 < 100; i13++)
       				{
       					if(Map[i12][i13] == START)
            			Map[i12][i13] = ROAD;
        			}
    			}
    			
    			Map[x][y] = START;
				MajorRole.x = x;
				MajorRole.y = y;
			}
		break;
		
		case PutGoal:
			if(x%2 != 0 && y%2 != 0)
			{
				for (i12 = 0; i12 < 100; i12++)
    			{
        			for(i13 = 0; i13 < 100; i13++)
       				{
       					if(Map[i12][i13] == END)
            			Map[i12][i13] = ROAD;
        			}
    			}
    			
    			Map[x][y] = END;
			}
		break;

		case Erase:
			if(Map[x][y] != ROAD )
			{
				if(Map[x][y] == START)
				{
					MajorRole.hp = 3;
					MajorRole.x = -10;
					MajorRole.y = -10;
				}
				
				Map[x][y] = ROAD;
			}
			
			for(i17 = 1; i17 < 1000; i17++)
			{
				if(Monster[i17].x == x && Monster[i17].y == y)
				{
					Monster[i17].hp = 0;
					Monster[i17].x = -10;
					Monster[i17].y = -10;
				}
			}
		break;
		
		case PutWall:
			if(x%2 == 1 || y%2 == 1)
			{
				Map[x][y] = WALL;
			}
		
		case Complete:
			Monster[0].hp = 100;
			ShiftPageTo(GAME_PAGE);
			
			
			
	}
	
	
}

int iscracked=0;
void myTimerEvent(int timerID)
{
    switch (timerID)
    {
    case MonsterTimer:
            if(Monster[0].hp != 100 || page_stage != GAME_PAGE) break;
            
            for(i14 = 1;i14 <= monsternum;i14 ++)
            {
            	int ifforwardplayer = rand()%10;
            	int monstermoverand = rand()%2;
                if(ifforwardplayer<8)//朝不朝
                {
                    if(monstermoverand)//走y还是x
                    {
                        if(MajorRole.x>Monster[i14].x)//走正还是走负
                        {
                            
							if(Map[Monster[i14].x+1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x++;
                                Monster[i14].x++;
                            }else{
                            	
							}
                        }
                        else
                        {	
                        	
                            if(Map[Monster[i14].x-1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x--;
                                Monster[i14].x--;
                            }else{
                            	
							}
							
                        }
                    }
                    else
                    {	
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
                else
                {
                    if(monstermoverand)//走y还是x
                    {
                        if(MajorRole.x>Monster[i14].x)//走正还是走负
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
                    else
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
        break;
    case FlashTimer:
    		if(iscracked>0)
				iscracked--;
            display();
            break;
    case GameTouchTimer:
    	    
    	    //怪兽碰撞事件 
    		for(i15 = 1; i15 <= monsternum; i15++ )
    		{
    			if(MajorRole.x == Monster[i15].x && MajorRole.y == Monster[i15].y &&page_stage==GAME_PAGE)
    			{
    				if(MajorRole.hp != 0 && iscracked == 0 )
    				{
    					MajorRole.hp--;
    					iscracked = 200;
					}
				}
			}
			
			//结束判断事件 
				if(page_stage==GAME_PAGE && Map[MajorRole.x][MajorRole.y] == END)
				{
						ShiftPageTo(END_PAGE);
   	 					int result = MessageBox(NULL, "\t!!!!!!! W  I  N !!!!!!!!\n\n\t是 否 保 存 地 图 ", "胜利", MB_YESNO);
    
    					if (result == IDYES)
    					{
        						if(saveMap())
        						{
        							int re = MessageBox(NULL, "\n\t保 存 成 功 ", "成功", MB_OK);
        				
								}
								else
								{
									int re1 = MessageBox(NULL, "\n\t保 存 失 败", "重试", MB_OK);
								}
								ShiftPageTo(MAIN_PAGE);
							

    					}
    					else if (result == IDNO)
    					{
        					ShiftPageTo(MAIN_PAGE);
    					}
					
					
				}
				
				if(MajorRole.hp == 0 && page_stage==GAME_PAGE)
				{		
						ShiftPageTo(END_PAGE);
   	 					int result1 = MessageBox(NULL, "\t再 接 再 厉 ！\n\n\t是 否 保 存 地 图 ", "失利", MB_YESNO);
    
    					if (result1 == IDYES)
    					{
        					if(saveMap())
        					{
        						int re = MessageBox(NULL, "\n\t保 存 成 功 ", "成功", MB_OK);
        						
							}
							else
							{
								int re1 = MessageBox(NULL, "\n\t保 存 失 败", "重试", MB_OK);
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
			}
				
        break;
}

}
