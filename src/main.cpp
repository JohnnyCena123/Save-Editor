// clangd automatically adds those when i use tab to autocomplete so who am i to argue
#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/GJAccountManager.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/utils/cocos.hpp"

#include "SaveEditorLayer.hpp"

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {

    bool init() {
        if (MenuLayer::init()) return false;
        auto spr = CircleButtonSprite::createWithSpriteFrameName("adRope_001.png");

	if (!spr) return true;
	auto btn = CCMenuItemSpriteExtra::create(
            spr,
            this, menu_selector(MyMenuLayer::onSaveEditor)
        );

	if (btn == nullptr) return true;

        auto menu = this->getChildByID("profile-menu");
        menu->setLayout(
            RowLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setGap(10.f)
        );

        menu->addChild(btn);
	menu
        return true;
    }

    void onSaveEditor(CCObject*) {
        (void)geode::cocos::switchToScene(SaveEditorLayer::create());
    }
};
