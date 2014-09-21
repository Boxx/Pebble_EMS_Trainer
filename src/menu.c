#include <pebble.h>
#include "menu.h"
  
// Menu constants
#define NO_MENU_SECTIONS 1
#define NO_MENU_ITEMS 2

// UI Declarations
static Window *window;
static SimpleMenuLayer *menu_layer;
static SimpleMenuSection menu_sections[NO_MENU_SECTIONS];
static SimpleMenuItem menu_items[NO_MENU_ITEMS];


// @TODO
// Add callbacks to select actions
static void select_quiz_callback(int index, void *ctx){
  
}
static void select_cpr_callback(int index, void *ctx){
  
}

void window_load(Window *window){
  
  menu_items[0] = (SimpleMenuItem) {
    .title = "Quiz",
    .callback = select_quiz_callback,
  };
  menu_items[1] = (SimpleMenuItem){
    .title = "CPR",
    .callback = select_cpr_callback,
  };
  
  menu_sections[0] = (SimpleMenuSection) {
    .num_items = NO_MENU_ITEMS,
    .items = menu_items,
  };
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  menu_layer = simple_menu_layer_create(bounds, window, menu_sections, 2, NULL);
  
  layer_add_child(window_layer, simple_menu_layer_get_layer(menu_layer));
  
  
}

void window_unload(Window *window){
  simple_menu_layer_destroy(menu_layer);
}

void menu_init(void){
  window = window_create();
//   window_set_click_config_provider(menu_window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers){
    .load = window_load,
    .unload = window_unload
  });
  window_stack_push(window, true);
}

void menu_deinit(void){
  window_destroy(window);
}