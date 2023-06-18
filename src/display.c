#include "MyHeader.h"

int xscale, yscale;
int CoinGet;
char mapx[4] = {'4', '\0'};
char mapy[4] = {'4', '\0'};
char monsnum[5] = {'3', '\0'};
char coinnum[5] = {'3', '\0'};

void display(void)
{

	DisplayClear();
	SetPenColor("Light Light Gray");
	drawRectangle(0, 0, 300, 200, 1);
	int imap, jmap;

	// 绘制最短路径
	if ((page_stage == GAME_PAGE || page_stage == TOOL_PAGE || page_stage == MENU_PAGE) && ButtonEnum[ShowShortestPath].stage == Button_DOWN)
	{

		pWay pshortestpen;
		pshortestpen = AllHead->ThisWay;

		if (pshortestpen->next != NULL)
		{
			while (pshortestpen->next->next != NULL)
			{

				if (pshortestpen->x == pshortestpen->next->x)
				{

					if (pshortestpen->y > pshortestpen->next->y)
					{
						if (pshortestpen->next->x == pshortestpen->next->next->x)
						{
							DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 3);
						}
						else if (pshortestpen->next->x > pshortestpen->next->next->x)
						{
							DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 7);
						}
						else if (pshortestpen->next->x < pshortestpen->next->next->x)
						{
							DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 6);
						}
					}
					else if (pshortestpen->y < pshortestpen->next->y)
					{
						if (pshortestpen->next->x == pshortestpen->next->next->x)
						{
							DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 1);
						}
						else if (pshortestpen->next->x < pshortestpen->next->next->x)
						{
							DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 5);
						}
						else if (pshortestpen->next->x > pshortestpen->next->next->x)
						{
							DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 8);
						}
					}
				}
				else if (pshortestpen->x < pshortestpen->next->x)
				{

					if (pshortestpen->next->y > pshortestpen->next->next->y)
					{
						DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 8);
					}
					else if (pshortestpen->next->y == pshortestpen->next->next->y)
					{
						DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 2);
					}
					else if (pshortestpen->next->y < pshortestpen->next->next->y)
					{
						DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 7);
					}
				}
				else if (pshortestpen->x > pshortestpen->next->x)
				{

					if (pshortestpen->next->y > pshortestpen->next->next->y)
					{
						DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 5);
					}
					else if (pshortestpen->next->y == pshortestpen->next->next->y)
					{
						DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 4);
					}
					else if (pshortestpen->next->y < pshortestpen->next->next->y)
					{
						DrawWayArrow(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y) * length / 2, length, 6);
					}
				}

				pshortestpen = pshortestpen->next;
			}
		}
		/*
		MovePen(X0 + (pshortestpen->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->y - 1) * length / 2 + length / 2);
		while (pshortestpen->next != NULL)
		{
			DrawLine((pshortestpen->next->x - pshortestpen->x) * length / 2, (pshortestpen->next->y - pshortestpen->y) * length / 2);
			pshortestpen = pshortestpen->next;
		}
		*/
	}

	// 绘制一条全部路径
	if ((page_stage == GAME_PAGE || page_stage == TOOL_PAGE || page_stage == MENU_PAGE) && ButtonEnum[ShowAllPath].stage == Button_DOWN)
	{
		// if(pvisiter->last==NULL)ButtonEnum[LeftShiftPath].visible=UNVISIBLE;
		// if(pvisiter->Next==NULL)ButtonEnum[RightShiftPath].visible=UNVISIBLE;
		/*
		SetPenColor("SafeWayGreen");
		pWay pallwaypen;
		pallwaypen = pvisiter->ThisWay;
		MovePen(X0 + (pallwaypen->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->y - 1) * length / 2 + length / 2);
		while (pallwaypen->next != NULL)
		{
			DrawLine((pallwaypen->next->x - pallwaypen->x) * length / 2, (pallwaypen->next->y - pallwaypen->y) * length / 2);
			pallwaypen = pallwaypen->next;
		}
		*/

		pWay pallwaypen;
		pallwaypen = pvisiter->ThisWay;

		if (pallwaypen->next != NULL)
		{
			while (pallwaypen->next->next != NULL)
			{

				if (pallwaypen->x == pallwaypen->next->x)
				{

					if (pallwaypen->y > pallwaypen->next->y)
					{
						if (pallwaypen->next->x == pallwaypen->next->next->x)
						{
							DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 3);
						}
						else if (pallwaypen->next->x > pallwaypen->next->next->x)
						{
							DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 7);
						}
						else if (pallwaypen->next->x < pallwaypen->next->next->x)
						{
							DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 6);
						}
					}
					else if (pallwaypen->y < pallwaypen->next->y)
					{
						if (pallwaypen->next->x == pallwaypen->next->next->x)
						{
							DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 1);
						}
						else if (pallwaypen->next->x < pallwaypen->next->next->x)
						{
							DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 5);
						}
						else if (pallwaypen->next->x > pallwaypen->next->next->x)
						{
							DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 8);
						}
					}
				}
				else if (pallwaypen->x < pallwaypen->next->x)
				{

					if (pallwaypen->next->y > pallwaypen->next->next->y)
					{
						DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 8);
					}
					else if (pallwaypen->next->y == pallwaypen->next->next->y)
					{
						DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 2);
					}
					else if (pallwaypen->next->y < pallwaypen->next->next->y)
					{
						DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 7);
					}
				}
				else if (pallwaypen->x > pallwaypen->next->x)
				{

					if (pallwaypen->next->y > pallwaypen->next->next->y)
					{
						DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 5);
					}
					else if (pallwaypen->next->y == pallwaypen->next->next->y)
					{
						DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 4);
					}
					else if (pallwaypen->next->y < pallwaypen->next->next->y)
					{
						DrawWayArrow(X0 + (pallwaypen->next->x - 1) * length / 2 + length / 2, Y0 + (pallwaypen->next->y) * length / 2, length, 6);
					}
				}

				pallwaypen = pallwaypen->next;
			}
		}
	}

	if (page_stage != MAIN_PAGE && page_stage != CHOSEMAP_PAGE) // 画地图
	{
		SetPenColor("Black");
		for (imap = 0; imap <= 2 * yscale; imap++)
		{
			for (jmap = 0; jmap <= 2 * xscale; jmap++)
			{
				if (Map[jmap][imap] == WALL && jmap % 2 == 0 && imap % 2 == 1)
				{
					drawBox(X0 + jmap / 2 * length, Y0 + (imap - 1) / 2 * length, 0.1, length, 1, "", 'M', "Black");
					// printf("%d %d| %d\n",jmap,imap,Map[jmap][imap]);
				}
				if (Map[jmap][imap] == WALL && jmap % 2 == 1 && imap % 2 == 0)
				{
					drawBox(X0 + (jmap - 1) / 2 * length, Y0 + imap / 2 * length, length, 0.1, 1, "", 'M', "Black");
				}
				if (Map[jmap][imap] == WALL && jmap % 2 == 0 && imap % 2 == 0)
				{
				}
				if (Map[jmap][imap] == COIN) // 画地图内金币
				{
					DrawCoin(X0 + (jmap - 1) / 2 * length + length / 2, Y0 + (imap - 1) / 2 * length + length / 2, length, 1);
				}
				if (Map[jmap][imap] == END) // 画终点
				{
					// SetPenColor("Green");
					// drawBox(X0 + (jmap - 1) / 2 * length + length / 6, Y0 + (imap - 1) / 2 * length + length / 6, length * 2 / 3, length * 2 / 3, 1, "", 'M', "Green");
					// SetPenColor("Black");
					DrawGoal(X0 + (jmap - 1) / 2 * length + length / 2, Y0 + (imap - 1) / 2 * length + length / 2, length);
				}
				// if (Map[jmap][imap] == START)
				//{
				//	SetPenColor("Blue");
				//	drawBox(X0 + (jmap - 1) / 2 * length + length / 6, Y0 + (imap - 1) / 2 * length + length / 6, length * 2 / 3, length * 2 / 3, 1, "", 'M', "Blue");
				//	SetPenColor("Black");
				// }
			}
		}

		// 画角色
		SetPenColor("Red");
		// drawBox(X0 + (MajorRole.x - 1) / 2 * length + length / 3, Y0 + (MajorRole.y - 1) / 2 * length + length / 3, length / 3, length / 3, 1, "", 'M', "Yellow");
		// DrawAvatar(X0 + (MajorRole.x - 1) / 2 * length, Y0 + (MajorRole.y - 1) / 2 * length, length);
		DrawRole(X0 + (MajorRole.x - 1) / 2 * length + length / 2, Y0 + (MajorRole.y - 1) / 2 * length + length / 2, length);

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
		char m[10];
		sprintf(m, "%d", CoinGet);
		drawBox(250, 140, 5, 10, 0, ": ", 'L', "Black");
		SetPenColor("Light Light Gray");
		drawBox(255, 140, 10, 10, 0, m, 'L', "Black");
		SetPenColor("Black");

		// 画怪兽
		if (page_stage == GAME_PAGE || page_stage == TOOL_PAGE || page_stage == MENU_PAGE)
		{
			SetPenColor("Brown");
			int monsnum;
			for (monsnum = 1; monsnum < monsternum + 1; monsnum++)
			{
				// drawBox(X0 + (Monster[monsnum].x - 1) / 2 * length + length / 3, Y0 + (Monster[monsnum].y - 1) / 2 * length + length / 3, length / 3, length / 3, 1, "", 'M', "Yellow");
				DrawMonster(X0 + (Monster[monsnum].x - 1) / 2 * length + length / 2, Y0 + (Monster[monsnum].y - 1) / 2 * length + length / 2, length);
			}
		}
	}

	// 绘制关于界面
	if (page_stage == INSTRUCT_PAGE)
	{
		int sizepen = GetPenSize();
		SetPenSize(2);
		SetPenColor("Light Light Gray");
		drawRectangle(0, 0, 300, 200, 1);
		drawBox(120, 150, 60, 20, 0, "关 于", 'M', "Blue");
		SetPenColor("Light Light Gray");
		drawBox(110, 130, 30, 10, 0, "作者：", 'M', "Blue");
		SetPenColor("Light Light Gray");
		drawBox(140, 130, 30, 10, 0, "郑灵杰", 'M', "Black");
		SetPenColor("Light Light Gray");
		drawBox(140, 120, 30, 10, 0, "耿传洪", 'M', "Black");
		SetPenColor("Light Light Gray");
		drawBox(140, 110, 30, 10, 0, "王志龙", 'M', "Black");
		SetPenColor("Light Light Gray");
		drawBox(105, 100, 40, 10, 0, "作品名称：", 'M', "Blue");
		SetPenColor("Light Light Gray");
		drawBox(140, 100, 40, 10, 0, "你逃它追插翅难飞", 'M', "Black");
		SetPenColor("Light Light Gray");
		drawBox(105, 50, 90, 5, 0, "谨此纪念我们的童年", 'M', "Blue");
		SetPenColor("Violet");
		drawRectangle(95, 40, 110, 132, 0);
		SetPenColor("Blue");
		drawRectangle(100, 45, 100, 120, 0);
		SetPenSize(sizepen);
	}

	// 绘制地图参数输入窗
	if (page_stage == CHOSEMAP_PAGE)
	{
		SetPenColor("Light Light Gray");
		drawBox(160, 140, 40, 10, 0, "地图规格\(4<=x<=40,4<=y<=40\)", 'L', "Black");
		SetPenColor("Light Light Gray");
		drawBox(160, 130, 10, 10, 0, "x:", 'L', "Black");
		SetPenColor("Light Light Gray");
		drawBox(185, 130, 10, 10, 0, "y:", 'L', "Black");
		SetPenColor("Light Light Gray");
		drawBox(160, 100, 40, 10, 0, "怪兽数量\(小于999\):", 'L', "Black");
		SetPenColor("Light Light Gray");
		drawBox(160, 70, 40, 10, 0, "金币数量\(若手动编辑无需输入\):", 'L', "Black");
		textbox(GenUIID(0), 170, 130, 10, 10, mapx, 3);
		textbox(GenUIID(0), 195, 130, 10, 10, mapy, 3);
		textbox(GenUIID(0), 200, 100, 10, 10, monsnum, 4);
		textbox(GenUIID(0), 225, 70, 10, 10, coinnum, 4);
		SetPenColor("Black");
		drawRectangle(140, 50, 110, 110, 0);
	}

	// 绘制下一步
	if ((page_stage == GAME_PAGE || page_stage == TOOL_PAGE || page_stage == MENU_PAGE) && ButtonEnum[PromptNextStep].stage == Button_DOWN)
	{

		// SetPenColor("SafeWayGreen");
		pWay pshortestpen;
		pshortestpen = AllHead->ThisWay;
		drawhat(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 2, Y0 + (pshortestpen->next->y - 1) * length / 2 + length / 2, length);
		if (MajorRole.x == pshortestpen->next->x && MajorRole.y == pshortestpen->next->y)
			ButtonEnum[PromptNextStep].stage = Button_UP;
		// MovePen(X0 + (pshortestpen->next->x - 1) * length / 2 + length / 6 * 5, Y0 + (pshortestpen->next->y - 1) * length / 2 + length / 2);
		// DrawArc(length / 3, 0, 360);
		// SetPenColor("Red");
	}

	SetPenColor("Blue");
	int j = 0;
	for (j; j < ButtonNum; j++) // 绘制按钮
	{
		if (ButtonEnum[j].visible == VISIBLE)
		{
			if (ButtonEnum[j].stage == Button_UP)
			{
				SetPenColor("Light Gray");
				drawRectangle(ButtonEnum[j].x,
							  ButtonEnum[j].y,
							  ButtonEnum[j].lx,
							  ButtonEnum[j].ly, 1);
				SetPenColor("Black");
				drawBox(ButtonEnum[j].x,
						ButtonEnum[j].y,
						ButtonEnum[j].lx,
						ButtonEnum[j].ly,
						0,
						ButtonEnum[j].name,
						'M', "Blue");
			}
			else
			{
				SetPenColor("Light Gray");
				drawRectangle(ButtonEnum[j].x,
							  ButtonEnum[j].y,
							  ButtonEnum[j].lx,
							  ButtonEnum[j].ly, 1);
				SetPenColor("Black");
				drawBox(ButtonEnum[j].x,
						ButtonEnum[j].y,
						ButtonEnum[j].lx,
						ButtonEnum[j].ly,
						0,
						ButtonEnum[j].name,
						'M', "Red");
				SetPenColor("Blue");
			}
		}
	}

	if (page_stage == EDIT_PAGE)
	{
		if (ifpre) // 呈现预览状态
		{
			switch (putting)
			{
			case PutWall:
				// 画框框
				SetPenColor("Blue");
				if (editx % 2 == 1)
				{
					drawRectangle(X0 + (editx - 1) / 2 * length, Y0 + (edity) / 2 * length - 0.8, length, 1.6, 0);
				}
				else
				{
					drawRectangle(X0 + editx / 2 * length - 0.8, Y0 + (edity - 1) / 2 * length, 1.6, length, 0);
				}
				SetPenColor("Black");
				break;

			case PutCoin:
				// 画预览金币
				DrawPreCoin(X0 + (editx - 1) / 2 * length + length / 2, Y0 + (edity - 1) / 2 * length + length / 2, length);
				break;

			case PutRole:
				// 画预览角色
				DrawPreRole(X0 + (editx - 1) / 2 * length + length / 2, Y0 + (edity - 1) / 2 * length + length / 2, length);
				break;

			case PutGoal:
				// 画预览终点
				DrawPreGoal(X0 + (editx - 1) / 2 * length + length / 2, Y0 + (edity - 1) / 2 * length + length / 2, length);
				break;

			case Erase:
				// 画框框
				SetPenColor("Blue");
				if (editx % 2 == 1)
				{
					drawRectangle(X0 + (editx - 1) / 2 * length, Y0 + (edity) / 2 * length - 0.8, length, 1.6, 0);
				}
				else
				{
					drawRectangle(X0 + editx / 2 * length - 0.8, Y0 + (edity - 1) / 2 * length, 1.6, length, 0);
				}
				SetPenColor("Black");
				break;
			}
		}
	}
	
	if(page_stage == END_PAGE && endtime != 0 && MajorRole.hp != 0)
	{
		int sizepenn;
		sizepenn = GetPointSize();
		MovePen(100,120);
    	SetPointSize(100);
			if(endtime>175)
			{
				SetPenColor("Green");
			}
			else if(endtime>150)
			{
				SetPenColor("Brown");
			}
			else if(endtime>125)
			{
				SetPenColor("Red");
			}
			else if(endtime>100)
			{
				SetPenColor("Blue");
			}
			else if(endtime>75)
			{
				SetPenColor("Violet");
			}
			else if(endtime>50)
			{
				SetPenColor("Yellow");
			}
			else if(endtime>25)
			{
				SetPenColor("Gray");
			}
			else
			{
				SetPenColor("Green");
			}
    	DrawTextString("!!! W I N !!!");
    	SetPointSize(sizepenn);
    	SetPenColor("Black");		
	}
	
	if(page_stage == END_PAGE && dietime != 0 && MajorRole.hp == 0)
	{
		int sizepene;
		sizepene = GetPointSize();
		MovePen(100,120);
    	SetPointSize(100);
			
			if(dietime>75)
			{
				SetPenColor("Violet");
			}
			else if(dietime>50)
			{
				SetPenColor("Gray");
			}
			else if(dietime>25)
			{
				SetPenColor("Violet");
			}
			else
			{
				SetPenColor("Gray");
			}
    	DrawTextString("TRY AGAIN!!!");
    	SetPointSize(sizepene);
    	SetPenColor("Black");
	}
}

