#include "MyHeader.h"

int MZX;
int MZY;
	
//ѭ������Ⱥ 
int i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14;

//�������ѡ��δ���ʷ���Ĺ����У����������
int rnum;
//�������ѡ��δ���ʷ���Ĺ����У���Ŷ�Ӧ�����ŷ��������
int rnumx,rnumy;

int monsternum;

//�������Թ������㷨���жϷ����Ƿ񱻷��ʹ�
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


//******�Զ������Թ�����******//
void CreateNewMap(void)
{
    //��ͼ�ָ�ԭʼ״̬Ϊ������׼��
    for (i12 = 0; i12 < 100; i12++)
    {
        for(i13 = 0; i13 < 100; i13++)
        {
            Map[i12][i13] = ROAD;
        }
    }
    

    //ȫͼ�����һȦ����Ϊǽ������ǰ�˲���ʾ������ֻ�Ǳ����㷨ʵ�֣���ȥ���۱߽����
    for(i1 = 0; i1<=MZX+1; i1++)
    {
        Map[i1][0] = WALL;
        Map[i1][MZY+1] = WALL;
    }
    
    for(i1 = 0; i1<=MZY+1; i1++)
    {
        Map[0][i1] = WALL;
        Map[MZX+1][i1] = WALL;
    }


    //��ʼ��ROAD��WALL���������У���֤ÿ��ROAD���������ĸ�������WALL
    for(i2 = 2; i2<=MZX-1; i2=i2 + 2)
    {
        for(i3 = 1; i3<=MZY; i3++)
        {
            Map[i2][i3] = WALL; //���Թ���������WALL
        }
    }

    for(i4 = 2; i4<=MZY-1; i4=i4 + 2)
    {
        for(i5 = 1; i5<=MZX; i5++)
        {
            Map[i5][i4] = WALL; //���Թ���������WALL
        }
    }
    //�Թ��ʼʱ�����˶�ΪROAD������ֻ��Ҫ���ó�ʼWALL����

    //��ʼ�������з�����Ϊδ����
    int visit[100+4][100+4];
    for(i10 = 0;i10<=MZX+3;i10++)
    {
    	for(i11 = 0;i11<=MZY+3;i11++)
    	{
    		visit[i10][i11] = NO;
		}
	}
    //visit[x+1][y+1]�������ж�ROAD�����Ƿ񱻷��ʹ������飬x��yΪ��������
    //+1�Ƿ�ֹ�·�visit�жϹ��̱߽����




    //�Թ��ӣ�1��1����ʼ����MZX��MZY������
    Map[1][1] = START;
    Map[MZX][MZY] = END;

    //vnum ��visitnumber,��¼���ʹ���ROAD(����END��START)������Ŀ���ﵽ��ʼ��ROAD��Ŀroadnumʱ��maze�������
    int vnum = 0; 
    int roadnum = (MZX+1)*(MZY+1)/4;
    
    
    struct nonvisit *head;
    struct nonvisit *p;
    struct nonvisit *tail;
    head = tail = NULL;

    //����һ����������ά��δ���ʷ���ı�
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

    //���ȷ�����㣨1��1��
    visit[1+1][1+1]=YES;
    printf("%d",visit[2][2]);
    vnum++;
    head = head->next;
    p = head;
    //ɾ��δ���ʱ��е���㷽��

	srand(time(0));
    //prim�㷨�����Թ�������ͼ
    while (vnum<roadnum)
    {
        //���ѡ��һ��δ���ʹ�����������ͨ·��ӵķ�����������ͨ·
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
                //�Ϸ����������δ���ʱ��г�ȡ��һ������
                //��ֱ����p�ƶ���������λ����Ϊ�˱���֮��ɾ������

                //�·������жϸ÷����Ƿ��뵱ǰͨ·���������������ͨǽ����¼���������δ���ʱ���ɾȥ
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
        
        p = head;   //�ɹ���ͨ·��չ��Ϊp�Ƶ���ͷΪ��һ��ѭ����׼��

        //��vnum����roadnumʱ��˵�����г�ʼ����ROAD���Ѿ������ʹ��ˣ�Ҳ����ζ���Թ�������ͼ�������
    }//�˳�ѭ��


	//�����ǽ�Ż��Թ������㷨 
	int randwallbreakx, randwallbreaky, randwallbreaknum;
	srand(time(0));
	for(randwallbreaknum = 0; randwallbreaknum <= MZX || randwallbreaknum <= MZY;)
	{
		randwallbreakx = rand()%(MZX) + 1;
		randwallbreaky = rand()%(MZY) + 1;
		
		if(Map[randwallbreakx][randwallbreaky] == WALL)
		{
			Map[randwallbreakx][randwallbreaky] = ROAD;
			 randwallbreaknum++;
		}	
	}
	for(randwallbreaknum = 0; randwallbreaknum <= 3; )
	{
		randwallbreakx = rand()%(MZX) + 1; 
		randwallbreaky = rand()%(MZY) + 1;
		
		if(Map[randwallbreakx][randwallbreaky] == WALL && randwallbreakx>MZX-5 && randwallbreaky>MZY-5)
		{
			randwallbreaknum ++;
			Map[randwallbreakx][randwallbreaky] = ROAD;
		}
	}
    //�����Թ���������������ɣ�����ڶ�ά����Map�У�ֻ��WALL��ROAD
    //��ע��Map����ʵ��Ҫ���������ݽ�Ϊ[1][1]��[MZX][MZY]
    //�յ�λ��[MZX][MZY],���λ��[1][1]��������Ҫ���Ը�����λ�û��ߵ�ͼ��С


    //����Ϊ������ޡ���ҳ�ʼ��
    GameInit();
    
    	//���Ե� 
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
		//���Խ��� 
}



