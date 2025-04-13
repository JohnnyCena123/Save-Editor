#pragma once

using namespace cocos2d;

class SaveEditorLayer : public CCLayer {
protected:
    CCSprite* m_bg;
	CCLayer* m_contentLayer;
	geode::ScrollLayer* m_scrollLayer;

	std::map<std::string, std::string> m_stats;
	geode::Ref<CCDictionary> m_statNodes = CCDictionary::create();

	CCMenu* m_btnMenu;
	CCMenuItemSpriteExtra* m_backBtn;
	CCMenuItemSpriteExtra* m_applyBtn;
    bool init() override;
	void addStats();
	void onBack(CCObject*);
	void onApply(CCObject*);

	void keyBackClicked() override;
public:
    static SaveEditorLayer* create();
};
