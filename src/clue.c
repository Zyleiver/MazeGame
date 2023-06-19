#include"MyHeader.h"

extern Map[100][100]; 		//��ͼ 

int finalx; 				//�յ�����x
int finaly;					//�յ�����y 
int solution;				//��¼�������� 

Pallway pvisiter = NULL; 	//����ָ�� 
Pallway AllHead = NULL;		//���н��ͷָ�� 
Pallway Alltail;			//���н��βָ�� 



//���·������н�� 
pWay head1 = NULL;
pWay tail1;
//���������ر��� 
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



//��ȫ�����㷨�ڲ��ж���ر��� 
int dir[4][4] = {{2,0,1,0},{-2,0,-1,0},{0,2,0,1},{0,-2,0,-1}};
int visiter[100+4][100+4];
int txdp,tydp,txdpwall,tydpwall;
//�����ջ��ر��� 
int top;
struct depthlist{
    int x;
    int y;
};
struct depthlist s[10000];



//****************************��������ģ��*********************************//

//���������� �������� 
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

//������������һ���� 
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



//****************************�����Ž�ģ��*********************************//

//���Ž�洢����
void fbfs(int t)
{
    if(t==0) return;
    fbfs(queue[t].father); 
	
	//�����·���⣨���ѽ���������н�� 
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

//�����Ž� BFS���庯�� 
int find_way_shortest(int curx,int cury)
{
	
	pvisiter = NULL;
	
	//�������� 
	AllHead = clear_AllWay(AllHead);
	//�������
	
	 
    header = 1; tailer = 1;

    //��ʼ���յ㡢�������顢��ʱ�ڵ�
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
            if(visit[finalx+1][finaly+1] == 1)
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
    fbfs(tailer - 1);

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



//****************************��ȫ����ģ��*********************************//

//DFS�жϵݹ����庯�� 
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

//��ȫ���� DFS���庯�� 
int find_way_all(int curx, int cury)
{
	
    //�����ʼ��
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
    
    //�������� 
	AllHead = clear_AllWay(AllHead);
	//�������
	
    //����ʼ��
    visiter[curx+1][cury+1] = 1;
    s[0].x = curx;
    s[0].y = cury;
    
    //��ʼ�ݹ�
    dfs(curx,cury);
    
    
	pvisiter = AllHead;
		
    if(solution == 0) 
		return 0;
    else 
		return 1;
    
}



//****************************����һ��ģ��*********************************// 
int next_move(void)
{
    //���ù��Ѻ��������·��������
    find_way_shortest(MajorRole.x, MajorRole.y);
    //��displayʱֻ��ʾ��һ��
}
