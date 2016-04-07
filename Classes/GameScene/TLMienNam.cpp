#include "TLMienNam.h"
#include <random>
#include "Config/GameConfig.h"
#include "GameScene/TLMienNam.h"

#define TAG_BTN_MENU 111
#define TAG_BTN_MESSAGE 112
#define TAG_BTN_PURCHASE 113
#define TAG_BTN_SOUND 114

#define TAG_BTN_CHONLAI 115
#define TAG_BTN_XEPBAI 116
#define TAG_BTN_DANHBAI 117

using namespace cocos2d;

#define CARD_SHOWING_ZORDER 1

#define CARD_SUIT_TYPE_NUM 4 // Loại bài trong bộ
#define CARD_NUM_OF_SUIT 13 // Số quân bài trong 1 loại

#define CARD_X_NUM 13 // rows
#define CARD_MARGIN 10 // Khoảng cách giữa các thẻ

Scene* TLMienNam::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TLMienNam::create();
 
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TLMienNam::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    this->initMenu(visibleSize, origin);

    sprite = Sprite::create("bgr_textview.png");
    sprite->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());
    this->addChild(sprite, 0);
    
    this->initGame();
   
    this->scheduleUpdate();
    
    return true;
}

void TLMienNam::initMenu(Size visibleSize,Vec2 origin){
    
    auto bkg = MSprite::create("bgr_select_table.jpg",visibleSize);
    bkg->setPosition(Point(origin.x, origin.y));
    
    auto btn_menu = MButton::create(BTN_MENU,TAG_BTN_MENU);
    btn_menu->setPosition(Vec2(origin.x+10,origin.y+visibleSize.height-btn_menu->getContentSize().height-10));
    btn_menu->addTouchEventListener(CC_CALLBACK_2(TLMienNam::menuCallBack,this));
    
    auto btn_message = MButton::create(BTN_MESSAGE,TAG_BTN_MESSAGE);
    btn_message->setPosition(Vec2(origin.x+ visibleSize.width - btn_message->getContentSize().width-10,
                                  origin.y+visibleSize.height-btn_message->getContentSize().height-10));
    btn_message->addTouchEventListener(CC_CALLBACK_2(TLMienNam::menuCallBack,this));
    
    auto btn_purcharse = MButton::create(BTN_PURCHASE,TAG_BTN_PURCHASE);
    btn_purcharse->setPosition(Vec2(btn_message->getPosition().x-10-btn_purcharse->getContentSize().width,
                                    origin.y+visibleSize.height-btn_purcharse->getContentSize().height-10));
    btn_purcharse->addTouchEventListener(CC_CALLBACK_2(TLMienNam::menuCallBack,this));
    
    auto btn_sound = MButton::create(BTN_SOUND_ON,TAG_BTN_SOUND);
    btn_sound->setPosition(Vec2(btn_purcharse->getPosition().x-10-btn_sound->getContentSize().width,
                                origin.y+visibleSize.height-btn_sound->getContentSize().height-10));
    btn_sound->addTouchEventListener(CC_CALLBACK_2(TLMienNam::menuCallBack,this));
    
    //================ play game button
    
    auto btn_chon_lai = MButton::create(BTN_BUTTON,"Chọn lại",25,TAG_BTN_CHONLAI);
    btn_chon_lai->setPosition(Vec2(origin.x+5,origin.y+5));
    btn_chon_lai->addTouchEventListener(CC_CALLBACK_2(TLMienNam::playCallBack,this));
    
    auto btn_xep_bai = MButton::create(BTN_BUTTON,"Xếp bài",25,TAG_BTN_XEPBAI);
    btn_xep_bai->setPosition(Vec2(btn_chon_lai->getPosition().x,
                                 btn_chon_lai->getPosition().y+btn_chon_lai->getContentSize().height));
    //btn_xep_bai->setPosition(Vec2(origin.x+5,origin.y+5));
    btn_xep_bai->addTouchEventListener(CC_CALLBACK_2(TLMienNam::playCallBack,this));
    
    auto btn_danh_bai = MButton::create(BTN_BUTTON,"Đánh bài",25,TAG_BTN_DANHBAI);
    //btn_danh_bai->setPosition(Vec2(btn_xep_bai->getPosition().x,
    //                            btn_xep_bai->getPosition().y+btn_xep_bai->getContentSize().height));
    btn_danh_bai->setPosition(Vec2(origin.x+visibleSize.width-btn_danh_bai->getContentSize().width-10,origin.y+5));
    btn_danh_bai->addTouchEventListener(CC_CALLBACK_2(TLMienNam::cardCallBack,this));
    
    this->addChild(bkg);
    this->addChild(btn_menu);
    this->addChild(btn_message);
    this->addChild(btn_purcharse);
    this->addChild(btn_sound);
    
    this->addChild(btn_chon_lai);
    this->addChild(btn_xep_bai);
    this->addChild(btn_danh_bai);
}

