// clangd automatically adds those when i use tab to autocomplete so who am i to argue
#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/GJAccountManager.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/utils/cocos.hpp"

#include "SaveEditorLayer.hpp"

using namespace cocos2d;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {

    bool init() {
        if (!MenuLayer::init()) return false;
        auto spr = geode::CircleButtonSprite::createWithSprite("btn.png"_spr, .75f);

	auto btn = CCMenuItemSpriteExtra::create(
            spr,
            this, menu_selector(MyMenuLayer::onSaveEditor)
        );

        auto menu = this->getChildByID("profile-menu");
        menu->addChild(btn);
	menu->setLayout(
            geode::RowLayout::create()
            ->setAxisAlignment(geode::AxisAlignment::Start)
            ->setGap(10.f)
	);

	btn->setID("button"_spr);

        return true;
    }

    void onSaveEditor(CCObject*) {
        (void)geode::cocos::switchToScene(SaveEditorLayer::create());
    }
};
