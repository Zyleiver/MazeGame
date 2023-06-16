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

	//最短路径解的表 
    pWay head1 = NULL;
    pWay tail1;
    
    //申请队列
    struct listnote queue[10000];
    int header = 1, tailer = 1, i1,i2;

void f(int t)
{
    if(t==0) return;
    f(queue[t].father);
	
printf("%d %d\n",queue[t].x,queue[t].y);//该行测试点 
	
	//将最短路径解（广搜解出）存储 
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


//使用广度优先搜索BFS
int find_way_shortest(int curx,int cury)
{
	
	pvisiter = NULL;
	//清理链表 
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
	//清理结束
	
	 
    header = 1; tailer = 1;

    //初始化终点、访问数组、临时节点
    int finalx = MZX, finaly = MZY;
    int visit[100+4][100+4] = {0};
    int tx,ty, txwall, tywall;
    
    //初始化方向
    int next[4][4] = {{0,2,0,1},{2,0,1,0},{-2,0,-1,0},{0,-2,0,-1}};

    //初始化起点并先使起点入队
    queue[tailer].x = curx;
    queue[tailer].y = cury;
    queue[tailer].father = 0;
    visit[curx+1][cury+1] = 1;
    tailer++;
	
    //用于判断是否有解
    int flag = 0;
    
    //探路主体 
    while(header<tailer)
    {
        //试探四个方向
        for(i1 = 0; i1<=3; i1++)
        {
        	//该方向上相邻的单元格 
            tx = queue[header].x + next[i1][0];
            ty = queue[header].y + next[i1][1];
			
			//用于判断该方向上是否有墙 
            txwall = queue[header].x + next[i1][2];
            tywall = queue[header].y + next[i1][3];
		

            if(visit[tx+1][ty+1]==0 && Map[txwall][tywall] ==ROAD)
            {
            	//若满足条件则将新单元入队 
                visit[tx+1][ty+1]=1;
                queue[tailer].x = tx;
                queue[tailer].y = ty;
                queue[tailer].father = header;
                
                //尾标后移 
                tailer++;
            }
            
            //判断是否需要终止
            if(visit[MZX+1][MZY+1] == 1)
            {
                flag = 1;//找到最短路径
                break;
            }
            
        }
        //找到则退出
        if(flag == 1) break;

		//队首出队头标后移 
        header++;

    }

	//无解，返回0 
    if(flag == 0) return 0;
	
	//递归存储最短路径解 
	head1 = NULL;
	tail1 = head1;
    f(tailer - 1);

    //存入allway总路径表
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
	
	//找到解返回1 
    return 1;

}

//使用深度优先搜索DFS
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

//递归主体 
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
        	
        	//该方向上相邻的单元格 
            txdp = x + dir[i1][0];
            tydp = y + dir[i1][1];
			
			//用于判断该方向上是否有墙 
            txdpwall = x + dir[i1][2];
            tydpwall = y + dir[i1][3];
		
            if(visiter[txdp+1][tydp+1]==0 && Map[txdpwall][tydpwall] == ROAD)
            {
            	//若满足条件则将新单元入队 
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

//找路主体 
int find_way_all(int curx, int cury)
{

    //清理初始化
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

    //清理链表 
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
	//清理结束
	
	printf("1\n");
    //起点初始化
    visiter[curx+1][cury+1] = 1;
    s[0].x = curx;
    s[0].y = cury;
    
    //开始递归
    printf("2\n");
    dfs(curx,cury);
    printf("3\n");
    
    if(solution==0) return 0 ;
    else return 1;
    
}


int next_move(void)
{
    //调用广搜函数（最短路径函数）
    find_way_shortest(MajorRole.x, MajorRole.y);
    //但display时只显示下一步
}


