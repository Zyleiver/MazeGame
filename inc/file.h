#ifndef FILE_H_
#define FILE_H_

//读取存档
int ReadData(void);

//存档
int saveMap(void);

//显示游戏说明
void Instruct(void);

//显示关于
void AboutGame(void);

//打开PDF文件
void openPDFInSubdirectory(const char* subdirectory, const char* filename);

#endif
