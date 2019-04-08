#include <stdio.h>
#include <WINSOCK2.H>
#include <STDIO.H>
#include<string.h>
#include"FileHelper.h"
#pragma  comment(lib,"ws2_32.lib")
//#define  BUFSIZ  40000;
 
int main(int argc, char* argv[])
{
	WORD sockVersion = MAKEWORD(2,2);//版本号
	WSADATA data;    //用来保存WSAStartup调用后返回的windows Sockets数据
	FileHelper fh;
	if(WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
 
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8000);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 
 
	while (true)
	{
		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sclient == INVALID_SOCKET)
		{
			printf("invalid socket !");
			return 0;
		}
		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{
			printf("connect error !");
			closesocket(sclient);
			return 0;
		}
		FILE *f=fh.selectfile();
		char sendData[40000];
		char recData[BUFSIZ];
		char over[BUFSIZ] = "Finnal";
		char * name = fh.getFileName();
		strcpy(sendData, name);
		printf("%s\n", sendData);
		int nCount;
		long long sum = 0;
		send(sclient, sendData, strlen(sendData)+1, 0);
		int ret = recv(sclient, recData, BUFSIZ, 0);
		printf(recData);
		while ((nCount=fread(sendData,1,BUFSIZ,f))>0)
		{
			printf("%db\n",sum+=nCount);
			
			send(sclient, sendData, nCount, 0);
			
			int ret = recv(sclient, recData, BUFSIZ, 0);
			if (ret >0)
			{
				
				//recData[ret] = 0x00;
				printf(recData);
			}
			else
			{
				printf("与服务器失去连接");
				break;
			}
		}
		send(sclient, over, BUFSIZ, 0);
		ret = recv(sclient, recData, BUFSIZ, 0);
		if (ret>0&&strcmp(recData,over)==0)
		{
			printf("传输成功！");
		}
		fclose(f);
		closesocket(sclient);
	}
	WSACleanup();
	getchar();
}
