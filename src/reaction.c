#include "MyHeader.h"

int putting; // 正在编辑的模块
int editx;   // 编辑地图的x坐标
int edity;   // 编辑地图的y坐标

int ifpre; // 是否显示预览

int aboutstage; //存储打开关于前的页面状态 

// 鼠标变成手指
void setMouseCursorHand()
{
    // 获取当前进程的窗口句柄
    HWND hWnd = GetForegroundWindow();

    // 加载手指光标资源
    HCURSOR handCursor = LoadCursor(NULL, IDC_HAND);

    // 设置鼠标指针
    SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR)handCursor);
    SetCursor(handCursor);
}

// 鼠标变成箭头
void setMouseCursorArrow()
{
    // 获取当前进程的窗口句柄
    HWND hWnd = GetForegroundWindow();

    // 加载箭头光标资源
    HCURSOR arrowCursor = LoadCursor(NULL, IDC_ARROW);

    // 设置鼠标指针
    SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR)arrowCursor);
    SetCursor(arrowCursor);
}

// 全部按钮不可见(除使用说明和关于)
void AllUnvisible(void)
{
    int j = 0;
    for (j; j < ButtonNum; j++)
    {
        if (j != LeftShiftPath && j != RightShiftPath)
            ButtonEnum[j].visible = UNVISIBLE;
    }
    ButtonEnum[Instruction].visible = VISIBLE;
    ButtonEnum[About_Game].visible = VISIBLE;
}

// 全部按钮松开
void AllButtonUp(void)
{
    int j = 0;
    for (j; j < ButtonNum; j++)
    {
        ButtonEnum[j].stage = Button_UP;
    }
}

