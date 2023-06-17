#include "MyHeader.h"

int MZX;
int MZY;

int coinNum;

// ѭ������Ⱥ ,
int i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i17;

// �������ѡ��δ���ʷ���Ĺ����У����������
int rnum;
// �������ѡ��δ���ʷ���Ĺ����У���Ŷ�Ӧ�����ŷ��������
int rnumx, rnumy;

int monsternum;

// �������Թ������㷨���жϷ����Ƿ񱻷��ʹ�
typedef enum
{
    NO,
    YES
} visitYorN;

struct nonvisit
{
    int x;
    int y;
    struct nonvisit *next;
};

double Xlength;
double Ylength;
double length;
double X0;
double Y0;

//******�Զ������Թ�����******//
void CreateNewMap(void)
{
     //���ɵ�ͼ��ģ
    if (abs(xscale - yscale) < 5)
    {
        length = 160 / sqrt(xscale * yscale);
    }
    else if (xscale > yscale)
    {
        length = 180 / xscale;
    }
    else
    {
        length = 160 / yscale;
    }

    Xlength = (double)xscale * length;
    Ylength = (double)yscale * length;
    X0 = 150 - Xlength / 2;
    Y0 = 90 - Ylength / 2;
    
    CoinGet = 0;
    MajorRole.hp = 3;
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

    // ��ʼ��ROAD��WALL���������У���֤ÿ��ROAD���������ĸ�������WALL
    for (i2 = 2; i2 <= 97; i2 = i2 + 2)
    {
        for (i3 = 1; i3 <= 98; i3++)
        {
            Map[i2][i3] = WALL; // ���Թ���������WALL
        }
    }

    for (i4 = 2; i4 <= 97; i4 = i4 + 2)
    {
        for (i5 = 1; i5 <= 98; i5++)
        {
            Map[i5][i4] = WALL; // ���Թ���������WALL
        }
    }
    // �Թ��ʼʱ�����˶�ΪROAD������ֻ��Ҫ���ó�ʼWALL����

    // ��ʼ�������з�����Ϊδ����
    int visit[100 + 4][100 + 4];
    for (i10 = 0; i10 <= 103; i10++)
    {
        for (i11 = 0; i11 <= 103; i11++)
        {
            visit[i10][i11] = NO;
        }
    }
    // visit[x+1][y+1]�������ж�ROAD�����Ƿ񱻷��ʹ������飬x��yΪ��������
    //+1�Ƿ�ֹ�·�visit�жϹ��̱߽����

    // �Թ��ӣ�1��1����ʼ����MZX��MZY������
    Map[1][1] = START;
    Map[MZX][MZY] = END;

    // vnum ��visitnumber,��¼���ʹ���ROAD(����END��START)������Ŀ���ﵽ��ʼ��ROAD��Ŀroadnumʱ��maze�������
    int vnum = 0;
    int roadnum = (MZX + 1) * (MZY + 1) / 4;

    struct nonvisit *head;
    struct nonvisit *p;
    struct nonvisit *tail;
    head = tail = NULL;

    // ����һ����������ά��δ���ʷ���ı�
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

    printf("t\n");

    // ���ȷ�����㣨1��1��
    visit[1 + 1][1 + 1] = YES;
    printf("%d", visit[2][2]);
    vnum++;
    head = head->next;
    p = head;
    // ɾ��δ���ʱ��е���㷽��

    srand(time(0));
    // prim�㷨�����Թ�������ͼ
    while (vnum < roadnum)
    {
        // ���ѡ��һ��δ���ʹ�����������ͨ·��ӵķ�����������ͨ·
        while (1)
        {
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
            // �Ϸ����������δ���ʱ��г�ȡ��һ������
            // ��ֱ����p�ƶ���������λ����Ϊ�˱���֮��ɾ������

            // �·������жϸ÷����Ƿ��뵱ǰͨ·���������������ͨǽ����¼���������δ���ʱ���ɾȥ
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

        p = head; // �ɹ���ͨ·��չ��Ϊp�Ƶ���ͷΪ��һ��ѭ����׼��

        // ��vnum����roadnumʱ��˵�����г�ʼ����ROAD���Ѿ������ʹ��ˣ�Ҳ����ζ���Թ�������ͼ�������
    } // �˳�ѭ��

    // �����ǽ�Ż��Թ������㷨
    int randwallbreakx, randwallbreaky, randwallbreaknum;
    srand(time(0));
    for (randwallbreaknum = 0; (randwallbreaknum <= MZX && randwallbreaknum <= MZY) && xscale + yscale > 12;)
    {
        randwallbreakx = rand() % (MZX) + 1;
        randwallbreaky = rand() % (MZY) + 1;

        if (Map[randwallbreakx][randwallbreaky] == WALL)
        {
            Map[randwallbreakx][randwallbreaky] = ROAD;
            randwallbreaknum++;
        }
    }
    for (randwallbreaknum = 0; randwallbreaknum <= 3 && xscale + yscale > 12;)
    {
        randwallbreakx = rand() % (MZX) + 1;
        randwallbreaky = rand() % (MZY) + 1;

        if (Map[randwallbreakx][randwallbreaky] == WALL && randwallbreakx > MZX - 5 && randwallbreaky > MZY - 5)
        {
            randwallbreaknum++;
            Map[randwallbreakx][randwallbreaky] = ROAD;
        }
    }

    // �����Թ���������������ɣ�����ڶ�ά����Map�У�ֻ��WALL��ROAD
    // ��ע��Map����ʵ��Ҫ���������ݽ�Ϊ[1][1]��[MZX][MZY]
    // �յ�λ��[MZX][MZY],���λ��[1][1]��������Ҫ���Ը�����λ�û��ߵ�ͼ��С

    // ����Ϊ������ޡ���ҳ�ʼ��

    // ���״̬��ʼ��
    int coinx, coiny;

    srand(time(0));
    while (i6 < coinNum)
    {
        coinx = rand() % (MZX) + 1;
        coiny = rand() % (MZY) + 1;
        if ((coinx >= MZX / 3 || coiny >= MZY / 3) && (coinx <= 4 * MZX / 5 || coiny <= 4 * MZY / 5) && (Map[coinx][coiny] == ROAD))
        {
            if (coinx % 2 != 0 && coiny % 2 != 0)
            {
                Map[coinx][coiny] = COIN;
                i6++;
            }
        }
    } // ��������ھ�����ʵ�ROAD��

    // ������޳�ʼ��
    GameInit();
}

//******��������Զ���ʼ��******//
void GameInit(void)
{
	if (abs(xscale - yscale) < 5)
    {
        length = 160 / sqrt(xscale * yscale);
    }
    else if (xscale > yscale)
    {
        length = 180 / xscale;
    }
    else
    {
        length = 160 / yscale;
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
    MajorRole.hp = 3;
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
        	if((Monster[i12].x>=MZX/3 && Monster[i12].y>=MZY/3) && (Monster[i12].x<=4*MZX/5 || Monster[i12].y<=4*MZY/5) && (Map[Monster[i12].x][Monster[i12].y] == ROAD))
        	{
     	       if(Monster[i12].x%2!=0 && Monster[i12].y%2!=0)
     	       break;
     	    }
    	}
	}
	Monster[0].hp = 100;
    //������������ʵ���Χ���ƶ�
    
    
}