void DrawCoin(double mx, double my, double l, int InMap)
{
	if (!InMap)
	{
		l = 20;
	}

	SetPenColor("Yellow");
	MovePen(mx + l / 4, my);
	StartFilledRegion(0.8);
	DrawArc(l / 4, 0, 360);
	EndFilledRegion();
	SetPenColor("Black");
	DrawArc(l / 4, 0, 360);
	MovePen(mx - l / 8, my + l / 8 + l / 32);
	DrawLine(l / 8, -l / 8);
	DrawLine(l / 8, l / 8);
	MovePen(mx - l / 8, my + l / 32);
	DrawLine(l / 4, 0);
	MovePen(mx - l / 8, my - l / 16);
	DrawLine(l / 4, 0);
	MovePen(mx, my + l / 32);
	DrawLine(0, -l * 3 / 16);
}

void DrawMonster(double mx, double my, double l)
{
	SetPenColor("Brown");
	MovePen(mx + l / 6, my + 0);
	StartFilledRegion(1);
	DrawArc(l / 6, 0, 360);
	EndFilledRegion();
	MovePen(mx, my);
	StartFilledRegion(1);
	DrawLine(l / 4, l / 6);
	DrawLine(l / 4, -l / 3);
	DrawLine(-l / 2, l / 6);
	EndFilledRegion();
	StartFilledRegion(1);
	DrawLine(-l / 4, l / 6);
	DrawLine(-l / 4, -l / 3);
	DrawLine(l / 2, l / 6);
	EndFilledRegion();
	SetPenColor("White");
	StartFilledRegion(1);
	MovePen(mx + l / 12, my);
	DrawArc(l / 12, 0, 360);
	EndFilledRegion();
	SetPenColor("Light Brown");
	StartFilledRegion(0.5);
	MovePen(mx + l / 20, my);
	DrawArc(l / 20, 0, 360);
	EndFilledRegion();
	SetPenColor("Black");
	StartFilledRegion(1);
	MovePen(mx + l / 80, my);
	DrawArc(l / 80, 0, 360);
	EndFilledRegion();

	return;
}