// 判断有无触发按钮
int TellPress(double mouse_x, double mouse_y, Button Butt)
{
    if (Butt.visible == VISIBLE)
    {
        if (mouse_x > Butt.x && mouse_x < Butt.x + Butt.lx)
        {
            if (mouse_y > Butt.y && mouse_y < Butt.y + Butt.ly)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

// 判断鼠标是否在按钮上
int TellOn(double mouse_x, double mouse_y, Button Butt)
{
    if (mouse_x > Butt.x && mouse_x < Butt.x + Butt.lx)
    {
        if (mouse_y > Butt.y && mouse_y < Butt.y + Butt.ly)
        {
            return 1;
        }
    }
    return 0;
}

// 鼠标事件
void myMouseEvent(int x, int y, int button, int event)
{
    uiGetMouse(x, y, button, event);
    static double mouse_x;
    static double mouse_y;

    mouse_x = ScaleXInches(x);
    mouse_y = ScaleYInches(y);

    if (button == LEFT_BUTTON && event == BUTTON_DOWN)
    {
        if (TellPress(mouse_x, mouse_y, ButtonEnum[Instruction])) // 点击使用说明
        {
            Instruct();
        }
        else if (TellPress(mouse_x, mouse_y, ButtonEnum[About_Game])) // 点击关于
        {
        	if(page_stage != INSTRUCT_PAGE)
        	aboutstage = page_stage;
            AboutGame();
        }
        else if (TellPress(mouse_x, mouse_y, ButtonEnum[Back])) // 点击回退
        {
            if (ButtonEnum[CrtNewMap].stage == Button_DOWN)
            {
                ShiftPageTo(MENU_PAGE);
            }
            else if (page_stage == CHOSEMAP_PAGE)
            {
                ShiftPageTo(MAIN_PAGE);
            }
            else if (page_stage == INSTRUCT_PAGE)
            {
            	ShiftPageTo(aboutstage);
			}
            ButtonEnum[CrtNewMap].stage = Button_UP;
            AllButtonUp();
        }
        else
        {
            switch (page_stage)
            {
            case MAIN_PAGE: // 主页面状态

                MainPageTell(mouse_x, mouse_y);

                break;

            case GAME_PAGE: // 游戏页面状态

                GamePageTell(mouse_x, mouse_y);

                break;

            case CHOSEMAP_PAGE: // 选择生成地图方式界面

                ChoseMapPageTell(mouse_x, mouse_y);
                break;

            case EDIT_PAGE: // 游戏编辑界面

                EditPageTell(mouse_x, mouse_y);
                break;

            case MENU_PAGE: // 菜单界面

                MenuPageTell(mouse_x, mouse_y);
                break;

            case TOOL_PAGE: // 工具界面

                ToolPageTell(mouse_x, mouse_y);
                break;

            case END_PAGE: // 结束页面状态

                break;
            }
        }
    }

    if (event == MOUSEMOVE)
    {
        int i;
        int isON;

        isON = 0;

        for (i = 0; i < ButtonNum; i++)
        {
            if (ButtonEnum[i].visible == VISIBLE && TellOn(mouse_x, mouse_y, ButtonEnum[i]))
            {
                isON = 1;
                setMouseCursorHand();
            }
        }
        if (!isON)
        {
            setMouseCursorArrow();
        }

        ifpre = 0;
        if (page_stage == EDIT_PAGE)
        {
            switch (putting)
            {
            case PutWall:
                if (TellWall(mouse_x, mouse_y))
                {
                    setMouseCursorHand();
                    ifpre = 1;
                }
                break;

            case PutCoin:
            case PutRole:
            case PutGoal:
                if (TellRoad(mouse_x, mouse_y))
                {
                    setMouseCursorHand();
                    if (Map[editx][edity] == COIN || Map[editx][edity] == START || Map[editx][edity] == END)
                    {
                        ifpre = 0;
                    }
                    else
                    {
                        ifpre = 1;
                    }
                }
                break;

            case Erase:
                if (TellWall(mouse_x, mouse_y))
                {
                    setMouseCursorHand();
                    ifpre = 1;
                }
                else if (TellRoad(mouse_x, mouse_y))
                {
                    setMouseCursorHand();
                }
                break;
            }
        }
    }
}

// 主页面按钮触发事件
void MainPageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, ButtonEnum[StartNewGame])) // 按下开启新游戏
    {
        ShiftPageTo(CHOSEMAP_PAGE);
        AllButtonUp();
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[ReadFiles])) // 按下读取存档
    {

        if (ReadData())
        {
            ShiftPageTo(GAME_PAGE);
        }
        else
        {
            int ReadFailed = MessageBox(NULL, "读取失败", "提醒", MB_OK | MB_ICONINFORMATION);
        }

        AllButtonUp();
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[ExitGame])) // 按下退出游戏
    {
        _exit(0);
    }
}

