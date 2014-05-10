#include "AppUntils.h"

AppUntils *AppUntils::appUntils = NULL;

AppUntils::AppUntils()
{
	 languageType = CCApplication::sharedApplication()->getCurrentLanguage();

	/* switch(type)  
	 {  
	 case kLanguageChinese: 
		 {
			 CCLog("chinese");
		 }
		 break;  
	 default:
		 break;
	 }*/

	 if(languageType == kLanguageChinese)
	 {
		 parseXml("fonts/chinese.xml");
	 }else if(languageType == kLanguageEnglish)
	 {
		 parseXml("fonts/english.xml");
	 }



}

AppUntils::~AppUntils()
{

}


AppUntils *AppUntils::getInstance()
{
	if(NULL ==appUntils)
	{
		appUntils = new AppUntils();
	}

	return appUntils;
}

void AppUntils::parseXml(const char *xmlPath)
{
	CCDictionary *string = CCDictionary::createWithContentsOfFile(xmlPath);
	const char *charchinese = ((CCString*)string->objectForKey("tip1"))->m_sString.c_str();

	CCLog("%s\n",charchinese);

}