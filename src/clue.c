#include"MyHeader.h"

#define MZX 35
#define MZY 35

Pallway Allhead = NULL;
Pallway Alltail;

extern Map[100][100];

struct listnote
{
        int x;
        int y;
        int father;
};

	//���·����ı� 
    pWay head1 = NULL;
    pWay tail1;
    
    //�������
    struct listnote queue[10000];
    int header = 1, tailer = 1, i1,i2;

void f(int t)
{
    if(t==0) return;
    f(queue[t].father);
	
printf("%d %d\n",queue[t].x,queue[t].y);//���в��Ե� 
	
	//�����·���⣨���ѽ�����洢 
    pWay p;
    p = (pWay)malloc(sizeof(struct Way));
    p->x = queue[t].x;
    p->y = queue[t].y;
    p->next = NULL;
    if(head1==NULL)
        head1 = p;
    else 
        tail1->next = p;

        tail1 = p;
}

//ʹ�ù����������BFS
int find_way_shortest(int curx,int cury)
{
    //���·������
    Pallway tempp1 = Allhead;
    while(tempp1 != NULL)
    {
        pWay temppp1 = Allhead->ThisWay;
        while (temppp1 != NULL)
        {
            Allhead->ThisWay = temppp1->next;
            free(temppp1);
            temppp1 = Allhead->ThisWay;
        }
        Allhead = tempp1->Next;
        free(tempp1);
        tempp1 = Allhead->Next;
    }
    tempp1 = Allhead = NULL;

    

    //

    header = 1; tailer = 1;

    //��ʼ���յ㡢�������顢��ʱ�ڵ�
    int finalx = MZX, finaly = MZY;
    int visit[MZX+4][MZY+4] = {0};
    int tx,ty, txwall, tywall;
    
    //��ʼ������
    int next[4][4] = {{0,2,0,1},{2,0,1,0},{-2,0,-1,0},{0,-2,0,-1}};

    //��ʼ����㲢��ʹ������
    queue[tailer].x = curx;
    queue[tailer].y = cury;
    queue[tailer].father = 0;
    visit[curx+1][cury+1] = 1;
    tailer++;
	
    //�����ж��Ƿ��н�
    int flag = 0;
    
    //̽·���� 
    while(header<tailer)
    {
        //��̽�ĸ�����
        for(i1 = 0; i1<=3; i1++)
        {
        	//�÷��������ڵĵ�Ԫ�� 
            tx = queue[header].x + next[i1][0];
            ty = queue[header].y + next[i1][1];
			
			//�����жϸ÷������Ƿ���ǽ 
            txwall = queue[header].x + next[i1][2];
            tywall = queue[header].y + next[i1][3];
		

            if(visit[tx+1][ty+1]==0 && Map[txwall][tywall] ==ROAD)
            {
            	//�������������µ�Ԫ��� 
                visit[tx+1][ty+1]=1;
                queue[tailer].x = tx;
                queue[tailer].y = ty;
                queue[tailer].father = header;
                
                //β����� 
                tailer++;
            }
            
            //�ж��Ƿ���Ҫ��ֹ
            if(visit[MZX+1][MZY+1] == 1)
            {
                flag = 1;//�ҵ����·��
                break;
            }
            
        }
        //�ҵ����˳�
        if(flag == 1) break;

		//���׳���ͷ����� 
        header++;

    }

	//�޽⣬����0 
    if(flag == 0) return 0;
	
	//�ݹ�洢���·���� 
	tail1 = head1;
    f(tailer - 1);

    //����allway��·����
    Alltail = Allhead;
    Pallway tempq;
    tempq = (Pallway)malloc(sizeof(struct AllWay));
    tempq->ThisWay = head1;
    tempq->Next = NULL;
    if(Allhead==NULL)
        Allhead = tempq;
    else 
        Alltail->Next = tempq;

        Alltail = tempq;



    //������ 
    pWay q = head1;
    while(q!=NULL)
    {
    	printf("%d %d\n",q->x,q->y);
       	int i8,j8; 
    	for(i8 = MZX+1;i8>=0;i8--)
    	{
    		for(j8 = 0;j8<=MZY+1;j8++)
    		{
    			if(Map[j8][i8]==ROAD)
    			printf("   ");
    			if(Map[j8][i8]==WALL)
    			printf(" # ");
    			if(Map[j8][i8]==COIN)
    			printf(" O ");
    			if(Map[j8][i8]==END)
    			printf(" w ");
    			if(Map[j8][i8]==START)
    			printf(" S ");
			}
			printf("\n");
		}
    	
    	Map[q->x][q->y] = ROAD;
    	q = q->next;
    	Map[q->x][q->y] = START;
    	getchar();
	}
	//���Խ��� 
	
	//�ҵ��ⷵ��1 
    return 1;

}

