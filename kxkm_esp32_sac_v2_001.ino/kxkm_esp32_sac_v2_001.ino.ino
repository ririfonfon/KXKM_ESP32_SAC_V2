/////////////////////////////////////////ID/////////////////////////////////////

#define SAC_VP_NUMBER 1
#define VERSION 1

/////////////////////////////////////////Adresse/////////////////////////////////////

#define adr 1
#define NUM_LEDS_PER_STRIP 29


/////////////////////////////////////////Debug///////////////////////////////////////
//#define DEBUG 1
//#define DEBUG_dmx 1
//#define DEBUG_STR 1

/////////////////////////////////////////lib/////////////////////////////////////////
#include "KXKM_STM32_energy_API.h"
#include <WiFi.h>
#include <WiFiUdp.h>
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

///////////////////////////////Lib esp32_digital_led_lib//////////////////////////////
#include "esp32_digital_led_lib.h"
#define min(m,n) ((m)<(n)?(m):(n))
#define NUM_STRIPS 2
int PINS[NUM_STRIPS] = {21, 22};
const int numberOfChannels = NUM_STRIPS * NUM_LEDS_PER_STRIP * 3;
const int numberOfLed = NUM_LEDS_PER_STRIP ;
strand_t STRANDS[NUM_STRIPS];
strand_t * strands [] = { &STRANDS[0], &STRANDS[1]};
bool randArray[numberOfLed];

///////////////////////////////////dmx variables////////////////////////////////////
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
int pix_start;
int pix_center;
int pix_end;
int master;
float rrr;
float ggg;
float bbb;
float rr;
float gg;
float bb;
float r;
float g;
float b;
int smaster;
float srr;
float sgg;
float sbb;
float sr;
float sg;
float sb;
int mod;
int pix_mod;
unsigned long t_now_effet = 0;
uint8_t strob_count = 0;
uint8_t strob_count_l = 0;
unsigned long str_ws_last = 0;
unsigned long t_last_l = 0;
#define STROB_FRACTION 10
#define STROB_ON 1
#define STROB_ON_MS 30
#define STROB_FRACTION_L 10
#define STROB_ON_L 1
#define STROB_ON_MS_L 30
int l_s_count = 1;
int pix_start_v;
int ref_pix_pos;
float pix_coef;
float pix_coefi;
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

int   percentage;
int led_niv = 10;
int etat_r = 0;

///////////////////////////////////// Artnet settings /////////////////////////////////////
ArtnetWifi artnet;
const int startUniverse = 0; // CHANGE FOR YOUR SETUP most software this is 1, some software send out artnet first universe as 0.

// Check if we got all universes
const int maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
bool universesReceived[maxUniverses];
bool sendFrame = 1;
int previousDataLength = 0;

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup() {
  // serial stm_32
  Serial.begin(115200, SERIAL_8N1);
  Serial.setTimeout(10);
  //init_seuil_bat
  sendSerialCommand(KXKM_STM32_Energy::SET_BATTERY_VOLTAGE_LOW, 21700);
  sendSerialCommand(KXKM_STM32_Energy::SET_BATTERY_VOLTAGE_1, 23100);
  sendSerialCommand(KXKM_STM32_Energy::SET_BATTERY_VOLTAGE_2, 23500);
  sendSerialCommand(KXKM_STM32_Energy::SET_BATTERY_VOLTAGE_3, 24500);
  sendSerialCommand(KXKM_STM32_Energy::SET_BATTERY_VOLTAGE_6, 29400);
  
#ifdef DEBUG
  Serial.begin(115200);
#endif
  // NODE ID
#ifdef SAC_VP_NUMBER
  eeprom_setID((byte)SAC_VP_NUMBER);
#endif

  // NAME
  myID = eeprom_getID();
  String myName("SAC_VP");
  sprintf(nodeName, "SAC_VP %02i %i", myID, VERSION);
#ifdef DEBUG
  Serial.print("Starting ");
  Serial.println(nodeName);
#endif

  //  pwm_init();
  leds_init();
  ConnectWifi();
  // OTA
  ota_setup();
  artnet.begin();
  artnet.setArtDmxCallback(onDmxFrame);
  initTest();
}//setup

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop() {
  if (wifi_isok()) artnet.read();
  eff_modulo();
  effet();
  if ((millis() - lastRefresh) > REFRESH) {
    if (!wifi_isok())  ledBlack();//passe led noir
    lastRefresh = millis();
  }
  // MILLIS overflow protection
  if (millis() < lastRefresh) {
    lastRefresh = millis();
  }
  // bat
    if ((millis() - lastRefresh_bat) > REFRESH_BAT) {
    get_percentage();
    lastRefresh_bat = millis();
  }
  // MILLIS overflow protection
  if (millis() < lastRefresh_bat) {
    lastRefresh_bat = millis();
  }
  // OTA
  ota_loop();
}//loop
