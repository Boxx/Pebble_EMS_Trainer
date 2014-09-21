#include "splash.h"
#include <pebble.h>

// UI
static Window *s_window;
static GBitmap *s_res_ems_splash_white;
static GFont s_res_gothic_14;
static BitmapLayer *s_bitmaplayer_2;
static TextLayer *s_textlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_ems_splash_white = gbitmap_create_with_resource(RESOURCE_ID_EMS_SPLASH_WHITE);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // s_bitmaplayer_2
  s_bitmaplayer_2 = bitmap_layer_create(GRect(35, 25, 75, 75));
  bitmap_layer_set_bitmap(s_bitmaplayer_2, s_res_ems_splash_white);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_2);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(23, 115, 100, 30));
  
  text_layer_set_text(s_textlayer_1, "Press any button");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_2);
  text_layer_destroy(s_textlayer_1);
  gbitmap_destroy(s_res_ems_splash_white);
}


static void handle_window_unload(Window* window) {
  destroy_ui();
}

void splash_init(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void splash_deinit(void) {
  window_stack_remove(s_window, true);
}
