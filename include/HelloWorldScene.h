// Copyright 2016 rapmocha

#ifndef HELLOWORLDSCENE_H_
#define HELLOWORLDSCENE_H_

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer {
 public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);
};

#endif  // HELLOWORLDSCENE_H_
