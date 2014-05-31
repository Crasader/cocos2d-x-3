#include "AppUtil.h"

AppUtil* AppUtil::appUtils = NULL;


AppUtil::AppUtil()
{

}

AppUtil *AppUtil::getInstance()
{
	if(appUtils == NULL)
	{
		appUtils = new AppUtil();
	}

	return appUtils;
}


void AppUtil::readChinesValue()
{
	tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument();
	if(NULL == document)
	{
		return;
	}

	if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		unsigned long nLength = 0;
		char *pBuff = (char *) CCFileUtils::sharedFileUtils()->getFileData("langueChineseValue.xml","rt",&nLength);
		document->Parse(pBuff);
		CCLog("%s\n",pBuff);
	}
	else
	{
		document->LoadFile("langueChineseValue.xml");
	}

	tinyxml2::XMLElement *rootEle = document->RootElement();

	tinyxml2::XMLElement *first =  rootEle->FirstChildElement();
	if(NULL == first)
	{
		return ;
	}

	while (first)
	{
		if (first->GetText() == NULL){
			m_mapChinesString.insert(map<string,string>::value_type(first->Value(),"default"));//FirstPerson->GetText()));
		}
		else{
			m_mapChinesString.insert(map<string,string>::value_type(first->Value(),first->GetText()));
		}
		first = first->NextSiblingElement();
	}

	delete document;
	document = NULL;
}

void AppUtil::readMonsterData()
{
	tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument();
	if(NULL == document)
	{
		return;
	}

	if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		unsigned long nLength = 0;
		char *pBuff = (char *) CCFileUtils::sharedFileUtils()->getFileData("enemyList.xml","rt",&nLength);
		document->Parse(pBuff);
		CCLog("%s\n",pBuff);
	}
	else
	{
		document->LoadFile("enemyList.xml");
	}

	tinyxml2::XMLElement *rootEle = document->RootElement();

	tinyxml2::XMLElement *first =  rootEle->FirstChildElement();
	if(NULL == first)
	{
		return ;
	}

	while (first)
	{
		const tinyxml2::XMLAttribute *idAttribute = first->FirstAttribute();
		const tinyxml2::XMLAttribute *decAttribute = idAttribute->Next();

		tinyxml2::XMLElement *firstChild = first->FirstChildElement();
		map<string,int> tempMap;
		while(firstChild)
		{
			tempMap.insert(map<string, int>::value_type (firstChild->Value(), atoi(firstChild->GetText())));
			firstChild = firstChild->NextSiblingElement();
			string childName = string(firstChild->Value());
			if ( childName == "boundRidus")
			{
				break;
			}
		}

		while(firstChild)
		{
			const tinyxml2::XMLAttribute *posXAttribute = firstChild->FirstAttribute();
			const tinyxml2::XMLAttribute *posYAttribute = posXAttribute->Next();
			const tinyxml2::XMLAttribute *radiusAttr = posYAttribute->Next();

			firstChild = firstChild->NextSiblingElement();
		}

		first = first->NextSiblingElement();
	}

	delete document;
	document = NULL;
}

void AppUtil::writeXml()
{
	std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "wociao.xml";

	tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
	if (NULL==pDoc) {
		return ;
	}

	tinyxml2::XMLDeclaration *pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	if (NULL==pDel) {
		return ;
	}
	pDoc->LinkEndChild(pDel);
	
	tinyxml2::XMLElement *plistElement = pDoc->NewElement("plist");
	plistElement->SetAttribute("version", "1.0");
	pDoc->LinkEndChild(plistElement);
	//节点dict
	tinyxml2::XMLElement *dictElement = pDoc->NewElement("dict");
	plistElement->LinkEndChild(dictElement);
	//节点key
	tinyxml2::XMLElement *keyElement = pDoc->NewElement("key");
	keyElement->LinkEndChild(pDoc->NewText("keyText"));
	dictElement->LinkEndChild(keyElement);

	tinyxml2::XMLElement *stringElement = pDoc->NewElement("string");
	stringElement->LinkEndChild(pDoc->NewText("stringText"));
	dictElement->LinkEndChild(stringElement);

	tinyxml2::XMLElement *arrayElemet = pDoc->NewElement("array");
	dictElement->LinkEndChild(arrayElemet);
	for (int i = 0; i<3; i++) {
		tinyxml2::XMLElement *strEle = pDoc->NewElement("string");
		strEle->LinkEndChild(pDoc->NewText("icon"));
		arrayElemet->LinkEndChild(strEle);
	}

	pDoc->SaveFile(filePath.c_str());
	pDoc->Print();//打印
	delete pDoc;
}

