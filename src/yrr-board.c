#include <yrr-mem.h>

#include <yrr-board.h>
#include <yrr-util.h>

void yrrFreeBoard(YrrBoard* board) {
    yrrFreeVecPlayers(board->players);
    free(board);
}

YrrBoard* yrrNewBoard(YrrPoint sz) {

    YrrPoint half = (YrrPoint) { .x = sz.x/2, .y = sz.y/2 };
    YrrPoint first = get_pseudo_rand((YrrPoint) { .x=0, .y=0 }, half);
    YrrVecPoints* firsts = yrrNewVecPoints(2);
    if (firsts == NULL) {
        return NULL;
    }
    yrrVecPointsPushBack(firsts, first);
    first.x = (first.x + sz.x/2) % sz.x;
    first.y = (first.y + sz.y/2) % sz.y;
    yrrVecPointsPushBack(firsts, first);

    YrrVecPlayers* players = yrrNewVecPlayers(firsts);
    yrrFreeVec(firsts);
    if (!players) {
        return NULL;
    }

    YrrBoard* rv = malloc(sizeof(YrrBoard));
    if(!rv) {
        yrrFreeVecPlayers(players);
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

int yrrResetBoard(YrrBoard* board) {
    YrrPoint half = (YrrPoint) { .x = board->width/2, .y = board->height/2 };
    YrrPoint first_compu = get_pseudo_rand((YrrPoint) { .x=0, .y=0 }, half);
    YrrPoint first_human = (YrrPoint) {
        .x = (first_compu.x + half.x) % board->width,
        .y = (first_compu.y + half.y) % board->height
    };
    int error = yrrResetPlayer(board->players->beg, first_compu);
    if (!error) {
        error = yrrResetPlayer(board->players->beg + 1, first_human);
    }
    return error;
}
