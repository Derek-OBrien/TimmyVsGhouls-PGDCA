#pragma once

#include "cocos2d.h"
#include "network/HttpClient.h"

class HttpConnection{
public:

	virtual bool init();

	
	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

private:

};