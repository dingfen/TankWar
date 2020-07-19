/*
 * 子画面表(Sprite Sheet) 在 SDL_Texture 中找到自己想要的子图片 然后渲染出来
 * 这些数据都是标明了各个子图的位置和大小，不可轻易改动
 */
#ifndef _DF_TANKWAR_SPRITECONFIG_H
#define _DF_TANKWAR_SPRITECONFIG_H

#include "type.h"

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