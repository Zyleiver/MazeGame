#include "MyHeader.h"

void ReadTemplate(void)
{
}
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
            int i = 0;
            int j = 0;
            for (i; i < 100; i++)
            {
                for (j; j < 100; j++)
                {
                    fprintf(file, "%d,", Map[i][j]);
                }
                fprintf(file, "\n");
            }
            fprintf(file, "%d %d %d\n", MajorRole.hp, MajorRole.x, MajorRole.y);
            fprintf(file,"%d\n",monsternum);
            int k;
            for(k=0;k<monsternum;k++)
            {
                fprintf(file,"%f %f,",Monster[k].x,Monster[k].y);
            }
            fprintf(file,"\n");
            fprintf(file,"%d",CoinGet);
            fclose(file);
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int ReadData(void)
{
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
            int i = 0;
            int j = 0;
            for (i; i < 100; i++)
            {
                for (j; j < 100; j++)
                {
                    fscanf(file, "%d,", &Map[i][j]);
                }
                fscanf(file, "\n");
            }
            fscanf(file, "%d %d %d\n", &MajorRole.hp, &MajorRole.x, &MajorRole.y);
            fscanf(file,"%d\n",&monsternum);
            int k;
            for(k=0;k<monsternum;k++)
            {
                fscanf(file,"%f %f,",&Monster[k].x,&Monster[k].y);
            }
            fscanf(file,"\n");
            fscanf(file,"%d",&CoinGet);
            fclose(file);
            return 1;
        }else{
            return 0;
        }
        
    }
    else
    {
        return 0;
    }
}

void OpenTemp(void)
{
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
            int i = 0;
            int j = 0;
            for (i; i < 100; i++)
            {
                for (j; j < 100; j++)
                {
                    fscanf(file, "%d,", &Map[i][j]);
                }
            }
            fclose(file);
        }
    }
}

void SaveGame_ingame(void)
{
}

void SaveAsTemplate(void)
{
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
            int i = 0;
            int j = 0;
            for (i; i < 100; i++)
            {
                for (j; j < 100; j++)
                {
                    fprintf(file, "%d,", Map[i][j]);
                }
                fprintf(file, "\n");
            }
            fclose(file);
        }
    }
}

void Instruct(void)
{
    int INSTRUCTION = MessageBox(NULL, "", "使用说明", MB_OK | MB_ICONINFORMATION);
}

void AboutGame(void)
{
    int INSTRUCTION = MessageBox(NULL, "", "关于", MB_OK | MB_ICONINFORMATION);
}