void AppUtil::parseXml()
{
	std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "wociao.xml";

	tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
	pDoc->LoadFile(filePath.c_str());

	tinyxml2::XMLElement *rootEle = pDoc->RootElement();

	CCLog("%s",rootEle->GetText());

	const tinyxml2::XMLAttribute *attribute = rootEle->FirstAttribute();

	CCLog("%s\n",attribute->Name());

	float value = 0.1f;
	rootEle->QueryFloatAttribute("version", &value);
	CCLog("%f",value);

	rootEle->SetAttribute("version", 1.4);

	tinyxml2::XMLElement *dictEle = rootEle->FirstChildElement();

	tinyxml2::XMLElement *keyEle = dictEle->FirstChildElement();

	CCLog("%s,%s",keyEle->Name(),keyEle->GetText());

	tinyxml2::XMLElement *stringEle = keyEle->NextSiblingElement();
	CCLog("%s,%s",stringEle->Name(),stringEle->GetText());

	tinyxml2::XMLElement *nulXmlEle = stringEle->FirstChildElement();
	if (NULL == nulXmlEle) {
		CCLog("parse end");
	}

	pDoc->SaveFile(filePath.c_str());
}


void AppUtil::writeXmlWithRapid()
{
	rapidxml::xml_document<> myRapidXmlDoc;

	rapidxml::xml_node<>* root=myRapidXmlDoc.allocate_node(rapidxml::node_element,"Jacky",NULL);

	myRapidXmlDoc.append_node(root);

	rapidxml::xml_node<>* info = myRapidXmlDoc.allocate_node(rapidxml::node_element,"Info",NULL);
	info->append_attribute(myRapidXmlDoc.allocate_attribute("test","0"));  
	info->append_attribute(myRapidXmlDoc.allocate_attribute("test1","1"));  
	info->append_attribute(myRapidXmlDoc.allocate_attribute("test2","2"));  
	root->append_node(info);

	rapidxml::xml_node<>* blog = myRapidXmlDoc.allocate_node(rapidxml::node_element,"blog","test1");  
	info->append_node(blog);  
	rapidxml::xml_node<>* website = myRapidXmlDoc.allocate_node(rapidxml::node_element,"website","test2");  
	info->append_node(website);  

	std::string text;  
	rapidxml::print(std::back_inserter(text), myRapidXmlDoc, 0);  
	CCLog(text.c_str());  
/*	std::ofstream out(CCFileUtils::sharedFileUtils()->fullPathForFilename("testRapid.xml"));  
	out << myRapidXmlDoc; */ 

	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "testRapid.xml";
	CCLog("path = %s\n",path.c_str());
	FILE* file = fopen(path.c_str(), "w");  
	if (file) {  
		fputs(text.c_str(), file);  
		fclose(file);  
	}  
	else  
	{
		CCLOG("save file error.");  
	}
}

void AppUtil::readXmlWithRapid()  
{  
	rapidxml::file<> fdoc(CCFileUtils::sharedFileUtils()->fullPathForFilename("testRapid.xml").c_str());//读取数据  
	CCLog(fdoc.data());  
	rapidxml::xml_document<> myRapidXMLDoc;  
	myRapidXMLDoc.parse<0>(fdoc.data());//将数据写入xml_document  

	rapidxml::xml_node<>* root = myRapidXMLDoc.first_node();//获取根节点  

	rapidxml::xml_node<>* info = root->first_node();//获取Info节点  

	rapidxml::xml_attribute<>* info_attr = info->first_attribute();//获取info属性  
	CCLog("%s:%s",info_attr->name(),info_attr->value());  
	CCLog("%s:%s",info_attr->next_attribute()->name(),info_attr->next_attribute()->value());  
	CCLog("%s:%s",info_attr->next_attribute()->next_attribute()->name(),info_attr->next_attribute()->next_attribute()->value());  

	rapidxml::xml_node<>* blog=info->first_node();//获取blog节点  
	CCLog("%s:%s",blog->name(),blog->value());  

	rapidxml::xml_node<>* website=blog->next_sibling();//获取website节点  
	CCLog("%s:%s",website->name(),website->value());  
}  