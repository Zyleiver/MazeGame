#include "MyHeader.h"

// 保存地图
int saveMap(void)
{
    OPENFILENAME ofn;
    char szFile[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;

    if (GetSaveFileName(&ofn) == TRUE)
    {
        char filePath[MAX_PATH];
        strcpy(filePath, szFile);
        const char *fileExtension = ".txt";
        size_t extensionPos = strlen(filePath) - 4;
        if (extensionPos == 0 || strcmp(filePath + extensionPos, fileExtension) != 0)
        {
            strcat(filePath, fileExtension);
        }
        strcpy(szFile, filePath);
        FILE *file = fopen(szFile, "w");
        if (file != NULL)
        {
            fprintf(file, "%d %d\n", xscale, yscale);

            int i;
            int j;
            for (i = 0; i < 100; i++)
            {
                for (j = 0; j < 100; j++)
                {
                    if (Map[i][j] == COINGOT)
                    {
                        int k = COIN;
                        fprintf(file, "%d,", k);
                    }
                    else
                    {
                        fprintf(file, "%d,", Map[i][j]);
                    }
                }
                fprintf(file, "\n");
            }
            fprintf(file, "%d", monsternum);

            fclose(file);
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

// 读取地图
int ReadData(void)
{
    char current_path[1024];
    getcwd(current_path, sizeof(current_path));
    OPENFILENAME ofn;
    char szFile[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        FILE *file = fopen(szFile, "r");
        if (file != NULL)
        {
            fscanf(file, "%d %d\n", &xscale, &yscale);
            printf("%d %d\n", xscale, yscale);
            int i;
            int j;
            for (i = 0; i < 100; i++)
            {
                for (j = 0; j < 100; j++)
                {
                    fscanf(file, "%d,", &Map[i][j]);
                    printf("%d,", Map[i][j]);
                }
                fscanf(file, "\n");
            }

            fscanf(file, "%d", &monsternum);
            printf("%d", monsternum);

            fclose(file);
            chdir(current_path);
            GameInit();
            return 1;
        }
        else
        {
            chdir(current_path);
            return 0;
        }
    }
    else
    {
        chdir(current_path);
        return 0;
    }
}

// 显示游戏说明
void Instruct(void)
{
    char current_path[1024];
    getcwd(current_path, sizeof(current_path));
    const char *subdirectory = "..\\游戏说明";
    const char *filename = "游戏说明.pdf";
    openPDFInSubdirectory(subdirectory, filename);
    chdir(current_path);
}

// 显示关于
void AboutGame(void)
{
    if (page_stage != INSTRUCT_PAGE)
        ShiftPageTo(INSTRUCT_PAGE);
    // int INSTRUCTION = MessageBox(NULL, "", "关于", MB_OK | MB_ICONINFORMATION);
}

// 打开PDF文件
void openPDFInSubdirectory(const char *subdirectory, const char *filename)
{
    char filepath[256];

#ifdef _WIN32
    // Windows系统
    snprintf(filepath, sizeof(filepath), "%s\\%s\\%s", ".", subdirectory, filename);
#else
    // Linux或Mac系统
    snprintf(filepath, sizeof(filepath), "./%s/%s", subdirectory, filename);
#endif

    char command[256];

#ifdef _WIN32
    // Windows系统
    snprintf(command, sizeof(command), "start %s", filepath);
#else
    // Linux或Mac系统
    snprintf(command, sizeof(command), "xdg-open '%s'", filepath);
#endif

    // 调用系统命令来打开PDF文件
    int result = system(command);
    if (result == -1)
    {
        fprintf(stderr, "无法打开PDF文件\n");
    }
}