//******������ޡ�����Զ���ʼ��******//
void GameInit(void)
{
    i6=0;

    //����״̬��ʼ��
    MajorRole.hp = 3;
    MajorRole.x = 1;
    MajorRole.y = 1;



    //�������״̬��ʼ��
    int coinx, coiny;
    
    srand(time(0));
    while(i6<3)
    {
        coinx = rand()%(MZX)+1;
        coiny = rand()%(MZY)+1;
        if((coinx>=MZX*3/5 && coiny>=MZY*2/5) && (coinx<MZX-1 && coiny<MZY-1) && (Map[coinx][coiny] == ROAD))
        {
            if(coinx%2!=0 && coiny%2!=0)
            {
                Map[coinx][coiny] = COIN;
                i6++;
            }
        }
    }//��������ھ�����ʵ�ROAD��

    //��ֻ����״̬��ʼ��
    if(monsternum > 0)
  	Monster[0].hp = 100;

    while (1)
    {
        Monster[0].x = rand()%(MZX)+1;
        Monster[0].y = rand()%(MZY)+1;
        if((Monster[0].x>=MZX/3 || Monster[0].y>=MZY/3) && (Monster[0].x<=4*MZX/5 || Monster[0].y<=4*MZY/5) && (Map[Monster[0].x][Monster[0].y] == ROAD))
        {
            if(Monster[0].x%2!=0 && Monster[0].y%2!=0)
            break;
        }
    }

    if(monsternum > 1)
    Monster[1].hp = 100;

    while (1)
    {
        Monster[1].x = rand()%(MZX)+1;
        Monster[1].y = rand()%(MZY)+1;
        if((Monster[1].x>=MZX/3 || Monster[1].y>=MZY/3) && (Monster[1].x<=4*MZX/5 || Monster[1].y<=4*MZY/5) && (Map[Monster[1].x][Monster[1].y] == ROAD))
        {
            if(fabs(Monster[1].x-Monster[0].x)>MZX/4 || fabs(Monster[1].y-Monster[0].y)>MZY/4)
            {
                if(Monster[1].x%2!=0 && Monster[1].y%2!=0)
                break;
            }
        }
    }
    
    if(monsternum > 2)
    Monster[2].hp = 100;
    
    while (1)
    {
    	
        Monster[2].x = rand()%(MZX)+1;
        Monster[2].y = rand()%(MZY)+1;
        if((Monster[2].x>=MZX/3 || Monster[2].y>=MZY/3) && (Monster[2].x<=4*MZX/5 || Monster[2].y<=4*MZY/5) && (Map[Monster[2].x][Monster[2].y] == ROAD))
        {
            if(fabs(Monster[2].x-Monster[0].x)>MZX/4 || fabs(Monster[2].y-Monster[0].y)>MZY/4)
            {
                if(fabs(Monster[2].x-Monster[1].x)>MZX/4 || fabs(Monster[2].y-Monster[1].y)>MZY/4)
                {
                    if(Monster[2].x%2!=0 && Monster[2].y%2!=0)
                    break;
                }
            }
        }
    }
    //������������ʵ���Χ���ƶ�
    
    
}


//******�ֶ����ɵ�ͼ******//
void BuildMap(void)
{
    
}

int iscracked=0;
void myTimerEvent(int timerID)
{
    switch (timerID)
    {
    	case MonsterTimer:
            if(Monster[0].hp != 100) break;
            
            for(i14 = 0;i14 < 3;i14 ++)
            {
            	int ifforwardplayer = rand()%10;
            	int monstermoverand = rand()%2;
            	
                if(ifforwardplayer<8)//������
                {
                    if(monstermoverand)//��y����x
                    {
                        if(MajorRole.x > Monster[i14].x)//���������߸�
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
                    if(monstermoverand)//��y����x
                    {
                        if(MajorRole.x > Monster[i14].x)//���������߸�
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
                        if(MajorRole.y > Monster[i14].y)
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
            display();
            break;
    	case GameTouchTimer:
    		
            break;
        default:
        	break;

    }
}
