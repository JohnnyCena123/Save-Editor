#include "SaveEditorLayer.hpp"

bool SaveEditorLayer::init() {
    m_bg = CCSprite::create("GJ_gradientBG.png");

    m_bg->setAnchorPoint({0.f, 0.f});
    m_bg->setPosition({-5.f, -5.f});

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto bgSize = m_bg->getContentSize();
    m_bg->setScaleX((winSize.width + 10.f) / bgSize.width);
    m_bg->setScaleY((winSize.height + 10.f) / bgSize.height);

    this->addChild(m_bg);

    return true;
}

SaveEditorLayer* SaveEditorLayer::create() {
    auto ret = new SaveEditorLayer();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}