#include "HttpConnection.h"
#include <vector>
USING_NS_CC;
using namespace std;

#define COCOS2D_DEBUG 1

bool HttpConnection::init(){

	__String *data = __String::create("name=testhttpandroid&score=1000&highscore=9000");

	cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();

	request->setUrl("http://pgd-ue4webapp.azurewebsites.net/postLeaderBoard.php");

	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(HttpConnection::onHttpRequestCompleted, this));
	request->setRequestData(data->getCString(), data->length());
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();

	return true;
}


void HttpConnection::onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response){

	std::vector<char> *buffer = response->getResponseData();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("Get data: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		CCLog("%c", (*buffer)[i]);
	}
	CCLog("\n");
	if (200 != response->getResponseCode())
	{
		CCLog("Succeeded");
		return;
	}
	else
	{
		CCLog("Failed");
	}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	CCLOG("Get data: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		CCLOG("%c", (*buffer)[i]);
	}
	CCLOG("\n");

	if (200 != response->getResponseCode())
	{
		CCLOG("Succeeded");
		return;
	}
	else
	{
		CCLOG("Failed");
	}
#endif
}
