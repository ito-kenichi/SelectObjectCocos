#include "ModalLayer.h"
#include "ModalTopScene.h"

using namespace cocos2d;

bool ModalLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // バックグランドカラー（グレー）
    auto background = LayerColor::create(Color4B::GRAY, visibleSize.width, visibleSize.height);
    background->setPosition(Vec2(origin.x, origin.y));
    this->addChild(background, 0);

    auto ResultMessage = Label::createWithSystemFont("結果表示", "HiraKakuProN-W6", 100);
    ResultMessage->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height * 0.7));
    ResultMessage->enableShadow(Color4B(255, 0, 0, 255), Size(2, -2));
    this->addChild(ResultMessage, 2);

    // Menu2
    auto nextButton = MenuItemImage::create("menu-image2.png",  // 通常状態の画像
                                          "menu-image2-hover.png",  // 押下状態の画像
                                          CC_CALLBACK_1(ModalLayer::menuCloseCallback, this));
    nextButton->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height * 0.3));
    
    auto menu = Menu::create(nextButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
    
    // モーダル処理
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch *touch,Event*event)->bool{
        return true;
    };
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void ModalLayer::setResultView(std::string totalPlayCount, std::string totalSuccessCount)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 合計タップ回数ラベル
    auto totalPlayCountLabel = Label::createWithSystemFont(totalPlayCount, "HiraKakuProN-W6", 50);
    totalPlayCountLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height * 0.6));
    totalPlayCountLabel->enableShadow(Color4B(255, 0, 0, 255), Size(2, -2));
    this->addChild(totalPlayCountLabel, 2);

    // 合計成功回数ラベル
    auto totalSuccessCountLabel = Label::createWithSystemFont(totalSuccessCount, "HiraKakuProN-W6", 50);
    totalSuccessCountLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2.0));
    totalSuccessCountLabel->enableShadow(Color4B(255, 0, 0, 255), Size(2, -2));
    this->addChild(totalSuccessCountLabel, 2);
}

// menuCloseCallback ModalLayerオブジェクトの削除
void ModalLayer::menuCloseCallback(Ref* pSender)
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    director->setOpenGLView(glview);
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 60);
    glview->setDesignResolutionSize(APP_VIEW_WIDTH, APP_VIEW_HEIGHT, ResolutionPolicy::SHOW_ALL);
    director->replaceScene(ModalTopScene::createScene());
    // ModalLayerオブジェクトの削除
    this->removeFromParentAndCleanup(true);
}
