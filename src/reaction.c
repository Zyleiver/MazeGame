#include "MyHeader.h"

int putting; // ���ڱ༭��ģ��
int editx;   // �༭��ͼ��x����
int edity;   // �༭��ͼ��y����

int ifpre; // �Ƿ���ʾԤ��

int aboutstage; //�洢�򿪹���ǰ��ҳ��״̬ 

// �������ָ
void setMouseCursorHand()
{
    // ��ȡ��ǰ���̵Ĵ��ھ��
    HWND hWnd = GetForegroundWindow();

    // ������ָ�����Դ
    HCURSOR handCursor = LoadCursor(NULL, IDC_HAND);

    // �������ָ��
    SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR)handCursor);
    SetCursor(handCursor);
}

// ����ɼ�ͷ
void setMouseCursorArrow()
{
    // ��ȡ��ǰ���̵Ĵ��ھ��
    HWND hWnd = GetForegroundWindow();

    // ���ؼ�ͷ�����Դ
    HCURSOR arrowCursor = LoadCursor(NULL, IDC_ARROW);

    // �������ָ��
    SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR)arrowCursor);
    SetCursor(arrowCursor);
}

// ȫ����ť���ɼ�(��ʹ��˵���͹���)
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

// ȫ����ť�ɿ�
void AllButtonUp(void)
{
    int j = 0;
    for (j; j < ButtonNum; j++)
    {
        ButtonEnum[j].stage = Button_UP;
    }
}

// �ж����޴�����ť
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

// �ж�����Ƿ��ڰ�ť��
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

// ����¼�
void myMouseEvent(int x, int y, int button, int event)
{
    uiGetMouse(x, y, button, event);
    static double mouse_x;
    static double mouse_y;

    mouse_x = ScaleXInches(x);
    mouse_y = ScaleYInches(y);

    if (button == LEFT_BUTTON && event == BUTTON_DOWN)
    {
        if (TellPress(mouse_x, mouse_y, ButtonEnum[Instruction])) // ���ʹ��˵��
        {
            Instruct();
        }
        else if (TellPress(mouse_x, mouse_y, ButtonEnum[About_Game])) // �������
        {
        	if(page_stage != INSTRUCT_PAGE)
        	aboutstage = page_stage;
            AboutGame();
        }
        else if (TellPress(mouse_x, mouse_y, ButtonEnum[Back])) // �������
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
            case MAIN_PAGE: // ��ҳ��״̬

                MainPageTell(mouse_x, mouse_y);

                break;

            case GAME_PAGE: // ��Ϸҳ��״̬

                GamePageTell(mouse_x, mouse_y);

                break;

            case CHOSEMAP_PAGE: // ѡ�����ɵ�ͼ��ʽ����

                ChoseMapPageTell(mouse_x, mouse_y);
                break;

            case EDIT_PAGE: // ��Ϸ�༭����

                EditPageTell(mouse_x, mouse_y);
                break;

            case MENU_PAGE: // �˵�����

                MenuPageTell(mouse_x, mouse_y);
                break;

            case TOOL_PAGE: // ���߽���

                ToolPageTell(mouse_x, mouse_y);
                break;

            case END_PAGE: // ����ҳ��״̬

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

// ��ҳ�水ť�����¼�
void MainPageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, ButtonEnum[StartNewGame])) // ���¿�������Ϸ
    {
        ShiftPageTo(CHOSEMAP_PAGE);
        AllButtonUp();
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[ReadFiles])) // ���¶�ȡ�浵
    {

        if (ReadData())
        {
            ShiftPageTo(GAME_PAGE);
        }
        else
        {
            int ReadFailed = MessageBox(NULL, "��ȡʧ��", "����", MB_OK | MB_ICONINFORMATION);
        }

        AllButtonUp();
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[ExitGame])) // �����˳���Ϸ
    {
        _exit(0);
    }
}

