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

// ��ҳ�水ť�����¼�
void MainPageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, StartNewGame)) // ���¿�������Ϸ
    {
        StartNewGamePage();
    }
    else if (TellPress(mouse_x, mouse_y, ReadFiles)) // ���¶�ȡ�浵
    {
        ReadData();
        ReadFilesPage();
        // ����
    }
    else if (TellPress(mouse_x, mouse_y, ExitGame)) // �����˳���Ϸ
    {
        Exit();
    }
    else if (TellPress(mouse_x, mouse_y, BuildMapAuto)) // �����Զ����ɵ�ͼ
    {
        CreateNewMap();
        page_stage = GAME_PAGE;
    }
    else if (TellPress(mouse_x, mouse_y, BuildMapManu)) // �����ֶ�������ͼ
    {
        BuildMapManuPage();
    }
    else if (TellPress(mouse_x, mouse_y, EmptyMap)) // ���¿հ׵�ͼ
    {
        page_stage = GAME_PAGE;
        BuildMap();
    }
    else if (TellPress(mouse_x, mouse_y, UseTemp)) // ����ʹ��ģ��
    {
        UseTempPage();
        // ����
    }
    else if (TellPress(mouse_x, mouse_y, TempFromFile)) // ���´浵ģ��
    {
        ReadTemplate();
        // ����
    }
    else if (TellPress(mouse_x, mouse_y, TempFromSys)) // ����ϵͳģ��
    {
        ReadSysTemplate();
        // ����
    }
}

/**************************************************
���ܣ��ж����޴�����ť
���룺double mouse_x, double mouse_y, Button Butt
�����0����δ������1��������
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

// ��ҳ��ȫ����ť���ɼ�
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

// �����Զ����ɵ�ͼ���ֶ�������ͼѡ��ҳ��
void StartNewGamePage(void)
{
    MainAllUnvisible();
    BuildMapAuto.visible = VISIBLE;
    BuildMapManu.visible = VISIBLE;
}

// ����浵ѡ��ҳ��
void ReadFilesPage(void)
{
    MainAllUnvisible();
    // ����
}

// ����հ׵�ͼ��ʹ��ģ��ҳ��
void BuildMapManuPage(void)
{
    MainAllUnvisible();
    EmptyMap.visible = UNVISIBLE;
    UseTemp.visible = UNVISIBLE;
}

// ����ϵͳĿ�ꡢ�浵ģ�����
void UseTempPage(void)
{
    MainAllUnvisible();
    TempFromSys.visible = VISIBLE;
    TempFromFile.visible = VISIBLE;
}

// ��Ϸ���水ť�¼�
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

// ����˵�ҳ��
void PageMenu(void)
{
    GameAllPageUnvisible();
    CrtNewMap.visible = VISIBLE;
    OpenMap.visible = VISIBLE;
    SaveGame.visible = VISIBLE;
    SaveAsTemp.visible = VISIBLE;
    BackToMP.visible = VISIBLE;
}

// �������ҳ��
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

// ��ɫ�����ƶ�
void Moveup(void)
{
    if (Map(MajorRole.x, MajorRole.y + 1) != WALL)
    {
        MajorRole.y++;
    }
}

// ��ɫ�����˶�
void Movedown(void)
{
    if (Map(MajorRole.x, MajorRole.y - 1) != WALL)
    {
        MajorRole.y--;
    }
}

// ��ɫ�����˶�
void Moveleft(void)
{
    if (Map(MajorRole.x - 1, MajorRole.y) != WALL)
    {
        MajorRole.x--;
    }
}

// ��ɫ�����˶�
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
            case 'c': // �½���ͼ
                page_stage = MAIN_PAGE;
                StartNewGamePage();
                break;

            case 'o': // �򿪵�ͼ
                OpenMap_ingame();
                break;

            case 's': // �����ͼ
                SaveGame_ingame();
                break;

            case 'm'://����Ϊģ��
                SaveAsTemplate();
                break;

            case 'b'://�ص���ҳ��
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
