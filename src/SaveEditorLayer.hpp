
using namespace geode::prelude;

class SaveEditorLayer : public CCLayer {
protected:
    CCSprite* m_bg;
    bool init();
public:
    static SaveEditorLayer* create();
};