// 选择地图生成方式界面按钮触发事件
void ChoseMapPageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, ButtonEnum[BuildMapAuto]))
    {
        AllButtonUp();
        xscale = atoi(mapx);
        yscale = atoi(mapy);
        monsternum = atoi(monsnum);
        coinNum = atoi(coinnum);
        MZX = xscale * 2 - 1;
        MZY = yscale * 2 - 1;
        int CodCrt = 1;
        if (xscale < 4)
        {
            int xlow = MessageBox(NULL, "x值太小", "提醒", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (xscale > 40)
        {
            int xmuch = MessageBox(NULL, "x值太大", "提醒", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (yscale < 4)
        {
            int ylow = MessageBox(NULL, "y值太小", "提醒", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (yscale > 40)
        {
            int ymuch = MessageBox(NULL, "y值太大", "提醒", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (monsternum < 0)
        {
            int monslow = MessageBox(NULL, "怪兽数量不得为负数", "提醒", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (monsternum > 999)
        {
            int monsmuch = MessageBox(NULL, "怪兽数量过多", "提醒", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (coinNum < 0)
        {
            int coinlow = MessageBox(NULL, "金币数量不得为负数", "提醒", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (coinNum > (int)((double)(xscale * yscale) * 7 / 9))
        {
            int coinmuch = MessageBox(NULL, "金币数量过多", "提醒", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }

        if (CodCrt)
        {
            CreateNewMap();
            ShiftPageTo(GAME_PAGE);
        }
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[BuildMapManu]))
    {
        AllButtonUp();
        xscale = atoi(mapx);
        yscale = atoi(mapy);
        monsternum = atoi(monsnum);
        coinNum = atoi(coinnum);
        MZX = xscale * 2 - 1;
        MZY = yscale * 2 - 1;
        int CodBld = 1;

        printf("\n%d\n", yscale);
        if (xscale < 4)
        {
            int xlow = MessageBox(NULL, "x值太小", "提醒", MB_OK | MB_ICONINFORMATION);
            CodBld = 0;
        }
        else if (xscale > 40)
        {
            int xmuch = MessageBox(NULL, "x值太大", "提醒", MB_OK | MB_ICONINFORMATION);
            CodBld = 0;
        }
        else if (yscale < 4)
        {
            int ylow = MessageBox(NULL, "y值太小", "提醒", MB_OK | MB_ICONINFORMATION);
            CodBld = 0;
        }
        else if (yscale > 40)
        {
            int ymuch = MessageBox(NULL, "y值太大", "提醒", MB_OK | MB_ICONINFORMATION);
            CodBld = 0;
        }
        else if (monsternum < 0)
        {
            int monslow = MessageBox(NULL, "怪兽数量不得为负数", "提醒", MB_OK | MB_ICONINFORMATION);
            CodBld = 0;
        }
        else if (monsternum > 999)
        {
            int monsmuch = MessageBox(NULL, "怪兽数量过多", "提醒", MB_OK | MB_ICONINFORMATION);
            CodBld = 0;
        }

        if (CodBld)
        {
            ShiftPageTo(EDIT_PAGE);
            BuildMap();
        }
    }
    ButtonEnum[CrtNewMap].stage = Button_UP;
}

// 游戏界面按钮触发事件
void GamePageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, ButtonEnum[Menu]))
    {
        ShiftPageTo(MENU_PAGE);
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[Tools]))
    {
        ShiftPageTo(TOOL_PAGE);
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[LeftShiftPath]))
    {
        if (pvisiter->last != NULL)
        {
            pvisiter = pvisiter->last;
            if (pvisiter->last == NULL)
            {
                ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
            }
            ButtonEnum[RightShiftPath].visible = VISIBLE;
        }
        ShiftPageTo(GAME_PAGE);
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[RightShiftPath]))
    {
        if (pvisiter->Next != NULL)
        {
            pvisiter = pvisiter->Next;
            if (pvisiter->Next == NULL)
            {
                ButtonEnum[RightShiftPath].visible = UNVISIBLE;
            }
            ButtonEnum[LeftShiftPath].visible = VISIBLE;
        }
        ShiftPageTo(GAME_PAGE);
    }
}

// 菜单界面按钮触发事件
void MenuPageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, ButtonEnum[CrtNewMap]))
    {
        ButtonEnum[CrtNewMap].stage = Button_DOWN;
        ShiftPageTo(CHOSEMAP_PAGE);
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[OpenMap]))
    {
        if (ReadData())
        {
            GameInit();
            AllButtonUp();
            ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
            ButtonEnum[RightShiftPath].visible = UNVISIBLE;
            ShiftPageTo(GAME_PAGE);
        }
        else
        {
            int OpenFailed = MessageBox(NULL, "打开失败", "提醒", MB_OK | MB_ICONINFORMATION);
        }
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[SaveGame]))
    {
        if (saveMap())
        {
            int Save = MessageBox(NULL, "保存成功", "提醒", MB_OK | MB_ICONINFORMATION);
            ShiftPageTo(GAME_PAGE);
        }
        else
        {
            int SaveFailed = MessageBox(NULL, "保存失败", "提醒", MB_OK | MB_ICONINFORMATION);
            ShiftPageTo(MENU_PAGE);
        }
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[BackToMP]))
    {
        AllButtonUp();
        ShiftPageTo(MAIN_PAGE);
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[LeftShiftPath]))
    {
        if (pvisiter->last != NULL)
        {
            pvisiter = pvisiter->last;
            if (pvisiter->last == NULL)
            {
                ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
            }
            ButtonEnum[RightShiftPath].visible = VISIBLE;
        }
        ShiftPageTo(GAME_PAGE);
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[RightShiftPath]))
    {
        if (pvisiter->Next != NULL)
        {
            pvisiter = pvisiter->Next;
            if (pvisiter->Next == NULL)
            {
                ButtonEnum[RightShiftPath].visible = UNVISIBLE;
            }
            ButtonEnum[LeftShiftPath].visible = VISIBLE;
        }
        ShiftPageTo(GAME_PAGE);
    }
    else
    {
        ShiftPageTo(GAME_PAGE);
    }
}

