/////////////////////////////////////////ID/////////////////////////////////////////
#define BAR_HS_NUMBER 1
#define VERSION 21
//#define NOEUX 0
#define UNIVERSE 1                      // DMX Universe to listen for

////////////////////////////////////////TaskHandle_t //////////////////////////////////
//TaskHandle_t Map1;
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

/////////////////////////////////////////Adresse/////////////////////////////////////
#define adr (1+(BAR_HS_NUMBER-1)*16)
//#define adr 1
#define NUM_LEDS_PER_STRIP 300
int N_L_P_S = NUM_LEDS_PER_STRIP;

/////////////////////////////////////////Debug///////////////////////////////////////
#define DEBUG 1
//#define DEBUG_dmx 1
//#define DEBUG_dmxframe 1
//#define DEBUG_STR 1
#define DEBUGosc 1

/////////////////////////////////////////lib/////////////////////////////////////////
#include "KXKM_STM32_energy_API.h"
#include <WiFi.h>
#include <ESPAsyncE131.h>//https://github.com/forkineye/ESPAsyncE131
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

///////////////////////////////Lib esp32_digital_led_lib//////////////////////////////
#include "esp32_digital_led_lib.h"
#define min(m,n) ((m)<(n)?(m):(n))
#define NUM_STRIPS 2
//int PINS[NUM_STRIPS] = {22, 21};// V1
int PINS[NUM_STRIPS] = {23, 22};// V2
const int numberOfChannels = NUM_STRIPS * NUM_LEDS_PER_STRIP * 4;
const int numberOfLed =  NUM_LEDS_PER_STRIP ;
strand_t STRANDS[NUM_STRIPS];
strand_t * strands [] = { &STRANDS[0], &STRANDS[1]};
bool randArray[numberOfLed];

///////////////////////////////////dmx variables////////////////////////////////////
//// Setup PWM State(s)
int ledChannelOne = 0;
int ledChannelTwo = 0;

float pi_n_1_r[NUM_LEDS_PER_STRIP];
float pi_n_1_g[NUM_LEDS_PER_STRIP];
float pi_n_1_b[NUM_LEDS_PER_STRIP];
float pi_n_1_w[NUM_LEDS_PER_STRIP];

float pi_1_r[NUM_LEDS_PER_STRIP];
float pi_1_g[NUM_LEDS_PER_STRIP];
float pi_1_b[NUM_LEDS_PER_STRIP];
float pi_1_w[NUM_LEDS_PER_STRIP];

float pi_1_sr[NUM_LEDS_PER_STRIP];
float pi_1_sg[NUM_LEDS_PER_STRIP];
float pi_1_sb[NUM_LEDS_PER_STRIP];
float pi_1_sw[NUM_LEDS_PER_STRIP];

int color_mode;
int mirror;

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

///////////////////////////////////// SACN settings /////////////////////////////////////
#define UNIVERSE_COUNT 1               // Total number of Universes to listen for, starting at UNIVERSE
// ESPAsyncE131 instance with UNIVERSE_COUNT buffer slots
ESPAsyncE131 e131(UNIVERSE_COUNT);

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup() {

  Serial.begin(115200);

  ///////////////////////////////////////////////// BAR_HS_NUMBER ID //////////////////////////////////////
#ifdef BAR_HS_NUMBER
  eeprom_setID((byte)BAR_HS_NUMBER);
#endif

  // NAME
  myID = eeprom_getID();
  String myName("BAR_HS");
  sprintf(nodeName, "BAR_HS %02i %i", myID, VERSION);
#ifdef DEBUG
  Serial.print("Starting ");
  Serial.println(nodeName);
#endif

  ///////////////////////////////////////////////// LEDS //////////////////////////////////////
  leds_init();
  ledSetup();

  ///////////////////////////////////////////////// WIFI //////////////////////////////////////
  ConnectWifi();

  ///////////////////////////////////////////////// OTA //////////////////////////////////////
  ota_setup();

  ///////////////////////////////////////////////// sACN //////////////////////////////////////
  // Choose one to begin listening for E1.31 data
  //  if (e131.begin(E131_UNICAST))                               // Listen via Unicast
  if (e131.begin(E131_MULTICAST, UNIVERSE, UNIVERSE_COUNT))   // Listen via Multicast
    Serial.println(F("Listening for data..."));
  else
    Serial.println(F("*** e131.begin failed ***"));

  ///////////////////////////////////////////////// INIT //////////////////////////////////////
  initTest();

  ///////////////////////////////////////////////// CORE //////////////////////////////////////
  //  create a task that will be executed in the Map1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(Map1code, "Map1code", 4096, NULL, 1, NULL, 1);   // core 1 = loop
  xTaskCreatePinnedToCore(effTask, "effTask", 4096, NULL, 1, NULL, 0);    // core 0 = wifi

  ///////////////////////////////////////////////// osc //////////////////////////////////////
    oscC_start();

}//setup

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop() {

  if (!e131.isEmpty()) {
    onDmxFrame();
    eff_modulo();
  }// if sacn

  if ((millis() - lastRefresh) > REFRESH) {
    if (!wifi_isok())  ledBlack();//passe led noir
    lastRefresh = millis();
  }
  // MILLIS overflow protection
  if (millis() < lastRefresh) {
    lastRefresh = millis();
  }

//  // BATTERIE 
//  if ((millis() - lastRefresh_bat) > REFRESH_BAT) {
//    get_percentage();
//    lastRefresh_bat = millis();
//  }
//  // MILLIS overflow protection
//  if (millis() < lastRefresh_bat) {
//    lastRefresh_bat = millis();
//  }

  // OTA
  ota_loop();
}//loop
