#include"MyHeader.h"

extern Map[100][100]; 		//地图 

int finalx; 				//终点坐标x
int finaly;					//终点坐标y 
int solution;				//记录解数变量 

Pallway pvisiter = NULL; 	//查找指针 
Pallway AllHead = NULL;		//所有解的头指针 
Pallway Alltail;			//所有解的尾指针 



//最短路径解的中介表 
pWay head1 = NULL;
pWay tail1;
//申请队列相关变量 
int header;
int tailer;
int i1,i2;
struct listnote
{
        int x;
        int y;
        int father;
};
struct listnote queue[10000];



//求全部解算法内部判断相关变量 
int dir[4][4] = {{2,0,1,0},{-2,0,-1,0},{0,2,0,1},{0,-2,0,-1}};
int visiter[100+4][100+4];
int txdp,tydp,txdpwall,tydpwall;
//申请堆栈相关变量 
int top;
struct depthlist{
    int x;
    int y;
};
struct depthlist s[10000];



//****************************清理链表模块*********************************//

//清理链表函数 （二级） 
pWay clear_Way(pWay way) 
{
    if (way == NULL) 
	{
        return NULL;
    }
    way->next = clear_Way(way->next);
    way->next = NULL;
    free(way);
    return NULL;
}

//清理链表函数（一级） 
Pallway clear_AllWay(Pallway allway) 
{
    if (allway == NULL) 
	{
        return NULL;
    }
    allway->ThisWay = clear_Way(allway->ThisWay);
    allway->Next = NULL;
    free(allway);
    return NULL;
}



//****************************求最优解模块*********************************//

//最优解存储函数
void fbfs(int t)
{
    if(t==0) return;
    fbfs(queue[t].father); 
	
	//将最短路径解（广搜解出）存入中介表 
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

//求最优解 BFS主体函数 
int find_way_shortest(int curx,int cury)
{
	
	pvisiter = NULL;
	
	//清理链表 
	AllHead = clear_AllWay(AllHead);
	//清理结束
	
	 
    header = 1; tailer = 1;

    //初始化终点、访问数组、临时节点
    for(i1 = 0; i1<100 ; i1++)
    {
        for(i2 = 0; i2<100 ; i2++)
        {
        	if(Map[i1][i2] == END)
            {
            	finalx = i1;
            	finaly = i2;
			}
        }
    }
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
            if(visit[finalx+1][finaly+1] == 1)
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
    fbfs(tailer - 1);

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



//****************************求全部解模块*********************************//

//DFS判断递归主体函数 
void dfs(int x, int y)
{
    if(visiter[MZX+1][MZY+1]==1)
    {
    	
        solution ++;
        		
		pWay dpthisheader = NULL;
		pWay dpthistailer;
		dpthistailer = dpthisheader;
		
		int ij;
        for(ij = 0; ij<=top;ij++)
        {
            pWay tt = (pWay)malloc(sizeof(struct Way));
            tt->x = s[ij].x;
            tt->y = s[ij].y;
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

//求全部解 DFS主体函数 
int find_way_all(int curx, int cury)
{
	
    //清理初始化
    pvisiter = NULL;
    for(i1 = 0; i1<104 ; i1++)
    {
        for(i2 = 0; i2<104 ; i2++)
        {
            visiter[i1][i2] = 0;
        }
    }
    top = 0;
    solution =0;

	for(i1 = 0; i1<100 ; i1++)
    {
        for(i2 = 0; i2<100 ; i2++)
        {
        	if(Map[i1][i2] == END)
            {
            	finalx = i1;
            	finaly = i2;
			}
        }
    }
    
    //清理链表 
	AllHead = clear_AllWay(AllHead);
	//清理结束
	
    //起点初始化
    visiter[curx+1][cury+1] = 1;
    s[0].x = curx;
    s[0].y = cury;
    
    //开始递归
    dfs(curx,cury);
    
    
	pvisiter = AllHead;
		
    if(solution == 0) 
		return 0;
    else 
		return 1;
    
}



//****************************求下一步模块*********************************// 
int next_move(void)
{
    //调用广搜函数（最短路径函数）
    find_way_shortest(MajorRole.x, MajorRole.y);
    //但display时只显示下一步
}
