// Copyright 2016 rapmocha

#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

static cocos2d::Size desSize = cocos2d::Size(480, 320);
static cocos2d::Size SSize = cocos2d::Size(480, 320);
static cocos2d::Size MSize = cocos2d::Size(1024, 768);
static cocos2d::Size LSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {}
AppDelegate::~AppDelegate() {}

void AppDelegate::initGLContextAttrs() {
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages() {
    return 0;  // flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect(
            "maketest", Rect(0, 0, desSize.width, desSize.height));
#else
        glview = GLViewImpl::create("maketest");
#endif
        director->setOpenGLView(glview);
    }
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
    glview->setDesignResolutionSize(
        desSize.width, desSize.height, ResolutionPolicy::NO_BORDER);
    Size frameSize = glview->getFrameSize();
    if (frameSize.height > MSize.height) {
        director->setContentScaleFactor(
            MIN(LSize.height/desSize.height, LSize.width/desSize.width));
    } else if (frameSize.height > SSize.height) {
        director->setContentScaleFactor(
            MIN(MSize.height/desSize.height, MSize.width/desSize.width));
    } else {
        director->setContentScaleFactor(
            MIN(SSize.height/desSize.height, SSize.width/desSize.width));
    }
    register_all_packages();
    auto scene = HelloWorld::createScene();
    director->runWithScene(scene);
    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}