//******�ֶ����ɵ�ͼ******//
void BuildMap(void)
{
    //���ɵ�ͼ��ģ
    if (abs(xscale - yscale) < 5)
    {
        length = 160 / sqrt(xscale * yscale);
    }
    else if (xscale > yscale)
    {
        length = 180 / xscale;
    }
    else
    {
        length = 160 / yscale;
    }

    Xlength = (double)xscale * length;
    Ylength = (double)yscale * length;
    X0 = 150 - Xlength / 2;
    Y0 = 90 - Ylength / 2;

    putting = 0;
    CoinGet = 0;
    MajorRole.hp = 3;
    MajorRole.x = -10;
    MajorRole.y = -10;
    for (i12 = 0; i12 < 1000; i12++)
    {
        Monster[i12].hp = 0;
        Monster[i12].x = -20;
        Monster[i12].y = -20;
    }

    // ��ͼ�ָ�ԭʼ״̬Ϊ������׼��
    for (i12 = 0; i12 < 100; i12++)
    {
        for (i13 = 0; i13 < 100; i13++)
        {
            Map[i12][i13] = ROAD;
        }
    }

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

    // ��ʼ��ROAD��WALL���������У���֤ÿ��ROAD���������ĸ�������WALL
    for (i2 = 2; i2 <= 97; i2 = i2 + 2)
    {
        for (i3 = 1; i3 <= 98; i3++)
        {
            Map[i2][i3] = WALL; // ���Թ���������WALL
        }
    }

    for (i4 = 2; i4 <= 97; i4 = i4 + 2)
    {
        for (i5 = 1; i5 <= 98; i5++)
        {
            Map[i5][i4] = WALL; // ���Թ���������WALL
        }
    }
    // �Թ��ʼʱ�����˶�ΪROAD������ֻ��Ҫ���ó�ʼWALL����
}

