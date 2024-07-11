#include <_main.hpp>

#include <Geode/modify/BoomScrollLayer.hpp>
class $modify(BoomScrollLayerExt, BoomScrollLayer) {
    static BoomScrollLayer* create(cocos2d::CCArray* pages, int unk1, bool unk2, cocos2d::CCArray* unk3, DynamicScrollDelegate* delegate) {
        /*log::debug(
            "\n{}(\ncocos2d::CCArray* {},\n int {}, bool {},\n cocos2d::CCArray* {},\n DynamicScrollDelegate* {}\n)\n",
            __FUNCTION__, pages, unk1, unk2, unk3, (CCObject*)delegate
        );*/
        if (auto mainLevelsLayer = typeinfo_cast<LevelSelectLayer*>(delegate)) {
            //mainLevelsLayer->setRotation(12.f);
            //yeaa pages is standing for 3 level pages (dont touch them :D)
            //unk3 contains level nodes.

            auto myLevelsArray = CCArray::create();

            //add levels
            int id = SETTING(int64_t, "start_id");
            int max_id = SETTING(int64_t, "max_id");
            for (id; id <= max_id; id++)
                myLevelsArray->addObject(LevelTools::getLevel(id, 0));

            //the_tower
            if (SETTING(bool, "the_tower")) myLevelsArray->addObject(unk3->objectAtIndex(unk3->count() - 2));

            //cumingson
            if (SETTING(bool, "coming_soon")) myLevelsArray->addObject(unk3->objectAtIndex(unk3->count() - 1));

            return BoomScrollLayer::create(pages, unk1, unk2, myLevelsArray, mainLevelsLayer);
        }
        return BoomScrollLayer::create(pages, unk1, unk2, unk3, delegate);
    }
};

#include <Geode/modify/LevelPage.hpp>
class $modify(LevelPage) {
    $override void updateDynamicPage(GJGameLevel* p0) {
        LevelPage::updateDynamicPage(p0);
        //difficultySprite
        if (auto difficultySprite = typeinfo_cast<CCSprite*>(this->getChildByIDRecursive("difficulty-sprite"))) {
            std::string frameName = GJDifficultySprite::getDifficultyFrame((int)p0->m_difficulty, GJDifficultyName::Short).data();
            frameName = std::regex_replace(frameName, std::regex("difficulty"), "diffIcon");
            if (auto frame = CCSpriteFrameCache::get()->spriteFrameByName(frameName.data()))
                difficultySprite->setDisplayFrame(frame);
        }
    }
};