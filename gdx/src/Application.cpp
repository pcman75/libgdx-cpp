#include "stdafx.h"
#include "Application.h"

void Application::log(const char* tag, const std::string& message)
{
	log(tag, message.c_str());
}

void Application::error(const char* tag, const std::string& message)
{
	error(tag, message.c_str());
}

void Application::debug(const char* tag, const std::string& message)
{
	debug(tag, message.c_str());
}
