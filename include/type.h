/*
 * in this file
 * we define some necessary datatype
 */ 
#ifndef _DF_TANKWAR_TYPE_H
#define _DF_TANKWAR_TYPE_H

#include <vector>
#include <memory>
#include <map>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using std::vector;
using std::shared_ptr;
using std::cerr;
using std::cout;
using std::endl;
using std::unique_ptr;

class Object;

struct PlayerData
{
    int player_id_;
    int score_;
    int life_count_;
    vector<shared_ptr<Object>> goods_;
};

enum class Direction {
    UP = 0, RIGHT = 32, DOWN = 64, LEFT = 96
};

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

#endif // _DF_TANKWAR_TYPE_H