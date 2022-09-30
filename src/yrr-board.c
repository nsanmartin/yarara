#include <yrr-board.h>
#include <yrr-util.h>

void yrrFreeBoard(YrrBoard* board) {
    yrrFreeVec(board->players);
    free(board);
}

YrrBoard* yrrNewBoard(YrrPoint sz) {

    YrrPoint half = (YrrPoint) { .x = sz.x/2, .y = sz.y/2 };
    YrrPoint first = get_pseudo_rand((YrrPoint) { .x=0, .y=0 }, half);
    YrrVecPoints* firsts = yrrNewVecPoints(2);
    yrrVecPushBack(firsts, first);
    first.x = (first.x + sz.x/2) % sz.x;
    first.y = (first.y + sz.y/2) % sz.y;
    yrrVecPushBack(firsts, first);

    YrrVecPlayers* players = yrrNewVecPlayers(firsts);
    if (!players) {
        return NULL;
    }

    yrrFreeVec(firsts);

    YrrBoard* rv = malloc(sizeof(YrrBoard));
    if(!rv) {
        return NULL;
    }
    
    *rv = (YrrBoard) {
        .width = sz.x,
        .height = sz.y,
        .players = players,
        .level = { .food = get_pseudo_rand(half, sz)}
    };

    return rv;
}

void yrrResetBoard(YrrBoard* board) {
    YrrPoint half = (YrrPoint) { .x = board->width/2, .y = board->height/2 };
    YrrPoint first = get_pseudo_rand((YrrPoint) { .x=0, .y=0 }, half);
    yrrResetYarara(board->players->beg->yarara, first);
    first.x = (first.x + half.x) % board->width;
    first.y = (first.y + half.y) % board->height;
    yrrResetYarara(board->players->beg[1].yarara, first);
    //,todo: apply to all
    //YrrVecPlayers* ps = board->players;
    //for (YrrPlayer* it = ps->beg; it < it->end; ++it) {
    //    yrrResetYarara(it, first);
    //}
}