void DrawGoal(double mx, double my, double l)
{
	MovePen(mx, my);
	SetPenColor("Red");
	StartFilledRegion(1);
	DrawLine(-l / 3, l / 6);
	DrawLine(l / 3, l / 6);
	DrawLine(0, -l / 4 - l / 3);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx, my);
	DrawLine(-l / 3, l / 6);
	DrawLine(l / 3, l / 6);
	DrawLine(0, -l / 4 - l / 3);
	StartFilledRegion(1);
	DrawLine(-l / 4, 0);
	DrawLine(0, -l / 8);
	DrawLine(l / 2, 0);
	DrawLine(0, l / 8);
	DrawLine(-l / 4, 0);
	EndFilledRegion();
}

void DrawRole(double mx, double my, double l)
{
	if (ButtonEnum[PromptNextStep].stage == Button_DOWN)
	{
		SetPenColor("FaceColor");
		MovePen(mx, my);
		StartFilledRegion(1);
		DrawLine(l / 4, 0);
		DrawLine(0, l / 8);
		DrawLine(-l / 2, 0);
		DrawLine(0, -l / 8);
		DrawLine(l / 4, 0);
		EndFilledRegion();
		SetPenColor("Black");
		MovePen(mx + l / 4, my);
		DrawLine(0, l / 8);
		DrawLine(-l / 2, 0);
		DrawLine(0, -l / 8);
	}
	else
	{
		SetPenColor("White");
		MovePen(mx, my);
		StartFilledRegion(1);
		DrawLine(l / 3, 0);
		DrawLine(0, l / 12);
		DrawLine(-l * 2 / 3, 0);
		DrawLine(0, -l / 12);
		DrawLine(l / 3, 0);
		EndFilledRegion();
		SetPenColor("Black");
		MovePen(mx, my);
		DrawLine(l / 3, 0);
		DrawLine(0, l / 12);
		DrawLine(-l * 2 / 3, 0);
		DrawLine(0, -l / 12);
		DrawLine(l / 3, 0);
		SetPenColor("White");
		MovePen(mx + l / 4, my + l / 12);
		StartFilledRegion(1);
		DrawLine(0, l / 4);
		DrawLine(-l / 2, 0);
		DrawLine(0, -l / 4);
		DrawLine(l / 2, 0);
		EndFilledRegion();
		SetPenColor("Black");
		MovePen(mx + l / 4, my + l / 12);
		DrawLine(0, l / 4);
		DrawLine(-l / 2, 0);
		DrawLine(0, -l / 4);
		DrawLine(l / 2, 0);
	}

	drawRectangle(mx - l / 4, my - l / 3, l / 6, l / 3, 1);
	MovePen(mx - l / 12, my);
	SetPenColor("FaceColor");
	StartFilledRegion(1);
	DrawLine(0, -l / 3);
	DrawLine(l / 3, 0);
	DrawLine(0, l / 9);
	DrawLine(l / 9, 0);
	DrawLine(0, l / 9);
	DrawLine(-l / 9, 0);
	DrawLine(0, l / 9);
	DrawLine(-l / 3, 0);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx - l / 12, my);
	DrawLine(0, -l / 3);
	DrawLine(l / 3, 0);
	DrawLine(0, l / 9);
	DrawLine(l / 9, 0);
	DrawLine(0, l / 9);
	DrawLine(-l / 9, 0);
	DrawLine(0, l / 9);
	if (ButtonEnum[PromptNextStep].stage != Button_DOWN)
		DrawLine(-l / 3, 0);
	SetPenColor("White");
	MovePen(mx + l / 12, my);
	StartFilledRegion(1);
	DrawLine(0, -l / 6);
	DrawLine(l / 24, 0);
	DrawLine(0, l / 6);
	DrawLine(-l / 24, 0);
	EndFilledRegion();
	SetPenColor("Black");
	drawRectangle(mx + l / 12, my - l / 6, l / 12, l / 6, 0);
	drawRectangle(mx + l / 8, my - l / 6, l / 24, l / 6, 1);

	if (iscracked > 0)
	{
		SetPenColor("Yellow");
		MovePen(mx + l / 2 - l / 64, my);
		DrawArc(l / 2 - l / 64, 0, 360);
		SetPenColor("Black");
	}
	return;
}

