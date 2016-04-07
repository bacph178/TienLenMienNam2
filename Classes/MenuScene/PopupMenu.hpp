//
//  PopupMenu.hpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//


///@ PopupSetting.h
#ifndef __POPUP_MENU_H__
#define __POPUP_MENU_H__

#include "CustomUI/Popup.hpp"

enum {
    eSldMusic = 0,
    eSldSound
};

class PopupMenu: public Popup {
public:
    CREATE_FUNC(PopupMenu);
    
    bool init();
    virtual void onExit();
    
    void sliderEvent(Ref *pSender, Slider::EventType type);
    void checkBoxSelectedEvent(Ref* pSender, CheckBox::EventType type);
    
    void changeVolumeOfAudio(int _typeAudio, float _valueVolume);
    
protected:
private:
    CheckBox					*m_checkboxMuteAllSound;
    Slider						*m_sliderOptionMusics[2];
};

#endif /* defined (__POPUP_MENU_H__) */
