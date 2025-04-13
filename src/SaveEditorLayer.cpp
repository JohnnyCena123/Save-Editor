#include "SaveEditorLayer.hpp"

using namespace cocos2d;

using geode::Anchor;
using geode::AxisAlignment;

bool SaveEditorLayer::init() {
	if (!CCLayer::init()) return false;

	this->setKeypadEnabled(true);

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

	m_scrollLayer = geode::ScrollLayer::create({winSize.width - 100.f, winSize.height - 100.f});
	m_scrollLayer->ignoreAnchorPointForPosition(false);
	m_contentLayer->addChildAtPosition(m_scrollLayer, Anchor::Center);

	m_scrollLayer->m_contentLayer->setLayout(geode::RowLayout::create()
//	m_scrollLayer->m_contentLayer->setLayout(geode::ColumnLayout::create()
		->setAxisAlignment(AxisAlignment::Start)
//		->setCrossAxisAlignment(AxisAlignment::End)
		->setGap(10.f)
//		->setAxisReverse(true)
//		->setCrossAxisReverse(true)
		->setGrowCrossAxis(true)
//		->setAutoGrowAxis(winSize.height - 100.f)
	);
//	m_scrollLayer->m_contentLayer->setAnchorPoint({0.f, 1.f});
//	m_scrollLayer->m_contentLayer->removeFromParent();
//	m_scrollLayer->addChildAtPosition(m_scrollLayer->m_contentLayer, Anchor::TopLeft);


	addStats();


	m_btnMenu = CCMenu::create();
	m_contentLayer->addChild(m_btnMenu);

	m_backBtn = CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png"),
		this, menu_selector(SaveEditorLayer::onBack)
	);
	m_backBtn->setAnchorPoint({0.f, 1.f});
	m_btnMenu->addChildAtPosition(m_backBtn, Anchor::TopLeft, {10.f, -10.f});

	m_applyBtn = CCMenuItemSpriteExtra::create(
		ButtonSprite::create("Apply"),
		this, menu_selector(SaveEditorLayer::onApply)
	);
	m_btnMenu->addChildAtPosition(m_applyBtn, Anchor::Bottom, {0.f, 25.f});

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

void SaveEditorLayer::onApply(CCObject*) {
	auto gsm = GameStatsManager::get();
	for (auto const& [key, btn] : geode::cocos::CCDictionaryExt<std::string, geode::TextInput*>(m_statNodes))
		gsm->setStat(key.c_str(), stoi(btn->getString()));
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
		auto node = geode::TextInput::create(100.f, name, "bigFont.fnt");
		node->setString(fmt::format("{}", gsm->getStat(key.c_str())));
		node->setLabel(name);
        	node->setFilter("0123456789");
		m_statNodes->setObject(node, key);

		auto container = CCNode::create();
		container->setContentSize({node->getContentWidth(), 1.5f * node->getContentHeight()});
		container->addChildAtPosition(node, Anchor::Center, {0.f, -.15f * node->getContentHeight()});
		m_scrollLayer->m_contentLayer->addChild(container);
	}

	m_scrollLayer->m_contentLayer->updateLayout();
//	m_scrollLayer->m_contentLayer->setContentHeight(std::max(
//		m_scrollLayer->getContentHeight(),
//		m_scrollLayer->m_contentLayer->getContentHeight()
//	));
}

void SaveEditorLayer::keyBackClicked() {
	onBack(nullptr);
}
