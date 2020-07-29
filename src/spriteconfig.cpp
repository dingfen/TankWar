#include "spriteconfig.h"

SpriteData::SpriteData(int x, int y, int w, int h) 
    : rect{x, y, w, h} {};

SpriteData::SpriteData(SDL_Rect rect)
    : rect(rect) {};

SpriteData::SpriteData() 
    : rect{0, 0, 0, 0} {};

void SpriteConfig::init() {
    configs_[SpriteType::TANK_A] = SpriteData(128, 0, 32, 32);
    configs_[SpriteType::TANK_B] = SpriteData(128, 64, 32, 32); 
    configs_[SpriteType::TANK_C] = SpriteData(128, 128, 32, 32);
    configs_[SpriteType::TANK_D] = SpriteData(128, 192, 32, 32);

    configs_[SpriteType::PLAYER_1] = SpriteData(640, 0, 32, 32);
    configs_[SpriteType::PLAYER_2] = SpriteData(768, 0, 32, 32);

    configs_[SpriteType::BRICK_WALL] = SpriteData(928, 0, 16, 16);
    configs_[SpriteType::STONE_WALL] = SpriteData(928, 144, 16, 16);
    configs_[SpriteType::WATER] = SpriteData(928, 160, 16, 16);
    configs_[SpriteType::BUSH] = SpriteData(928, 192, 16, 16);
    configs_[SpriteType::ICE] = SpriteData(928, 208, 16, 16);

    configs_[SpriteType::BONUS_GRENADE] = SpriteData(896, 0, 32, 32);
    configs_[SpriteType::BONUS_HELMET] = SpriteData(896, 32, 32, 32);
    configs_[SpriteType::BONUS_CLOCK] = SpriteData(896, 64, 32, 32);
    configs_[SpriteType::BONUS_SHOVEL] = SpriteData(896, 96, 32, 32);
    configs_[SpriteType::BONUS_TANK] = SpriteData(896, 128, 32, 32);
    configs_[SpriteType::BONUS_STAR] = SpriteData(896, 160, 32, 32);
    configs_[SpriteType::BONUS_GUN] = SpriteData(896, 192, 32, 32);
    configs_[SpriteType::BONUS_BOAT] = SpriteData(896, 224, 32, 32);

    configs_[SpriteType::SHIELD] = SpriteData(976, 0, 32, 32);
    configs_[SpriteType::CREATE] = SpriteData(1008, 0, 32, 32);
    configs_[SpriteType::DESTROY_TANK] = SpriteData(1040, 0, 64, 64);
    configs_[SpriteType::DESTROY_BULLET] = SpriteData(1108, 0, 32, 32);
    configs_[SpriteType::BOAT_P1] = SpriteData(944, 96, 32, 32);
    configs_[SpriteType::BOAT_P2] = SpriteData(976, 96, 32, 32);

    configs_[SpriteType::EAGLE] = SpriteData(944, 0, 32, 32);
    configs_[SpriteType::DESTROY_EAGLE] = SpriteData(1040, 0, 64, 64);
    configs_[SpriteType::FLAG] = SpriteData(944, 64, 16, 16);
    configs_[SpriteType::BULLET] = SpriteData(944, 128, 8, 8);

    configs_[SpriteType::LEFT_ENEMY] = SpriteData(944, 144, 16, 16);
    configs_[SpriteType::STAGE_STATUS] = SpriteData(976, 64, 32, 32);
    configs_[SpriteType::TANKS_LOGO] = SpriteData(0, 260, 406, 72);
};

SpriteConfig::SpriteConfig() {
    init();
}


const SpriteData& SpriteConfig::get(SpriteType type) const {
    return configs_.at(type);
}