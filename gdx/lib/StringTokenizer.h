#pragma once

class StringTokenizer
{
private:
	std::vector<std::string> m_tokens;
	int m_curToken;

public:
	StringTokenizer(const std::string& str, const std::string& delimiters);
	std::string& nextToken();

private:
	void tokenize(const std::string& str, const std::string& delimiters);
};