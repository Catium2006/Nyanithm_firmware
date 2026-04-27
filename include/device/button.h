#ifndef __BUTTON_H__
#define __BUTTON_H__

enum Button{
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_PUSH
};

void initButtons();

bool getButtonState(Button button);

#endif