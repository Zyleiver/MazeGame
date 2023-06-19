#include "MyHeader.h"

int MZX;			//��ͼ�㷨�����ܳ� 
int MZY;			//��ͼ�㷨�����ܳ� 

int coinNum;		//������� 
int monsternum;		//�������� 
int endtime;		//ʤ�����㶯����ʾʱ�� 
int dietime;		//ʧ�����㶯����ʾʱ�� 
int iscracked = 0;	//�޵�ʱ����� 
int ender = 0;		//�ж�ʤ������ʧ�� 
int bubuhat = 0;	//�ɾ�ʹ�ñ��� 

double Xlength;		//Xlength=��ͼ�����ܳ� 
double Ylength;		//Ylength=��ͼ�����ܳ�
double length;		//���Ӵ�С 
double X0;			//��ͼ���½Ǻ�����
double Y0;			//��ͼ���½�������


//ѭ������Ⱥ 
int i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i17;
//�������ѡ��δ���ʷ���Ĺ����д��������� 
int rnum;
int rnumx, rnumy;
//�������Թ������㷨���жϷ����Ƿ񱻷��ʹ�
typedef enum
{
    NO,
    YES
} visitYorN;
//δ���ʱ� 
struct nonvisit
{
    int x;
    int y;
    struct nonvisit *next;
};


//****************************�Զ������Թ�ģ��*********************************//

//�Զ����ɻ�ͼ���� 
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

    // ��ͼ�ָ�ԭʼ״̬Ϊ������׼��
    for (i12 = 0; i12 < 100; i12++)
    {
        for (i13 = 0; i13 < 100; i13++)
        {
            Map[i12][i13] = ROAD;
        }
    }
    AllButtonUp();

    // ȫͼ�����һȦ����Ϊǽ������ǰ�˲���ʾ������ֻ�Ǳ����㷨ʵ�֣���ȥ���۱߽����
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

    //���Թ���������WALL
    for (i2 = 2; i2 <= 97; i2 = i2 + 2)
    {
        for (i3 = 1; i3 <= 98; i3++)
        {
            Map[i2][i3] = WALL; 
        }
    }
	//���Թ���������WALL
    for (i4 = 2; i4 <= 97; i4 = i4 + 2)
    {
        for (i5 = 1; i5 <= 98; i5++)
        {
            Map[i5][i4] = WALL; 
        }
    }

    // ��ʼ�������з�����Ϊδ����
    int visit[100 + 4][100 + 4];
    for (i10 = 0; i10 <= 103; i10++)
    {
        for (i11 = 0; i11 <= 103; i11++)
        {
            visit[i10][i11] = NO;
        }
    }

    //��������Թ�ʱѡ����㣬�յ� 
    Map[1][1] = START;
    Map[MZX][MZY] = END;
	
	//����һ����������ά��δ���ʵķ���
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
    
    //vnum��visitnumber,��¼���ʹ��ķ�������roadnumΪ��ͼ�ܹ���Ҫ���ʵķ����� 
    int vnum = 0;
    int roadnum = (MZX + 1) * (MZY + 1) / 4;

    //���Ƚ������� 
    visit[1 + 1][1 + 1] = YES;
    vnum++;
    head = head->next;
    p = head;

    // prim�㷨�����Թ�������ͼ
    srand(time(0));
    while (vnum < roadnum)
    {     
        while (1)
        {
        	//�����ȡһ��δ���ʶ��е��·���
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
            

            //�ж��·����Ƿ��뵱ǰͨ·����������������� 
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

    // �����ǽ�����Ż��Թ������㷨
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
    //�����Թ���������WALL��ROAD������ɣ�����ڶ�ά����Map��

    //��������ھ�����ʵ�ROAD��
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
	
	//���������� 
    GameInit();
}

//��������Զ���ʼ������ 
void GameInit(void)
{
	//���ɵ�ͼ��ģ 
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
    // ����״̬��ʼ��
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

    // ����״̬��ʼ��
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
	
	//����0�����ж�׼�������Ƿ���� 
	Monster[0].hp = 100;
    
}


//****************************�ֶ������Թ�ģ��*********************************//

//��ͼ��ͼ��ʼ�� 
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

    // ��ͼ�ָ�ԭʼ״̬Ϊ������׼��
    for (i12 = 0; i12 < 100; i12++)
    {
        for (i13 = 0; i13 < 100; i13++)
        {
            Map[i12][i13] = ROAD;
        }
    }
    AllButtonUp();

    // ȫͼ�����һȦ����Ϊǽ
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

    // ��ʼ��ROAD��WALL���������У���֤ÿ��ROAD���������ĸ�������WALL
    // ���Թ���������WALL
    for (i2 = 2; i2 <= 97; i2 = i2 + 2)
    {
        for (i3 = 1; i3 <= 98; i3++)
        {
            Map[i2][i3] = WALL; 
        }
    }
	
	// ���Թ���������WALL
    for (i4 = 2; i4 <= 97; i4 = i4 + 2)
    {
        for (i5 = 1; i5 <= 98; i5++)
        {
            Map[i5][i4] = WALL;
        }
    }
    
}

