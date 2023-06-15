#include "MyHeader.h"

// ȫ����ť���ɼ�(��ʹ��˵���͹���)
void AllUnvisible(void)
{
    int j=0;
    for(j;j<25;j++){
        ButtonEnum[j].visible=UNVISIBLE;
    }
    ButtonEnum[Instruction].visible=VISIBLE;
    ButtonEnum[About_Game].visible=VISIBLE;
}

//�ж����޴�����ť
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
        if (TellPress(mouse_x, mouse_y, ButtonEnum[Instruction]))//���ʹ��˵��
        {
            Instruct();
        }
        else if (TellPress(mouse_x, mouse_y, ButtonEnum[About_Game]))//�������
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
            case MAIN_PAGE://��ҳ��״̬

                MainPageTell(mouse_x, mouse_y);

                break;

            case GAME_PAGE://��Ϸҳ��״̬

                GamePageTell(mouse_x, mouse_y);

                break;
                
            case CHOSEMAP_PAGE://ѡ�����ɵ�ͼ��ʽ����

                ChoseMapPageTell(mouse_x,mouse_y);
                break;

            case EDIT_PAGE://��Ϸ�༭����

                EditPageTell(mouse_x,mouse_y);
                break;

            case MENU_PAGE://�˵�����

                MenuPageTell(mouse_x,mouse_y);
                break;

            case TOOL_PAGE://���߽���

                ToolPageTell(mouse_x,mouse_y);
                break;

            case END_PAGE://����ҳ��״̬


                break;
            }
        }
    }
}

// ��ҳ�水ť�����¼�
void MainPageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, ButtonEnum[StartNewGame])) // ���¿�������Ϸ
    {
        ShiftPageTo(CHOSEMAP_PAGE);
        
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[ReadFiles])) // ���¶�ȡ�浵
    {
        if(ReadData())
        {
            ShiftPageTo(GAME_PAGE);
        }
        
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[ExitGame])) // �����˳���Ϸ
    {
        _exit(0);

    }
    
}

//ѡ���ͼ���ɷ�ʽ���水ť�����¼�
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


// ��Ϸ���水ť�����¼�
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


// �˵����水ť�����¼�
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

//�༭���水ť�¼�
void EditPageTell (double mouse_x,double mouse_y)
{

}

//���߽��水ť�����¼�
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

// ��ɫ�����ƶ�
void Moveup(void)
{
    if (Map[MajorRole.x][MajorRole.y + 1] != WALL)
    {
        MajorRole.y=MajorRole.y+2;
    }
}

// ��ɫ�����˶�
void Movedown(void)
{
    if (Map[MajorRole.x][ MajorRole.y - 1] != WALL)
    {
        MajorRole.y=MajorRole.y-2;
    }
}

// ��ɫ�����˶�
void Moveleft(void)
{
    if (Map[MajorRole.x - 1][MajorRole.y] != WALL)
    {
		MajorRole.x=MajorRole.x-2;
        
    }
}

// ��ɫ�����˶�
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
            case 'c': // �½���ͼ
                ShiftPageTo(MAIN_PAGE);
                break;

            case 'o': // �򿪵�ͼ
                OpenMap_ingame();
                break;

            case 's': // �����ͼ
                SaveGame_ingame();
                break;


            case 'b'://�ص���ҳ��
                ShiftPageTo(MAIN_PAGE);

            }
        }else if(ifshift==1)
        {
            switch (ch)
            {
            case 'p'://��ʾ��һ��
                next_move();
                break;
            
            case 'r'://��ʾ���·��
                find_way_shortest(MajorRole.x,MajorRole.y);
                break;

            case 'a'://��ʾȫ��·��
                find_way_all(MajorRole.x,MajorRole.y);
                break;

            }
           
        }else
        {
            switch (ch)//�ж�wasd���Ƶ����������ƶ�
            {
                case 'a'://��������
                    Moveleft();
                    break;

                case 'd'://��������
                    Moveright();
                    break;

                case 'w'://��������
                    Moveup();
                    break;

                case 's'://��������
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


