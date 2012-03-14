#pragma once

class StringTokenizer
{
private:
	std::vector<std::string> m_tokens;
	int m_curToken;

public:
	StringTokenizer(const std::string& str, const std::string& delimiters);
	std::string& nextToken();

	static void split(const std::string& str, std::vector<std::string>& tokens);
	static void split(const std::string& str, const std::string& delimiters, std::vector<std::string>& tokens);
};