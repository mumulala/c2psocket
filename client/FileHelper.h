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
		printf("������Ҫ���͵��ļ���\n");
		scanf("%s",path_buffer);
 
		if (f=fopen(path_buffer,"rb"))
		{
			printf("�ļ��򿪳ɹ�\n");
			return f;
		}
		else
		{
			printf("�ļ������ڣ�����������\n");
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
			printf("�ļ������ɹ�\n");
 
		}
		else
		{
			printf("�ļ�����ʧ��\n");
		}
		return f;
	}
 
	bool createDir(char *dir)
	{
		char head[MAX_PATH] = "md ";
		return system(strcat(head, dir));
	}
 
 
 
 
 
};
