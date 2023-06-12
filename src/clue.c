#include"MyHeader.h"

Pallway Allhead;

//路径节点
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
    int header = 1, tailer = 1, i1;

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

		//队首出队头标后移 
        header++;

    }

	//无解，返回0 
    if(flag == 0) return 0;
	
	//递归存储最短路径解 
	tail1 = head1;
    f(tailer - 1);
    
    
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
int find_way_all(int curx, int cury)
{
    
}


int next_move(int curx,int cury)
{
    
}