void DrawPreCoin(double mx, double my, double l)
{
	SetPenColor("Yellow");
	MovePen(mx + l / 4, my);
	StartFilledRegion(0.2);
	DrawArc(l / 4, 0, 360);
	EndFilledRegion();
	SetPenColor("Black");
	DrawArc(l / 4, 0, 360);
	MovePen(mx - l / 8, my + l / 8 + l / 32);
	DrawLine(l / 8, -l / 8);
	DrawLine(l / 8, l / 8);
	MovePen(mx - l / 8, my + l / 32);
	DrawLine(l / 4, 0);
	MovePen(mx - l / 8, my - l / 16);
	DrawLine(l / 4, 0);
	MovePen(mx, my + l / 32);
	DrawLine(0, -l * 3 / 16);
}

void DrawPreGoal(double mx, double my, double l)
{
	MovePen(mx, my);
	SetPenColor("Red");
	StartFilledRegion(0.2);
	DrawLine(-l / 3, l / 6);
	DrawLine(l / 3, l / 6);
	DrawLine(0, -l / 4 - l / 3);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx, my);
	DrawLine(-l / 3, l / 6);
	DrawLine(l / 3, l / 6);
	DrawLine(0, -l / 4 - l / 3);
	StartFilledRegion(0.2);
	DrawLine(-l / 4, 0);
	DrawLine(0, -l / 8);
	DrawLine(l / 2, 0);
	DrawLine(0, l / 8);
	DrawLine(-l / 4, 0);
	EndFilledRegion();
}

