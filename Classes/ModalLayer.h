#ifndef __Modal__ModalLayer__
#define __Modal__ModalLayer__

#define APP_VIEW_WIDTH   828
#define APP_VIEW_HEIGHT  1792

#include "cocos2d.h"

USING_NS_CC;

class ModalLayer : public cocos2d::Layer
{
    
public:
    
    virtual bool init();
    
    void setResultView(std::string totalPlayCount, std::string totalSuccessCount);

    void menuCloseCallback(Ref* pSender);
    
    CREATE_FUNC(ModalLayer);
};

#endif /* defined(__Modal__ModalLayer__) */
