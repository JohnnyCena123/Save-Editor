#pragma once

using namespace cocos2d;

class SaveEditorLayer : public CCLayer {
protected:
    CCSprite* m_bg;
	CCLayer* m_contentLayer;
	geode::ScrollLayer* m_scrollLayer;
	std::map<std::string, std::string> m_stats;
	CCMenu* m_btnMenu;
	CCMenuItemSpriteExtra* m_backBtn;
    bool init();
	void addStats();
	void onBack(CCObject*);
public:
    static SaveEditorLayer* create();
};