void DrawPreRole(double mx, double my, double l)
{
	SetPenColor("White");
	MovePen(mx, my);
	StartFilledRegion(0.3);
	DrawLine(l / 3, 0);
	DrawLine(0, l / 12);
	DrawLine(-l * 2 / 3, 0);
	DrawLine(0, -l / 12);
	DrawLine(l / 3, 0);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx, my);
	DrawLine(l / 3, 0);
	DrawLine(0, l / 12);
	DrawLine(-l * 2 / 3, 0);
	DrawLine(0, -l / 12);
	DrawLine(l / 3, 0);
	SetPenColor("White");
	MovePen(mx + l / 4, my + l / 12);
	StartFilledRegion(0.3);
	DrawLine(0, l / 4);
	DrawLine(-l / 2, 0);
	DrawLine(0, -l / 4);
	DrawLine(l / 2, 0);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx + l / 4, my + l / 12);
	DrawLine(0, l / 4);
	DrawLine(-l / 2, 0);
	DrawLine(0, -l / 4);
	DrawLine(l / 2, 0);
	drawRectangle(mx - l / 4, my - l / 3, l / 6, l / 3, 1);
	MovePen(mx - l / 12, my);
	SetPenColor("FaceColor");
	StartFilledRegion(0.3);
	DrawLine(0, -l / 3);
	DrawLine(l / 3, 0);
	DrawLine(0, l / 9);
	DrawLine(l / 9, 0);
	DrawLine(0, l / 9);
	DrawLine(-l / 9, 0);
	DrawLine(0, l / 9);
	DrawLine(-l / 3, 0);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx - l / 12, my);
	DrawLine(0, -l / 3);
	DrawLine(l / 3, 0);
	DrawLine(0, l / 9);
	DrawLine(l / 9, 0);
	DrawLine(0, l / 9);
	DrawLine(-l / 9, 0);
	DrawLine(0, l / 9);
	DrawLine(-l / 3, 0);
	SetPenColor("White");
	MovePen(mx + l / 12, my);
	StartFilledRegion(0.3);
	DrawLine(0, -l / 6);
	DrawLine(l / 24, 0);
	DrawLine(0, l / 6);
	DrawLine(-l / 24, 0);
	EndFilledRegion();
	SetPenColor("Black");
	drawRectangle(mx + l / 12, my - l / 6, l / 12, l / 6, 0);
	drawRectangle(mx + l / 8, my - l / 6, l / 24, l / 6, 1);
}

