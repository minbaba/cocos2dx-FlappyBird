//
//  PiPe.cpp
//  FlappyBird
//
//  Created by dell on 15/8/21.
//
//

#include "Pip.h"
USING_NS_CC;

#define INTERVAL_ROUND 70

#pragma mark - 初始化方法
bool Pip::init(Layer *layer,int speed) {
    _speed = speed;
    _layer = layer;
    _visibleSize = Director::getInstance()->getVisibleSize();
    _currentRound = 0;
    
    addPips();
    
    return true;
}

#pragma mark - 管道管理者的创造方法
Pip *Pip::create(Layer *layer,int speed) {
    auto _ins = new Pip();
    _ins->init(layer, speed);
    _ins->autorelease();
    
    return _ins;
}

#pragma mark - 创建新的管道
Sprite * Pip::createPip(const std::string &fileName, float positionY) {
    auto sp = Sprite::create(fileName);
    sp->setPosition(_visibleSize.width , positionY);
    sp->setContentSize(Size(46, 437));
    sp->setPhysicsBody(PhysicsBody::createBox(Size(46, 437)));
    //设置为静态刚体 不受重力影响
    sp->getPhysicsBody()->setDynamic(false);
    //设置碰撞器
    sp->getPhysicsBody()->setContactTestBitmask(1);
    
    return sp;
}

#pragma mark - 周期更新
void Pip::onUpdate() {
    for (int i = 0; i < _ups.size(); i++) {
        auto up = _ups.at(i);
        auto down = _downs.at(i);
        
        up->setPositionX(up->getPositionX() - _speed);
        down->setPositionX(down->getPositionX() - _speed);
        
        if (up->getPositionX() < 0 - _visibleSize.width /2) {
            _ups.eraseObject(up);
            _downs.eraseObject(down);
            i--;
        }
    }
    
    _currentRound ++;
    if (_currentRound == INTERVAL_ROUND) {
        addPips();
        _currentRound = 0;
    }
}
#pragma mark - 添加管道
void Pip::addPips() {
    float positionY = arc4random() % (int)(_visibleSize.height /3) +_visibleSize.height/4;
    auto down = createPip("pip_up.png", positionY + 437 /2.0 +_visibleSize.height /5);
    _layer->addChild(down, 100);
    _downs.pushBack(down);
    
    auto up = createPip("pip_down.png", positionY - 437 /2.0);
    _layer->addChild(up, 100);
    _ups.pushBack(up);
}



