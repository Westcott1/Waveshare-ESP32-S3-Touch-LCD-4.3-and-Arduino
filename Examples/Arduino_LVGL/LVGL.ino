#include <lvgl.h>
#include <bb_captouch.h>

BBCapTouch bbct;

#define TOUCH_SDA 8
#define TOUCH_SCL 9
#define TOUCH_INT 4
#define TOUCH_RST 0

const char* szNames[] = { "Unknown", "FT6x36", "GT911", "CST820" };

// These MUST be static otherwise the ESP32 will crash at lv_disp_drv_register(&disp_drv);
static lv_disp_draw_buf_t draw_buf;
static lv_color_t* disp_draw_buf;
static lv_disp_drv_t disp_drv;

// These are all needed to avoid compiler errors
void DisplayFlush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p);
void TouchRead(lv_indev_drv_t* indev_driver, lv_indev_data_t* data);
void LvSetBGcolor(lv_obj_t* obj, int col);

void LVGLinit() {
  Serial.println("LVGL init...");

  int drawBufSize = TFT_HOR_RES * 40;  // (TFT_HOR_RES * TFT_VER_RES) / 10;
  disp_draw_buf = (lv_color_t*)heap_caps_malloc(sizeof(lv_color_t) * drawBufSize, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

  if (!disp_draw_buf) {
    Serial.println("LVGL disp_draw_buf allocate failed!");
  } else {
    lv_init();
    delay(100);
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, drawBufSize);

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_HOR_RES;
    disp_drv.ver_res = TFT_VER_RES;
    disp_drv.flush_cb = DisplayFlush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = TouchRead;
    lv_indev_drv_register(&indev_drv);

    // Change the active screen's background color
    LvSetBGcolor(lv_scr_act(), 0xffffaa);
    lv_obj_set_style_text_font(lv_scr_act(), &lv_font_montserrat_32, 0);

    lv_obj_t* Marea = lv_obj_create(lv_scr_act());
    lv_obj_set_size(Marea, 350, 80);
    lv_obj_align(Marea, LV_ALIGN_CENTER, 0, 0);
    LvSetBGcolor(Marea, 0xaaccaa);

    lv_obj_t* Mlabel = lv_label_create(Marea);
    lv_label_set_text(Mlabel, "Hello LVGL (V" GFX_STR(LVGL_VERSION_MAJOR) "." GFX_STR(LVGL_VERSION_MINOR) "." GFX_STR(LVGL_VERSION_PATCH) ")");
    lv_obj_align(Mlabel, LV_ALIGN_CENTER, 0, 0);

    Serial.println("LVGL OK");
  }
}

void LvSetBGcolor(lv_obj_t* obj, int col) {
  lv_obj_set_style_bg_color(obj, lv_color_hex(col), LV_PART_MAIN);
}

/* Display flushing */
void DisplayFlush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p) {
//  Serial.println("Flush");
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  GFXdraw16bitRGBBitmap(area->x1, area->y1, (uint16_t*)&color_p->full, w, h);
  lv_disp_flush_ready(disp);
}

void LvTimerHandler() {
  lv_timer_handler(); /* let the GUI do its work */
}

void TouchInit() {
  Serial.println("Touch init...");
  bbct.init(TOUCH_SDA, TOUCH_SCL, TOUCH_RST, TOUCH_INT);
  int iType = bbct.sensorType();
  Serial.printf("Touch sensor type = %s\n", szNames[iType]);
}

void TouchRead(lv_indev_drv_t* indev_driver, lv_indev_data_t* data) {
  TOUCHINFO ti;

  if (bbct.getSamples(&ti)) {  // if LVGL touch event happened
    Serial.printf("Touch x: %d y: %d size: %d\n", ti.x[0], ti.y[0], ti.area[0]);

    data->state = LV_INDEV_STATE_PR;
    data->point.x = ti.x[0];
    data->point.y = ti.y[0];
  } else
    data->state = LV_INDEV_STATE_REL;
}
