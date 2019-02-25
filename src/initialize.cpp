#include "main.h"

int auton = 0;
bool flag_mode_state = false;



const std::string auton_names[AUTON_MAX] = {"auton1", "auton2", "auton3"};

//needed but unused beyond inputManager
lv_indev_state_t temp_state;
int temp_x, temp_y;

lv_obj_t *flag_button_label;
lv_obj_t *flag_button;
lv_obj_t *auton_display_label;

static lv_style_t custom_style, custom_style_pressed, custom_style_textbox, custom_style_background, custom_style_flag_red, custom_style_flag_blue;


bool inputManager(lv_indev_data_t *temp_data) {
    temp_data -> state = temp_state;
    temp_data -> point.x = temp_x;
    temp_data -> point.y = temp_y;
    return false;
}

lv_res_t buttonAutonSubtract(lv_obj_t *button) {
    if(pros::competition::is_disabled()) {
        auton--;

        if(auton < 0) {
            auton = AUTON_MAX - 1;
        }
    }

    return LV_RES_OK;
}

lv_res_t buttonAutonAdd(lv_obj_t *button) {
    if(pros::competition::is_disabled()) {
        auton++;

        if(auton >= AUTON_MAX) {
            auton = 0;
        }
    }

    return LV_RES_OK;
}

lv_res_t buttonFlagModeSwitch(lv_obj_t *button) {
    if(flag_mode_state) {
        flag_mode_state = false;
        lv_label_set_text(flag_button_label, "BLUE");
        lv_btn_set_style(flag_button, LV_BTN_STYLE_REL, &custom_style_flag_blue);
    } else {
        flag_mode_state = true;
        lv_label_set_text(flag_button_label, "RED");
        lv_btn_set_style(flag_button, LV_BTN_STYLE_REL, &custom_style_flag_red);
    }
    
    return LV_RES_OK;
}


void initialize() {
    //initialized the touch device as a pointer, and points to the state function
    lv_indev_drv_t device_driver;
    lv_indev_drv_init(&device_driver);
    device_driver.type = LV_INDEV_TYPE_POINTER;
    device_driver.read = inputManager;
    lv_indev_drv_register(&device_driver);

    //create styles
    lv_style_copy(&custom_style_background, &lv_style_scr);
    custom_style_background.body.main_color = LV_COLOR_BLACK;
    custom_style_background.body.grad_color = LV_COLOR_BLACK;

    lv_style_copy(&custom_style, &lv_style_pretty);
    custom_style.body.main_color = LV_COLOR_BLACK;
    custom_style.body.grad_color = LV_COLOR_BLACK;
    custom_style.body.radius = 0;
    custom_style.body.border.color = LV_COLOR_WHITE;
    custom_style.text.color = LV_COLOR_WHITE;

    lv_style_copy(&custom_style_pressed, &custom_style);
    custom_style_pressed.body.main_color = LV_COLOR_GRAY;
    custom_style_pressed.body.grad_color = LV_COLOR_GRAY;

    lv_style_copy(&custom_style_textbox, &lv_style_plain_color);
    custom_style_textbox.body.border.color = LV_COLOR_WHITE;
    custom_style_textbox.body.border.width = 2;
    custom_style_textbox.text.color = LV_COLOR_BLACK;

    lv_style_copy(&custom_style_flag_red, &custom_style);
    custom_style_flag_red.body.main_color = LV_COLOR_RED;
    custom_style_flag_red.body.grad_color = LV_COLOR_RED;

    lv_style_copy(&custom_style_flag_blue, &custom_style);
    custom_style_flag_blue.body.main_color = LV_COLOR_BLUE;
    custom_style_flag_blue.body.grad_color = LV_COLOR_BLUE;

    //creates a screen and loads it
    lv_obj_t *screen = lv_obj_create(NULL,NULL);
    lv_scr_load(screen);
    lv_obj_set_style(screen, &custom_style_background);

    //create line below top
    lv_obj_t *top_line = lv_obj_create(screen, NULL);
    lv_obj_set_size(top_line, lv_obj_get_width(lv_scr_act()), 2);
    lv_obj_set_pos(top_line, 0, 0);
    lv_obj_set_style(top_line, &lv_style_scr);

    //creates left and right buttons
    lv_obj_t *left_button = lv_btn_create(screen, NULL);
    lv_obj_set_size(left_button, lv_obj_get_width(lv_scr_act()) / 4, LV_DPI / 2);
    lv_obj_set_pos(left_button, 20, 150);
    lv_btn_set_action(left_button, LV_BTN_ACTION_CLICK, buttonAutonSubtract);
    lv_obj_t *left_button_label = lv_label_create(left_button, NULL);
    lv_label_set_text(left_button_label, "<");
    lv_btn_set_style(left_button, LV_BTN_STYLE_REL, &custom_style);
    lv_btn_set_style(left_button, LV_BTN_STYLE_PR, &custom_style_pressed);
    
    lv_obj_t *right_button = lv_btn_create(screen, NULL);
    lv_obj_set_size(right_button, lv_obj_get_width(lv_scr_act()) / 4, LV_DPI / 2);
    lv_obj_set_pos(right_button, 335, 150);
    lv_btn_set_action(right_button, LV_BTN_ACTION_CLICK, buttonAutonAdd);
    lv_obj_t *right_button_label = lv_label_create(right_button, NULL);
    lv_label_set_text(right_button_label, ">");
    lv_btn_set_style(right_button, LV_BTN_STYLE_REL, &custom_style);
    lv_btn_set_style(right_button, LV_BTN_STYLE_PR, &custom_style_pressed);

    //create flag switch button
    flag_button = lv_btn_create(screen, NULL);
    lv_obj_set_size(flag_button, lv_obj_get_width(lv_scr_act()) / 5, LV_DPI / 3);
    lv_obj_set_pos(flag_button, 20, 20);
    lv_btn_set_action(flag_button, LV_BTN_ACTION_CLICK, buttonFlagModeSwitch);
    lv_btn_set_style(flag_button, LV_BTN_STYLE_REL, &custom_style_flag_red);
    lv_btn_set_style(flag_button, LV_BTN_STYLE_PR, &custom_style_pressed);
    
    flag_button_label = lv_label_create(flag_button, NULL);
    lv_label_set_text(flag_button_label, "RED");

    //create middle label
    lv_obj_t *auton_display = lv_obj_create(screen, NULL);
    lv_obj_set_size(auton_display, lv_obj_get_width(lv_scr_act()) - 40, LV_DPI / 2);
    lv_obj_set_pos(auton_display, 20, LV_DPI / 2 + 10);
    lv_obj_set_style(auton_display, &custom_style_textbox);

    auton_display_label = lv_label_create(auton_display, NULL);
    lv_obj_align(auton_display_label, auton_display, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_set_y(auton_display_label, 20);
}


void disabled() {
    char *label_buffer = "test";

    while(pros::competition::is_disabled()) {
        printf("%d", auton);
        lv_label_set_text(auton_display_label, auton_names[auton].c_str());

        pros::delay(20);
    }
}


void competition_initialize() {
    char *label_buffer = "test";

    while(pros::competition::is_disabled()) {
        printf("%d", auton);
        lv_label_set_text(auton_display_label, auton_names[auton].c_str());

        pros::delay(20);
    }
}
