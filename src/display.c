#include "MyHeader.h"

int xscale, yscale;
int CoinGet;

void display(void)
{

	DisplayClear();
	SetPenColor("Light Light Gray");
	drawRectangle(0,0,300,200,1);
	int imap, jmap;
	double Xlength;
	double Ylength;
	double length;
	double x0;
	double y0;

	// length = -0.68 * ((double)xscale + (double)yscale) + 32;
	if (abs(xscale - yscale) < 5)
	{
		length = 160 / sqrt(xscale * yscale);
	}
	else if (xscale > yscale)
	{
		length = 180 / xscale;
	}
	else
	{
		length = 160 / yscale;
	}

	Xlength = (double)xscale * length;
	Ylength = (double)yscale * length;
	x0 = 150 - Xlength / 2;
	y0 = 90 - Ylength / 2;
	if (page_stage != MAIN_PAGE && page_stage != CHOSEMAP_PAGE) // 画地图
	{
		SetPenColor("Black");
		for (imap = 0; imap <= 2 * yscale; imap++)
		{
			for (jmap = 0; jmap <= 2 * xscale; jmap++)
			{
				if (Map[jmap][imap] == WALL && jmap % 2 == 0 && imap % 2 == 1)
				{
					drawBox(x0 + jmap / 2 * length, y0 + (imap - 1) / 2 * length, 0.1, length, 1, "", 'M', "Black");
					// printf("%d %d| %d\n",jmap,imap,Map[jmap][imap]);
				}
				if (Map[jmap][imap] == WALL && jmap % 2 == 1 && imap % 2 == 0)
				{
					drawBox(x0 + (jmap - 1) / 2 * length, y0 + imap / 2 * length, length, 0.1, 1, "", 'M', "Black");
				}
				if (Map[jmap][imap] == WALL && jmap % 2 == 0 && imap % 2 == 0)
				{
				}
				if (Map[jmap][imap] == COIN) // 画地图内金币
				{
					DrawCoin(x0 + (jmap - 1) / 2 * length+length/2, y0 + (imap - 1) / 2 * length+length/2, length, 1);
				}
				if (Map[jmap][imap] == END)//画终点
				{
					//SetPenColor("Green");
					//drawBox(x0 + (jmap - 1) / 2 * length + length / 6, y0 + (imap - 1) / 2 * length + length / 6, length * 2 / 3, length * 2 / 3, 1, "", 'M', "Green");
					//SetPenColor("Black");
					DrawGoal(x0 + (jmap - 1) / 2 * length+length/2,y0 + (imap - 1) / 2 * length+length/2,length);
				}
				// if (Map[jmap][imap] == START)
				//{
				//	SetPenColor("Blue");
				//	drawBox(x0 + (jmap - 1) / 2 * length + length / 6, y0 + (imap - 1) / 2 * length + length / 6, length * 2 / 3, length * 2 / 3, 1, "", 'M', "Blue");
				//	SetPenColor("Black");
				// }
			}
		}

		// 画角色
		SetPenColor("Red");
		// drawBox(x0 + (MajorRole.x - 1) / 2 * length + length / 3, y0 + (MajorRole.y - 1) / 2 * length + length / 3, length / 3, length / 3, 1, "", 'M', "Yellow");
		//DrawAvatar(x0 + (MajorRole.x - 1) / 2 * length, y0 + (MajorRole.y - 1) / 2 * length, length);
		DrawRole(x0 + (MajorRole.x - 1) / 2 * length+length/2,y0 + (MajorRole.y - 1) / 2 * length+length/2,length);

		// 血量显示
		SetPenColor("Light Light Gray");
		drawBox(240, 158, 10, 10, 0, "hp", 'M', "Red");
		SetPenColor("Red");
		drawBox(250, 160, 10 * MajorRole.hp, 5, 1, "", 'M', "Red");
		SetPenColor("Black");
		drawBox(250, 160, 30, 5, 0, "", 'M', "Black");

		// 金币显示
		DrawCoin(245, 145, 5, 0);
		SetPenColor("Light Light Gray");
		switch (CoinGet)
		{
		case 0:
			drawBox(250, 140, 30, 10, 0, ": 0", 'L', "Black");
			break;

		case 1:
			drawBox(250, 140, 30, 10, 0, ": 1", 'L', "Black");
			break;

		case 2:
			drawBox(250, 140, 30, 10, 0, ": 2", 'L', "Black");
			break;

		case 3:
			drawBox(250, 140, 30, 10, 0, ": 3", 'L', "Black");
			break;

		case 4:
			drawBox(250, 140, 30, 10, 0, ": 4", 'L', "Black");
			break;

		case 5:
			drawBox(250, 140, 30, 10, 0, ": 5", 'L', "Black");
			break;

		case 6:
			drawBox(250, 140, 30, 10, 0, ": 6", 'L', "Black");
			break;

		case 7:
			drawBox(250, 140, 30, 10, 0, ": 7", 'L', "Black");
			break;

		case 8:
			drawBox(250, 140, 30, 10, 0, ": 8", 'L', "Black");
			break;

		case 9:
			drawBox(250, 140, 30, 10, 0, ": 9", 'L', "Black");
			break;
			
		case 10:
			drawBox(250, 140, 30, 10, 0, ": 10", 'L', "Black");
			break;
		}
		SetPenColor("Black");

		// 画怪兽
		if (page_stage == GAME_PAGE)
		{
			SetPenColor("Brown");
			int monsnum;
			for (monsnum = 0; monsnum < monsternum; monsnum++)
			{
				//drawBox(x0 + (Monster[monsnum].x - 1) / 2 * length + length / 3, y0 + (Monster[monsnum].y - 1) / 2 * length + length / 3, length / 3, length / 3, 1, "", 'M', "Yellow");
				DrawMonster(x0 + (Monster[monsnum].x - 1) / 2 * length+length/2,y0 + (Monster[monsnum].y - 1) / 2 * length+length/2,length);
			}
		}
	}

	if (ButtonEnum[ShowShortestPath].stage == Button_DOWN) // 绘制最短路径
	{

		SetPenColor("Green");
		pWay pshortestpen;
		pshortestpen = AllHead->ThisWay;
		printf("1 %d %d\n", pshortestpen->x, pshortestpen->y);
		printf("2 %d %d\n", pshortestpen->next->x, pshortestpen->next->y);
		MovePen(x0 + (pshortestpen->x - 1) * length / 2 + length / 2, y0 + (pshortestpen->y - 1) * length / 2 + length / 2);
		while (pshortestpen->next != NULL)
		{
			DrawLine((pshortestpen->next->x - pshortestpen->x) * length / 2, (pshortestpen->next->y - pshortestpen->y) * length / 2);
			pshortestpen = pshortestpen->next;
		}
	}

	if (ButtonEnum[PromptNextStep].stage == Button_DOWN) // 绘制下一步
	{

		SetPenColor("Green");
		pWay pshortestpen;
		pshortestpen = AllHead->ThisWay;
		MovePen(x0 + (pshortestpen->next->x - 1) * length / 2 + length / 6 * 5, y0 + (pshortestpen->next->y - 1) * length / 2 + length / 2);
		DrawArc(length / 3, 0, 360);
		SetPenColor("Red");
	}

	SetPenColor("Red");
	int j = 0;
	for (j; j < ButtonNum; j++) // 绘制按钮
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

void DrawAvatar(double mx, double my, double length) // 画角色
{
	;
	if (iscracked)
	{ // 角色被碰撞后变成红色
		SetPenColor("Red");
	}
	else
	{
		SetPenColor("Blue");
	}
	MovePen(mx + length / 4, my + 0.6 * length);
	DrawLine(0, -0.44 * length);
	DrawLine(0.5 * length, 0);
	DrawLine(0, length * 0.44);

	StartFilledRegion(1);
	DrawLine(-0.11 * length, 0.1 * length);
	DrawLine(-0.08 * length, -0.22 * length);
	DrawLine(-0.11 * length, 0.14 * length);
	DrawLine(-0.2 * length, -0.02 * length);
	DrawLine(-0.04 * length, -0.004 * length);
	DrawLine(-0.05 * length, 0.2 * length);
	DrawLine(-0.1 * length, -0.01 * length);
	DrawLine(0.2 * length, 0.1 * length);
	DrawLine(-0.1 * length, 0.02 * length);
	DrawLine(0.24 * length, 0.03 * length);
	DrawLine(0.05 * length, -0.02 * length);
	DrawLine(0.05 * length, 0.02 * length);
	DrawLine(0.24 * length, -0.03 * length);
	DrawLine(-0.1 * length, -0.02 * length);
	DrawLine(0.2 * length, -0.05 * length);
	DrawLine(-0.05 * length, -0.01 * length);
	DrawLine(0.15 * length, -0.2 * length);
	DrawLine(-0.18 * length, 0.02 * length);
	DrawLine(-0.01 * length, -0.046 * length);
	EndFilledRegion();

	MovePen(mx + length / 4 + length / 32, my + 0.56 * length);
	DrawLine(length * 3 / 16, -length * 1 / 32);
	MovePen(mx + length / 4 + length / 32 + length * 3 / 64, my + 0.56 * length - length * 1 / 64);
	DrawLine(length * 3 / 16 / 32, -length * 3 / 16 / 3);
	DrawLine(length * 3 / 16 / 2 - length * 3 / 16 / 32, 0);
	DrawLine(length * 3 / 16 / 32, length * 3 / 16 / 3 * 7 / 8);
	MovePen(mx + length - (length / 4 + length / 32), my + 0.56 * length);
	DrawLine(-length * 3 / 16, -length * 1 / 32);
	MovePen(mx + length - (length / 4 + length / 32 + length * 3 / 64), my + 0.56 * length - length * 1 / 64);
	DrawLine(-length * 3 / 16 / 32, -length * 3 / 16 / 3);
	DrawLine(-length * 3 / 16 / 2 - length * 3 / 16 / 32, 0);
	DrawLine(-length * 3 / 16 / 32, length * 3 / 16 / 3 * 7 / 8);
	drawRectangle(mx + length / 4 + length / 9, my + 0.48 * length, length / 32, length / 32 + 0.04 * length, 1);
	drawRectangle(mx + length - (length / 4 + length / 9) - length / 32, my + 0.48 * length, length / 32, length / 32 + 0.04 * length, 1);
	MovePen(mx + length / 4 + length / 16, my + 0.38 * length);
	DrawLine(length / 32, -length / 10);
	DrawLine(length * 5 / 16, 0);
	DrawLine(length / 32, length / 10);
}

void DrawCoin(double mx, double my, double l, int InMap)
{
	if (!InMap)
	{
		l = 20;
	}
	
	SetPenColor("Yellow");
	MovePen(mx+l/4, my);
	StartFilledRegion(0.8);
	DrawArc(l/4, 0, 360);
	EndFilledRegion();
	SetPenColor("Black");
	DrawArc(l /4, 0, 360);
	MovePen(mx -l/8, my +l/8+l/32);
	DrawLine(l/8, -l / 8);
	DrawLine(l/8, l/8);
	MovePen(mx - l / 8, my +l/32);
	DrawLine(l/4, 0);
	MovePen(mx -l/8, my-l/16);
	DrawLine(l / 4, 0);
	MovePen(mx, my+l/32 );
	DrawLine(0, -l*3/16);
}

void DrawMonster(double mx,double my,double l)
{
	SetPenColor("Brown");
	MovePen(mx+l/6,my+0);
	StartFilledRegion(1);
	DrawArc(l/6,0,360);
	EndFilledRegion();
	MovePen(mx,my);
	StartFilledRegion(1);
	DrawLine(l/4,l/6);
	DrawLine(l/4,-l/3);
	DrawLine(-l/2,l/6);
	EndFilledRegion();
	StartFilledRegion(1);
	DrawLine(-l/4,l/6);
	DrawLine(-l/4,-l/3);
	DrawLine(l/2,l/6);
	EndFilledRegion();
	SetPenColor("White");
	StartFilledRegion(1);
	MovePen(mx+l/12,my);
	DrawArc(l/12,0,360);
	EndFilledRegion();
	SetPenColor("Light Brown");
	StartFilledRegion(0.5);
	MovePen(mx+l/20,my);
	DrawArc(l/20,0,360);
	EndFilledRegion();
	SetPenColor("Black");
	StartFilledRegion(1);
	MovePen(mx+l/80,my);
	DrawArc(l/80,0,360);
	EndFilledRegion(); 
	
	return;
}

void DrawGoal(double mx,double my,double l)
{
	MovePen(mx,my);
	SetPenColor("Red");
	StartFilledRegion(1);
	DrawLine(-l/3,l/6);
	DrawLine(l/3,l/6);
	DrawLine(0,-l/4-l/3);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx,my);
	DrawLine(-l/3,l/6);
	DrawLine(l/3,l/6);
	DrawLine(0,-l/4-l/3);
	StartFilledRegion(1);
	DrawLine(-l/4,0);
	DrawLine(0,-l/8);
	DrawLine(l/2,0);
	DrawLine(0,l/8);
	DrawLine(-l/4,0);
	EndFilledRegion();
	
}

