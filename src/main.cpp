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
        auto btn = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSprite("btn.png"_spr), 
            this, menu_selector(MyMenuLayer::onSaveEditor)
        );

        auto menu = this->getChildByID("profile-menu");
        menu->setLayout(
            RowLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setGap(10.f)
        );

        menu->addChild(btn);

        return true;
    }

    void onSaveEditor(CCObject*) {
        (void)geode::cocos::switchToScene(SaveEditorLayer::create());
    }
};