#include "HelloWorldScene.h"
#include "BackGroud.h"
#include "Pip.h"
#include "bird.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
//    scene->getPhysicsWorld()->setGravity(Vec2(0, -180));
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    float scale = visibleSize.height /105 *0.06;
    float speed = visibleSize.width /280;

    //创建背景管理器和管道管理器
    _backGround = BackGroud::create(this, speed);
    _backGround->retain();
    _pip = Pip::create(this, speed);
    _pip->retain();
    
    //创造小鸟
    auto bird = Bird::create();
    bird->setPosition(Point(bird->getContentSize().width *3 *scale, visibleSize.height/2));
    addChild(bird ,100);
    //创建碰撞检测器
    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = [this](PhysicsContact & contact){
        this->unschedule("fly");
        auto n_scene = GameOver::createScene();
        Director::getInstance()->replaceScene(n_scene);
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    //创建触摸检测器
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [bird, this, visibleSize](Touch * t,Event * e){
        bird->getPhysicsBody()->setVelocity(Vec2(0, visibleSize.height /5.5));
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //启动定时器
    schedule([this](float f) {
        this->_backGround->onUpdate(f);
        this->_pip->onUpdate();
    }, 1.0 /30, "fly");
    return true;
}

void HelloWorld::update(float dt) {
    
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