void AllEditButtonUp(void)
{
    ButtonEnum[PutWall].stage = Button_UP;
    ButtonEnum[PutRole].stage = Button_UP;
    ButtonEnum[PutGoal].stage = Button_UP;
    ButtonEnum[PutCoin].stage = Button_UP;
    ButtonEnum[Erase].stage = Button_UP;
}
// 编辑界面按钮事件
void EditPageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, ButtonEnum[Menu]))
    {
        int EditMenu = MessageBox(NULL, "请先完成编辑或退出编辑", "提醒", MB_OK | MB_ICONINFORMATION);
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[Tools]))
    {
        int EditTools = MessageBox(NULL, "请先完成编辑或退出编辑", "提醒", MB_OK | MB_ICONINFORMATION);
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[PutWall]))
    {
        AllEditButtonUp();
        ButtonEnum[PutWall].stage = Button_DOWN;
        putting = PutWall;
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[PutRole]))
    {
        AllEditButtonUp();
        ButtonEnum[PutRole].stage = Button_DOWN;
        putting = PutRole;
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[PutGoal]))
    {
        AllEditButtonUp();
        ButtonEnum[PutGoal].stage = Button_DOWN;
        putting = PutGoal;
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[PutCoin]))
    {
        AllEditButtonUp();
        ButtonEnum[PutCoin].stage = Button_DOWN;
        putting = PutCoin;
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[Erase]))
    {
        AllEditButtonUp();
        ButtonEnum[Erase].stage = Button_DOWN;
        putting = Erase;
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[Complete]))
    {
        int havend = 0;
        int a, b;
        for (a = 0; a < 100; a++)
        {
            for (b = 0; b < 100; b++)
            {
                if (Map[a][b] == END)
                {
                    havend = 1;
                }
            }
        }
        if (MajorRole.x > 0 && havend)
        {
            AllUnvisible();
            Monster[0].hp = 100;
            GameInit();
            ShiftPageTo(GAME_PAGE);
        }
        else
        {
            int EditComplete = MessageBox(NULL, "请放置起点与终点", "提醒", MB_OK | MB_ICONINFORMATION);
        }
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[Cancel]))
    {
        AllEditButtonUp();
        ShiftPageTo(CHOSEMAP_PAGE);
    }
    else
    {
        switch (putting)
        {
        case PutWall:
            if (TellWall(mouse_x, mouse_y))
            {
                // 将editx,edity,PutWall传递给编辑函数
                EditMap(editx, edity, putting);
            }
            break;

        case PutCoin:
        case PutRole:
        case PutGoal:
            if (TellRoad(mouse_x, mouse_y))
            {
                // 将editx,edity,(PutCoin/PutRole/PutGoal)传递给编辑函数
                EditMap(editx, edity, putting);
            }
            break;

        case Erase:
            if (TellWall(mouse_x, mouse_y))
            {
                // 将editx,edity,Erase传递给编辑函数
                EditMap(editx, edity, putting);
            }
            else if (TellRoad(mouse_x, mouse_y))
            {
                // 将editx,edity,Erase传递给编辑函数
                EditMap(editx, edity, putting);
            }
        }
    }
}

