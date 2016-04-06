#include "IntroScene.h"
#include "MLabel.hpp"
#include "MSprite.hpp"

Scene* IntroScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IntroScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("resources.plist");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //=============
    
	auto introBG = MSprite::create("bg.png",visibleSize);
	introBG->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    introBG->setColor(Color3B::BLACK);
    
	this->addChild(introBG);
    
    auto label = MLabel::create("BigKen Online", 65);
    label->setPosition(Vec2(origin.x + visibleSize.width/2 - label->getWidth()/2,
                            origin.y + visibleSize.height/2 - label->getHeight()/2));
    
    this->addChild(label);

	this->scheduleOnce(schedule_selector(IntroScene::gotoStartScene), 2.0f);
    
    return true;
}

void IntroScene::gotoStartScene(float dt)
{
	//auto startscene = LoginScene::createScene();
	//Director::getInstance()->replaceScene(TransitionCrossFade::create(0.25f, startscene));
}
