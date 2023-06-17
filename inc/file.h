#ifndef FILE_H_
#define FILE_H_

//读取存档
int ReadData(void);

//读取系统模板
void OpenTemp(void);

//存档
int saveMap(void);


//显示使用说明
void Instruct(void);

//显示关于
void AboutGame(void);

//打开pdf
void openPDFInSubdirectory(const char* subdirectory, const char* filename);

#endif
