#include "MyHeader.h"

//��ʱ�����Զ����ɵ�ͼʱ������������
Charactor Monster1;
Charactor Monster2;
Charactor Monster3;
	
//ѭ������Ⱥ 
int i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11;

//�������ѡ��δ���ʷ���Ĺ����У����������
int rnum;
//�������ѡ��δ���ʷ���Ĺ����У���Ŷ�Ӧ�����ŷ��������
int rnumx,rnumy;

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
    int visit[MZX+4][MZY+4];
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

    //���ȷ�����㣨1��1��
    visit[1+1][1+1]=YES;
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

    //�����Թ���������������ɣ�����ڶ�ά����Map�У�ֻ��WALL��ROAD
    //��ע��Map����ʵ��Ҫ���������ݽ�Ϊ[1][1]��[17][17]
    //�յ�λ��[17][17],���λ��[1][1]��������Ҫ���Ը�����λ�û��ߵ�ͼ��С

    //������ͼ
    display();

    //����Ϊ������ޡ���ҳ�ʼ��
    GameInit();
    
    //���Ե㣬��ɾȥ
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
		getchar();
    //���Ե����
}



//******������ޡ�����Զ���ʼ��******//
void GameInit(void)
{
    i6=0;

    //����״̬��ʼ��
    MajorRole.hp = 3;
    MajorRole.x = 1;
    MajorRole.y = 1;

    //��������
    display();

    //�������״̬��ʼ��
    int coinx, coiny;
    
    srand(time(0));
    while(i6<3)
    {
        coinx = rand()%(MZX)+1;
        coiny = rand()%(MZY)+1;
        if((coinx>=MZX/3 || coiny>=MZY/3) && (coinx<=4*MZX/5 || coiny<=4*MZY/5) && (Map[coinx][coiny] == ROAD))
        {
            Map[coinx][coiny] = COIN;
            i6++;
        }
    }//��������ھ�����ʵ�ROAD��

    //��ֻ����״̬��ʼ��
    Monster1.hp = 100;
    while (1)
    {
        Monster1.x = rand()%(MZX)+1;
        Monster1.y = rand()%(MZY)+1;
        if((Monster1.x>=MZX/3 || Monster1.y>=MZY/3) && (Monster1.x<=4*MZX/5 || Monster1.y<=4*MZY/5) && (Map[Monster1.x][Monster1.y] == ROAD))
        {
            break;
        }
    }

    Monster2.hp = 100;
    while (1)
    {
        Monster2.x = rand()%(MZX)+1;
        Monster2.y = rand()%(MZY)+1;
        if((Monster2.x>=MZX/3 || Monster2.y>=MZY/3) && (Monster2.x<=4*MZX/5 || Monster2.y<=4*MZY/5) && (Map[Monster2.x][Monster2.y] == ROAD))
        {
            if(fabs(Monster2.x-Monster1.x)>MZX/4 || fabs(Monster2.y-Monster1.y)>MZY/4)
            break;
        }
    }
    
    Monster3.hp = 100;
    while (1)
    {
    	
        Monster3.x = rand()%(MZX)+1;
        Monster3.y = rand()%(MZY)+1;
        if((Monster3.x>=MZX/3 || Monster3.y>=MZY/3) && (Monster3.x<=4*MZX/5 || Monster3.y<=4*MZY/5) && (Map[Monster3.x][Monster3.y] == ROAD))
        {
            if(fabs(Monster3.x-Monster1.x)>MZX/4 || fabs(Monster3.y-Monster1.y)>MZY/4)
            {
                if(fabs(Monster3.x-Monster2.x)>MZX/4 || fabs(Monster3.y-Monster2.y)>MZY/4)
                    break;
            }
        }
    }
    //������ֻ���޵ĳ�ʼ���꣬�Ҿ����ʵ�

    //������ʼ����1��2��3
    display();

    //������������ʵ���Χ���ƶ�
    startTimer(MonsterTimer,SPEED);
    //������Ҫ��ʱ��ص����������д...
    //����Ҫ��MyHeader.h����дһ��ʱ��ص������ĸ���timeID
}


//******�ֶ����ɵ�ͼ******//
void BuildMap(void)
{
    //����Ҳ��Ҫ�õ��ص��������ж��û�ѡ���button��������
    
}
