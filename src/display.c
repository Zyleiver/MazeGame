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

	length = -0.7 * ((double)xscale + (double)yscale) + 36;
	Xlength = (double)xscale * length;
	Ylength = (double)yscale * length;
	x0 = 150 - Xlength / 2;
	y0 = 90 - Ylength / 2;
	if (page_stage != MAIN_PAGE && page_stage != CHOSEMAP_PAGE)//»­µØÍ¼
	{
		SetPenColor("Black");
		for (imap = 0; imap <= 2 * yscale; imap++)
		{
			for (jmap = 0; jmap <= 2 * xscale; jmap++)
			{
				if (Map[jmap][imap] == WALL && jmap % 2 == 0 && imap % 2 == 1)
				{
					drawBox(x0 + jmap / 2 * length, y0 + (imap - 1) / 2 * length, 0.1, length, 1, "", 'M', "Black");
					//printf("%d %d| %d\n",jmap,imap,Map[jmap][imap]);
				}
				if (Map[jmap][imap] == WALL && jmap % 2 == 1 && imap % 2 == 0)
				{
					drawBox(x0 + (jmap - 1) / 2 * length, y0 + imap / 2 * length, length, 0.1, 1, "", 'M', "Black");
				}
				if (Map[jmap][imap] == WALL && jmap % 2 == 0 && imap % 2 == 0)
				{
				}
				if (Map[jmap][imap] == COIN)
				{
					SetPenColor("Yellow");
					drawBox(x0 + (jmap - 1) / 2 * length + length / 3, y0 + (imap - 1) / 2 * length + length / 3, length / 3, length / 3, 1, "", 'M', "Yellow");
					SetPenColor("Black");
				}
				if (Map[jmap][imap] == END)
				{
					SetPenColor("Green");
					drawBox(x0 + (jmap - 1) / 2 * length + length / 6, y0 + (imap - 1) / 2 * length + length / 6, length * 2 / 3, length * 2 / 3, 1, "", 'M', "Green");
					SetPenColor("Black");
				}
				if (Map[jmap][imap] == START)
				{
					SetPenColor("Blue");
					drawBox(x0 + (jmap - 1) / 2 * length + length / 6, y0 + (imap - 1) / 2 * length + length / 6, length * 2 / 3, length * 2 / 3, 1, "", 'M', "Blue");
					SetPenColor("Black");
				}
			}
		}

		SetPenColor("Red");
		drawBox(x0 + (MajorRole.x - 1) / 2 * length + length / 3, y0 + (MajorRole.y - 1) / 2 * length + length / 3, length / 3, length / 3, 1, "", 'M', "Yellow");
		SetPenColor("Brown");
		int monsnum;
		for(monsnum=0;monsnum<monsternum;monsnum++)
		{
			drawBox(x0 + (Monster[monsnum].x - 1) / 2 * length + length / 3, y0 + (Monster[monsnum].y - 1) / 2 * length + length / 3, length / 3, length / 3, 1, "", 'M', "Yellow");
		}
	}

	if (ButtonEnum[ShowShortestPath].stage == Button_DOWN)
	{
		
		SetPenColor("Green");
		pWay pshortestpen;
		pshortestpen = AllHead->ThisWay;
		MovePen(x0+(pshortestpen->x-1)*length/2+length/2,y0+(pshortestpen->y-1)*length/2+length/2);
		while(pshortestpen->next!=NULL)
		{
			DrawLine((pshortestpen->next->x-pshortestpen->x)*length/2,(pshortestpen->next->y-pshortestpen->y)*length/2);
			pshortestpen=pshortestpen->next;
		}
	}

	if (ButtonEnum[PromptNextStep].stage == Button_DOWN)
	{
		
		SetPenColor("Green");
		pWay pshortestpen;
		pshortestpen = AllHead->ThisWay;
		MovePen(x0+(pshortestpen->next->x-1)*length/2+length/6*5,y0+(pshortestpen->next->y-1)*length/2+length/2);
		DrawArc(length/3,0,360);
		SetPenColor("Red");
		
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
