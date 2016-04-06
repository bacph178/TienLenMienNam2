//
//  CardSprite.cpp

#include "CardSprite.hpp"
#include "Config/GameConfig.h"

using namespace cocos2d;

CardSprite* CardSprite::create(Card card, PositionIndex PositionIndex) {
    
    CardSprite* cardSprite = CardSprite::create();
    cardSprite->setCard(card);
    cardSprite->setPositionIndex(PositionIndex);
    cardSprite->setTexture(cardSprite->getFileName(card));
    cardSprite->addEvents();
    return cardSprite;
}

bool CardSprite::init() {
    
    if (!Sprite::init()) {
        return false;
    }
    
    this->isBack = false;
    this->suit = "Spade";
    this->value = "1";
    this->state = Idle;
    
    this->cardState = Idle;
    this->isFirstTimeClick = false;
    this->origionPostion = cocos2d::Vec2(0,0);
    
    return true;
}

std::string CardSprite::getName(){
    return getFileName(this->getCard());
}

void CardSprite::onEnter() {
    Sprite::onEnter();
}

void CardSprite::addEvents(){
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p))
        {
            return true; // to indicate that we have consumed it.
        }
        
        return false; // we did not consume this event, pass thru.
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        
        CardSprite::touchEvent(touch);
        if(cardState == Idle){
            if(!isFirstTimeClick){
                origionPostion = this->getPosition();
                isFirstTimeClick = true;
            }
            cardState = OnHand;
            auto moveBy = MoveBy::create(0.15f, cocos2d::Vec2(0,25));
            this->runAction(moveBy);
            
        }else if(cardState == OnHand){
            cardState = Idle;
            isFirstTimeClick = false;
            auto moveBy = MoveBy::create(0.15f, cocos2d::Vec2(0,-25));
            this->runAction(moveBy);
        }
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// MOVE

void CardSprite::setMove(float x, float y, float time){
    this->runAction(MoveTo::create(time,cocos2d::Vec2(x,y)));
}

void CardSprite::setMove(float x, float y){
    this->runAction(MoveTo::create(0.15f,cocos2d::Vec2(x,y)));
}

// GET & SET

void CardSprite::setValue(string value){
    this->value = value;
}

string CardSprite::getValue(){
    return this->value;
}

void CardSprite::setSuit(string suit){
    this->suit = suit;
}

string CardSprite::getSuit(){
    return this->suit;
}

void CardSprite::setIsBack(bool isBack){
    this->isBack = isBack;
}

bool CardSprite::getIsBack(){
    return this->isBack;
}

void CardSprite::setState(CardState state){
    this->state = state;
}

CardState CardSprite::getState(){
    return this->state;
}

void CardSprite::setCardValue(int cardValue){
    this->cardValue = cardValue;
}

int CardSprite::getCardValue(){
    return this->cardValue;
}

void CardSprite::setNumberValue(int numberValue){
    this->numberValue = numberValue;
}

int CardSprite::getNumberValue(){
    return this->numberValue;
}

void CardSprite::setNumberSuit(int numberSuit){
    this->numberSuit = numberSuit;
}

int CardSprite::getNumberSuit(){
    return this->numberSuit;
}

void CardSprite::setIndex(int index){
    this->index = index;
}

int CardSprite::getIndex(){
    return this->index;
}


void CardSprite::update(){
    switch(state)
    {
        case Idle:
        {
            break;
        }
        case OnHand:
        {
            break;
        }
        case Putted:
        {
            break;
        }
        case Fold:
        {
            break;
        }
        case Destroy:
        {
            
            break;
        }
        default:
        {
            break;
        }
    }
}



// Touch Event!

void CardSprite::touchEvent(cocos2d::Touch* touch)
{
    CCLOG("touched : %s",getName().c_str());
}

std::string CardSprite::getFileName(Card card)
{
    std::string filename;
    
    switch (card.type) {
            
        case Diamonds: {
            filename = StringUtils::format("%02dro.png",card.number);
            break;
        }
        case Hearts: {
            filename = StringUtils::format("%02dco.png",card.number);
            break;
        }
        case Clubs: {
            filename = StringUtils::format("%02dtep.png",card.number);
            break;
        }
        case Spade: {
            filename = StringUtils::format("%02dbich.png",card.number);
            break;
        }
        case OTHER: {
            filename = StringUtils::format("nullx.png");
            break;
        }
    }
    
    return filename;
}