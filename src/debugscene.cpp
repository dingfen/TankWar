#include "debugscene.h"
#include "engine.h"

DebugScene::DebugScene() {
    is_finished_ = false;
    prepare_time_ = AppConfig::prepare_time;
}

DebugScene::~DebugScene() {

}

void DebugScene::draw() {
    Engine *e = Engine::getInstance();
    e->clear();

    if (prepare_time_ > 0) {
        std::string text = "This is Debug Scene. Ready ?";
        e->writeText(SDL_Point{-1, -1}, text);
        e->update();
    }
}

void DebugScene::update(int dt) {
    if (prepare_time_ > 0) {
        prepare_time_ -= dt;
        SDL_UpdateWindowSurface(Engine::getInstance()->getWindow());
    } else {

    }
}

void DebugScene::event(SDL_Event *e) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
        case SDLK_ESCAPE:
            is_finished_ = true;
            break;
        default:
            break;
        }
    }
}

bool DebugScene::finish() {
    return this->is_finished_;
}

void DebugScene::nextstate(unique_ptr<AppState>& app_state) {
    if (is_finished_) {
        app_state.reset();
    }
}