#ifndef __Modal__ModalTopScene__
#define __Modal__ModalTopScene__

#include "cocos2d.h"

USING_NS_CC;

class ModalTopScene : public Layer
{
    
public:

    const float sprite_width = 150.0;
    const float sprite_height = 150.0;
    const float sprite_height_mergin = sprite_height / 3;
    const int max_image_count = 8;
    
    virtual bool init();
    
    static Scene* createScene();
    
    // タイマー
    void countTimerPer1sec(float time);
    
    // タップイベント
    bool onTouchBegan(Touch* touch, Event* event);
    
    // 画像描画、画像操作
    void replaceImage(int imageTag);
    
    void setSprite(std::string defaultImage, int imageTag, float width, float height);
    
    CREATE_FUNC(ModalTopScene);
};

#endif /* defined(__Modal__ModalTopScene__) */
