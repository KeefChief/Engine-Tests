#include "input.h"
#include <stdio.h>

static KeyState keys[KEY_COUNT];

void UpdateInput(){
    for(int i = 0; i < KEY_COUNT; i++){
	keys[i].is_down = 0;
	keys[i].is_up = 0;
    }
}

void SetKeyDown(Key key){
    printf("Key down: %d\n", key);
    keys[key].is_down = 1;
    keys[key].is_pressed = 1;
}

void SetKeyUp(Key key){
    printf("Key down: %d\n", key);
    keys[key].is_pressed = 0;
    keys[key].is_up = 1;
}

int GetKeyDown(Key key){
    return keys[key].is_down;
}

int GetKeyUp(Key key){
    return keys[key].is_up;
}

int GetKey(Key key){
    return keys[key].is_pressed;
}
