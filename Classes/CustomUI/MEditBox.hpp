//
//  MEditBox.hpp
//  GameVina
//
//  Created by Black3rry on 3/24/16.
//
//

#ifndef MEditBox_hpp
#define MEditBox_hpp

#include "cocos-ext.h"
#include "cocos2d.h"

class MEditBox : public cocos2d::ui::EditBox{
    
public:
    
    static MEditBox* create(cocos2d::Size size,std::string fileName);
    static MEditBox* createExtends(cocos2d::Size size,std::string fileName);
    
    virtual bool init() override; // Initializing process
    CREATE_FUNC(MEditBox);
    
public:
    
    float getWidth();
    float getHeight();
    
};

#endif /* MEditBox_hpp */
