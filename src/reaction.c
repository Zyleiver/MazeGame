#include "MyHeader.h"

void myMouseEvent(int x, int y, int button, int event)
{
    uiGetMouse(x, y, button, event);
    static double mouse_x;
    static double mouse_y;

    mouse_x = ScaleXInches(x);
    mouse_y = ScaleYInches(y);
    if (button == LEFT_BUTTON && event == Button_DOWN)
    {
        if (TellPress(mouse_x, mouse_y, Instruction))
        {
            //
        }
        else if (TellPress(mouse_x, mouse_y, About_Game))
        {
            //
        }
        else
        {
            switch (page_stage)
            {
            case MAIN_PAGE:

                MainPageTell(mouse_x, mouse_y);

                break;

            case GAME_PAGE:

                GamePageTell(mouse_x, mouse_y);

                break;

            case END_PAGE:

                break;
            }
        }
    }
}

// 主页面按钮触发事件
void MainPageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, StartNewGame)) // 按下开启新游戏
    {
        StartNewGamePage();
    }
    else if (TellPress(mouse_x, mouse_y, ReadFiles)) // 按下读取存档
    {
        ReadData();
        ReadFilesPage();
        // 待定
    }
    else if (TellPress(mouse_x, mouse_y, ExitGame)) // 按下退出游戏
    {
        Exit();
    }
    else if (TellPress(mouse_x, mouse_y, BuildMapAuto)) // 按下自动生成地图
    {
        CreateNewMap();
        page_stage = GAME_PAGE;
    }
    else if (TellPress(mouse_x, mouse_y, BuildMapManu)) // 按下手动创建地图
    {
        BuildMapManuPage();
    }
    else if (TellPress(mouse_x, mouse_y, EmptyMap)) // 按下空白地图
    {
        page_stage = GAME_PAGE;
        BuildMap();
    }
    else if (TellPress(mouse_x, mouse_y, UseTemp)) // 按下使用模板
    {
        UseTempPage();
        // 待定
    }
    else if (TellPress(mouse_x, mouse_y, TempFromFile)) // 按下存档模板
    {
        ReadTemplate();
        // 待定
    }
    else if (TellPress(mouse_x, mouse_y, TempFromSys)) // 按下系统模板
    {
        ReadSysTemplate();
        // 待定
    }
}

/**************************************************
功能：判断有无触发按钮
输入：double mouse_x, double mouse_y, Button Butt
输出：0——未触发，1——触发
**************************************************/
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

// 主页面全部按钮不可见
void MainAllUnvisible(void)
{
    StartNewGame.visible = UNVISIBLE;
    ReadFiles.visible = UNVISIBLE;
    ExitGame.visible = UNVISIBLE;
    BuildMapAuto.visible = UNVISIBLE;
    BuildMapManu.visible = UNVISIBLE;
    EmptyMap.visible = UNVISIBLE;
    UseTemp.visible = UNVISIBLE;
    TempFromSys.visible = UNVISIBLE;
    TempFromFile.visible = UNVISIBLE;
}

// 进入自动生成地图和手动创建地图选择页面
void StartNewGamePage(void)
{
    MainAllUnvisible();
    BuildMapAuto.visible = VISIBLE;
    BuildMapManu.visible = VISIBLE;
}

// 进入存档选择页面
void ReadFilesPage(void)
{
    MainAllUnvisible();
    // 待定
}

// 进入空白地图、使用模板页面
void BuildMapManuPage(void)
{
    MainAllUnvisible();
    EmptyMap.visible = UNVISIBLE;
    UseTemp.visible = UNVISIBLE;
}

// 进入系统目标、存档模板界面
void UseTempPage(void)
{
    MainAllUnvisible();
    TempFromSys.visible = VISIBLE;
    TempFromFile.visible = VISIBLE;
}

