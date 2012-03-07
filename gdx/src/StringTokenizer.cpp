#include "stdafx.h"
#include "StringTokenizer.h"

using namespace std;

StringTokenizer::StringTokenizer(const string& str, const string& delimiters)
	:m_curToken(0)
{
	tokenize(str, delimiters);
}
string& StringTokenizer::nextToken()
{
	return m_tokens[m_curToken++];
}


void StringTokenizer::tokenize(const string& str, const string& delimiters)
{
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos     = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		m_tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}
