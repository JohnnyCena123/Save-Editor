#include "SaveEditorLayer.hpp"

using namespace cocos2d;

bool SaveEditorLayer::init() {
    m_bg = CCSprite::create("GJ_gradientBG.png");

    m_bg->setAnchorPoint({0.f, 0.f});
    m_bg->setPosition({-5.f, -5.f});

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto bgSize = m_bg->getContentSize();
    m_bg->setScaleX((winSize.width + 10.f) / bgSize.width);
    m_bg->setScaleY((winSize.height + 10.f) / bgSize.height);
    m_bg->setColor({0, 102, 255});
	this->addChild(m_bg);

	m_contentLayer = geode::GenericContentLayer::create(winSize.width, winSize.height);
	m_contentLayer->setLayout(geode::AnchorLayout::create());
	m_contentLayer->setAnchorPoint({0.f, 0.f});
	this->addChild(m_contentLayer);


	auto gsm = GameStatsManager::get();

	auto jumps = geode::TextInput::create(100.f, "Jumps", "bigFont.fnt");
	jumps->setFilter("0123456789");
	jumps->setCallback([gsm](std::string const& str) {
		gsm->setStat("1", stoi(str));
	});

	m_contentLayer->addChildAtPosition(jumps, geode::Anchor::Center);

	m_btnMenu = CCMenu::create();
	m_contentLayer->addChild(m_btnMenu);

	m_backBtn = CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png"),
		this, menu_selector(SaveEditorLayer::onBack)
	);
	m_backBtn->setAnchorPoint({0.f, 1.f});
	m_btnMenu->addChildAtPosition(
		m_backBtn, geode::Anchor::TopLeft, {10.f, -10.f}
	);

	m_bg->setID("background");
	m_btnMenu->setID("button-menu");
	m_backBtn->setID("back-button");
	this->setID("layer"_spr);

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

void SaveEditorLayer::onBack(CCObject*) {
	CCDirector::get()->replaceScene(CCTransitionFade::create(0.5, MenuLayer::scene(false)));
}
