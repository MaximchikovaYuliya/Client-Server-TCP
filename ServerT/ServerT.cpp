#include <iostream>
#include "Winsock2.h"

#pragma comment(lib, "WS2_32.lib")  

using namespace std;

string GetErrorMsgText(int code)									// cформировать текст ошибки 
{
	string msgText;
	switch (code)													// проверка кода возврата 
	{
	case WSAEINTR:          msgText = "WSAEINTR";         break;
	case WSAEACCES:         msgText = "WSAEACCES";        break;
	case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE"; break;
	default:                msgText = "***ERROR***";      break;
	};
	return msgText;
};

string  SetErrorMsgText(string msgText, int code)
{
	return  msgText + GetErrorMsgText(code);
};


int main()
{
	WSAData ws;
	SOCKET sS;
	try
	{
		if (FAILED(WSAStartup(MAKEWORD(2, 0), &ws)))
			throw SetErrorMsgText("STARTUP: ", WSAGetLastError());

		if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw  SetErrorMsgText("SOCKET: ", WSAGetLastError());
		cout << "Socket created." << endl;

		SOCKADDR_IN serv;                     // параметры  сокета sS
		serv.sin_family = AF_INET;           // используется IP-адресация  
		serv.sin_port = htons(2000);          // порт 2000
		serv.sin_addr.s_addr = INADDR_ANY;

		if (bind(sS, (LPSOCKADDR)& serv, sizeof(serv)) == SOCKET_ERROR)
			throw  SetErrorMsgText("BIND: ", WSAGetLastError());

		if (listen(sS, SOMAXCONN) == SOCKET_ERROR)
			throw  SetErrorMsgText("LISTEN: ", WSAGetLastError());

		SOCKET cS;	                 // сокет для обмена данными с клиентом 
		SOCKADDR_IN clnt;             // параметры  сокета клиента
		memset(&clnt, 0, sizeof(clnt)); // обнулить память
		int lclnt = sizeof(clnt);    // размер SOCKADDR_IN

		if ((cS = accept(sS, (sockaddr*)& clnt, &lclnt)) == INVALID_SOCKET)
			throw  SetErrorMsgText("ACCEPT: ", WSAGetLastError());


		if (closesocket(sS) == SOCKET_ERROR)
			throw  SetErrorMsgText("CLOSE_SOCKET: ", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw  SetErrorMsgText("CLENUP: ", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << endl << "WSAGetLastError: " << errorMsgText;
	}

	return 0;
}

