#include <button.h>
#include <gpio_def.h>
#include <pico/stdlib.h>

void initButtons() {
    gpio_set_dir(GPIO_BUTTON_UP, false);
    gpio_set_dir(GPIO_BUTTON_DOWN, false);
    gpio_set_dir(GPIO_BUTTON_PUSH, false);

    gpio_pull_up(GPIO_BUTTON_UP);
    gpio_pull_up(GPIO_BUTTON_DOWN);
    gpio_pull_up(GPIO_BUTTON_PUSH);
}

bool getButtonState(Button button) {
    if (button == BUTTON_UP) {
        return !gpio_get(GPIO_BUTTON_UP);
    }
    if (button == BUTTON_DOWN) {
        return !gpio_get(GPIO_BUTTON_DOWN);
    }
    if (button == BUTTON_PUSH) {
        return !gpio_get(GPIO_BUTTON_PUSH);
    }
    return false;
}