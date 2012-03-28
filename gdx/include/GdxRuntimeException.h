#pragma once

class GdxRuntimeException : public std::exception
{
public:
	GdxRuntimeException(const std::string& message);
	virtual ~GdxRuntimeException(void) throw();

	virtual const char* what() const throw();
private:
	std::string m_message;
};

