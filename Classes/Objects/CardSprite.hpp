//
//  CardSprite.hpp

#ifndef CardSprite_hpp
#define CardSprite_hpp

using namespace std;

#include "cocos2d.h"
#include "Config/GameConfig.h"

struct Card {
    int number;
    CardType type;
};

struct PositionIndex {
    int x;
    int y;
};

class CardSprite : public cocos2d::Sprite {
public:
    static CardSprite* create(Card card, PositionIndex PositionIndex);
    virtual bool init() override; // Initializing process
    void onEnter() override; // Display pre-treatment
    void addEvents();
    void touchEvent(cocos2d::Touch* touch);
    
    std::string getName(); // get name
    CardState cardState;  // card state
    bool isFirstTimeClick;
    cocos2d::Vec2 origionPostion;
    
    void update();
    
    CREATE_FUNC(CardSprite); // create Function create macro
    
    CC_SYNTHESIZE(Card, _card, Card); // Card information
    CC_SYNTHESIZE(PositionIndex, _positionIndex, PositionIndex); // Showing the location
    
public:
    
    //MOVE
    void setMove(float x,float y,float time);
    void setMove(float x,float y);
    
    // GET & SET
    void setValue(string value);
    string getValue();
    
    void setSuit(string suit);
    string getSuit();
    
    void setIsBack(bool isBack);
    bool getIsBack();
    
    void setState(CardState state);
    enum CardState getState();
    
    void  setCardValue(int cardValue);
    int getCardValue();
    
    void setNumberValue(int numberValue);
    int getNumberValue();
    
    void setNumberSuit(int numberSuit);
    int getNumberSuit();
    
    void setIndex(int index);
    int getIndex();
    
    void setCardType(CardType type);
    CardType getCardType();
    
    void setPostion(cocos2d::Vec2 postion);
    cocos2d::Vec2 getpostion();
    
private:
    std::string getFileName(Card card); // get image

private:
    std::string suit;
    std::string value;
    int cardValue;
    int numberValue;
    int numberSuit;
    
    int index;
    
    bool isBack;
    enum CardState state;
    cocos2d::Vec2 originalPosition;
    
    cocos2d::Vec2 screenPoint;
    cocos2d::Vec2 offset;
    
    bool isSavedPosition;
};

#endif /* CardSprite_hpp */
