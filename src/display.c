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

	//length = -0.68 * ((double)xscale + (double)yscale) + 32;
	if(abs(xscale-yscale)<5)
	{
		length=160/sqrt(xscale*yscale);
	}else if(xscale>yscale){
		length=180/xscale;
	}else{
		length=160/yscale;
	}
	
	Xlength = (double)xscale * length;
	Ylength = (double)yscale * length;
	x0 = 150 - Xlength / 2;
	y0 = 90 - Ylength / 2;
	if (page_stage != MAIN_PAGE && page_stage != CHOSEMAP_PAGE)//画地图
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
				//if (Map[jmap][imap] == START)
				//{
				//	SetPenColor("Blue");
				//	drawBox(x0 + (jmap - 1) / 2 * length + length / 6, y0 + (imap - 1) / 2 * length + length / 6, length * 2 / 3, length * 2 / 3, 1, "", 'M', "Blue");
				//	SetPenColor("Black");
				//}
			}
		}

		//画角色
		SetPenColor("Red");
		//drawBox(x0 + (MajorRole.x - 1) / 2 * length + length / 3, y0 + (MajorRole.y - 1) / 2 * length + length / 3, length / 3, length / 3, 1, "", 'M', "Yellow");
		DrawAvatar(x0 + (MajorRole.x - 1) / 2 * length,y0 + (MajorRole.y - 1) / 2 * length,length);
		
		//血量显示
		SetPenColor("White");
		drawBox(240,158,10,10,0,"hp",'M',"Red");
		SetPenColor("Red");
		drawBox(250,160,10*MajorRole.hp,5,1,"",'M',"Red");
		drawBox(250,160,30,5,0,"",'M',"Red");
		
		//画怪兽
		if(page_stage==GAME_PAGE){
			SetPenColor("Brown");
			int monsnum;
			for(monsnum=0;monsnum<monsternum;monsnum++)
			{
				drawBox(x0 + (Monster[monsnum].x - 1) / 2 * length + length / 3, y0 + (Monster[monsnum].y - 1) / 2 * length + length / 3, length / 3, length / 3, 1, "", 'M', "Yellow");
			}
		}
		
	}

	if (ButtonEnum[ShowShortestPath].stage == Button_DOWN)//绘制最短路径
	{
		
		SetPenColor("Green");
		pWay pshortestpen;
		pshortestpen = AllHead->ThisWay;
		printf("1 %d %d\n",pshortestpen->x,pshortestpen->y);
		printf("2 %d %d\n",pshortestpen->next->x,pshortestpen->next->y);
		MovePen(x0+(pshortestpen->x-1)*length/2+length/2,y0+(pshortestpen->y-1)*length/2+length/2);
		while(pshortestpen->next!=NULL)
		{
			DrawLine((pshortestpen->next->x-pshortestpen->x)*length/2,(pshortestpen->next->y-pshortestpen->y)*length/2);
			pshortestpen=pshortestpen->next;
		}
	}

	if (ButtonEnum[PromptNextStep].stage == Button_DOWN)//绘制下一步
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
	for (j; j < ButtonNum; j++)//绘制按钮
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


void DrawAvatar(double mx, double my, double length)//画角色
{	
	;
	if(iscracked){				//角色被碰撞后变成红色 
		SetPenColor("Red");
	}else{
		SetPenColor("Blue");
	}
	MovePen(mx+length/4,my+0.6*length);
	DrawLine(0,-0.44*length);
	DrawLine(0.5*length,0);
	DrawLine(0,length*0.44);
	DrawLine(-0.11*length,0.1*length);
	DrawLine(-0.08*length,-0.22*length);
	DrawLine(-0.11*length,0.14*length);
	DrawLine(-0.2*length,-0.02*length);
	DrawLine(-0.04*length,-0.004*length);
	DrawLine(-0.05*length,0.2*length);
	DrawLine(-0.1*length,-0.01*length);
	DrawLine(0.2*length,0.1*length);
	DrawLine(-0.1*length,0.02*length);
	DrawLine(0.24*length,0.03*length);
	DrawLine(0.05*length,-0.02*length);
	DrawLine(0.05*length,0.02*length);
	DrawLine(0.24*length,-0.03*length);
	DrawLine(-0.1*length,-0.02*length);
	DrawLine(0.2*length,-0.05*length);
	DrawLine(-0.05*length,-0.01*length);
	DrawLine(0.15*length,-0.2*length);
	DrawLine(-0.18*length,0.02*length);
	DrawLine(-0.02*length,-0.05*length);
	MovePen(mx+length/4+length/32,my+0.56*length);
	DrawLine(length*3/16,-length*1/32);
	MovePen(mx+length/4+length/32+length*3/64,my+0.56*length-length*1/64);
	DrawLine(length*3/16/32,-length*3/16/3);
	DrawLine(length*3/16/2-length*3/16/32,0);
	DrawLine(length*3/16/32,length*3/16/3*7/8);
	MovePen(mx+length-(length/4+length/32),my+0.56*length);
	DrawLine(-length*3/16,-length*1/32);
	MovePen(mx+length-(length/4+length/32+length*3/64),my+0.56*length-length*1/64);
	DrawLine(-length*3/16/32,-length*3/16/3);
	DrawLine(-length*3/16/2-length*3/16/32,0);
	DrawLine(-length*3/16/32,length*3/16/3*7/8);
	drawRectangle(mx+length/4+length/9,my+0.48*length,length/32,length/32+0.04*length,1);
	drawRectangle(mx+length-(length/4+length/9)-length/32,my+0.48*length,length/32,length/32+0.04*length,1);
	MovePen(mx+length/4+length/16,my+0.38*length);
	DrawLine(length/32,-length/10);
	DrawLine(length*5/16,0);
	DrawLine(length/32,length/10);
}
