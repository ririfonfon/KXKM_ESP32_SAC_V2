/////////////////////////////////////////ID/////////////////////////////////////////
// #define NODEID 42 // id card

#define ESP_SK_PW 1

#define VERSION 35

#define UNI 0                     // DMX Universe to listen for

////////////////////////////////////////TaskHandle_t //////////////////////////////////
//TaskHandle_t Map1;
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

/////////////////////////////////////////Adresse/////////////////////////////////////
#define adr (1+(ESP_SK_PW-1)*19)
#define NUM_LEDS_PER_STRIP_MAX 120
int NUM_LEDS_PER_STRIP = NUM_LEDS_PER_STRIP_MAX;
int N_L_P_S = NUM_LEDS_PER_STRIP;

/////////////////////////////////////////Debug///////////////////////////////////////
//#define DEBUG 1
//#define DEBUG_dmx 1
//#define DEBUG_dmxframe 1
//#define DEBUG_STR 1
//#define DEBUGosc 1
//#define DEBUGwifi 1

/////////////////////////////////////////lib/////////////////////////////////////////
#include "K32.h"
#include <ArtnetWifi.h>//https://github.com/rstephan/ArtnetWifi
unsigned long lastRefresh = 0;
#define REFRESH 10
unsigned long lastRefresh_bat = 0;
#define REFRESH_BAT 100


#if defined(ARDUINO) && ARDUINO >= 100
// No extras
#elif defined(ARDUINO) // pre-1.0
// No extras
#elif defined(ESP_PLATFORM)
#include "arduinoish.hpp"
#endif

#define HBSIZE 32
char nodeName[HBSIZE];
byte myID;

K32* engine;

///////////////////////////////Lib esp32_digital_led_lib//////////////////////////////

#define min(m,n) ((m)<(n)?(m):(n))
#define NUM_STRIPS 2
//int PINS[NUM_STRIPS] = {22, 21};// V1
int PINS[NUM_STRIPS] = {23, 22};// V2
const int numberOfChannels = NUM_STRIPS * NUM_LEDS_PER_STRIP_MAX * 4;
//const int NUM_LEDS_PER_STRIP =  NUM_LEDS_PER_STRIP_MAX ;
strand_t STRANDS[NUM_STRIPS];
strand_t * strands [] = { &STRANDS[0], &STRANDS[1]};

//// Setup PWM State(s)
int ledChannelOne = 0;
int ledChannelTwo = 0;

///////////////////////////////////dmx variables////////////////////////////////////

float zo_pi_n_1_r[NUM_LEDS_PER_STRIP_MAX];
float zo_pi_n_1_g[NUM_LEDS_PER_STRIP_MAX];
float zo_pi_n_1_b[NUM_LEDS_PER_STRIP_MAX];
float zo_pi_n_1_w[NUM_LEDS_PER_STRIP_MAX];

float pi_n_1_r[NUM_LEDS_PER_STRIP_MAX];
float pi_n_1_g[NUM_LEDS_PER_STRIP_MAX];
float pi_n_1_b[NUM_LEDS_PER_STRIP_MAX];
float pi_n_1_w[NUM_LEDS_PER_STRIP_MAX];

float pi_1_r[NUM_LEDS_PER_STRIP_MAX];
float pi_1_g[NUM_LEDS_PER_STRIP_MAX];
float pi_1_b[NUM_LEDS_PER_STRIP_MAX];
float pi_1_w[NUM_LEDS_PER_STRIP_MAX];

float pi_1_sr[NUM_LEDS_PER_STRIP_MAX];
float pi_1_sg[NUM_LEDS_PER_STRIP_MAX];
float pi_1_sb[NUM_LEDS_PER_STRIP_MAX];
float pi_1_sw[NUM_LEDS_PER_STRIP_MAX];

int color_mode;
int mirror;
int zoom;
int offset;
int di;

