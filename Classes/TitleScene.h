#ifndef __Modal__TitleScene__
#define __Modal__TitleScene__

#include "cocos2d.h"

USING_NS_CC;

class TitleScene : public Layer
{
    
public:

    const float appWidth = 828;
    const float appHeight = 1792;
    const float sprite_height = 150.0;
    
    virtual bool init();
    
    static Scene* createScene();
    
    void startCallback(Ref* pSender);
    
    CREATE_FUNC(TitleScene);
};

#endif /* defined(__Modal__TitleScene__) */
