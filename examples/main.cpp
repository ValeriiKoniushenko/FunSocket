#include "HTTPClientSocket.h"
#include "HTTPServerSocket.h"
#include "Wsa.h"

#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	try
	{
		Wsa::instance().initialize(1, 1);
		tcp::HTTPClientSocket client;

		client.connectByHostName("buff.163.com", 443);
		client.send(
			"GET /api/market/goods?game=csgo&page_num=1&use_suggestion=0&_=1693235615178 HTTP/1.0\r\n"
			"Host: buff.163.com\r\n"
			"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.5) Gecko/20091102 Firefox/3.5.5 (.NET CLR "
			"3.5.30729)\r\n"
			"Accept: "
			"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/"
			"signed-exchange;v=b3;q=0.7\r\n"
			"Connection: keep-alive\r\n"
			"Pragma: no-cache\r\n"
			"Cache-Control: no-cache\r\n\r\n");

		cout << client.receiveAsString();
		// client.send("GET /index.html HTTP/1.0 \r\nHost: www.google.com\r\n\r\n");
		// std::cout << client.receiveAsString();
		/*tcp::HTTPServerSocket listener("127.0.0.1", 27080);
		listener.listen();

		ClientSocket connectedClient = listener.accept();
		std::cout << "Connected client: " << connectedClient.getAddress().getAddress() << ":"
				  << connectedClient.getAddress().getPort() << std::endl;

		connectedClient.send("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length:11\r\n\r\nHello world");
		std::cout << connectedClient.receiveAsString();*/
	}
	catch (std::runtime_error& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	return 0;
}