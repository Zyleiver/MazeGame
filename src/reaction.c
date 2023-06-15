#include "MyHeader.h"

// 全部按钮不可见(除使用说明和关于)
void AllUnvisible(void)
{
    int j=0;
    for(j;j<25;j++){
        ButtonEnum[j].visible=UNVISIBLE;
    }
    ButtonEnum[Instruction].visible=VISIBLE;
    ButtonEnum[About_Game].visible=VISIBLE;
}

//判断有无触发按钮
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

void myMouseEvent(int x, int y, int button, int event)
{
    static double mouse_x;
    static double mouse_y;

    mouse_x = ScaleXInches(x);
    mouse_y = ScaleYInches(y);

    if (button == LEFT_BUTTON && event == BUTTON_DOWN)
    {	
    	printf("%.0f %.0f | ",mouse_x,mouse_y);
        if (TellPress(mouse_x, mouse_y, ButtonEnum[Instruction]))//点击使用说明
        {
            Instruct();
        }
        else if (TellPress(mouse_x, mouse_y, ButtonEnum[About_Game]))//点击关于
        {
            AboutGame();
        }else if(TellPress(mouse_x,mouse_y,ButtonEnum[Back]))
        {
            if(ButtonEnum[CrtNewMap].stage==Button_DOWN){
                ShiftPageTo(MENU_PAGE);
                ButtonEnum[CrtNewMap].stage=Button_UP;
            }else if(page_stage==CHOSEMAP_PAGE){
                ShiftPageTo(MAIN_PAGE);
            }
        }
        else
        {
            switch (page_stage)
            {
            case MAIN_PAGE://主页面状态

                MainPageTell(mouse_x, mouse_y);

                break;

            case GAME_PAGE://游戏页面状态

                GamePageTell(mouse_x, mouse_y);

                break;
                
            case CHOSEMAP_PAGE://选择生成地图方式界面

                ChoseMapPageTell(mouse_x,mouse_y);
                break;

            case EDIT_PAGE://游戏编辑界面

                EditPageTell(mouse_x,mouse_y);
                break;

            case MENU_PAGE://菜单界面

                MenuPageTell(mouse_x,mouse_y);
                break;

            case TOOL_PAGE://工具界面

                ToolPageTell(mouse_x,mouse_y);
                break;

            case END_PAGE://结束页面状态


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
        
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[ReadFiles])) // 按下读取存档
    {
        if(ReadData())
        {
            ShiftPageTo(GAME_PAGE);
        }
        
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[ExitGame])) // 按下退出游戏
    {
        _exit(0);

    }
    
}

//选择地图生成方式界面按钮触发事件
void ChoseMapPageTell(double mouse_x,double mouse_y)
{
    if(TellPress(mouse_x,mouse_y,ButtonEnum[BuildMapAuto]))
    {
        CreateNewMap();
        ShiftPageTo(GAME_PAGE);
    }else if(TellPress(mouse_x,mouse_y,ButtonEnum[BuildMapManu]))
    {
        ShiftPageTo(EDIT_PAGE);
    }
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
 
}


// 菜单界面按钮触发事件
void MenuPageTell(double mouse_x, double mouse_y)
{
    if(TellPress(mouse_x,mouse_y,ButtonEnum[CrtNewMap]))
    {
        ButtonEnum[CrtNewMap].stage=Button_DOWN;
        ShiftPageTo(CHOSEMAP_PAGE);
        
    }else if(TellPress(mouse_x,mouse_y,ButtonEnum[OpenMap]))
    {
        ReadData();
    }else if(TellPress(mouse_x,mouse_y,ButtonEnum[SaveGame]))
    {
        saveMap();
    }else if(TellPress(mouse_x,mouse_y,ButtonEnum[BackToMP]))
    {
        ShiftPageTo(MAIN_PAGE);
    }else{
        ShiftPageTo(GAME_PAGE);
    }
    
}