int TellWall(double x, double y)
{

    int i, j;
    for (i = 1; i <= 2 * xscale - 1; i++)
    {
        if (i % 2 == 1)
        {
            if (x >= X0 + length * (i - 1) / 2 && x <= X0 + length * (i + 1) / 2)
            {
                for (j = 1; j <= yscale - 1; j++)
                {
                    if (abs(y - (Y0 + length * j)) < 0.1)
                    {
                        editx = i;
                        edity = j * 2;
                        return 1;
                    }
                }
            }
        }
        else if (i % 2 == 0)
        {
            if (abs(x - (X0 + length * i / 2)) < 0.1)
            {
                for (j = 0; j < yscale; j++)
                {
                    if (y >= Y0 + length * j && y <= Y0 + length * (j + 1))
                    {
                        editx = i;
                        edity = j * 2 + 1;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int TellRoad(double x, double y)
{
    int i, j;
    for (i = 0; i < xscale; i++)
    {
        for (j = 0; j < yscale; j++)
        {
            if (x > X0 + length * i + 0.2 && x < X0 + length * (i + 1) - 0.2)
            {
                if (y > Y0 + length * j + 0.2 && y < Y0 + length * (j + 1) - 0.2)
                {
                    editx = i * 2 + 1;
                    edity = j * 2 + 1;
                    return 1;
                }
            }
        }
    }
    return 0;
}

// 工具界面按钮触发事件
void ToolPageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, ButtonEnum[PromptNextStep]))
    {
        if (next_move())
        {
            ButtonEnum[PromptNextStep].stage = 1 - ButtonEnum[PromptNextStep].stage;
            ButtonEnum[ShowAllPath].stage = Button_UP;
            ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
            ButtonEnum[RightShiftPath].visible = UNVISIBLE;
            ButtonEnum[ShowShortestPath].stage = Button_UP;
            ShiftPageTo(GAME_PAGE);
        }
        else
        {
            int noprom = MessageBox(NULL, "该地图无解", "提醒", MB_OK | MB_ICONINFORMATION);
        }
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[ShowShortestPath]))
    {
        if (find_way_shortest(MajorRole.x, MajorRole.y))
        {
            ButtonEnum[ShowShortestPath].stage = 1 - ButtonEnum[ShowShortestPath].stage;
            ButtonEnum[PromptNextStep].stage = Button_UP;
            ButtonEnum[ShowAllPath].stage = Button_UP;
            ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
            ButtonEnum[RightShiftPath].visible = UNVISIBLE;
            ShiftPageTo(GAME_PAGE);
        }
        else
        {
            int nosh = MessageBox(NULL, "该地图无解", "提醒", MB_OK | MB_ICONINFORMATION);
        }
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[ShowAllPath]))
    {
        if (find_way_all(MajorRole.x, MajorRole.y))
        {
            ButtonEnum[ShowAllPath].stage = 1 - ButtonEnum[ShowAllPath].stage;
            if (pvisiter->Next != NULL)
            {
                ButtonEnum[RightShiftPath].visible = VISIBLE;
            }
            else
            {
                ButtonEnum[RightShiftPath].visible = UNVISIBLE;
            }
            ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
            if (ButtonEnum[ShowAllPath].stage == Button_UP)
            {
                ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
                ButtonEnum[RightShiftPath].visible = UNVISIBLE;
            }
            ButtonEnum[PromptNextStep].stage = Button_UP;
            ButtonEnum[ShowShortestPath].stage = Button_UP;

            ShiftPageTo(GAME_PAGE);
        }
        else
        {
            int noway = MessageBox(NULL, "该地图无解", "提醒", MB_OK | MB_ICONINFORMATION);
        }
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[LeftShiftPath]))
    {
        if (pvisiter->last != NULL)
        {
            pvisiter = pvisiter->last;
            if (pvisiter->last == NULL)
            {
                ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
            }
            ButtonEnum[RightShiftPath].visible = VISIBLE;
        }
        ShiftPageTo(GAME_PAGE);
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[RightShiftPath]))
    {
        if (pvisiter->Next != NULL)
        {
            pvisiter = pvisiter->Next;
            if (pvisiter->Next == NULL)
            {
                ButtonEnum[RightShiftPath].visible = UNVISIBLE;
            }
            ButtonEnum[LeftShiftPath].visible = VISIBLE;
        }
        ShiftPageTo(GAME_PAGE);
    }
    else
    {
        ShiftPageTo(GAME_PAGE);
    }
}

