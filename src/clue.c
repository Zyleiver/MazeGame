#include"MyHeader.h"

Pallway AllHead = NULL;
Pallway Alltail;

extern Map[100][100]; 

Pallway pvisiter = NULL; 

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
	
	pvisiter = NULL;
	//�������� 
	Pallway p1, p2;
	pWay p3, p4;
	p1 = AllHead;
	if(AllHead == NULL)
		p2 = NULL;
	else
		p2 = AllHead->Next;
		
	while(p2 != NULL)
	{
		p1->Next = p2->Next;
		//
		p3 = p2->ThisWay;
		if(p2->ThisWay == NULL)
			p4 = NULL;
		else
			p4 = p2->ThisWay->next;
		
		while(p4 != NULL)
		{
			p3->next = p4->next;
			free(p4);
			p4 = p3->next;
		}
		if(p2->ThisWay != NULL)
		{
			p2->ThisWay = NULL;
			free(p3);	
		}
		//
		free(p2);
		p2 = p1->Next;
	}
	
	if(AllHead != NULL)
	{
		AllHead = NULL;
		//
		p3 = p1->ThisWay;
		if(p1->ThisWay == NULL)
			p4 = NULL;
		else
			p4 = p1->ThisWay->next;
		
		while(p4 != NULL)
		{
			p3->next = p4->next;
			free(p4);
			p4 = p3->next;
		}
		if(p1->ThisWay != NULL)
		{
			p1->ThisWay = NULL;
			free(p3);	
		}
		//
		free(p1);	
	}
	//�������
	
	 
    header = 1; tailer = 1;

    //��ʼ���յ㡢�������顢��ʱ�ڵ�
    int finalx = MZX, finaly = MZY;
    int visit[100+4][100+4] = {0};
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
	head1 = NULL;
	tail1 = head1;
    f(tailer - 1);

    //����allway��·����
    Alltail = AllHead;
    Pallway tempq;
    tempq = (Pallway)malloc(sizeof(struct AllWay));
    tempq->ThisWay = head1;
    tempq->Next = NULL;
    if(AllHead==NULL)
        AllHead = tempq;
    else 
        Alltail->Next = tempq;

        Alltail = tempq;
	
	//�ҵ��ⷵ��1 
    return 1;

}

//ʹ�������������DFS
int dir[4][4] = {{2,0,1,0},{-2,0,-1,0},{0,2,0,1},{0,-2,0,-1}};

int visiter[100+4][100+4] = {0};

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

//�ݹ����� 
void dfs(int x, int y)
{
    if(visiter[MZX+1][MZY+1]==1)
    {
        solution ++;
		
		pWay dpthisheader = NULL;
		pWay dpthistailer;
		dpthistailer = dpthisheader;
		
        for(i1 = 0; i1<=top;i1++)
        {
            pWay tt = (pWay)malloc(sizeof(struct Way));
            tt->x = s[i1].x;
            tt->y = s[i1].y;
            tt->next = NULL;

            if(dpthisheader == NULL)
                dpthisheader = tt;
            else 
				dpthistailer->next = tt;
				
                dpthistailer = tt;
        }
        
        Pallway temdp = (Pallway)malloc(sizeof(struct AllWay));
        temdp->ThisWay = dpthisheader;
        temdp->Next = NULL;
        temdp->last = NULL;
        
        if(AllHead == NULL)
        	AllHead = temdp;
        else
        {
        	temdp->last = Alltail;
        	Alltail->Next = temdp;
		}
        	
        	
        	Alltail = temdp;

		
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
               
				int temi1 = i1;
				int temtxdp = txdp;
				int temtydp = tydp;
                dfs(txdp,tydp);
                txdp = temtxdp;
                tydp = temtydp;
                
                i1 = temi1;

                visiter[txdp+1][tydp+1]=0;
                top--;
            }

        }
}

//��·���� 
int find_way_all(int curx, int cury)
{

    //�����ʼ��
    pvisiter = NULL;
    for(i1 = 0; i1<MZX+4 ; i1++)
    {
        for(i2 = 0; i2<MZY+4 ; i2++)
        {
            visiter[i1][i2] = 0;
        }
    }
    top = 0;
    solution =0;

    //�������� 
	Pallway p1, p2;
	pWay p3, p4;
	p1 = AllHead;
	if(AllHead == NULL)
		p2 = NULL;
	else
		p2 = AllHead->Next;
		
	while(p2 != NULL)
	{
		p1->Next = p2->Next;
		//
		p3 = p2->ThisWay;
		if(p2->ThisWay == NULL)
			p4 = NULL;
		else
			p4 = p2->ThisWay->next;
		
		while(p4 != NULL)
		{
			p3->next = p4->next;
			free(p4);
			p4 = p3->next;
		}
		if(p2->ThisWay != NULL)
		{
			p2->ThisWay = NULL;
			free(p3);	
		}
		//
		free(p2);
		p2 = p1->Next;
	}
	
	if(AllHead != NULL)
	{
		AllHead = NULL;
		//
		p3 = p1->ThisWay;
		if(p1->ThisWay == NULL)
			p4 = NULL;
		else
			p4 = p1->ThisWay->next;
		
		while(p4 != NULL)
		{
			p3->next = p4->next;
			free(p4);
			p4 = p3->next;
		}
		if(p1->ThisWay != NULL)
		{
			p1->ThisWay = NULL;
			free(p3);	
		}
		//
		free(p1);	
	}
	//�������
	
	printf("1\n");
    //����ʼ��
    visiter[curx+1][cury+1] = 1;
    s[0].x = curx;
    s[0].y = cury;
    
    //��ʼ�ݹ�
    printf("2\n");
    dfs(curx,cury);
    printf("3\n");
    
    if(solution==0) return 0 ;
    else return 1;
    
}


int next_move(void)
{
    //���ù��Ѻ��������·��������
    find_way_shortest(MajorRole.x, MajorRole.y);
    //��displayʱֻ��ʾ��һ��
}


