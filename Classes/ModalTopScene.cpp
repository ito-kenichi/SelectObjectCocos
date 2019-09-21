#include "ModalTopScene.h"
#include "ModalLayer.h"
#include <unordered_set>
#include <string.h>

USING_NS_CC;

std::unordered_set<int> image_set;
int timer;
int play_count;
int success_count;

Scene* ModalTopScene::createScene()
{
    // 「シーン」は自動解放オブジェクトです
    auto scene = Scene::create();
    
    // 「レイアウト」は自動解放オブジェクトです
    auto layer = ModalTopScene::create();
    
    // シーンに子としてレイヤーを追加
    scene->addChild(layer);
    
    // シーンを返す
    return scene;
}

// 「INIT」初期化
bool ModalTopScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // タイマー
    timer = 60;
    
    // 回数カウント
    play_count = 0;
    success_count = 0;
    
    // 画面サイズを取得
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // バックグランドカラー（グレー）
    auto background = LayerColor::create(Color4B::GRAY, visibleSize.width, visibleSize.height);
    background->setPosition(origin.x, origin.y);
    this->addChild(background, 0);
    
    // 中央
    float center_x = visibleSize.width / 2 + origin.x;
    float center_y = visibleSize.height / 2 + origin.y;
    
    // sprite Y 調整値
    float sprite_y_adjust = sprite_width / 4;
    
    // Y軸ラベル位置
    float base_y_position = center_y + (sprite_height * 3);
    
    auto *_timer_label = Label::createWithSystemFont("残り : 60秒", "HiraKakuProN-W6", 28);
    _timer_label->setPosition(Vec2(center_x - (sprite_width * 2), base_y_position));
    _timer_label->setColor(Color3B::WHITE);
    this->addChild(_timer_label, 1, 10);
    this->schedule(schedule_selector(ModalTopScene::countTimerPer1sec), 1.0f);
    
    auto *_play_count_label = Label::createWithSystemFont("タップ : 0回", "HiraKakuProN-W6", 35);
    _play_count_label->setPosition(Vec2(center_x + (sprite_width * 2), base_y_position + sprite_y_adjust));
    _play_count_label->setColor(Color3B::BLUE);
    this->addChild(_play_count_label, 1, 12);
    
    auto *_success_count_label = Label::createWithSystemFont("成功 : 0回", "HiraKakuProN-W6", 35);
    _success_count_label->setPosition(Vec2(center_x + (sprite_width * 2), base_y_position - sprite_y_adjust));
    _success_count_label->setColor(Color3B::BLUE);
    this->addChild(_success_count_label, 1, 11);
    
    auto *_decision_label = Label::createWithSystemFont("", "HiraKakuProN-W6", 40);
    _decision_label->setPosition(Vec2(center_x, base_y_position - sprite_y_adjust - sprite_height));
    _decision_label->setColor(Color3B::RED);
    this->addChild(_decision_label, 1, 13);
    
    FileUtils::getInstance()->addSearchPath("img");
    
    auto *mainImage = Sprite::create("image001.png");
    mainImage->setName("image001");
    mainImage->setPosition(Vec2(center_x, base_y_position));
    mainImage->setContentSize(Size(sprite_width, sprite_height));
    this->addChild(mainImage, 0, 50);
    
    // sprite Y 2段目 位置
    float first_sprite_position_y = base_y_position - sprite_height * 2 - (sprite_height_mergin * 4);
    // sprite Y 1段目 位置
    float second_sprite_position_y = first_sprite_position_y + sprite_height + sprite_height_mergin;
    // sprite X 調整値
    float sprite_x_adjust = (this->getContentSize().width - (sprite_width * 4)) / 5;
    
    float sprie_x_01 = sprite_x_adjust * 3;
    float sprie_x_02 = sprie_x_01 + sprite_width + sprite_x_adjust;
    float sprie_x_03 = sprie_x_02 + sprite_width + sprite_x_adjust;
    float sprie_x_04 = sprie_x_03 + sprite_width + sprite_x_adjust;
    
    ModalTopScene::setSprite("image001.png", 51, sprie_x_01, first_sprite_position_y);
    ModalTopScene::setSprite("image002.png", 52, sprie_x_02, first_sprite_position_y);
    ModalTopScene::setSprite("image003.png", 53, sprie_x_03, first_sprite_position_y);
    ModalTopScene::setSprite("image004.png", 54, sprie_x_04, first_sprite_position_y);
    ModalTopScene::setSprite("image005.png", 55, sprie_x_01, second_sprite_position_y);
    ModalTopScene::setSprite("image006.png", 56, sprie_x_02, second_sprite_position_y);
    ModalTopScene::setSprite("image007.png", 57, sprie_x_03, second_sprite_position_y);
    ModalTopScene::setSprite("image008.png", 58, sprie_x_04, second_sprite_position_y);

    replaceImage(50);
    image_set.clear();
    
    for(int imageCount = 51; imageCount < 59; imageCount++) replaceImage(imageCount);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(ModalTopScene::onTouchBegan, this);
    
    // ディスパッチャーに登録
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void ModalTopScene::countTimerPer1sec(float time)
{
    // タイマー停止
    if (timer == 0) {
        this->unschedule(schedule_selector(ModalTopScene::countTimerPer1sec));
        
        // モーダルレイヤーを追加
        auto modalLayer = ModalLayer::create();
        modalLayer->setResultView(StringUtils::format("合計タップ回数 : %i回", play_count),
                                  StringUtils::format("合計成功回数 : %i回", success_count));
        this->addChild(modalLayer, 2);
    } else {
        // カウントダウン
        timer--;
        auto _timer_label = (Label*)this->getChildByTag(10);
        _timer_label->setString(StringUtils::format("残り : %i秒", timer));
    }
}

