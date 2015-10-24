//
//  bird.h
//  FlappyBird
//
//  Created by dell on 15/8/21.
//
//

#ifndef __FlappyBird__bird__
#define __FlappyBird__bird__

#include <cocos2d.h>

class Bird:public cocos2d::Sprite {
private:
    float _scale;
public:
    virtual bool init();
    
    CREATE_FUNC(Bird);
};

#endif /* defined(__FlappyBird__bird__) */
