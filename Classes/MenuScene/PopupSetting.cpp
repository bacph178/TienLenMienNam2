//
//  PopupSetting.cpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupSetting.cpp
#include "PopupSetting.hpp"
#include "CustomUI/MLabel.hpp"
#include "CustomUI/MButton.hpp"

#include "Config/GameConfig.h"

#define TAG_BTN_BACK 12

bool PopupSetting::init() {
    if (!Popup::init())
        return false;
    
    setTitlePopup("STR_SETTING_TITLE");
    
    for (int index = 0; index < 2; index++) {
        // label
        auto  _label = MLabel::create("Setting", 30);
        _label->setAdditionalKerning(7.0f);
        _label->setPosition(Vec2(backgroundContentSize.width / 2 + origin.x,
                                 backgroundContentSize.height * (7 - index*2) / 10 + origin.y));
        _label->setColor(Color3B::WHITE);
        m_popupLayer->addChild(_label, 1);
       
    }
    
    auto btn_back = MButton::create(BTN_BACK,TAG_BTN_BACK);
    btn_back->setPosition(Vec2(this->getPosition().x ,this->getPosition().y));
    m_popupLayer->addChild(btn_back);
    btn_back ->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->disappear();
                break;
            default:
                break;
        }
    });
    
    /// init checkbox
    // label
    auto  _labelMuteAllSound = MLabel::create("Sound", 30);
    _labelMuteAllSound->setAdditionalKerning(7.0f);
    _labelMuteAllSound->setPosition(Vec2(backgroundContentSize.width * 2 / 3 + origin.x,
                                         backgroundContentSize.height * 1 / 4 + origin.y));
    _labelMuteAllSound->setColor(Color3B::WHITE);
    m_popupLayer->addChild(_labelMuteAllSound, 1);
    
    // checkbox
    m_checkboxMuteAllSound = CheckBox::create(BTN_CENTS, BTN_HELPER, "cross", BTN_MENU, "crossed");
    m_checkboxMuteAllSound->setPosition(Vec2(backgroundContentSize.width * 1 / 3 + origin.x,
                                             backgroundContentSize.height * 1 / 4 + origin.y));
    m_checkboxMuteAllSound->addEventListener(CC_CALLBACK_2(PopupSetting::checkBoxSelectedEvent, this));
    m_popupLayer->addChild(m_checkboxMuteAllSound, 1);
    
    return true;
}

void PopupSetting::checkBoxSelectedEvent(Ref* pSender, CheckBox::EventType type) {
    switch (type)
    {
        case CheckBox::EventType::SELECTED:
            m_sliderOptionMusics[eSldMusic]->setPercent(0);
            m_sliderOptionMusics[eSldSound]->setPercent(0);
            
            // m_audio->setEffectsVolume(0.0f);
            // m_audio->setBackgroundMusicVolume(0.0f);
            break;
            
        case CheckBox::EventType::UNSELECTED:
            m_sliderOptionMusics[eSldSound]->setPercent(50);
            m_sliderOptionMusics[eSldMusic]->setPercent(50);
            
            //m_audio->setEffectsVolume(0.5f);
            //m_audio->setBackgroundMusicVolume(0.5f);
            break;
            
        default:
            break;
    }
}

void PopupSetting::changeVolumeOfAudio(int _typeAudio, float _valueVolume) {
    /* if (_typeAudio == eSldSound)
     m_audio->setEffectsVolume(_valueVolume);
    	else
     m_audio->setBackgroundMusicVolume(_valueVolume); */
}

void PopupSetting::onExit() {
    Popup::onExit(); 
}
