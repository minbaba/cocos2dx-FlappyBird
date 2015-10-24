//
//  BackGroud.h
//  FlappyBird
//
//  Created by dell on 15/8/21.
//
//

#ifndef __FlappyBird__BackGroud__
#define __FlappyBird__BackGroud__

class BackGroud:public cocos2d::Ref {
    int _speed;
    float _scaleX;
    float _scaleY;
    cocos2d::Layer *_layer;
    cocos2d::Vector<cocos2d::Sprite *> _floors;
    cocos2d::Vector<cocos2d::Sprite *> _skys;
    cocos2d::Size _visibleSize;
public:
    
    virtual bool init(cocos2d::Layer *layer, int speed);
    /**创造一个背景管理机*/
    static BackGroud * create(cocos2d::Layer *layer, int speed);
    
    void onUpdate(float dt);
    
    cocos2d::Sprite *createSprite(const std::string &filename, cocos2d::Point position);
};

#endif /* defined(__FlappyBird__BackGroud__) */
