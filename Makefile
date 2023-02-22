SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
CFLAGS = -Wextra -Werror -Wall  -pedantic -fanalyzer -I./include $(SDL_CFLAGS)
CC=gcc

BUILD_DIR=./build
OBJ_DIR=./obj
SRC_DIR=./src

HEADERS=$(wildcard include/*.h)
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=obj/%.o)

MALLOCTIMES := 9

SRCS=$(wildcard src/*.c)

yarara: main.c $(OBJS)
	$(CC) -o $(BUILD_DIR)/$@ $^ $(CFLAGS) $(SDL_LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) 
	$(CC) -c -o $@ $< $(CFLAGS) 

tmalloc0: main.c $(OBJS)
	$(CC) -DMALLOC_TIMES$(MALLOCTIMES) -o $(BUILD_DIR)/$@ $^ $(CFLAGS) $(SDL_LDFLAGS)


TAGS:
	universal-ctags -R -e .


clean:
	find $(BUILD_DIR) -type f -delete
	find $(OBJ_DIR) -type f -delete