void EditMap(int x, int y, int buttonusing)
{
    static int i18 = 0;

    switch (buttonusing)
    {
    case PutCoin:
        if (x % 2 != 0 && y % 2 != 0)
        {
            if(Map[x][y]==ROAD)
            {
                Map[x][y] = COIN;
            }
            
        }

        break;

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

    case Erase:
        if (Map[x][y] != ROAD && x >= 1 && y >= 1 && x <= MZX + 1 && y <= MZY + 1)
        {
            if (Map[x][y] == START)
            {
                MajorRole.hp = 3;
                MajorRole.x = -10;
                MajorRole.y = -10;
            }

            Map[x][y] = ROAD;
        }

        for (i17 = 1; i17 < 1000; i17++)
        {
            if (Monster[i17].x == x && Monster[i17].y == y)
            {
                Monster[i17].hp = 0;
                Monster[i17].x = -10;
                Monster[i17].y = -10;
            }
        }
        break;

    case PutWall:
        if (x % 2 == 1 || y % 2 == 1)
        {
            Map[x][y] = WALL;
        }
        break;

    case Complete:
        Monster[0].hp = 100;
        ShiftPageTo(GAME_PAGE);
        break;
    }
}

int iscracked = 0;
void myTimerEvent(int timerID)
{
    switch (timerID)
    {
    case MonsterTimer:
        if (Monster[0].hp != 100 || page_stage != GAME_PAGE)
            break;

       for(i14 = 1;i14 <= monsternum;i14 ++)
            {
            	int ifforwardplayer = rand()%10;
            	int monstermoverand = rand()%2;
                if(ifforwardplayer<8)//������
                {
                    if(monstermoverand)//��y����x
                    {
                        if(MajorRole.x>Monster[i14].x)//���������߸�
                        {
                            
							if(Map[Monster[i14].x+1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x++;
                                Monster[i14].x++;
                            }else{
                            	//
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
								// 
							}
                        }
                        else
                        {	
                        	
                            if(Map[Monster[i14].x-1][Monster[i14].y]!=WALL)
                            {
                                Monster[i14].x--;
                                Monster[i14].x--;
                            }else{
                            	//
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
                            	//
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
                        	else{
                        		//
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
                        		//
							}
                        }
                        else
                        {
                            if(Map[Monster[i14].x][Monster[i14].y-1]!=WALL)
                            {
                                Monster[i14].y--;
                                Monster[i14].y--;
                            }
                            else{
                            	//
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
                        		//
							}
                        }
                    }
                }
                else
                {
                    if(monstermoverand)//��y����x
                    {
                        if(MajorRole.x>Monster[i14].x)//���������߸�
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
    	    
    	    //������ײ�¼� 
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
			
			//�����ж��¼� 
				if(page_stage==GAME_PAGE && Map[MajorRole.x][MajorRole.y] == END)
				{
						ShiftPageTo(END_PAGE);
                        int result;
						if(CoinGet < coinNum)
   	 						 result = MessageBox(NULL, "\t!!!!!!! W  I  N !!!!!!!!\n\n\t�� �� �� �� �� ͼ ", "ʤ��", MB_YESNO);
    					else 
    						 result = MessageBox(NULL, "\t!!!!!!! W  I  N !!!!!!!!\n\n\t�� �� �� �� ���� �� ��\n\n\t�� �� �� �� �� ͼ ", "ʤ��", MB_YESNO);
    					
						if (result == IDYES)
    					{
        						if(saveMap())
        						{
        							int re = MessageBox(NULL, "\n\t�� �� �� �� ", "�ɹ�", MB_OK);
        				
								}
								else
								{
									int re1 = MessageBox(NULL, "\n\t�� �� ʧ ��", "����", MB_OK);
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
                        int result1;
						if(CoinGet < coinNum)
   	 						result1 = MessageBox(NULL, "\t�� �� �� �� !\n\n\t�� �� �� �� �� ͼ ", "ʧ��", MB_YESNO);
    					else 
    						result1 = MessageBox(NULL, "\t�� �� �� �� !\n\n\t�� �� �� �� �� ͼ ", "ʧ��", MB_YESNO);
    						
    					if (result1 == IDYES)
    					{
        					if(saveMap())
        					{
        						int re = MessageBox(NULL, "\n\t�� �� �� �� ", "�ɹ�", MB_OK);
        						
							}
							else
							{
								int re1 = MessageBox(NULL, "\n\t�� �� ʧ ��", "����", MB_OK);
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
				if(MajorRole.hp < 3)
					MajorRole.hp++;
			}
				
        break;
        
    /* 
    case GameTouchTimer:

        // ������ײ�¼�
        for (i15 = 1; i15 <= monsternum; i15++)
        {
            if (MajorRole.x == Monster[i15].x && MajorRole.y == Monster[i15].y && page_stage == GAME_PAGE)
            {
                if (MajorRole.hp != 0 && iscracked == 0)
                {
                    MajorRole.hp--;
                    iscracked = 200;
                }
            }
        }

        // �����ж��¼�
        if (page_stage == GAME_PAGE && Map[MajorRole.x][MajorRole.y] == END)
        {
            ShiftPageTo(END_PAGE);
            int result;
            if (CoinGet < 3)
                result = MessageBox(NULL, "\t!!!!!!! W  I  N !!!!!!!!\n\n\t�� �� �� �� �� ͼ ", "ʤ��", MB_YESNO);
            else
                result = MessageBox(NULL, "\t!!!!!!! W  I  N !!!!!!!!\n\n\t�� �� �� �� ���� �� ��\n\n\t�� �� �� �� �� ͼ ", "ʤ��", MB_YESNO);

            if (result == IDYES)
            {
                if (saveMap())
                {
                    int re = MessageBox(NULL, "\n\t�� �� �� �� ", "�ɹ�", MB_OK);
                }
                else
                {
                    int re1 = MessageBox(NULL, "\n\t�� �� ʧ ��", "����", MB_OK);
                }
                ShiftPageTo(MAIN_PAGE);
            }
            else if (result == IDNO)
            {
                ShiftPageTo(MAIN_PAGE);
            }
        }

        if (MajorRole.hp == 0 && page_stage == GAME_PAGE)
        {
            ShiftPageTo(END_PAGE);
            int result1;
            if (CoinGet < 3)
                result1 = MessageBox(NULL, "\t�� �� �� �� !\n\n\t�� �� �� �� �� ͼ ", "ʧ��", MB_YESNO);
            else
                result1 = MessageBox(NULL, "\t�� �� �� �� !\n\n\t�� �� �� �� �� ͼ ", "ʧ��", MB_YESNO);

            if (result1 == IDYES)
            {
                if (saveMap())
                {
                    int re = MessageBox(NULL, "\n\t�� �� �� �� ", "�ɹ�", MB_OK);
                }
                else
                {
                    int re1 = MessageBox(NULL, "\n\t�� �� ʧ ��", "����", MB_OK);
                }
                ShiftPageTo(MAIN_PAGE);
            }
            else if (result1 == IDNO)
            {
                ShiftPageTo(MAIN_PAGE);
            }
        }

        // �����ײ�¼�
        if (Map[MajorRole.x][MajorRole.y] == COIN && page_stage == GAME_PAGE)
        {
            Map[MajorRole.x][MajorRole.y] = COINGOT;
            CoinGet++;
        }

        break;
        */ 
    }
}