int ifctrl = 0;
int ifshift = 0;

void myKeyboardEvent(int key, int event)
{
    uiGetKeyboard(key, event);
    // 判断是否按下Ctrl或Shift
    if (event == KEY_DOWN && key == VK_CONTROL)
    {
        ifctrl = 1;
    }
    else if (event == KEY_DOWN && key == VK_SHIFT)
    {
        ifshift = 1;
    }
    else if (event == KEY_UP && key == VK_CONTROL)
    {
        ifctrl = 0;
    }
    else if (event == KEY_UP && key == VK_SHIFT)
    {
        ifshift = 0;
    }

    // 按上下左右键角色移动
    if (page_stage == GAME_PAGE)
    {
        if (event == KEY_DOWN && key == VK_UP)
        {
            Moveup();
        }
        else if (event == KEY_DOWN && key == VK_DOWN)
        {
            Movedown();
        }
        else if (event == KEY_DOWN && key == VK_LEFT)
        {
            Moveleft();
        }
        else if (event == KEY_DOWN && key == VK_RIGHT)
        {
            Moveright();
        }
    }
}

// 角色向上移动
void Moveup(void)
{
    if (Map[MajorRole.x][MajorRole.y + 1] != WALL)
    {
        MajorRole.y = MajorRole.y + 2;
    }
}

// 角色向下运动
void Movedown(void)
{
    if (Map[MajorRole.x][MajorRole.y - 1] != WALL)
    {
        MajorRole.y = MajorRole.y - 2;
    }
}

// 角色向左运动
void Moveleft(void)
{
    if (Map[MajorRole.x - 1][MajorRole.y] != WALL)
    {
        MajorRole.x = MajorRole.x - 2;
    }
}

// 角色向右运动
void Moveright(void)
{
    if (Map[MajorRole.x + 1][MajorRole.y] != WALL)
    {
        MajorRole.x = MajorRole.x + 2;
    }
}

