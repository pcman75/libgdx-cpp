#include "stdafx.h"
#include "StringUtils.h"

bool StringUtils::startsWith(const std::string& str, const char* with)
{
	return str.compare(0, strlen(with), with) == 0;
}

bool StringUtils::endsWith(const std::string& str, const char* with)
{
	int lenWidth = strlen(with);
	int lenStr = str.size();
	return str.compare(lenStr - lenWidth, strlen(with), with) == 0;
}