//编辑界面按钮事件
void EditPageTell (double mouse_x,double mouse_y)
{

}

//工具界面按钮触发事件
void ToolPageTell(double mouse_x,double mouse_y)
{
    if(TellPress(mouse_x,mouse_y,ButtonEnum[PromptNextStep]))
    {
        next_move();
        ButtonEnum[PromptNextStep].stage=1-ButtonEnum[PromptNextStep].stage;
        ButtonEnum[ShowAllPath].stage=Button_UP;
        ButtonEnum[LeftShiftPath].visible=UNVISIBLE;
        ButtonEnum[RightShiftPath].visible=UNVISIBLE;
        ButtonEnum[ShowShortestPath].stage=Button_UP;
        ShiftPageTo(GAME_PAGE);
    }else if(TellPress(mouse_x,mouse_y,ButtonEnum[ShowShortestPath]))
    {   
        ButtonEnum[ShowShortestPath].stage=1-ButtonEnum[ShowShortestPath].stage;
        find_way_shortest(MajorRole.x,MajorRole.y);

        ButtonEnum[PromptNextStep].stage=Button_UP;
        ButtonEnum[ShowAllPath].stage=Button_UP;
        ButtonEnum[LeftShiftPath].visible=UNVISIBLE;
        ButtonEnum[RightShiftPath].visible=UNVISIBLE;
        ShiftPageTo(GAME_PAGE);
    }else if(TellPress(mouse_x,mouse_y,ButtonEnum[ShowAllPath]))
    {   
        ButtonEnum[ShowAllPath].stage=1-ButtonEnum[ShowAllPath].stage;
        ButtonEnum[LeftShiftPath].visible=1-ButtonEnum[LeftShiftPath].visible;
        ButtonEnum[RightShiftPath].visible=1-ButtonEnum[RightShiftPath].visible;
        ButtonEnum[PromptNextStep].stage=Button_UP;
        ButtonEnum[ShowShortestPath].stage=Button_UP;
    }else{
        ShiftPageTo(GAME_PAGE);
    }
}

int ifctrl=0;
int ifshift=0;

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
    if (Map[MajorRole.x][MajorRole.y + 1] != WALL)
    {
        MajorRole.y=MajorRole.y+2;
    }
}

// 角色向下运动
void Movedown(void)
{
    if (Map[MajorRole.x][ MajorRole.y - 1] != WALL)
    {
        MajorRole.y=MajorRole.y-2;
    }
}

// 角色向左运动
void Moveleft(void)
{
    if (Map[MajorRole.x - 1][MajorRole.y] != WALL)
    {
		MajorRole.x=MajorRole.x-2;
        
    }
}

// 角色向右运动
void Moveright(void)
{
    if (Map[MajorRole.x + 1][MajorRole.y] != WALL)
    {
        MajorRole.x=MajorRole.x+2;
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
                ShiftPageTo(MAIN_PAGE);
                break;

            case 'o': // 打开地图
                OpenMap_ingame();
                break;

            case 's': // 保存地图
                SaveGame_ingame();
                break;


            case 'b'://回到主页面
                ShiftPageTo(MAIN_PAGE);

            }
        }else if(ifshift==1)
        {
            switch (ch)
            {
            case 'p'://提示下一步
                next_move();
                break;
            
            case 'r'://显示最短路径
                find_way_shortest(MajorRole.x,MajorRole.y);
                break;

            case 'a'://显示全部路径
                find_way_all(MajorRole.x,MajorRole.y);
                break;

            }
           
        }else
        {
            switch (ch)//判断wasd控制的上下左右移动
            {
                case 'a'://人物左移
                    Moveleft();
                    break;

                case 'd'://人物右移
                    Moveright();
                    break;

                case 'w'://人物上移
                    Moveup();
                    break;

                case 's'://人物下移
                    Movedown();
                    break;
            }
        }
    }
}


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


