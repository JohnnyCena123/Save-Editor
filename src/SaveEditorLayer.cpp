#include "SaveEditorLayer.hpp"

using namespace cocos2d;

using geode::Anchor;
using geode::AxisAlignment;

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


	m_contentLayer = CCLayer::create();
	m_contentLayer->setLayout(geode::AnchorLayout::create());
	m_contentLayer->setAnchorPoint({0.f, 0.f});
	this->addChild(m_contentLayer);

	m_scrollLayer = geode::ScrollLayer::create({winSize.width - 100.f, winSize.height - 50.f});
	m_scrollLayer->ignoreAnchorPointForPosition(false);
	m_contentLayer->addChildAtPosition(m_scrollLayer, Anchor::Center);

	m_scrollLayer->m_contentLayer->setLayout(geode::RowLayout::create()
		->setAxisAlignment(AxisAlignment::Center)
		->setCrossAxisAlignment(AxisAlignment::End)
		->setGap(25.f)
		->setGrowCrossAxis(true)
	);

	addStats();


	m_btnMenu = CCMenu::create();
	m_contentLayer->addChild(m_btnMenu);

	m_backBtn = CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png"),
		this, menu_selector(SaveEditorLayer::onBack)
	);
	m_backBtn->setAnchorPoint({0.f, 1.f});
	m_btnMenu->addChildAtPosition(
		m_backBtn, Anchor::TopLeft, {10.f, -10.f}
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

void SaveEditorLayer::addStats() {

	auto gsm = GameStatsManager::get();


	m_stats["1"] = "Jumps";
	m_stats["2"] = "Attempts";
	m_stats["3"] = "Completed Official Levels";
	m_stats["4"] = "Completed Online Levels";
	m_stats["5"] = "Completed Demons";
	m_stats["6"] = "Total Stars";
	m_stats["7"] = "Completed MapPacks";


	for (auto const& [key, name] : m_stats) {
		auto node = geode::TextInput::create(100.f, /* capitalize */name, "bigFont.fnt");
		node->setString(fmt::format("{}", gsm->getStat(key.c_str())));
		node->setLabel(name);
        	node->setFilter("0123456789");
        	node->setCallback([&](std::string const& str) {
           		gsm->setStat(key.c_str(), stoi(str));
        	});
		m_scrollLayer->m_contentLayer->addChild(node);
	}

	m_scrollLayer->m_contentLayer->updateLayout();
	m_scrollLayer->m_contentLayer->setContentHeight(std::max(
		m_scrollLayer->getContentHeight(),
		m_scrollLayer->m_contentLayer->getContentHeight()
	));
}