unsigned long now;
int effet_etat = 0;
int last_time_effet = 0;
int type_effet = 0;
int modulo = 0;
unsigned int str_ws = 0;
unsigned int l_str;
int type_modulo = 0;
int str = 0;
int str_l = 0;
int pix_pos;
int pix_pos_v;
int pix_start;
int pix_center;
int pix_end;
int master;
float rrr;
float ggg;
float bbb;
float www;
float rr;
float gg;
float bb;
float ww;
float r;
float g;
float b;
float w;
float srr;
float sgg;
float sbb;
float sww;
int mod;
int pix_mod;
unsigned long t_now_effet = 0;
uint8_t strob_count = 0;
uint8_t strob_count_l = 0;
unsigned long str_ws_last = 0;
unsigned long t_last_l = 0;
#define STROB_FRACTION 5
#define STROB_ON 1
#define STROB_ON_MS 15
#define STROB_FRACTION_L 5
#define STROB_ON_L 1
#define STROB_ON_MS_L 15
int l_s_count = 1;
int pix_start_v;
int ref_pix_pos;
float pix_coef;
float pix_coefi;
float pix_coef_fond;
float pix_coefi_fond;
int M_g;
int M_g_ref;
int M_g1;
int M_g1_ref;
int M_g2;
int M_g2_ref;
int M_g3;
int M_g3_ref;
int M_g4;
int S_seuil;
int old_S_seuil = 0;
int S_count;
int a;
float str_blind_ws = 1;
float str_blind_l = 1;

///////////////////////////////////// batterie variable /////////////////////////////////////

int percentage;
int led_niv = 10;
int etat_r = 0;

///////////////////////////////////// Artnet settings /////////////////////////////////////
ArtnetWifi artnet;
////const int startUniverse = 0; // CHANGE FOR YOUR SETUP most software this is 1, some software send out artnet first universe as 0.
const int startUniverse = UNI; // CHANGE FOR UNIVERSE.

// Check if we got all universes
const int maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
bool universesReceived[maxUniverses];
bool sendFrame = 1;
int previousDataLength = 0;

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup() {

  Serial.begin(115200);

  //////////////////////////////////////// K32_lib ////////////////////////////////////
  engine = new K32({
    .stm32    = true,     // stm32 event listening and battery monitoring
    .leds     = false,     // dual ws2812
    .audio    = false,     // audio engine with PCM51xx sound card
    .sampler  = false,     // media indexing to midi bank/note-xxx
    .wifi     = {
      .ssid = "kxkm24lulu",             // ssid (NULL to disable)
      .password = NULL,             // password (NULL if not secured)
      .ip = ("2.0.0." + String(ESP_SK_PW + 100)).c_str()                 // static ip (NULL to use DHCP)
    },
    .osc  = {
      .port_in  = 1818,             // osc port input (0 = disable)  // 1818
      .port_out = 1819,             // osc port output (0 = disable) // 1819
      .beatInterval     = 0,        // heartbeat interval milliseconds (0 = disable)
      .beaconInterval   = 3000      // full beacon interval milliseconds (0 = disable)
    },
    .mqtt = {
      .broker = "2.0.0.1",      //"2.0.0.1"
      .beatInterval = 0            // heartbeat interval milliseconds (0 = disable)
    }
  });

  // Settings SET
#ifdef NODEID
  engine->settings->set("id", NODEID);
  engine->settings->set("model", 2);   // 0: proto -- 1: big -- 2: small
  engine->settings->set("channel", 15);
#endif

#ifdef DEBUG
  Serial.print("Starting ");
  Serial.println(nodeName);
#endif

  ///////////////////////////////////////////////// LEDS //////////////////////////////////////
  leds_init();
  ledSetup();


  /////////////////////////////////////////////// ARTNET //////////////////////////////////////
  artnet.begin();
  artnet.setArtDmxCallback(onDmxFrame);

  ///////////////////////////////////////////////// INIT //////////////////////////////////////
  initTest();

  ///////////////////////////////////////////////// CORE //////////////////////////////////////
  //  create a task that will be executed in the Map1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(Map1code, "Map1code", 4096, NULL, 1, NULL, 1);   // core 1 = loop
  xTaskCreatePinnedToCore(effTask, "effTask", 4096, NULL, 1, NULL, 0);    // core 0 = wifi

  ///////////////////////////////////////////////// osc //////////////////////////////////////

}//setup

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop() {

  if (engine->wifi->isConnected()) {
    artnet.read();
    eff_modulo();
  }// if wifi

  if ((millis() - lastRefresh) > REFRESH) {
    if (!engine->wifi->isConnected()) {
      ledBlack();//passe led noir
    }
    lastRefresh = millis();
  }
  // MILLIS overflow protection
  if (millis() < lastRefresh) {
    lastRefresh = millis();
  }

  //    // BATTERIE
  //    if ((millis() - lastRefresh_bat) > REFRESH_BAT) {
  //      get_percentage();
  //      lastRefresh_bat = millis();
  //    }
  //    // MILLIS overflow protection
  //    if (millis() < lastRefresh_bat) {
  //      lastRefresh_bat = millis();
  //    }

}//loop
