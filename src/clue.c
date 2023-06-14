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
    //清空路径链表
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

    //初始化终点、访问数组、临时节点
    int finalx = MZX, finaly = MZY;
    int visit[MZX+4][MZY+4] = {0};
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
	tail1 = head1;
    f(tailer - 1);

    //存入allway总路径表
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



    //测试用 
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
	//测试结束 
	
	//找到解返回1 
    return 1;

}

//使用深度优先搜索DFS
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
                
                dfs(txdp,tydp);

                visiter[txdp+1][tydp+1]=0;
                top--;
            }

        }
}


int find_way_all(int curx, int cury)
{

    //清理初始化
    for(i1 = 0; i1<MZX+4 ; i1++)
    {
        for(i2 = 0; i2<MZY+4 ; i2++)
        {
            visiter[i1][i2] = 0;
        }
    }
    top = 0;
    solution =0;

    //清空路径链表
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
    
    //起点初始化
    visiter[curx+1][cury+1] = 1;
    s[0].x = curx;
    s[0].y = cury;

    dpalltail = Allhead;
    dpthistail = Allhead->ThisWay;
    //开始递归
    dfs(curx,cury);
    
    if(solution==0) return 0 ;
    else return 1;
    
}


int next_move(int curx,int cury)
{
    //调用广搜函数（最短路径函数）
    find_way_shortest(curx, cury);
    display();
    //但display时只显示下一步
}
