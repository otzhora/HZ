#include "server.h"


int main(int argc, char* argv[])
{
	try
	{
		int port = 8000;
		if (argc == 2)
		{
			port = atoi(argv[1]);
		}

		boost::asio::io_service io_service;
		tcp::endpoint endpoint(tcp::v4(), port);
		chat_server_ptr server(new chat_server(io_service, endpoint));

		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}