void TLMienNam::initGame(){
    this->initCards();
    this->showInitCard();
}

void TLMienNam::initCards(){
    std::vector<Card> cards;
    for (int type = 0; type < CARD_SUIT_TYPE_NUM; type++) {
        for (int number = 0; number < CARD_NUM_OF_SUIT; number++) {
            Card card;
            card.number = number + 1; // Số thẻ là 1-13
            card.type = (CardType)type;
            
            // Thêm một thẻ
            cards.push_back(card);
        }
    }
    
    // clear các mẫu thẻ.
    _cards.clear();
    for (int i = 0; i < CARD_X_NUM; i++) {
        
        auto card = cards[i+1];
        cards.erase(cards.begin() + (i+1));
        
        _cards.push_back(card);
    }
    
}

Card TLMienNam::getCard()
{
    std::random_device rd;
    std::mt19937 rand = std::mt19937(rd());
    
    int index = std::uniform_int_distribution<int>(0, (int)_cards.size() - 1)(rand);
    auto card = _cards[index];
    _cards.erase(_cards.begin() + index);
    
    return card;
}

void TLMienNam::createOtherCards(PositionIndex positionIndex, int tag,float marginX,float marginY,float rotage){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    double cardScale = this->cardScale();
    
    auto cardSprite = Sprite::create("nullx.png");
    
    Size cardSize = Size(cardSprite->getContentSize().width * cardScale,
                         cardSprite->getContentSize().height * cardScale);
    
    cardSprite->setPosition(Vec2(origin.x+visibleSize.width/2,
                                 origin.y+visibleSize.height/2));
    cardSprite->setScaleX(cardScale);
    cardSprite->setScaleY(cardScale);
    //cardSprite->setTag(tag);
    
    auto delay = DelayTime::create(1.5f);
    auto rotaged = RotateTo::create(0, rotage);
    auto scaleBy = ScaleBy::create(0, 0.8f);
    cardSize = cardSize*0.8f;
    Vec2 move;
    if(marginX<visibleSize.width/2){ //============================== left
        move = Vec2(origin.x + marginX + cardSize.height/2,
                    origin.y + marginY
                    +(positionIndex.y-6)*cardSize.width/4);
    }else if (marginX>visibleSize.width/2){ //======================= right
        move = Vec2(origin.x + marginX - cardSize.height/2,
                    origin.y + marginY
                    +(positionIndex.y-6)*cardSize.width/4);
    }else{ //========================================================= top
        move = Vec2(origin.x + marginX
                    + (positionIndex.x-6)*cardSize.width/3,
                    origin.y+marginY - cardSize.height/2);
    }
    auto moveTo = MoveTo::create(0.5f, move);
    auto sequence = Sequence::create(delay,rotaged,scaleBy,moveTo, NULL);
    cardSprite->runAction(sequence);
    
    this->addChild(cardSprite,CARD_SHOWING_ZORDER);
}


void TLMienNam::createCards(PositionIndex positionIndex, int tag){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    double cardScale = this->cardScale();
    
    auto card = this->getCard();
    CardSprite* cardSprite = CardSprite::create(card, positionIndex);
    
    Size cardSize = Size(cardSprite->getContentSize().width * cardScale,
                         cardSprite->getContentSize().height * cardScale);
    
    cardSprite->setPosition(Vec2(origin.x+visibleSize.width/2,
                                 origin.y + visibleSize.height/2));
    cardSprite->setScaleX(cardScale);
    cardSprite->setScaleY(cardScale);
    cardSprite->setTag(tag);
    
    auto delay = DelayTime::create(1.5f);
    MoveTo* moveTo;
    
    moveTo = MoveTo::create(0.5f,
                            Vec2(origin.x + visibleSize.width/2 + (positionIndex.x-6) * cardSize.width/3,
                            origin.y + 50 +cardSize.height/2 ));
    
    auto sequence = Sequence::create(delay,moveTo, NULL);
    cardSprite->runAction(sequence);
    
    this->card_tag.push_back(cardSprite);
}


