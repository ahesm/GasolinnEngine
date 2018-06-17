#include"String.h"


namespace gfunc
{
	std::string *String::Split(std::string strTarget, std::string strTok)
	{
		int     nCutPos;
		int     nIndex = 0;
		std::string* strResult = new std::string[2];

		while ((nCutPos = strTarget.find_first_of(strTok)) != strTarget.npos)
		{
			if (nCutPos > 0)
			{
				strResult[nIndex++] = strTarget.substr(0, nCutPos);
			}
			strTarget = strTarget.substr(nCutPos + 1);
		}

		if (strTarget.length() > 0)
		{
			strResult[nIndex++] = strTarget.substr(0, nCutPos);
		}

		return strResult;
	}
}