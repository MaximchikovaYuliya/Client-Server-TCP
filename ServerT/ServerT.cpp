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
		if (FAILED(WSAStartup(MAKEWORD(2, 2), &ws)))
			throw SetErrorMsgText("wsastartup:", WSAGetLastError());
		if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw  SetErrorMsgText("socket:", WSAGetLastError());
		if (closesocket(sS) == SOCKET_ERROR)
			throw  SetErrorMsgText("closesocket:", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw  SetErrorMsgText("Cleanup:", WSAGetLastError());

	}
	catch (string errorMsgText)
	{
		cout << endl << "WSAGetLastError: " << errorMsgText;
	}

	return 0;
}

