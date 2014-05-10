#ifndef APP_UNTILS_H 
#define APP_UNTILS_H 

#include <map>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class AppUntils
{
public:
	AppUntils();
	~AppUntils();

	enum StringKey
	{
		TITLE = 0,
		NAME,
		NUMBER,
	};

	static AppUntils *getInstance();
	static AppUntils *appUntils;
	map<string,string> languageMap;

	ccLanguageType languageType;

private:
	void parseXml(const char *xmlPath);
};

#endif