// 游戏界面按钮事件
void GamePageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, Menu))
    {
        PageMenu();
    }
    else if (TellPress(mouse_x, mouse_y, Tools))
    {
        PageTools();
    }
    else if (TellPress(mouse_x, mouse_y, CrtNewMap))
    {
        CreateMap_ingame();
        GameAllPageUnvisible();
    }
    else if (TellPress(mouse_x, mouse_y, OpenMap))
    {
        OpenMap_ingame();
        GameAllPageUnvisible;
    }
    else if (TellPress(mouse_x, mouse_y, SaveGame))
    {
        SaveGame_ingame();
    }
    else if (TellPress(mouse_x, mouse_y, SaveAsTemp))
    {
        SaveAsTemplate();
    }
    else if (TellPress(mouse_x, mouse_y, BackToMP))
    {
        page_stage = MAIN_PAGE;
        InitGame();
    }
    else if (TellPress(mouse_x, mouse_y, EditMap))
    {
        GameAllPageUnvisible();
        BuildMap();
    }
    else if (TellPress(mouse_x, mouse_y, PromptNextStep))
    {
        next_move(MajorRole.x, MajorRole.y);
    }
    else if (TellPress(mouse_x, mouse_y, ShowShortestPath))
    {
        //
    }
    else if (TellPress(mouse_x, mouse_y, ShowAllPath))
    {
        //
    }
    else if (TellPress(mouse_x, mouse_y, LeftShiftPath))
    {
        //
    }
    else if (TellPress(mouse_x, mouse_y, RightShiftPath))
    {
        //
    }
    
}

void GameAllPageUnvisible(void)
{
    Menu.visible = UNVISIBLE;
    CrtNewMap.visible = UNVISIBLE;
    OpenMap.visible = UNVISIBLE;
    SaveGame.visible = UNVISIBLE;
    SaveAsTemp.visible = UNVISIBLE;
    BackToMP.visible = UNVISIBLE;
    Tools.visible = UNVISIBLE;
    EditMap.visible = UNVISIBLE;
    PromptNextStep.visible = UNVISIBLE;
    ShowShortestPath.visible = UNVISIBLE;
    ShowAllPath.visible = UNVISIBLE;
    LeftShiftPath.visible = UNVISIBLE;
    RightShiftPath.visible = UNVISIBLE;
}

// 点击菜单页面
void PageMenu(void)
{
    GameAllPageUnvisible();
    CrtNewMap.visible = VISIBLE;
    OpenMap.visible = VISIBLE;
    SaveGame.visible = VISIBLE;
    SaveAsTemp.visible = VISIBLE;
    BackToMP.visible = VISIBLE;
}

// 点击工具页面
void PageTools(void)
{
    GameAllPageUnvisible();
    EditMap.visible = VISIBLE;
    PromptNextStep.visible = VISIBLE;
    ShowShortestPath.visible = VISIBLE;
    ShowAllPath.visible = VISIBLE;
}

void myKeyboardEvent(int key, int event)
{
    uiGetKeyboard(key, event);
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
    if (Map(MajorRole.x, MajorRole.y + 1) != WALL)
    {
        MajorRole.y++;
    }
}

// 角色向下运动
void Movedown(void)
{
    if (Map(MajorRole.x, MajorRole.y - 1) != WALL)
    {
        MajorRole.y--;
    }
}

// 角色向左运动
void Moveleft(void)
{
    if (Map(MajorRole.x - 1, MajorRole.y) != WALL)
    {
        MajorRole.x--;
    }
}

// 角色向右运动
void Moveright(void)
{
    if (Map(MajorRole.x + 1, MajorRole.y) != WALL)
    {
        MajorRole.x++;
    }
}

void mycharEvent(char ch)
{
    if (page_stage == GAME_PAGE)
    {
        if (ifctrl == 1)
        {
            switch (ch)
            {
            case 'c': // 新建地图
                page_stage = MAIN_PAGE;
                StartNewGamePage();
                break;

            case 'o': // 打开地图
                OpenMap_ingame();
                break;

            case 's': // 保存地图
                SaveGame_ingame();
                break;

            case 'm'://保存为模板
                SaveAsTemplate();
                break;

            case 'b'://回到主页面
                page_stage=MAIN_PAGE;
                MainAllUnvisible();
                
            }
        }
    }
}


void Exit(void)
{
}

void CreateMap_ingame(void)
{
}

void OpenMap_ingame(void)
{
}

void BackToMainPage(void)
{
}

void TellStuff(void)
{
}
