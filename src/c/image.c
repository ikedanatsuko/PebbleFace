#include <pebble.h>

Window *window;

TextLayer *text_layer;
#define TEXT_LEN (32)
char text[TEXT_LEN + 1];

int mode = 1; //画像をアニメーションさせるための変数
int min = 0; //今何分か

BitmapLayer *bitmap_layer_back;
BitmapLayer *bitmap_layer_l;
BitmapLayer *bitmap_layer_r;
GBitmap *bitmap_l;
GBitmap *bitmap_r;

// TickTimerService ハンドラ（1秒ごとに呼ばれる）
void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  
  // 表示する文字を作成
  strftime(text, TEXT_LEN, "%m/%d %H", tick_time);
  
  // 表示する文字をtext_layerに設定
  text_layer_set_text(text_layer, text);
  
  // 時間取得
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  // min に今何分かを格納
  min = t->tm_min;
  
  // リソースから画像を生成 
  //int tens = min / 10;
  int tens = 0;
  if(tens == 0) {
    bitmap_l = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_01);
    /*if(mode == 1) {
      bitmap_l = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_0_1);
    }
    if(mode == -1) {
      bitmap_l = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_0_2);
    }*/
  }
  if(tens == 1) {
    bitmap_l = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_1);
  }
  if(tens == 2) {
    bitmap_l = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_2);
  }
  if(tens == 3) {
    bitmap_l = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_3);
  }
  if(tens == 4) {
    bitmap_l = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_4);
  }
  if(tens == 5) {
    bitmap_l = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_5);
  }
  if(tens == 6) {
    bitmap_l = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_6);
  }
  //mode *= -1;
  // bitmap_layer に画像を設定
  bitmap_layer_set_bitmap(bitmap_layer_l, bitmap_l);
  
  // リソースから画像を生成
  int num = min % 10;
  if(num == 0) {
    bitmap_r = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_01);
  }
  if(num == 1) {
    bitmap_r = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_1);
  }
  if(num == 2) {
    bitmap_r = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_2);
  }
  if(num == 3) {
    bitmap_r = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_3);
  }
  if(num == 4) {
    bitmap_r = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_4);
  }
  if(num == 5) {
    bitmap_r = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_5);
  }
  if(num == 6) {
    bitmap_r = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_6);
  }
  if(num == 7) {
    bitmap_r = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_7);
  }
  if(num == 8) {
    bitmap_r = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_8);
  }
  if(num == 9) {
    bitmap_r = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_9);
  }
  // bitmap_layer に画像を設定
  bitmap_layer_set_bitmap(bitmap_layer_r, bitmap_r);
}

// 初期化
void handle_init(void) {
  // window を作成
  window = window_create();
  Layer *root_layer = window_get_root_layer(window);
  
  // bitmap_layer_back
  {    
    // bitmap_layer_back を作成
    bitmap_layer_back = bitmap_layer_create(layer_get_bounds(root_layer));
    
    // bitmap_layer_back の背景色を黒に指定
    bitmap_layer_set_background_color(bitmap_layer_back, GColorBlack);
    
    // bitmap_layer_back を root_layer に重ねる
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bitmap_layer_back));
  }
  
  // bitmap_layer_left
  {    
    // bitmap_layer_l を作成
    //bitmap_layer_l = bitmap_layer_create(layer_get_bounds(root_layer));
    bitmap_layer_l = bitmap_layer_create(GRect(0, 38, 72, 130));
    
    // bitmap_layer_l の背景色を指定
    bitmap_layer_set_background_color(bitmap_layer_l, GColorBlack);
    
    // bitmap_layer を root_layer に重ねる
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bitmap_layer_l));
  }
  
  // bitmap_layer_right
  {    
    // bitmap_layer を作成
    bitmap_layer_r = bitmap_layer_create(GRect(72, 38, 72, 130));
    
    // bitmap_layer の背景色を指定
    bitmap_layer_set_background_color(bitmap_layer_r, GColorBlack);
    
    // bitmap_layer を root_layer に重ねる
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bitmap_layer_r));
  }
  
  // text_layer
  {
    // text_layer を作成
    text_layer = text_layer_create(layer_get_bounds(root_layer));
    
    // text_layer のフォントを GOTHIC ボールド 28px に設定
    text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
    
    // text_layer をセンタリング
    text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
    
    // text_layer の文字色を 白 に設定
    text_layer_set_text_color(text_layer, GColorIslamicGreen);
    
    // text_layer の背景色を透明に設定
    text_layer_set_background_color(text_layer, GColorClear);
    
    // textx_layer を root_layer に重ねる
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
  }
  
  // window をウィンドウ・スタックに重ねる
  window_stack_push(window, true);
  
  // TickTimerService を使用して1秒ごとにハンドラが呼ばれるように設定
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  //tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  
  // ログを表示
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

// 終了関数
void handle_deinit(void) {
  // text_layer を破棄
  text_layer_destroy(text_layer);
  
  // bitmap_layer を破棄
  bitmap_layer_destroy(bitmap_layer_back);
  bitmap_layer_destroy(bitmap_layer_l);
  bitmap_layer_destroy(bitmap_layer_r);
  
  // 画像を破棄
  gbitmap_destroy(bitmap_l);
  gbitmap_destroy(bitmap_r);
  
  // window を破棄
  window_destroy(window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}