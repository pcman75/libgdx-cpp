#pragma once
class Utilities
{
public:
	Utilities(void);
	~Utilities(void);

	template <class PFunction>
	static bool CheckFunction(PFunction function)
	{
		bool ret = true;
		if(function == NULL)
		{
			ret = false;
			//TODO:
			//Log or throw error?
		}
		return ret;
	}
};

