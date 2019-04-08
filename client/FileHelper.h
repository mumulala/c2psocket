#include<stdio.h>
#include<stdlib.h>
#include <WINSOCK2.H>
#include <STDIO.H>
#pragma  comment(lib,"ws2_32.lib")
 
class FileHelper
{
private:
	FILE *f;
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
 
public:
	FILE * selectfile()
	{
		printf("请输入要传送的文件名\n");
		scanf("%s",path_buffer);
 
		if (f=fopen(path_buffer,"rb"))
		{
			printf("文件打开成功\n");
			return f;
		}
		else
		{
			printf("文件不存在，请重新输入\n");
			return selectfile();
		}
	}
 
	char * getFileName()
	{
		_splitpath(path_buffer, drive, dir, fname, ext);
		return strcat(fname, ext);
	}
	FILE * createFile(char *name)
	{
		remove(name);
		if (f = fopen(name, "ab"))
		{
			printf("文件创建成功\n");
 
		}
		else
		{
			printf("文件创建失败\n");
		}
		return f;
	}
 
	bool createDir(char *dir)
	{
		char head[MAX_PATH] = "md ";
		return system(strcat(head, dir));
	}
 
 
 
 
 
};
