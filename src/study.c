
#include <pebble.h>
#include "study.h"
#include "menu.h"
#include "util.h"


static Window *s_window;
// static TextLayer *s_textlayer;
// static ScrollLayer *s_scroll_layer;
static TextLayer *s_card_no;
static TextLayer *s_card_content;
static int pos = 0;


// Func declarations
void show_cards(void);
static void window_load(struct Window *param_window);
static void window_unload(struct Window *param_window);
void cards_deinit(void);
static void click_config_provider(void *context);
static void down_click_handler(ClickRecognizerRef recog, void *context);
static void up_click_handler(ClickRecognizerRef recog, void *context);

// struct StudyUI {
    
// } ui;

#define NO_NOTE_CARDS 9
typedef struct NoteCard {
  char * term;
  char * definition;
  char * number;
  int state;
} NoteCard;
static NoteCard note_cards[NO_NOTE_CARDS];

void show_cards(void) {
	s_window = window_create();
	window_set_window_handlers(s_window, (WindowHandlers){
		.load = window_load,
		.unload = window_unload
	});
  window_set_click_config_provider(s_window, click_config_provider);
	window_stack_push(s_window, true);
}



static void window_load(struct Window *param_window) {


  window_set_fullscreen(param_window, false);
  s_card_no = text_layer_create(GRect(24, 2, 100, 20));
  s_card_content = text_layer_create(GRect(4, 54, 137, 86));
  text_layer_set_text_alignment(s_card_no, GTextAlignmentCenter);
  text_layer_set_text_alignment(s_card_content, GTextAlignmentCenter);

  layer_add_child(window_get_root_layer(param_window), (Layer *)s_card_no);
  layer_add_child(window_get_root_layer(param_window), (Layer *)s_card_content);

  note_cards[0] = (NoteCard) {
    .number = "Card 1",
    .term = "Who sets the curriculum for all EMS courses?",
    .definition = "DOT",
    .state = 0
  };
  note_cards[1] = (NoteCard) {
    .number = "Card 2",
    .term = "Provides national standards for EMT testing and certification",
    .definition = "National Registery",
    .state = 0
  };
  note_cards[2] = (NoteCard) {
    .number = "Card 3",
    .term = "Types of stress include:",
    .definition = "Cumulative, post-traumatic stress reaction, eustruss, acute stress, and chronic stress",
    .state = 0
  };
  note_cards[3] = (NoteCard) {
    .number = "Card 4",
    .term = "Control and prevention of contamination include?",
    .definition = "Hand washing, gloves, eye protection, gowns, masks, mask, respirators, barrier devices, and immunizations.",
    .state = 0
  };
  note_cards[4] = (NoteCard) {
    .number = "Card 5",
    .term = "Duty to Act is?",
    .definition = "An obligation to provide care.",
    .state = 0
  };
  note_cards[5] = (NoteCard) {
    .number = "Card 6",
    .term = "The scope of practice is?",
    .definition = "The scope of practice is? Description of what assessment and treatment skills and EMT may legally perform.",
    .state = 0
  };
  note_cards[6] = (NoteCard) {
    .number = "Card 7",
    .term = "Implied consent is?",
    .definition = "Consent in which a patient is unable to give consent and is provided treatment under the implication they would want treament.",
    .state = 0
  };
  note_cards[7] = (NoteCard) {
    .number = "Card 8",
    .term = "Informed consent is?",
    .definition = "Permission for treatment given by a patient after the potential risks, benefits, and alternatives to treatment have been explained.",
    .state = 0
  };
  note_cards[8] = (NoteCard) {
    .number = "Card 9",
    .term = "Ethics",
    .definition = "The discipline dealing with what is good and bad.",
    .state = 0
  };
  //         char pos;
  //         pos = card_no+1;
  text_layer_set_text(s_card_no, note_cards[pos].number);
  text_layer_set_text(s_card_content, note_cards[pos].term);
}


static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
}
static void down_click_handler(ClickRecognizerRef recog, void *context) {
  if (pos == NO_NOTE_CARDS-1 && note_cards[pos].state == 1) {
    note_cards[pos].state = 0;
    pos = 0;
    text_layer_set_text(s_card_no, note_cards[pos].number);
    text_layer_set_text(s_card_content, note_cards[pos].term);
  }else {
    if (note_cards[pos].state == 0) {
      light_enable_interaction();
      text_layer_set_text(s_card_content, note_cards[pos].definition);
      note_cards[pos].state = 1;
    }else if (note_cards[pos].state == 1){
        pos++;
        text_layer_set_text(s_card_no, note_cards[pos].number);
        text_layer_set_text(s_card_content, note_cards[pos].term);
    }
  }
  
  
}
static void up_click_handler(ClickRecognizerRef recog, void *context) {
  if (pos == 0 && note_cards[pos].state == 0) {
    pos = NO_NOTE_CARDS-1;
    text_layer_set_text(s_card_no, note_cards[pos].number);
    text_layer_set_text(s_card_content, note_cards[pos].term);
  }else {
    if (note_cards[pos].state == 0) {
      pos--;
      text_layer_set_text(s_card_no, note_cards[pos].number);
      text_layer_set_text(s_card_content, note_cards[pos].definition);
      note_cards[pos].state = 1;
    }else if (note_cards[pos].state == 1){
      text_layer_set_text(s_card_content, note_cards[pos].term);
      note_cards[pos].state = 0;
    }
  }
}

static void window_unload(struct Window *param_window) {
	window_destroy(param_window);
	text_layer_destroy(s_card_no);
	text_layer_destroy(s_card_content);
}

void cards_deinit(void) {
  window_unload(s_window);
}