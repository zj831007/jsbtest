//
//  XMLHttpRequest.h
//  jsbtest
//
//  Created by Justin on 13-4-29.
//
//

#ifndef __jsbtest__XMLHttpRequest__
#define __jsbtest__XMLHttpRequest__

#include "cocos2d.h"
#include "HttpClient.h"

class XMLHttpRequest:public cocos2d::CCLayer
{
public:
    XMLHttpRequest();
    ~XMLHttpRequest();
    
    void open(std::string method, std::string url, bool async);
    void send(std::string param);
    void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
    
    int getStatus();
    int getReadyState();
    std::string getResponseText();
    
private:
    std::string reqUrl;
    int status=0;
    int readyState=0; //0 unsent  1 opend  2 headers_received  3 loading 4 done
    std::string responseText;
    
};


#endif /* defined(__jsbtest__XMLHttpRequest__) */
