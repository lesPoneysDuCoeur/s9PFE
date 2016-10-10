#include <pebble.h>

static Window* window;
static TextLayer *bt_layer, *accel_layer, *deep_layer, *checkDeep_layer;
 
static void window_load(Window *window)
{
  //Setup Accel Layer
  accel_layer = text_layer_create(GRect(5, 35, 144, 30));
  text_layer_set_font(accel_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(accel_layer, "Accel tap: N/A");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(accel_layer));
  
  //Setup Deep Layer
  deep_layer = text_layer_create(GRect(5, 65, 144, 30));
  text_layer_set_font(deep_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(deep_layer, "Deep value : N/A");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(deep_layer));
  
  //Setup checkDeep Layer
  checkDeep_layer = text_layer_create(GRect(5, 95, 144, 30));
  text_layer_set_font(checkDeep_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(checkDeep_layer, "Deep check");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(checkDeep_layer));
  
  //Setup BT Layer
  bt_layer = text_layer_create(GRect(5, 5, 144, 30));
  text_layer_set_font(bt_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  if(bluetooth_connection_service_peek() == true)
  {
    text_layer_set_text(bt_layer, "BLUETOOTH CONNECTED");
  }
  else
  {
    text_layer_set_text(bt_layer, "NO BLUETOOTH");
  }
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(bt_layer));
}
 
static void window_unload(Window *window)
{
  text_layer_destroy(bt_layer);
}

static void bt_handler(bool connected)
{
  if(connected == true)
  {
    text_layer_set_text(bt_layer, "BLUETOOTH CONNECTED");
  }
  else
  {
    text_layer_set_text(bt_layer, "NO BLUETOOTH");
  }
}

static void accel_tap_handler(AccelAxisType axis, int32_t direction)
{
  switch(axis)
  {
  case ACCEL_AXIS_X:
    if(direction > 0)
    {
      text_layer_set_text(accel_layer, "Accel tap: X (+)");
    }
    else
    {
      text_layer_set_text(accel_layer, "Accel tap: X (-)");
    }
    break;
  case ACCEL_AXIS_Y:
    if(direction > 0)
    {
      text_layer_set_text(accel_layer, "Accel tap: Y (+)");
    }
    else
    {
      text_layer_set_text(accel_layer, "Accel tap: Y (-)");
    }
    break;
  case ACCEL_AXIS_Z:
    if(direction > 0)
    {
      text_layer_set_text(accel_layer, "Accel tap: Z (+)");
    }
    else
    {
      text_layer_set_text(accel_layer, "Accel tap: Z (-)");
    }
    break;
  }
}

int toMillimeter(AccelData *data){
 return data[0].z/2;
}

static void accel_raw_handler(AccelData *data, uint32_t num_samples)
{
  static char bufferStringPosition[] = "XYZ: 9999 / 9999 / 9999";
  snprintf(bufferStringPosition, sizeof("XYZ: 9999 / 9999 / 9999\n"), "XYZ: %d / %d / %d\n", data[0].x, data[0].y, data[0].z);
  static char bufferStringDeep[] = "Profondeur : NULL\n";
  static char bufferStringDeepOK[] = "*** MESSAGE ***\n";
  int hauteur = toMillimeter(data);
  if(hauteur < 50){
    snprintf(bufferStringDeepOK, sizeof("*** MESSAGE ***\n"), "*** PLUS ***\n");
  }
  else if(hauteur > 60){
    snprintf(bufferStringDeepOK, sizeof("*** MESSAGE ***\n"), "*** MOINS ***\n");
  }
  else{
    snprintf(bufferStringDeepOK, sizeof("*** MESSAGE ***\n"), "*** OUI ***\n");
  }
  snprintf(bufferStringDeep, sizeof("Profondeur : NULL\n"), "Profondeur : %d\n", hauteur);
  text_layer_set_text(accel_layer, bufferStringPosition);
  text_layer_set_text(deep_layer, bufferStringDeep);
  text_layer_set_text(checkDeep_layer, bufferStringDeepOK);

}
 
static void init()
{
 
  window = window_create();
  WindowHandlers handlers = {
    .load = window_load,
    .unload = window_unload
  };
  window_set_window_handlers(window, (WindowHandlers) handlers);
  window_stack_push(window, true);
  bluetooth_connection_service_subscribe(bt_handler);
  accel_data_service_subscribe(1, accel_raw_handler);
}
 
static void deinit()
{
  window_destroy(window);
}

int main(void)
{
  init();
  app_event_loop();
  deinit();
}