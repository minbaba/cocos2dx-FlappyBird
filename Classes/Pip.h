//
//  PiPe.h
//  FlappyBird
//
//  Created by dell on 15/8/21.
//
//

#ifndef __FlappyBird__PiPe__
#define __FlappyBird__PiPe__

#include <cocos2d.h>

class Pip:public cocos2d::Ref {
    int _speed;
    int _currentRound;
    cocos2d::Layer *_layer;
    cocos2d::Size _visibleSize;
    cocos2d::Vector<cocos2d::Sprite *> _ups;
    cocos2d::Vector<cocos2d::Sprite *> _downs;
public:
    virtual bool init(cocos2d::Layer *layer,int speed);
    static Pip *create(cocos2d::Layer *layer, int speed);
    cocos2d::Sprite * createPip(const std::string &fileName, float positionY);
    
    void addPips();
    
    void onUpdate();
};

#endif /* defined(__FlappyBird__PiPe__) */
