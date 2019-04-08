#include <stdio.h>
#include <stdio.h>
#include <winsock2.h>
#include "FileHelper.h"
#pragma comment(lib,"ws2_32.lib")
 
int main(int argc, char* argv[])
{
	//初始化WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	FileHelper fh;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
 
	//创建套接字
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}
 
	//绑定IP和端口
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8000);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}
 
	//开始监听
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}
 
	//循环接收数据
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[BUFSIZ];
	while (true)
	{
		printf("等待连接...\n");
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));
		/*if (fh.createDir(inet_ntoa(remoteAddr.sin_addr)))
			printf("文件夹创建成功！");*/
		int ret = 0;
		long long count = 0;
		char sendData[BUFSIZ] = "你好，TCP客户端！\n";
		ret = recv(sClient, revData, BUFSIZ, 0);
		char fromname[BUFSIZ] = {};
		strcpy(fromname, revData);
		char mid[3] = "\\";
		char finame[MAX_PATH] = {};
		char over[BUFSIZ] = "Finnal";
		strcat(finame, inet_ntoa(remoteAddr.sin_addr));
		printf(finame);
		strcat(finame, mid);
		strcat(finame, revData);
		printf(finame);
		FILE *f = fh.createFile("1.exe");
		send(sClient, sendData, BUFSIZ, 0);
		while ((ret = recv(sClient, revData, BUFSIZ, 0)) > 0)
		{
			//printf("%d\n", ret);
			printf("%db\n", count += ret);
			if (strcmp(revData,over)==0)
			{
				printf("文件%s传输成功\n", fromname);
				break;
				send(sClient, over, BUFSIZ, 0);
			}
			fwrite(revData, 1, ret, f);
			send(sClient, sendData, BUFSIZ, 0);
		}
		fclose(f);
		if (strcmp(revData, over) != 0)
		{
			printf("IP：%s发来的%s传输过程中失去连接\n", inet_ntoa(remoteAddr.sin_addr),fromname);
			remove(finame);
		}
 
 
		closesocket(sClient);
	}
 
	closesocket(slisten);
	WSACleanup();
	return 0;
}