void TLMienNam::showInitCard(){
    
    for(int i=0;i<CARD_X_NUM;i++){
        
    }
//    for (int tag = 0; tag < CARD_X_NUM; tag++) {
//        auto card = this->getChildByTag(tag);
//        if (card) {
//            // Xoá bỏ Nếu thẻ vẫn còn trên màn hình
//            card->removeFromParentAndCleanup(true);
//        }
//    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
    
    //createCard
    
    
    for (int i = 0; i < CARD_X_NUM; i++) {
        PositionIndex positionIndex;
        positionIndex.x = i;
        positionIndex.y = 0;
        this->createCards(positionIndex, i);
        this->addChild(card_tag[i]);
    }
    //for (int i=0; i<card_tag.size(); i++) {
        
    //}
    
    //create other Cards left
    float marginXLeft = 200;
    float marginYLeft = visibleSize.height/2;
    for(int i=0;i<CARD_X_NUM;i++){
        PositionIndex positionIndex;
        positionIndex.x = 0;
        positionIndex.y = i;
        this->createOtherCards(positionIndex, i,marginXLeft,marginYLeft,90);
    }
    
    //create other Cards right
    float marginXRight = visibleSize.width-200;
    float marginYRight = visibleSize.height/2;
    for(int i=0;i<CARD_X_NUM;i++){
        PositionIndex positionIndex;
        positionIndex.x = 0;
        positionIndex.y = i;
        this->createOtherCards(positionIndex, i,marginXRight,marginYRight,90);
    }
    
    //create other Cards top
    float marginXTop = visibleSize.width/2;
    float marginYTop = visibleSize.height-50;
    for(int i=0;i<CARD_X_NUM;i++){
        PositionIndex positionIndex;
        positionIndex.x = i;
        positionIndex.y = 0;
        this->createOtherCards(positionIndex, i,marginXTop,marginYTop,0);
    }
    
    
}

double TLMienNam::cardScale(){
    static double cardScale = 0;
    
    if (cardScale == 0) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        auto card = Sprite::create("01co.png");
        double scaleX = ((visibleSize.width - CARD_MARGIN * (CARD_X_NUM + 1)) / CARD_X_NUM) / card->getContentSize().width;
        
        cardScale = scaleX;
    }
    return cardScale;
}

void TLMienNam::cardCallBack(cocos2d::Ref *pSender, ui::Widget::TouchEventType eventType){
    if(eventType == ui::Widget::TouchEventType::ENDED){
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        //MButton *button = (MButton*) pSender;
        for (int i=0; i<card_tag.size(); i++) {
            if(card_tag[i]->isFirstTimeClick)
                card_tag[i]->setMove(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2, 0.15f);
            
        
        }
    }
}


void TLMienNam::update(float delta){
    auto position = sprite->getPosition();
    //cocos2d::log("%f",delta);
    position.x -= 250 * delta;
    if (position.x  < 0 - (sprite->getBoundingBox().size.width / 2))
        position.x = this->getBoundingBox().getMaxX() + sprite->getBoundingBox().size.width/2;
    sprite->setPosition(position);
}

void TLMienNam::playCallBack(Ref *pSender, ui::Widget::TouchEventType eventType){
    MButton *btn = (MButton*) pSender;
     if(eventType == ui::Widget::TouchEventType::ENDED){
         int tag = btn->getTag();
         switch (tag) {
             case TAG_BTN_XEPBAI:
                 CCLOG("%s","xep bai");
                 break;
             case TAG_BTN_CHONLAI:
                 CCLOG("%s","chon lai");
                 break;
             default:
                 break;
         }
     }
    
}

void TLMienNam::menuCallBack(Ref *pSender, ui::Widget::TouchEventType eventType){
    MButton *btn = (MButton*) pSender;
    if(eventType == ui::Widget::TouchEventType::ENDED){
        int tag = btn->getTag();
        switch (tag) {
            case TAG_BTN_MENU:
                CCLOG("%s","menu");
                {
                    //auto select = TableSelect::createScene();
                    //Director::getInstance()->replaceScene(TransitionCrossFade::create(0.15f, select));
                }
                break;
            case TAG_BTN_MESSAGE:
                CCLOG("%s","message");
                break;
            case TAG_BTN_PURCHASE:
                CCLOG("%s","purchase");
                break;
            case TAG_BTN_SOUND:
                CCLOG("%s","sound");
                break;
            default:
                break;
        }
    }
    
}



