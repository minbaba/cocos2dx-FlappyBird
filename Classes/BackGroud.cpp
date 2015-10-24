
//
//  BackGroud.cpp
//  FlappyBird
//
//  Created by dell on 15/8/21.
//
//

#include "BackGroud.h"
USING_NS_CC;
#pragma mark - 初始化方法
bool BackGroud::init(cocos2d::Layer *layer, int speed) {
    _speed = speed;
    _visibleSize = Director::getInstance()->getVisibleSize();
    _layer = layer;
    _scaleX = _visibleSize.width /800;
    _scaleY = _visibleSize.height /480;
    
    //创建一个天空背景
    auto sky = createSprite("bg_sky.png", Point(_visibleSize.width /2,_visibleSize.height - (416 *_scaleY)/2));
    _layer->addChild(sky, 0);
    _skys.pushBack(sky);
    
    //创建一个地板背景
    auto floor = createSprite("bg_floor.png", Point(_visibleSize.width /2, (64 *_scaleY)/2));
    floor->setPhysicsBody(PhysicsBody::createBox(Size(_visibleSize.width, 64*_scaleY)));
    floor->getPhysicsBody()->setDynamic(false);
    //设置碰撞器
    floor->getPhysicsBody()->setContactTestBitmask(1);
    _layer->addChild(floor, 101);
    _floors.pushBack(floor);
    
    return true;
}
#pragma mark - 创造方法
BackGroud *BackGroud::create(cocos2d::Layer *layer, int speed) {
    BackGroud* _ins = new(std::nothrow) BackGroud;
    _ins->autorelease();
    _ins->init(layer, speed);
    log(">>>>%d", _ins->getReferenceCount());
    
    return _ins;
}
#pragma mark - 创建一个背景
Sprite *BackGroud::createSprite(const std::string &filename, cocos2d::Point position) {
    //创建一个背景
    auto img = Director::getInstance()->getTextureCache()->addImage(filename);
    auto bg = Sprite::createWithTexture(img);
    bg->setScale(_scaleX, _scaleY);
    bg->cocos2d::Node::setPosition(position);
    return bg;
}
#pragma mark - 更新 轮播背景
void BackGroud::onUpdate(float dt) {
    
    log("-----%d", getReferenceCount());
    for (int i = 0; i < _skys.size(); i++) {
        auto sky = _skys.at(i);
        auto floor = _floors.at(i);
        sky->setPositionX(sky->getPositionX() - _speed);
        floor->setPositionX(floor->getPositionX() - _speed);
        if (sky->getPositionX() < 0 - _visibleSize.width /2) {
            _skys.eraseObject(sky);
            _floors.eraseObject(floor);
            i--;
        }
        if (i == _skys.size() -1 && sky->getPositionX() <= _visibleSize.width/2){
            auto n_sky = createSprite("bg_sky.png", Point(sky->getPositionX() +_visibleSize.width, sky->getPositionY()));
            _layer->addChild(n_sky, 0);
            _skys.pushBack(n_sky);
            
            auto n_floor = createSprite("bg_floor.png", Point(floor->getPositionX() +_visibleSize.width, floor->getPositionY()));
            n_floor->setPhysicsBody(PhysicsBody::createBox(Size(_visibleSize.width, 64*_scaleY)));
            n_floor->getPhysicsBody()->setDynamic(false);
            //设置碰撞器
            n_floor->getPhysicsBody()->setContactTestBitmask(1);
            _layer->addChild(n_floor, 101);
            _floors.pushBack(n_floor);
        }
    }
    
//    for (auto it = _bgs.begin(); it != _bgs.end(); it++) {
//        //移动背景
//        (*it)->setPositionX((*it)->getPositionX() - _speed);
//        //判断背景是否已经移除视野 进行删除
//        if ((*it)->getPositionX() < 0 - _visibleSize.width /2) {
//            (*it)->removeFromParent();
//            _bgs.eraseObject(*it);
//        }
//        //判断是否需要新加bg图片
//        if (it +1 == _bgs.end() && (*it)->getPositionX() <=_visibleSize.width/2 -_speed) {
//            auto bg = createSprite(Point((*it)->getPositionX() +_visibleSize.width -_speed, _visibleSize.height /2));
//            _layer->addChild(bg, 0);
//            _bgs.pushBack(bg);
//            break;
//        }
//    }
}