void drawhat(double mx, double my, double l)
{
	SetPenColor("White");
	MovePen(mx, my - l / 6);
	StartFilledRegion(1);
	DrawLine(l / 3, 0);
	DrawLine(0, l / 12);
	DrawLine(-l * 2 / 3, 0);
	DrawLine(0, -l / 12);
	DrawLine(l / 3, 0);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx, my - l / 6);
	DrawLine(l / 3, 0);
	DrawLine(0, l / 12);
	DrawLine(-l * 2 / 3, 0);
	DrawLine(0, -l / 12);
	DrawLine(l / 3, 0);
	SetPenColor("White");
	MovePen(mx + l / 4, my + l / 12 - l / 6);
	StartFilledRegion(1);
	DrawLine(0, l / 4);
	DrawLine(-l / 2, 0);
	DrawLine(0, -l / 4);
	DrawLine(l / 2, 0);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(mx + l / 4, my + l / 12 - l / 6);
	DrawLine(0, l / 4);
	DrawLine(-l / 2, 0);
	DrawLine(0, -l / 4);
	DrawLine(l / 2, 0);
}

void DrawWayArrow(double mx, double my, double length, int stage)
{

	SetPenColor("SafeWayGreen");

	switch (stage)
	{
	case 1:

		MovePen(mx, my + length / 8);
		StartFilledRegion(0.6);
		DrawLine(length * 3 / 8, -length / 8);
		DrawLine(0, length / 4);
		DrawLine(-length * 3 / 8, length / 8);
		DrawLine(-length * 3 / 8, -length / 8);
		DrawLine(0, -length / 4);
		DrawLine(length * 3 / 8, length / 8);
		EndFilledRegion();

		MovePen(mx, my - length * 3 / 8);
		StartFilledRegion(0.6);
		DrawLine(length * 3 / 8, -length / 8);
		DrawLine(0, length / 4);
		DrawLine(-length * 3 / 8, length / 8);
		DrawLine(-length * 3 / 8, -length / 8);
		DrawLine(0, -length / 4);
		DrawLine(length * 3 / 8, length / 8);
		EndFilledRegion();
		break;

	case 2:

		MovePen(mx + length / 8, my);
		StartFilledRegion(0.6);
		DrawLine(-length / 8, length * 3 / 8);
		DrawLine(length / 4, 0);
		DrawLine(length / 8, -length * 3 / 8);
		DrawLine(-length / 8, -length * 3 / 8);
		DrawLine(-length / 4, 0);
		DrawLine(length / 8, length * 3 / 8);
		EndFilledRegion();

		MovePen(mx - length * 3 / 8, my);
		StartFilledRegion(0.6);
		DrawLine(-length / 8, length * 3 / 8);
		DrawLine(length / 4, 0);
		DrawLine(length / 8, -length * 3 / 8);
		DrawLine(-length / 8, -length * 3 / 8);
		DrawLine(-length / 4, 0);
		DrawLine(length / 8, length * 3 / 8);
		EndFilledRegion();

		break;

	case 3:

		MovePen(mx, my - length / 8);
		StartFilledRegion(0.6);
		DrawLine(length * 3 / 8, length / 8);
		DrawLine(0, -length / 4);
		DrawLine(-length * 3 / 8, -length / 8);
		DrawLine(-length * 3 / 8, length / 8);
		DrawLine(0, length / 4);
		DrawLine(length * 3 / 8, -length / 8);
		EndFilledRegion();

		MovePen(mx, my + length * 3 / 8);
		StartFilledRegion(0.6);
		DrawLine(length * 3 / 8, length / 8);
		DrawLine(0, -length / 4);
		DrawLine(-length * 3 / 8, -length / 8);
		DrawLine(-length * 3 / 8, length / 8);
		DrawLine(0, length / 4);
		DrawLine(length * 3 / 8, -length / 8);
		EndFilledRegion();

		break;

	case 4:

		MovePen(mx - length / 8, my);
		StartFilledRegion(0.6);
		DrawLine(length / 8, length * 3 / 8);
		DrawLine(-length / 4, 0);
		DrawLine(-length / 8, -length * 3 / 8);
		DrawLine(length / 8, -length * 3 / 8);
		DrawLine(length / 4, 0);
		DrawLine(-length / 8, length * 3 / 8);
		EndFilledRegion();

		MovePen(mx + length * 3 / 8, my);
		StartFilledRegion(0.6);
		DrawLine(length / 8, length * 3 / 8);
		DrawLine(-length / 4, 0);
		DrawLine(-length / 8, -length * 3 / 8);
		DrawLine(length / 8, -length * 3 / 8);
		DrawLine(length / 4, 0);
		DrawLine(-length / 8, length * 3 / 8);
		EndFilledRegion();

		break;

	case 5:

		MovePen(mx + length * 3 / 8, my - length * 3 / 8);
		StartFilledRegion(0.6);
		DrawLine(0, length * 9 / 16);
		DrawArc(length * 9 / 16, 90, 90);
		DrawLine(length * 9 / 16, 0);
		EndFilledRegion();
		SetPenColor("Light Light Gray");
		StartFilledRegion(1);
		DrawLine(0,length*3/16);
		DrawArc(length * 3 / 16, 90, 90);
		DrawLine(length*3/16,0);
		EndFilledRegion();
		SetPenColor("SafeWayGreen");

		break;

	case 6:

		MovePen(mx + length * 3 / 8, my + length * 3 / 8);
		StartFilledRegion(0.6);
		DrawLine(-length * 9 / 16, 0);
		DrawArc(length * 9 / 16, 180, 90);
		DrawLine(0, length * 9 / 16);
		EndFilledRegion();
		SetPenColor("Light Light Gray");
		StartFilledRegion(1);
		DrawLine(-length*3/16,0);
		DrawArc(length * 3 / 16, 180, 90);
		DrawLine(0,length*3/16);
		EndFilledRegion();
		SetPenColor("SafeWayGreen");

		break;

	case 7:

		MovePen(mx - length * 3 / 8, my + length * 3 / 8);
		StartFilledRegion(0.6);
		DrawLine(0, -length * 9 / 16);
		DrawArc(length * 9 / 16, 270, 90);
		DrawLine(-length * 9 / 16, 0);
		EndFilledRegion();
		SetPenColor("Light Light Gray");
		StartFilledRegion(1);
		DrawLine(0,-length*3/16);
		DrawArc(length * 3 / 16, 270, 90);
		DrawLine(-length*3/16,0);
		EndFilledRegion();
		SetPenColor("SafeWayGreen");

		break;

	case 8:

		MovePen(mx - length * 3 / 8, my - length * 3 / 8);
		StartFilledRegion(0.6);
		DrawLine(length * 9 / 16, 0);
		DrawArc(length * 9 / 16, 0, 90);
		DrawLine(0, -length * 9 / 16);
		EndFilledRegion();
		SetPenColor("Light Light Gray");
		StartFilledRegion(1);
		DrawLine(length*3/16,0);
		DrawArc(length * 3 / 16, 0, 90);
		DrawLine(0,-length*3/16);
		EndFilledRegion();
		SetPenColor("SafeWayGreen");

		break;
	}

	SetPenColor("Black");
}
