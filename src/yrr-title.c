#include <yrr-title.h>


YrrPoint YrrLetterBigY[4] = {
    { .x = 0, .y = 0 },
    { .x = 2, .y = 0 },
    { .x = 1, .y = 1 },
    { .x = 1, .y = 2 }
};

YrrPoint YrrLetterA[4] = {
    { .x = 0, .y = 0 },
    { .x = 1, .y = 1 },
    { .x = 0, .y = 2 },
    { .x = 1, .y = 2 }
};

YrrPoint YrrLetterR[3] = {
    { .x = 1, .y = 0 },
    { .x = 0, .y = 1 },
    { .x = 0, .y = 2 },
};

YrrLetter YrrTitleLetters[] = {
    { .data = YrrLetterBigY,  .size = 4},
    { .data = YrrLetterA, .size = 4},
    { .data = YrrLetterR, .size = 3},
    { .data = YrrLetterA, .size = 4},
    { .data = YrrLetterR, .size = 3},
    { .data = YrrLetterA, .size = 4}
};

YrrTitle YrrGameTitle = {
   .data = YrrTitleLetters,
   .size = 6,
   .offset = {0} 

};

YrrTitle* yrrGetTitle(void) {
   return &YrrGameTitle;
}