//�Թ��༭���� 
void EditMap(int x, int y, int buttonusing)
{
    switch (buttonusing)
    {
    //���ý�� 
  	case PutCoin:
        if (x % 2 != 0 && y % 2 != 0)
        {
            if(Map[x][y]==ROAD)
            {
                Map[x][y] = COIN;
            }
            
        }

        break;

	//���ý�ɫ 
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
	
	//�����յ� 
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

	//ʹ����Ƥ����Ԫ�� 
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

	//����ǽ 
    case PutWall:
        if (x % 2 == 1 || y % 2 == 1)
        {
            Map[x][y] = WALL;
        }
        break;

	//��ɱ༭��ʼ���� 
    case Complete:
        Monster[0].hp = 100;
        ShiftPageTo(GAME_PAGE);
        break;
    }
}


//****************************��Ϸ��̬����ģ��*********************************//

//ʱ��ص����� 
void myTimerEvent(int timerID)
{
    switch (timerID)
    {
    //�����ƶ�ʱ��ص� 
    case MonsterTimer:
    	//��֤����ֻ����Ϸʱ�ƶ�
        if (Monster[0].hp != 100 || page_stage != GAME_PAGE) 
        {
        	break;
		}
            
		//�ֱ��ÿֻ��Ϸ�й��޵�·�������ж� 
       for(i14 = 1;i14 <= monsternum;i14 ++)
        {
       			int ifforwardplayer = rand()%10;
       			int monstermoverand = rand()%2;
       			
    	        if(ifforwardplayer<8)//���������ߣ�4/5�ĸ��� 
                {
                    if(monstermoverand)//��x
                    {
                        if(MajorRole.x>Monster[i14].x)//����
                        {
                            
							if(Map[Monster[i14].x+1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x++;
                                Monster[i14].x++;
                            }else{
                            	//��x�߲�ͨ�ͳ�����y 
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
                        else//�߸� 
                        {	
                        	
                            if(Map[Monster[i14].x-1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x--;
                                Monster[i14].x--;
                            }else{
                            	//��x�߲�ͨ�ͳ�����y 
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
                    else//��y 
                    {	
                        if(MajorRole.y>Monster[i14].y)//���� 
                        {
                            if(Map[Monster[i14].x][Monster[i14].y+1]!=WALL)
                            {   
                                Monster[i14].y++;
                                Monster[i14].y++;
                            }
                        	else{
                        		//��y�߲�ͨ������x 
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
                        else//�߸� 
                        {
                            if(Map[Monster[i14].x][Monster[i14].y-1]!=WALL)
                            {
                                Monster[i14].y--;
                                Monster[i14].y--;
                            }
                            else{
                            	//��y�߲�ͨ������x 
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
                else//���������� 
                {
        
					if(monstermoverand)//��x
                    {
                        if(MajorRole.x>Monster[i14].x)//�߸�
                        {
                            if(Map[Monster[i14].x-1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x--;
                                Monster[i14].x--;
                            }
                            else//��x��ͨ�ͳ�����y 
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
                        else//���� 
                        {
                            if(Map[Monster[i14].x+1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x++;
                                Monster[i14].x++;
                            }
                            else//��x��ͨ�ͳ�����y 
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
                    else//��y 
                    {
                        if(MajorRole.y>Monster[i14].y)//�߸� 
                        {
                            if(Map[Monster[i14].x][Monster[i14].y-1]!=WALL)
                            {   
                                Monster[i14].y--;
                                Monster[i14].y--;
                            }
                            else//��y��ͨ�ͳ�����x 
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
                        else//���� 
                        {
                            if(Map[Monster[i14].x][Monster[i14].y+1]!=WALL)
                            {
                                Monster[i14].y++;
                                Monster[i14].y++;
                            }
                            else//��y��ͨ�ͳ�����x 
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
    
	//ˢ��ʱ��ص�    
    case FlashTimer:
    		if(iscracked>0)
				iscracked--;
			if(endtime > 0)
				endtime--;
			if(dietime > 0)
				dietime--;
            display();
            break;
            
    //��Ϸ����ʱ��ص� 
    case GameTouchTimer:
    	    
    	    //������ײ�¼� 
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
			
				//�����յ� 
				if(page_stage==GAME_PAGE && Map[MajorRole.x][MajorRole.y] == END)
				{
					if(ButtonEnum[PromptNextStep].stage == Button_DOWN)
						bubuhat = 1;
					ShiftPageTo(END_PAGE);
					endtime = 200;
					ender = 1;	
				}
				//��ɫʧ�� 
				if(page_stage==GAME_PAGE && MajorRole.hp == 0)
				{
					ShiftPageTo(END_PAGE);
					dietime = 100;
					ender = 2;
				}
				
				//ʤ���ɾ��жϺͱ���ѯ�� 
				if(page_stage==END_PAGE && endtime == 0 && ender == 1)
				{		
                        int result;
						if(CoinGet < coinNum || coinNum == 0)
						{
							ender = 0;
							if(MajorRole.hp == 12)
							{
								if(CoinGet == 0)
									result = MessageBox(NULL, "\t�� �� �� �� ���� � ���� �� �� ʲ ô�� \n\n\t�� �� �� �� �� ͼ ", "ʤ��", MB_YESNO);
								else if(bubuhat == 0)
									result = MessageBox(NULL, "\t�� �� �� �� ���� � ���� �� �� ��\n\n\t�� �� �� �� �� ͼ ", "ʤ��", MB_YESNO);
								else
								{
									bubuhat = 0;
									result = MessageBox(NULL, "\t�� �� �� �� ���� �� �� �� ʲ ô��\n\n\t�� �� �� �� �� ͼ ", "ʤ��", MB_YESNO);
								}
							
							}
							else if(bubuhat == 1)
							{
								bubuhat = 0;
								result = MessageBox(NULL, "\t�� �� �� �� ���� �� �� �� ʲ ô��\n\n\t�� �� �� �� �� ͼ ", "ʤ��", MB_YESNO);
							}
							else
								result = MessageBox(NULL, "\t�� �� �� �� �� ͼ ", "ʤ��", MB_YESNO);
							
						}
    					else 
    					{
    						ender = 0;
    						if(MajorRole.hp != 12)
    							result = MessageBox(NULL, "\t�� �� �� �� ���� �� ��\n\n\t�� �� �� �� �� ͼ ", "ʤ��", MB_YESNO);
							else 
								result = MessageBox(NULL, "\t�� �� �� �� ���� � ���� �� �� �� �� ��\n\n\t�� �� �� �� �� ͼ ", "ʤ��", MB_YESNO);
						}
    					
    					//������ 
						if (result == IDYES)
    					{
        						if(saveMap())
        						{
        							int re = MessageBox(NULL, "\n\t����ɹ� ", "�ɹ�", MB_OK);
								}
								else
								{
									int re1 = MessageBox(NULL, "\n\t����ʧ��", "����", MB_OK);
								}
								
								ShiftPageTo(MAIN_PAGE);
							
    					}
    					else if (result == IDNO)
    					{
        					ShiftPageTo(MAIN_PAGE);
    					}
					
					
				}
				
				//ʧ���ɾ��жϺͱ���ʱ�� 
				if(page_stage==END_PAGE && dietime == 0 && ender == 2)
				{		
						
                        int result1;
						if(CoinGet < coinNum || coinNum == 0)
						{
							ender = 0;
							if(monsternum >= 200)
								result1 = MessageBox(NULL, "\t�� �� �� �� ���� �� �� �� ��\n\n\t�� �� �� �� �� ͼ ", "ʧ��", MB_YESNO);
							else
								result1 = MessageBox(NULL, "\t�� �� �� �� !\n\n\t�� �� �� �� �� ͼ ", "ʧ��", MB_YESNO);
						}
    					else 
    					{
    						ender = 0;
    						result1 = MessageBox(NULL, "\t�� �� �� �� ���� �� �� �� ��\n\n\t�� �� �� �� �� ͼ ", "ʧ��", MB_YESNO);
						}
    					
    					//������ 
    					if (result1 == IDYES)
    					{
        					if(saveMap())
        					{
        						int re = MessageBox(NULL, "\n\t����ɹ� ", "�ɹ�", MB_OK);
        						
							}
							else
							{
								int re1 = MessageBox(NULL, "\n\t����ʧ��", "����", MB_OK);
							}
							ShiftPageTo(MAIN_PAGE);
        					
    					}
    					else if (result1 == IDNO)
    					{
        					ShiftPageTo(MAIN_PAGE);
    					}
    				
				}
				
			//�����ײ�¼�
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
