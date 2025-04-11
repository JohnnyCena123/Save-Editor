#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {

    bool init() {
        if (MenuLayer::init()) return false;
        auto btnSpr = CCSprite::create("btn.png"_spr);
        return true;
    }
};