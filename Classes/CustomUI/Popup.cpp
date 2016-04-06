///@ Popup.cpp


#include "Popup.hpp"
#include "CustomUI/MLabel.hpp"

bool Popup::init() {
    if (!Node::init())
        return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = Sprite::create("bgr_charge.png");
    background->setAnchorPoint(Vec2::ZERO);
    background->setPosition(Point::ZERO);
    
    backgroundContentSize = background->getContentSize();
    
    m_popupLayer = Layer::create();
    m_popupLayer->setAnchorPoint(Vec2::ZERO);
    m_popupLayer->setPosition(Vec2(origin.x+visibleSize.width/2-backgroundContentSize.width/2,
                                   origin.y+visibleSize.height));
    addChild(m_popupLayer);
    
    m_popupLayer->addChild(background);
    
    m_appearAction = TargetedAction::create(m_popupLayer,MoveTo::create(0.15f,
                                            Vec2(origin.x+visibleSize.width/2-backgroundContentSize.width/2,
                                            visibleSize.height/2 - backgroundContentSize.height/2 +origin.y)));
    
    m_disappearAction = TargetedAction::create(m_popupLayer,MoveTo::create(0.15f,
                                                Vec2(origin.x+visibleSize.width/2-backgroundContentSize.width/2, origin.y+visibleSize.height)));
    
    m_appearAction->retain();
    m_disappearAction->retain();
    
    return true;
}

void Popup::disappear() {
    this->runAction(m_disappearAction->clone());
}

void Popup::appear() {
    this->runAction(m_appearAction->clone());
}

void Popup::setTitlePopup(std::string _titlePopup) {
    auto _title = MLabel::create("Tesst", 30);
    _title->setAdditionalKerning(7.0f);
    _title->setPosition(Point(backgroundContentSize.width / 2 + origin.x,
                              backgroundContentSize.height * 8 / 10 + origin.y));
    
    _title->setColor(Color3B::WHITE);
    _title->setScale(1.5f);
    
    m_popupLayer->addChild(_title);
}

void Popup::onExit() {
    m_appearAction->release();
    m_disappearAction->release();
    
    Node::onExit();
}