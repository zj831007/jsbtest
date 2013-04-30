//
//  XMLHttpRequest.cpp
//  jsbtest
//
//  Created by Justin on 13-4-29.
//
//
#include "jsapi.h"
#include "ScriptingCore.h"
#include "XMLHttpRequest.h"

USING_NS_CC_EXT;
USING_NS_CC;

XMLHttpRequest::XMLHttpRequest(){
    
}

XMLHttpRequest::~XMLHttpRequest(){
    
}

void XMLHttpRequest::open(std::string method, std::string url, bool async){
    reqUrl = url;
    
    readyState = 0;
}
void XMLHttpRequest::send(std::string param){
    readyState = 1;
    CCHttpRequest *request = new CCHttpRequest();
    request->setUrl(reqUrl.c_str());
    request->setRequestType(CCHttpRequest::kHttpGet);
    
//    std::vector<std::string> headers;
//    headers.push_back("Content-Type: application/json; charset=utf-8");
//    request->setHeaders(headers);
    
    request->setResponseCallback(this, callfuncND_selector(XMLHttpRequest::onHttpRequestCompleted));
    request->setRequestData(param.c_str(), strlen(param.c_str()));
    request->setTag("wx");
    CCHttpClient::getInstance()->send(request);
    request->release();
    readyState = 3;
}


void XMLHttpRequest::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data){
    readyState = 4;
    
    CCHttpResponse *response = (CCHttpResponse *)data;
    if (!response) {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    
    status = statusCode; //http status 
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::string res;
    std::vector<char> *buffer = response->getResponseData();
    
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        res += ((*buffer)[i]);
    }
    
//    std::string res;
//    std::vector<char> *buffer = response->getResponseData();
//    res.clear();
//    res.assign((*buffer).begin(), (*buffer).end());
    
    responseText = res;
    

    JSBool hasAction;
    jsval temp_retval;
    
    do{
    if (JS_HasProperty(ScriptingCore::getInstance()->getGlobalContext(), ScriptingCore::getInstance()->getGlobalObject(), "onreadystatechange", &hasAction) && hasAction) {
        if(!JS_GetProperty(ScriptingCore::getInstance()->getGlobalContext(), ScriptingCore::getInstance()->getGlobalObject(), "onreadystatechange", &temp_retval)) {
            break;
        }
        if(temp_retval == JSVAL_VOID) {
            break;
        }
                
        jsval jsret;
        
        JS_CallFunctionName(ScriptingCore::getInstance()->getGlobalContext(), ScriptingCore::getInstance()->getGlobalObject(), "onreadystatechange", 0, NULL, &jsret);
    }

    }while(0);
//    jsval *retval;
//    JS_CallFunctionName(ScriptingCore::getInstance()->getGlobalContext(),
//                        ScriptingCore::getInstance()->getGlobalObject(),
//                        "onreadystatechange", NULL, NULL, retval);
}

int XMLHttpRequest::getStatus(){
    return status;
}
int XMLHttpRequest::getReadyState(){
    return readyState;
}
std::string XMLHttpRequest::getResponseText(){
    return responseText;
}
