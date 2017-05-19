
#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message
{
public:
	enum { header_length = 4 };
	enum { max_body_length = 512 };

	chat_message()
		: body_length_(0)
	{
		strcpy(id_, "0000\0");
	}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	char* id()
	{
		memcpy(id_, data_ + header_length, header_length);
		id_[header_length] = '\0';
		return id_;
	}

	char* id(char*id)
	{
		memcpy(id_, id, header_length);
		memcpy(data_ + header_length, id_, header_length);
		id_[header_length] = '\0';
		return id_;
	}

	size_t length() const
	{
		return 2 * header_length + body_length_;
	}

	const char* body() const
	{
		return data_ + 2 * header_length;
	}

	char* body()
	{
		return data_ + 2 * header_length;
	}

	size_t body_length() const
	{
		return body_length_;
	}

	void body_length(size_t new_length)
	{
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}

	bool decode_header()
	{
		using namespace std; // For strncat and atoi.
		char header[header_length + 1] = "";
		strncat(header, data_, header_length);
		body_length_ = atoi(header);
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}

		std::cout << "bdl: " << body_length_ << " id_: " << id_ << std::endl;
		return true;
	}

	void encode_header()
	{
		using namespace std; // For sprintf and memcpy.
		char header[header_length + 1] = "";
		sprintf(header, "%4d", body_length_);
		memcpy(data_, header, header_length);
		memcpy(data_ + header_length, id_, header_length);
	}

private:
	char data_[header_length + max_body_length];
	size_t body_length_;
	char id_[header_length + 1];
};

#endif // CHAT_MESSAGE_HPP