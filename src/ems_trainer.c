#include <pebble.h>
#include "menu.h"
#include "splash.h"
#include "test.h"


static void init(void) {
//   splash_init();
//   menu_init();
  show_test();
}

static void deinit(void) {
  hide_splash();
  menu_deinit();
  hide_test();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
