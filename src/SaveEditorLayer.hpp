#pragma once

using namespace cocos2d;

class SaveEditorLayer : public CCLayer {
protected:
    CCSprite* m_bg;
	geode::GenericContentLayer* m_contentLayer;
	CCMenu* m_btnMenu;
	CCMenuItemSpriteExtra* m_backBtn;
    bool init();
	void onBack(CCObject*);
public:
    static SaveEditorLayer* create();
};
