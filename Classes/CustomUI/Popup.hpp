//
//  Popup.hpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//

//
//  Popup.cpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//

///@ Popup.h
#ifndef ___POPUP_HPP__
#define ___POPUP_HPP__

#include "string"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

USING_NS_CC;

class Popup : public Node {
public:
    CREATE_FUNC(Popup);
    
    virtual bool init();
    virtual void onExit();
    
    virtual void disappear();
    virtual void appear();
    
    virtual void setTitlePopup(std::string _titlePopup);
    
protected:
    Layer                       *m_popupLayer;
    
    Size                        backgroundContentSize;
    Size                        visibleSize;
    Point                       origin;
    
    ActionInterval              *m_appearAction;
    ActionInterval              *m_disappearAction;
    
private:
};

#endif /* defined (___POPUP_HPP__) */
