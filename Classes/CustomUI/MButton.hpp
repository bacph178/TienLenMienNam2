//
//  MButton.hpp
//  GameVina
//
//  Created by Black3rry on 3/22/16.
//
//

#ifndef MButton_hpp
#define MButton_hpp

#include "ui/UIButton.h"

class MButton : public cocos2d::ui::Button {
    
public:
    
    static MButton* create(std::string textureNormal,int tag);
    static MButton* create(std::string textureNormal,std::string text,float size,int tag);
    static MButton* create(std::string textureNormal,std::string texturePressed,std::string text,float size,int tag);
    static MButton* create(std::string textureNormal,std::string text,float size,cocos2d::Color3B color,int tag);
    static MButton* create(std::string text,float size,int tag);
    
    static MButton* createExtends(std::string textureNormal,std::string text,float size,int tag);
    static MButton* createItem(std::string textureNormal,int tag);
    
    static MButton* createWidthSize(std::string textureNormal,cocos2d::Size size,std::string text,int tag);
    
    float getWidth();
    float getHeight();
    
    //===== init
    
    virtual bool init() override; // Initializing process
    
    CREATE_FUNC(MButton);
    
};

#endif /* MButton_hpp */
