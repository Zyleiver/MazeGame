#include"MyHeader.h"

Pallway Allhead;

//·���ڵ�
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
    int header = 1, tailer = 1, i1;

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

		//���׳���ͷ����� 
        header++;

    }

	//�޽⣬����0 
    if(flag == 0) return 0;
	
	//�ݹ�洢���·���� 
	tail1 = head1;
    f(tailer - 1);
    
    
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
int find_way_all(int curx, int cury)
{
    
}


int next_move(int curx,int cury)
{
    
}
