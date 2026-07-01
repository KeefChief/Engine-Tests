#pragma once

typedef enum Key{
    KEY_UNKNOWN,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_JUMP,
    KEY_SHOOT,
    KEY_COUNT,
}Key;

typedef struct KeyState{
    int is_down; 
    int is_up;
    int is_pressed;
}KeyState;

void UpdateInput();
void SetKeyDown(Key key);
void SetKeyUp(Key key);
int GetKeyDown(Key key);
int GetKeyUp(Key key);
int GetKey(Key key);
