#define _CRT_SECURE_NO_WARNINGS

#ifndef CLIENT
#define CLIENT

#include <cstdlib>
#include <deque>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "message.h"

using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class chat_client
{
public:
	chat_client(boost::asio::io_service& io_service,
		tcp::resolver::iterator endpoint_iterator, chat_message msg)
		: io_service_(io_service),
		socket_(io_service)
	{
		strcpy(id_, "0000\0");
		memcpy(read_msg_.data(), msg.data(), msg.length());
		boost::asio::async_connect(socket_, endpoint_iterator,
			boost::bind(&chat_client::handle_connect, this,
				boost::asio::placeholders::error));
	}

	void write(const chat_message& msg)
	{
		io_service_.post(boost::bind(&chat_client::do_write, this, msg));
	}

	void close()
	{
		io_service_.post(boost::bind(&chat_client::do_close, this));
	}

	void enter_msg(const chat_message& msg)
	{
		boost::asio::write(socket_, boost::asio::buffer(msg.data(), msg.length()));
	}

	char* id()
	{
		return id_;
	}

	void recv_id()
	{
		chat_message recv;
		boost::asio::read(socket_, boost::asio::buffer(recv.data(), 520));
		strcpy(id_, recv.id());
		std::cout << id_ << std::endl;
	}
private:

	void handle_connect(const boost::system::error_code& error)
	{
		if (!error)
		{
			enter_msg(read_msg_);
			recv_id();

			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), 2 * chat_message::header_length),
				boost::bind(&chat_client::handle_read_header, this,
					boost::asio::placeholders::error));
		}
	}

	void handle_read_header(const boost::system::error_code& error)
	{
		if (!error && read_msg_.decode_header())
		{
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&chat_client::handle_read_body, this,
					boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			std::cout.write(read_msg_.body(), read_msg_.body_length());
			std::cout << "\n";
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), 2 * chat_message::header_length),
				boost::bind(&chat_client::handle_read_header, this,
					boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void do_write(chat_message msg)
	{
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()),
				boost::bind(&chat_client::handle_write, this,
					boost::asio::placeholders::error));
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().data(),
						write_msgs_.front().length()),
					boost::bind(&chat_client::handle_write, this,
						boost::asio::placeholders::error));
			}
		}
		else
		{
			do_close();
		}
	}

	void do_close()
	{
		socket_.close();
	}

	
private:
	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
	char id_[chat_message::header_length+1];
};


#endif