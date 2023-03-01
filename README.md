This is the snake game, similar to nibbles.

Run the game:
============

Install [SDL2](https://github.com/libsdl-org/SDL)

In debian, ubuntu, etc
```
sudo apt install libsdl2-2.0-0 libsdl2-dev
Also, libudev-dev to play in tty (adding user to input group).

```


Build:

make yarara

Run:

./build/yarara

Play:

Press `s' in the title screen to start. Move with the arrows, `q' to quit.


You can test malloc usage with

```
MKFLG="-DYRR_MALLOC -DMALLOC_TIMES=N" make
```

where `N` is the maximum numbers of `malloc/realloc` calls allowed to the program
(default is 16 if only `-DYRR_MALLOC` is passed).