void mycharEvent(char ch)
{
	uiGetChar(ch);
	printf("ifctrl=%d,ifshift=%d,input=%c\n",ifctrl,ifshift,ch);
    if (page_stage == GAME_PAGE || page_stage == MENU_PAGE || page_stage == TOOL_PAGE)
    {
    	printf("%d\n",ifctrl);
    	printf("%c\n",ch);
        if (ifctrl == 1)
        {
            switch (ch)
            {
            case '':
			case 'C': 
			case 'c': // 新建地图
                ButtonEnum[CrtNewMap].stage = Button_DOWN;
                ShiftPageTo(CHOSEMAP_PAGE);
                break;

            case '':
			case 'X':
			case 'x': // 打开地图
                if (ReadData())
                {
                    GameInit();
                    AllButtonUp();
                    ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
                    ButtonEnum[RightShiftPath].visible = UNVISIBLE;
                    ShiftPageTo(GAME_PAGE);
                }
                else
                {
                    int OpenFailed = MessageBox(NULL, "打开失败", "提醒", MB_OK | MB_ICONINFORMATION);
                }
                break;
			
			case '':
            case 'V':
			case 'v': // 保存地图
                if (saveMap())
                {
                    int Save = MessageBox(NULL, "保存成功", "提醒", MB_OK | MB_ICONINFORMATION);
                    ShiftPageTo(GAME_PAGE);
                }
                else
                {
                    int SaveFailed = MessageBox(NULL, "保存失败", "提醒", MB_OK | MB_ICONINFORMATION);
                    ShiftPageTo(MENU_PAGE);
                }
                break;
                
			case '':
            case 'Q':
			case 'q': // 回到主页面
                AllButtonUp();
                ShiftPageTo(MAIN_PAGE);
            }
        }
        else if (ifshift == 1)
        {
            switch (ch)
            {
            case 'P':
			case 'p': // 提示下一步
                if (next_move())
                {
                    ButtonEnum[PromptNextStep].stage = 1 - ButtonEnum[PromptNextStep].stage;
                    ButtonEnum[ShowAllPath].stage = Button_UP;
                    ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
                    ButtonEnum[RightShiftPath].visible = UNVISIBLE;
                    ButtonEnum[ShowShortestPath].stage = Button_UP;
                    ShiftPageTo(GAME_PAGE);
                }
                else
                {
                    int noprom = MessageBox(NULL, "该地图无解", "提醒", MB_OK | MB_ICONINFORMATION);
                }
                break;

            case 'R':
			case 'r': // 显示最短路径
                if (find_way_shortest(MajorRole.x, MajorRole.y))
                {
                    ButtonEnum[ShowShortestPath].stage = 1 - ButtonEnum[ShowShortestPath].stage;
                    ButtonEnum[PromptNextStep].stage = Button_UP;
                    ButtonEnum[ShowAllPath].stage = Button_UP;
                    ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
                    ButtonEnum[RightShiftPath].visible = UNVISIBLE;
                    ShiftPageTo(GAME_PAGE);
                }
                else
                {
                    int nosh = MessageBox(NULL, "该地图无解", "提醒", MB_OK | MB_ICONINFORMATION);
                }
                break;

            case 'M':
			case 'm': // 显示全部路径
                if (find_way_all(MajorRole.x, MajorRole.y))
                {
                    ButtonEnum[ShowAllPath].stage = 1 - ButtonEnum[ShowAllPath].stage;
                    if (pvisiter->Next != NULL)
                    {
                        ButtonEnum[RightShiftPath].visible = VISIBLE;
                    }
                    else
                    {
                        ButtonEnum[RightShiftPath].visible = UNVISIBLE;
                    }
                    ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
                    if (ButtonEnum[ShowAllPath].stage == Button_UP)
                    {
                        ButtonEnum[LeftShiftPath].visible = UNVISIBLE;
                        ButtonEnum[RightShiftPath].visible = UNVISIBLE;
                    }
                    ButtonEnum[PromptNextStep].stage = Button_UP;
                    ButtonEnum[ShowShortestPath].stage = Button_UP;

                    ShiftPageTo(GAME_PAGE);
                }
                else
                {
                    int noway = MessageBox(NULL, "该地图无解", "提醒", MB_OK | MB_ICONINFORMATION);
                }
                break;
            }
        }
        else
        {
            switch (ch) // 判断wasd控制的上下左右移动
            {
            case 'A':
			case 'a': // 人物左移
                Moveleft();
                break;

            case 'D':
			case 'd': // 人物右移
                Moveright();
                break;

            case 'W':
			case 'w': // 人物上移
                Moveup();
                break;

            case 'S':
			case 's': // 人物下移
                Movedown();
                break;
            }
        }
    }
}

/*
void Exit(void)
{
    ExitGraphics();
}

void CreateMap_ingame(void)
{
    ShiftPageTo(MAIN_PAGE);

}

void OpenMap_ingame(void)
{
    InitGame();
    ReadData();

}

void BackToMainPage(void)
{
    InitGame();
}
*/



