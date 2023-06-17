#include "MyHeader.h"

void openPDFInSubdirectory(const char* subdirectory, const char* filename) {
    char filepath[256];

#ifdef _WIN32
    // Windowsϵͳ
    snprintf(filepath, sizeof(filepath), "%s\\%s\\%s", ".", subdirectory, filename);
#else
    // Linux��Macϵͳ
    snprintf(filepath, sizeof(filepath), "./%s/%s", subdirectory, filename);
#endif

    char command[256];

#ifdef _WIN32
    // Windowsϵͳ
    snprintf(command, sizeof(command), "start %s", filepath);
#else
    // Linux��Macϵͳ
    snprintf(command, sizeof(command), "xdg-open '%s'", filepath);
#endif

    // ����ϵͳ��������PDF�ļ�
    int result = system(command);
    if (result == -1) {
        fprintf(stderr, "�޷���PDF�ļ�\n");
    }
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
            
			int i ;
            int j ;
            for (i=0; i < 100; i++)
            {
                for (j=0; j < 100; j++)
                {
                    if (Map[i][j]==COINGOT)
                    {	
                    	int k=COIN;
                        fprintf(file,"%d,",k);
                    }else
                    {
                        fprintf(file, "%d,", Map[i][j]);
                    }
                    
                    
                }
    			fprintf(file,"\n");
            }
            fprintf(file,"%d",monsternum);

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
            printf("%d %d\n",xscale,yscale);
            int i;
            int j;
            for (i=0; i < 100; i++)
            {
                for (j=0; j < 100; j++)
                {
                    fscanf(file, "%d,", &Map[i][j]);
                    printf("%d,",Map[i][j]);
                }
                fscanf(file, "\n");
            }

            fscanf(file,"%d",&monsternum);
            printf("%d",monsternum);
            
            fclose(file);
            GameInit();
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



void Instruct(void)
{
    const char* subdirectory = "..\\��Ϸ˵��";
    const char* filename = "��Ϸ˵��.pdf";
    openPDFInSubdirectory(subdirectory, filename);
}

void AboutGame(void)
{
	if(page_stage != INSTRUCT_PAGE)
		ShiftPageTo(INSTRUCT_PAGE);
    //int INSTRUCTION = MessageBox(NULL, "", "����", MB_OK | MB_ICONINFORMATION);
}
