#include "test.h"
#include "splash.h"
#include "menu.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static TextLayer *s_textlayer_1;
static BitmapLayer *s_bitmaplayer_2;
static GBitmap *s_res_ems_splash_white;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  s_res_ems_splash_white = gbitmap_create_with_resource(RESOURCE_ID_EMS_SPLASH_WHITE);
  
  s_bitmaplayer_2 = bitmap_layer_create(GRect(35, 25, 75, 75));
  bitmap_layer_set_bitmap(s_bitmaplayer_2, s_res_ems_splash_white);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_2);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(23, 115, 100, 30));
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_text(s_textlayer_1, "Welcome to EMS Trainer");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
//   text_layer_destroy(s_textlayer_1);
  bitmap_layer_destroy(s_bitmaplayer_2);
}
// END AUTO-GENERATED UI CODE
static void click_handler(ClickRecognizerRef recog, void *context){
//   ButtonId clicked = click_recognizer_get_button_id(recog);
  show_menu();
}

static void click_config_provider(void *context){
  window_single_click_subscribe(BUTTON_ID_SELECT, click_handler);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_test(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_set_click_config_provider(s_window, click_config_provider);
  window_stack_push(s_window, true);
}

void hide_test(void) {
  window_stack_remove(s_window, true);
}

void test_deinit(void){
  window_destroy(s_window);
}
