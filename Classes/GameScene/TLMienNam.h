#ifndef __TLMIENNAM_SCENE_H__
#define __TLMIENNAM_SCENE_H__

#include "cocos2d.h"
#include "Objects/CardSprite.hpp"
#include "CustomUI/MButton.hpp"
#include "CustomUI/MSprite.hpp"

class SettingDialog;

using namespace cocos2d;

class TLMienNam : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(TLMienNam);
    
    void update(float) override;

protected:
    std::vector<Card> _cards;
    std::vector<Card> _cards_left;
    std::vector<Card> _cards_right;
    std::vector<Card> _cards_top;
    
    std::vector<CardSprite*> card_tag;
    
    void initMenu(Size size,Vec2 origin);
    void initCards();
    Card getCard();
    void createCards(PositionIndex index,int tag);
    void createOtherCards(PositionIndex index,int tag,float marginX,float marginY,float rotage);
    void showInitCard();
    void initGame();
    double cardScale();
    
    void menuCallBack(Ref *pSender, ui::Widget::TouchEventType eventType);
    void playCallBack(Ref *pSender, ui::Widget::TouchEventType eventType);
    void cardCallBack(Ref *pSender, ui::Widget::TouchEventType eventType);
    
private:
    
    Sprite * sprite;
    int cardTag;
    //CardSprite *cardSprite;
    
    
   
};


#endif // __TLMIENNAM_SCENE_H__