void DrawRole(double mx,double my,double l)
{
	SetPenColor("White");
	MovePen(mx,my);
	StartFilledRegion(1);
	DrawLine(l/3,0);
	DrawLine(0,l/12);
	DrawLine(-l*2/3,0);
	DrawLine(0,-l/12);
	DrawLine(l/3,0);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx,my);
	DrawLine(l/3,0);
	DrawLine(0,l/12);
	DrawLine(-l*2/3,0);
	DrawLine(0,-l/12);
	DrawLine(l/3,0);
	SetPenColor("White");
	MovePen(mx+l/4,my+l/12);
	StartFilledRegion(1);
	DrawLine(0,l/4);
	DrawLine(-l/2,0);
	DrawLine(0,-l/4);
	DrawLine(l/2,0);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx+l/4,my+l/12);
	DrawLine(0,l/4);
	DrawLine(-l/2,0);
	DrawLine(0,-l/4);
	DrawLine(l/2,0);
	drawRectangle(mx-l/4,my-l/3,l/6,l/3,1);
	MovePen(mx-l/12,my);
	SetPenColor("FaceColor");
	StartFilledRegion(1);
	DrawLine(0,-l/3);
	DrawLine(l/3,0);
	DrawLine(0,l/9);
	DrawLine(l/9,0);
	DrawLine(0,l/9);
	DrawLine(-l/9,0);
	DrawLine(0,l/9);
	DrawLine(-l/3,0);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx-l/12,my);
	DrawLine(0,-l/3);
	DrawLine(l/3,0);
	DrawLine(0,l/9);
	DrawLine(l/9,0);
	DrawLine(0,l/9);
	DrawLine(-l/9,0);
	DrawLine(0,l/9);
	DrawLine(-l/3,0);
	SetPenColor("White");
	MovePen(mx+l/12,my);
	StartFilledRegion(1);
	DrawLine(0,-l/6);
	DrawLine(l/24,0);
	DrawLine(0,l/6);
	DrawLine(-l/24,0);
	EndFilledRegion();
	SetPenColor("Black");
	drawRectangle(mx+l/12,my-l/6,l/12,l/6,0);
	drawRectangle(mx+l/8,my-l/6,l/24,l/6,1);

	if(iscracked>0)
	{
		SetPenColor("Red");
		MovePen(mx+l*(1-(double)iscracked/200)/2,my);
		DrawArc(l*(1-(double)iscracked/200)/2,0,360);
		SetPenColor("Black");
	}
	return;
}