#include <SDL2/SDL.h>
#include <State/WorldStateMove.hpp>

void WorldStateMove::handleInput() {
    SDL_Event event;
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ){
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym ) {

            case SDLK_LEFT:
                if (mWorld.existsActivePolygon()) {
                    mWorld.getActivePolygon()->moveX(-2);
                }
                break;

            case SDLK_RIGHT:
                if (mWorld.existsActivePolygon()) {
                    mWorld.getActivePolygon()->moveX(2);
                }

                break;

            case SDLK_UP:
                if (mWorld.existsActivePolygon()) {
                    mWorld.getActivePolygon()->moveY(-2);
                }
                break;

            case SDLK_DOWN:
                if (mWorld.existsActivePolygon()) {
                    mWorld.getActivePolygon()->moveY(2);
                }

                break;

            case SDLK_r:
                
                if (mWorld.existsActivePolygon()) {
                    int rot{6};

                    if (event.key.keysym.mod & KMOD_SHIFT) {
                        rot = 354;
                    }

                    mWorld.getActivePolygon()->rotate(rot);
                }

                break;

            case SDLK_q:
                mWorld.quit();
                break;

            case SDLK_ESCAPE:
                mWorld.changeState(
                    World::StateEnum::Presentation);
                break;

            default:
                break;
            }
            break;
        case SDL_KEYUP:
            break;

        case SDL_QUIT:
            mWorld.quit();
            break;

        default:
            break;
        }

    }
}



void WorldStateMove::update() {

}

void WorldStateMove::onEnter() {
    //mWorld.PushCajita(Cajita{100, 100});

    std::vector<Point> vertices{
        Point{0,0}, Point{0, 100}, Point{100, 100}, Point{100,0}};

    uint64_t color {};
    Point pos{0,0};
    mWorld.pushPolygon(new Triangle{
            std::vector<Point> {
                Point{0,0}, Point{80, 120}, Point{210, 30}},
                color, pos});
    // mWorld.PushPolygon(new Polygon{vertices, color, pos});
                    
                
}

void WorldStateMove::onExit() {
    mWorld.popPolygon();
}