//ʹ�������������DFS
int dir[4][4] = {{2,0,1,0},{-2,0,-1,0},{0,2,0,1},{0,-2,0,-1}};

int visiter[MZX+4][MZY+4] = {0};

int txdp,tydp,txdpwall,tydpwall;

typedef struct depthlist{
    int x;
    int y;
} dplist;

dplist s[10000];

int top = 0;
int solution = 0;

Pallway dpalltail;
pWay dpthistail;


void dfs(int x, int y)
{
    if(visiter[x+1][y+1]==1)
    {
        solution ++;

        Pallway dpthishead = (Pallway)malloc(sizeof(struct AllWay));

        for(i1 = 0; i1<=top;i1++)
        {
            pWay tt = (pWay)malloc(sizeof(struct Way));
            tt->x = s[i1].x;
            tt->y = s[i1].y;
            tt->next = NULL;

            if(dpthishead->ThisWay == NULL)
                dpthishead->ThisWay = tt;
            else dpthistail->next = tt;

                dpthistail = tt;
        }

        dpthishead->Next = NULL;

        if(Allhead == NULL)
            Allhead = dpthishead;
        else dpalltail->Next = dpthishead;

            dpalltail = dpthishead;

        return;
    }

    for(i1 = 0; i1<=3; i1++)
        {
        	//�÷��������ڵĵ�Ԫ�� 
            txdp = x + dir[i1][0];
            tydp = y + dir[i1][1];
			
			//�����жϸ÷������Ƿ���ǽ 
            txdpwall = x + dir[i1][2];
            tydpwall = y + dir[i1][3];
		
            if(visiter[txdp+1][tydp+1]==0 && Map[txdpwall][tydpwall] == ROAD)
            {
            	//�������������µ�Ԫ��� 
                visiter[txdp+1][tydp+1]=1;
                top++;
                s[top].y = tydp;
                s[top].x = txdp;
                
                dfs(txdp,tydp);

                visiter[txdp+1][tydp+1]=0;
                top--;
            }

        }
}


int find_way_all(int curx, int cury)
{

    //�����ʼ��
    for(i1 = 0; i1<MZX+4 ; i1++)
    {
        for(i2 = 0; i2<MZY+4 ; i2++)
        {
            visiter[i1][i2] = 0;
        }
    }
    top = 0;
    solution =0;

    //���·������
    Pallway tempp1 = Allhead;
    while(tempp1 != NULL)
    {
        pWay temppp1 = Allhead->ThisWay;
        while (temppp1 != NULL)
        {
            Allhead->ThisWay = temppp1->next;
            free(temppp1);
            temppp1 = Allhead->ThisWay;
        }
        Allhead = tempp1->Next;
        free(tempp1);
        tempp1 = Allhead->Next;
    }
    tempp1 = Allhead = NULL;
    
    //����ʼ��
    visiter[curx+1][cury+1] = 1;
    s[0].x = curx;
    s[0].y = cury;

    dpalltail = Allhead;
    dpthistail = Allhead->ThisWay;
    //��ʼ�ݹ�
    dfs(curx,cury);
    
    if(solution==0) return 0 ;
    else return 1;
    
}


int next_move(int curx,int cury)
{
    //���ù��Ѻ��������·��������
    find_way_shortest(curx, cury);
    display();
    //��displayʱֻ��ʾ��һ��
}
