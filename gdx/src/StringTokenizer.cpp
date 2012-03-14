#include "stdafx.h"
#include "StringTokenizer.h"

using namespace std;

StringTokenizer::StringTokenizer(const string& str, const string& delimiters)
	:m_curToken(0)
{
	split(str, delimiters, m_tokens);
}

string& StringTokenizer::nextToken()
{
	return m_tokens[m_curToken++];
}

void StringTokenizer::split(const string& str, const string& delimiters, std::vector<std::string>& tokens)
{
	tokens.clear();

	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void StringTokenizer::split(const string& str, vector<string>& tokens)
{
	split(str, " ", tokens);
}

