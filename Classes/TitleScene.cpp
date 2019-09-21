#include "TitleScene.h"
#include "ModalTopScene.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    // 「シーン」は自動解放オブジェクトです
    auto scene = Scene::create();
    
    // 「レイアウト」は自動解放オブジェクトです
    auto layer = TitleScene::create();
    
    // シーンに子としてレイヤーを追加
    scene->addChild(layer);
    
    // シーンを返す
    return scene;
}

bool TitleScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 中央
    float center_x = visibleSize.width / 2 + origin.x;
    float center_y = visibleSize.height / 2 + origin.y;
    
    // Y軸ラベル位置
    float base_y_position = center_y + (sprite_height * 3);
    

    // バックグランドカラー（グレー）
    auto background = LayerColor::create(Color4B::GREEN, visibleSize.width, visibleSize.height);
    background->setPosition(Vec2(origin.x, origin.y));
    this->addChild(background, 0);
    
    auto *_description_label = Label::createWithSystemFont("同じ画像をタップしてね", "HiraKakuProN-W6", 50);
    _description_label->setPosition(Vec2(center_x, base_y_position + sprite_height));
    _description_label->setColor(Color3B::BLUE);
    this->addChild(_description_label, 1);
    
    auto nextButton = MenuItemImage::create("start.png",  // 通常状態の画像
                                            "start.png",  // 押下状態の画像
                                            CC_CALLBACK_1(TitleScene::startCallback, this));
    nextButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.3));
    
    auto menu = Menu::create(nextButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
    
    return true;
}

void TitleScene::startCallback(Ref* pSender)
{
    Scene *scece = ModalTopScene::createScene();
    Director::getInstance()->replaceScene(scece);
}
