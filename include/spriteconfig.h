/*
 * 子画面表(Sprite Sheet) 在 SDL_Texture 中找到自己想要的子图片 然后渲染出来
 * 这些数据都是标明了各个子图的位置和大小，不可轻易改动
 */
#ifndef _DF_TANKWAR_SPRITECONFIG_H
#define _DF_TANKWAR_SPRITECONFIG_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

// 一定要用 std::map 不能用 std::unorded_map 因为 unorded_map 要求 key 类一定可以被 hash
using std::map;

// 想要的图片类型
enum class SpriteType {
    TANK_A,
    TANK_B,
    TANK_C,
    TANK_D,

    PLAYER_1,
    PLAYER_2,

    BRICK_WALL,
    STONE_WALL,
    WATER,
    BUSH,
    ICE,

    BONUS_BOAT,
    BONUS_CLOCK,
    BONUS_GRENADE,
    BONUS_GUN,
    BONUS_HELMET,
    BONUS_SHOVEL,
    BONUS_STAR,
    BONUS_TANK,

    SHIELD,
    CREATE,
    DESTROY_TANK,
    DESTROY_BULLET,
    DESTROY_EAGLE,
    BOAT_P1,
    BOAT_P2,
    EAGLE,

    FLAG,
    BULLET,
    LEFT_ENEMY,
    STAGE_STATUS,
    TANKS_LOGO,

    NONE
};

class SpriteData {
public:
    SDL_Rect rect;

    SpriteData();
    SpriteData(int x, int y, int w, int h);
    SpriteData(SDL_Rect);
};

class SpriteConfig {
using Map = std::map<SpriteType, SpriteData>;
public:
    static SpriteConfig* getInstance() {
        static SpriteConfig sc;
        return &sc;
    };

    const SpriteData& get(SpriteType) const;
private:
    Map configs_;
    void init();

    SpriteConfig();
    SpriteConfig(const SpriteConfig&) {};
    SpriteConfig& operator=(const SpriteConfig &) {};
    ~SpriteConfig() {};
};

#endif // _DF_TANKWAR_SPRITECONFIG_H