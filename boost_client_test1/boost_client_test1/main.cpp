#include "client.h"


int main(int argc, char* argv[])
{
	try
	{
		char* ip = new char[20];
		char * port = new char[20];
		strcpy(ip, "127.0.0.1");
		strcpy(port, "8000");

		if (argc == 3)
		{
			std::cout << argv[1] << "|" << argv[2] << std::endl;
			strcpy(ip, argv[1]);
			strcpy(port, argv[2]);
		}

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(ip, port);
		tcp::resolver::iterator iterator = resolver.resolve(query);
		char line[chat_message::max_body_length + 1];
		chat_message msg;
		std::cin >> line;
		msg.body_length(strlen(line));
		memcpy(msg.body(), line, msg.body_length());
		msg.id("0000\0");
		msg.encode_header();
		chat_client c(io_service, iterator, msg);

		boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

		
		while (std::cin.getline(line, chat_message::max_body_length + 1))
		{
			using namespace std; // For strlen and memcpy.
			
			msg.body_length(strlen(line));
			memcpy(msg.body(), line, msg.body_length());
			msg.encode_header();
			c.write(msg);
		}

		c.close();
		t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}