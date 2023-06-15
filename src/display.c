#include "MyHeader.h"

int xscale, yscale;

void display(void)
{	
	
	DisplayClear();
	int imap, jmap;
	double Xlength;
	double Ylength;
	double length;
	double x0;
	double y0;

	length = -0.7 * ((double)xscale + (double)yscale) + 34;
	Xlength = (double)xscale * length;
	Ylength = (double)yscale * length;
	x0 = 150 - Xlength / 2;
	y0 = 90 - Ylength / 2;
	if (page_stage != MAIN_PAGE && page_stage != CHOSEMAP_PAGE)
	{

		for (imap = 0; imap <= 2 * yscale; imap++)
		{
			for (jmap = 0; jmap <= 2 * xscale; jmap++)
			{
				if (Map[jmap][imap] == WALL && jmap % 2 == 0 && imap % 2 == 1)
				{
					drawBox(x0 + jmap / 2 * length, y0 + (imap - 1) / 2 * length, 0.1, length, 1, "", 'M', "Red");
				}
				if (Map[jmap][imap] == WALL && jmap % 2 == 1 && imap % 2 == 0)
				{
					drawBox(x0 + (jmap - 1) / 2 * length, y0 + imap / 2 * length, length, 0.1, 1, "", 'M', "Red");
				}
				if (Map[jmap][imap] == WALL && jmap % 2 == 0 && imap % 2 == 0)
				{
				}
				if (Map[jmap][imap] == COIN)
				{
					SetPenColor("Yellow");
					drawBox(x0 + (jmap - 1) / 2 * length + length / 3, y0 + (imap - 1) / 2 * length + length / 3, length / 6, length / 6, 1, "", 'M', "Yellow");
					SetPenColor("Red");
				}
				if (Map[jmap][imap] == END)
				{
					SetPenColor("Green");
					drawBox(x0 + (jmap - 1) / 2 * length + length / 6, y0 + (imap - 1) / 2 * length + length / 6, length * 2 / 3, length * 2 / 3, 1, "", 'M', "Green");
					SetPenColor("Red");
				}
				if (Map[jmap][imap] == START)
				{
					SetPenColor("Blue");
					drawBox(x0 + (jmap - 1) / 2 * length + length / 6, y0 + (imap - 1) / 2 * length + length / 6, length * 2 / 3, length * 2 / 3, 1, "", 'M', "Blue");
					SetPenColor("Red");
				}
			}
		}
	}

	if (ButtonEnum[ShowShortestPath].stage == Button_DOWN)
	{
		
		SetPenColor("Green");
		pWay pshortestpen;
		pshortestpen = AllHead->ThisWay;
		MovePen(x0+(pshortestpen->x-1)*length/2+length/2,y0+(pshortestpen->y-1)*length/2+length/2);
		printf("*****************\n");
		printf("%d %d \n",pshortestpen->x,pshortestpen->y);
		printf("%.0f %.0f\n",x0+(pshortestpen->x-1)*length/2+length/2,y0+(pshortestpen->y-1)*length/2+length/2);
		printf("*****************\n");
		while(pshortestpen->next!=NULL)
		{
			DrawLine((pshortestpen->next->x-pshortestpen->x)*length/2,(pshortestpen->next->y-pshortestpen->y)*length/2);
			pshortestpen=pshortestpen->next;
			printf("%d %d \n",pshortestpen->x,pshortestpen->y);
		}
	printf("____________________");
	}
	
	
	SetPenColor("Red");
	int j = 0;
	for (j; j < 25; j++)
	{
		if (ButtonEnum[j].visible == VISIBLE)
		{
			if (ButtonEnum[j].stage == Button_UP)
			{
				drawBox(ButtonEnum[j].x,
						ButtonEnum[j].y,
						ButtonEnum[j].lx,
						ButtonEnum[j].ly,
						0,
						ButtonEnum[j].name,
						'M', "Red");
			}
			else
			{
				drawBox(ButtonEnum[j].x,
						ButtonEnum[j].y,
						ButtonEnum[j].lx,
						ButtonEnum[j].ly,
						0,
						ButtonEnum[j].name,
						'M', "Black");
				SetPenColor("Red");
			}
		}
	}

	// char *List[5]={"1","2","3","4","5"};
	// int x= menuList(1, 30, 30, 10, 10, 50, List,5);
	// int x = MessageBox(NULL, "aaa", "djcg", MB_OK| MB_ICONINFORMATION );
}