// ѡ���ͼ���ɷ�ʽ���水ť�����¼�
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
            int xlow = MessageBox(NULL, "xֵ̫С", "����", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (xscale > 40)
        {
            int xmuch = MessageBox(NULL, "xֵ̫��", "����", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (yscale < 4)
        {
            int ylow = MessageBox(NULL, "yֵ̫С", "����", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (yscale > 40)
        {
            int ymuch = MessageBox(NULL, "yֵ̫��", "����", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (monsternum < 0)
        {
            int monslow = MessageBox(NULL, "������������Ϊ����", "����", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (monsternum > 999)
        {
            int monsmuch = MessageBox(NULL, "������������", "����", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (coinNum < 0)
        {
            int coinlow = MessageBox(NULL, "�����������Ϊ����", "����", MB_OK | MB_ICONINFORMATION);
            CodCrt = 0;
        }
        else if (coinNum > (int)((double)(xscale * yscale) * 7 / 9))
        {
            int coinmuch = MessageBox(NULL, "�����������", "����", MB_OK | MB_ICONINFORMATION);
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
            int xlow = MessageBox(NULL, "xֵ̫С", "����", MB_OK | MB_ICONINFORMATION);
            CodBld = 0;
        }
        else if (xscale > 40)
        {
            int xmuch = MessageBox(NULL, "xֵ̫��", "����", MB_OK | MB_ICONINFORMATION);
            CodBld = 0;
        }
        else if (yscale < 4)
        {
            int ylow = MessageBox(NULL, "yֵ̫С", "����", MB_OK | MB_ICONINFORMATION);
            CodBld = 0;
        }
        else if (yscale > 40)
        {
            int ymuch = MessageBox(NULL, "yֵ̫��", "����", MB_OK | MB_ICONINFORMATION);
            CodBld = 0;
        }
        else if (monsternum < 0)
        {
            int monslow = MessageBox(NULL, "������������Ϊ����", "����", MB_OK | MB_ICONINFORMATION);
            CodBld = 0;
        }
        else if (monsternum > 999)
        {
            int monsmuch = MessageBox(NULL, "������������", "����", MB_OK | MB_ICONINFORMATION);
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

// �˵����水ť�����¼�
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
            int OpenFailed = MessageBox(NULL, "��ʧ��", "����", MB_OK | MB_ICONINFORMATION);
        }
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[SaveGame]))
    {
        if (saveMap())
        {
            int Save = MessageBox(NULL, "����ɹ�", "����", MB_OK | MB_ICONINFORMATION);
            ShiftPageTo(GAME_PAGE);
        }
        else
        {
            int SaveFailed = MessageBox(NULL, "����ʧ��", "����", MB_OK | MB_ICONINFORMATION);
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
// �༭���水ť�¼�
void EditPageTell(double mouse_x, double mouse_y)
{
    if (TellPress(mouse_x, mouse_y, ButtonEnum[Menu]))
    {
        int EditMenu = MessageBox(NULL, "������ɱ༭���˳��༭", "����", MB_OK | MB_ICONINFORMATION);
    }
    else if (TellPress(mouse_x, mouse_y, ButtonEnum[Tools]))
    {
        int EditTools = MessageBox(NULL, "������ɱ༭���˳��༭", "����", MB_OK | MB_ICONINFORMATION);
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
            int EditComplete = MessageBox(NULL, "�����������յ�", "����", MB_OK | MB_ICONINFORMATION);
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
                // ��editx,edity,PutWall���ݸ��༭����
                EditMap(editx, edity, putting);
            }
            break;

        case PutCoin:
        case PutRole:
        case PutGoal:
            if (TellRoad(mouse_x, mouse_y))
            {
                // ��editx,edity,(PutCoin/PutRole/PutGoal)���ݸ��༭����
                EditMap(editx, edity, putting);
            }
            break;

        case Erase:
            if (TellWall(mouse_x, mouse_y))
            {
                // ��editx,edity,Erase���ݸ��༭����
                EditMap(editx, edity, putting);
            }
            else if (TellRoad(mouse_x, mouse_y))
            {
                // ��editx,edity,Erase���ݸ��༭����
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

// ���߽��水ť�����¼�
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
            int noprom = MessageBox(NULL, "�õ�ͼ�޽�", "����", MB_OK | MB_ICONINFORMATION);
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
            int nosh = MessageBox(NULL, "�õ�ͼ�޽�", "����", MB_OK | MB_ICONINFORMATION);
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
            int noway = MessageBox(NULL, "�õ�ͼ�޽�", "����", MB_OK | MB_ICONINFORMATION);
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
    // �ж��Ƿ���Ctrl��Shift
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

    // ���������Ҽ���ɫ�ƶ�
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
        MajorRole.y = MajorRole.y + 2;
    }
}

// ��ɫ�����˶�
void Movedown(void)
{
    if (Map[MajorRole.x][MajorRole.y - 1] != WALL)
    {
        MajorRole.y = MajorRole.y - 2;
    }
}

// ��ɫ�����˶�
void Moveleft(void)
{
    if (Map[MajorRole.x - 1][MajorRole.y] != WALL)
    {
        MajorRole.x = MajorRole.x - 2;
    }
}

// ��ɫ�����˶�
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
			case 'c': // �½���ͼ
                ButtonEnum[CrtNewMap].stage = Button_DOWN;
                ShiftPageTo(CHOSEMAP_PAGE);
                break;

            case '':
			case 'X':
			case 'x': // �򿪵�ͼ
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
                    int OpenFailed = MessageBox(NULL, "��ʧ��", "����", MB_OK | MB_ICONINFORMATION);
                }
                break;
			
			case '':
            case 'V':
			case 'v': // �����ͼ
                if (saveMap())
                {
                    int Save = MessageBox(NULL, "����ɹ�", "����", MB_OK | MB_ICONINFORMATION);
                    ShiftPageTo(GAME_PAGE);
                }
                else
                {
                    int SaveFailed = MessageBox(NULL, "����ʧ��", "����", MB_OK | MB_ICONINFORMATION);
                    ShiftPageTo(MENU_PAGE);
                }
                break;
                
			case '':
            case 'Q':
			case 'q': // �ص���ҳ��
                AllButtonUp();
                ShiftPageTo(MAIN_PAGE);
            }
        }
        else if (ifshift == 1)
        {
            switch (ch)
            {
            case 'P':
			case 'p': // ��ʾ��һ��
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
                    int noprom = MessageBox(NULL, "�õ�ͼ�޽�", "����", MB_OK | MB_ICONINFORMATION);
                }
                break;

            case 'R':
			case 'r': // ��ʾ���·��
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
                    int nosh = MessageBox(NULL, "�õ�ͼ�޽�", "����", MB_OK | MB_ICONINFORMATION);
                }
                break;

            case 'M':
			case 'm': // ��ʾȫ��·��
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
                    int noway = MessageBox(NULL, "�õ�ͼ�޽�", "����", MB_OK | MB_ICONINFORMATION);
                }
                break;
            }
        }
        else
        {
            switch (ch) // �ж�wasd���Ƶ����������ƶ�
            {
            case 'A':
			case 'a': // ��������
                Moveleft();
                break;

            case 'D':
			case 'd': // ��������
                Moveright();
                break;

            case 'W':
			case 'w': // ��������
                Moveup();
                break;

            case 'S':
			case 's': // ��������
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



