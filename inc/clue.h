#ifndef CLUE_H_
#define CLUE_H_

#define MZX 35
#define MZY 35

extern Map[100][100];

//���·��Ѱ�ң�����curx��cury����ǰ�������꣩����·���������������0Ϊδ�ҵ�������1Ϊ�ҵ�
int find_way_shortest(int curx,int cury);

//����·��Ѱ�ң�����0�޽�
int find_way_all(int curx, int cury);

//��ʾ��һ��,����curx��cury����ǰ�������꣩��������һ���ķ��򣬷���0�޽�
int next_move(void);

#endif