bool ModalTopScene::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 location = touch->getLocation();
    
    bool tapped = false;
    Sprite *mainImage = (Sprite*)this->getChildByTag(50);
    for(int imageCount = 51; imageCount < 59; imageCount++)
    {
        Sprite *sprite = (Sprite*)this->getChildByTag(imageCount);
        Rect spriteRect = Rect(sprite->getPosition().x - sprite->getContentSize().width / 2,
                               sprite->getPosition().y - sprite->getContentSize().width / 2,
                               sprite->getContentSize().width,
                               sprite->getContentSize().height);
        
        if (spriteRect.containsPoint(location)) {
            std::string msg = "はずれ〜";
            if (strcmp(sprite->getName().c_str(), mainImage->getName().c_str()) == 0) {
                success_count++;
                msg = "当ったり〜";
            }
            play_count++;
            Label *_decision_label = (Label*)this->getChildByTag(13);
            _decision_label->setString(msg);
            tapped = true;
            break;
        }
    }
    auto *_success_count_label = (Label*)this->getChildByTag(11);
    auto *_play_count_label = (Label*)this->getChildByTag(12);

    _success_count_label->setString(StringUtils::format("成功 : %i回", success_count));
    _play_count_label->setString(StringUtils::format("タップ : %i回", play_count));

    if(tapped)
    {
        replaceImage(50);
        image_set.clear();
        for(int imageCount = 51; imageCount < 59; imageCount++) replaceImage(imageCount);
    }

    return true;
}

void ModalTopScene::replaceImage(int imageTag)
{
    std::string main_num = "image00";
    int random_num = cocos2d::random<int>(1, max_image_count);
    if (imageTag != 50) {
        while(image_set.count(random_num) >= 1)
        {
            random_num = cocos2d::random<int>(1, max_image_count);
        }
        image_set.insert(random_num);
    }
    main_num.append(StringUtils::toString(random_num));
    main_num.append(".png");

    Sprite *sprite = (Sprite*)this->getChildByTag(imageTag);
    sprite->setSpriteFrame(Sprite::create(main_num.c_str())->getSpriteFrame());
    sprite->setName(main_num.c_str());
    sprite->setContentSize(Size(sprite_width, sprite_height));
}

void ModalTopScene::setSprite(std::string defaultImage, int imageTag, float width, float height)
{
    if((Sprite*)this->getChildByTag(imageTag) != nullptr) this->removeChildByTag(imageTag);
    
    auto *sprite = Sprite::create(defaultImage);
    sprite->setPosition(Vec2(width, height));
    sprite->setContentSize(Size(sprite_width, sprite_height));
    this->addChild(sprite, 0, imageTag);
}
