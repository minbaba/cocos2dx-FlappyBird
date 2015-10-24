//
//  bird.cpp
//  FlappyBird
//
//  Created by dell on 15/8/21.
//
//

#include "bird.h"

USING_NS_CC;
//初始化方法
bool Bird::init() {
    if (!Sprite::initWithFile("bird.png")) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    _scale = visibleSize.height /105 *0.06;
    auto size = Size(156, 105);
    //设置大小
    Sprite::setContentSize(size);
    Sprite::setPhysicsBody(PhysicsBody::createBox(size));
    Sprite::setScale(_scale);
    
    //设置碰撞器
    getPhysicsBody()->setContactTestBitmask(1);
    
    return true;
}
