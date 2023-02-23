SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
CFLAGS = -Wextra -Werror -Wall  -pedantic -I./include $(SDL_CFLAGS)

BUILD_DIR=./build
OBJ_DIR=./obj
SRC_DIR=./src

HEADERS=$(wildcard include/*.h)
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=obj/%.o)

SRCS=$(wildcard src/*.c)

$(BUILD_DIR)/yarara: main.c $(OBJS)
	$(CC) $(MKFLG) -o $@ $^ $(CFLAGS) $(SDL_LDFLAGS)

analyze-gcc: main.c $(OBJS)
	$(CC) $(MKFLG) -o $(BUILD_DIR)/$@ $^ -fanalyzer $(CFLAGS) $(SDL_LDFLAGS)

analyze-clang: main.c $(OBJS)
	$(CC) $(MKFLG) -o $(BUILD_DIR)/$@ $^ --analyze $(CFLAGS) $(SDL_LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) 
	$(CC) $(MKFLG) -c -o $@ $< $(CFLAGS) 


TAGS: $(HEADERS) $(SRCS)
	universal-ctags -R -e .


clean:
	find $(BUILD_DIR) -type f -delete
	find $(OBJ_DIR) -type f -delete
