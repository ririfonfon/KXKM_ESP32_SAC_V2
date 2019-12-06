/////////////////////////////////////////ID/////////////////////////////////////////
//#define K32_SET_NODEID        66 // board unique id    (necessary first time only)
// #define K32_SET_HWREVISION    2  // board HW revision  (necessary first time only)

#define LULU_ID   17
#define LULU_TYPE "SK_PWM"
#define LULU_UNI  0                     // DMX Universe to listen for

#define LULU_VER  37
#define LULU_PATCHSIZE 19

/////////////////////////////////////////Adresse/////////////////////////////////////
#define adr (1+(LULU_ID-1)*(LULU_PATCHSIZE))
#define NUM_LEDS_PER_STRIP_MAX 120
int NUM_LEDS_PER_STRIP = NUM_LEDS_PER_STRIP_MAX;
int N_L_P_S = NUM_LEDS_PER_STRIP;

/////////////////////////////////////////Debug///////////////////////////////////////
#define DEBUG 1
//#define DEBUG_dmx 1
//#define DEBUG_dmxframe 1
//#define DEBUG_STR 1
//#define DEBUG_calibre_btn 1
// #define DEBUG_btn 1


/////////////////////////////////////////lib/////////////////////////////////////////
#include "K32.h"
#include <ArtnetWifi.h>           //https://github.com/rstephan/ArtnetWifi
unsigned long lastRefresh = 0;
#define REFRESH 10
unsigned long lastRefresh_bat = 0;
#define REFRESH_BAT 100

String nodeName;
K32* k32;

///////////////////////////////Lib esp32_digital_led_lib//////////////////////////////

#define min(m,n) ((m)<(n)?(m):(n))
#define NUM_STRIPS 2
int PINS[NUM_STRIPS];
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
//int l_s_count = 1;
int pix_start_v;
int ref_pix_pos;
float pix_coef;
float pix_coefi;
float pix_coef_fond;
float pix_coefi_fond;
int S_seuil;
int old_S_seuil = 0;
int S_count;
int a;
float str_blind_ws = 1;

///////////////////////////////////// batterie variable /////////////////////////////////////

int percentage;
int led_niv = 25;
int etat_r = 0;

///////////////////////////////////// botton variable /////////////////////////////////////

bool lock = false;

///////////////////////////////////// Wifi variable /////////////////////////////////////

bool lostConnection = true;

///////////////////////////////////// Artnet settings /////////////////////////////////////
ArtnetWifi artnet;
////const int startUniverse = 0; // CHANGE FOR YOUR SETUP most software this is 1, some software send out artnet first universe as 0.
const int startUniverse = LULU_UNI; // CHANGE FOR UNIVERSE.

// Check if we got all universes
const int maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
bool universesReceived[maxUniverses];
bool sendFrame = 1;
int previousDataLength = 0;


///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup() {

  Serial.begin(115200);

  //////////////////////////////////////// K32_lib ////////////////////////////////////
  k32 = new K32();

  nodeName += String(LULU_TYPE) + "-" + String(LULU_ID) + "-v" + String(LULU_VER);
  PINS[0] = k32->system->ledpin(0);
  PINS[1] = k32->system->ledpin(1);

  //////////////////////////////////////// K32 modules ////////////////////////////////////
  k32->init_stm32();

  // WIFI
  k32->init_wifi( nodeName );
  k32->wifi->staticIP("2.0.0." + String(k32->system->id() + 100), "2.0.0.1", "255.0.0.0");
  k32->wifi->connect("kxkm24lulu", NULL);

  // Start OSC
  k32->init_osc({
    .port_in  = 1818,             // osc port input (0 = disable)  // 1818
    .port_out = 1819,             // osc port output (0 = disable) // 1819
    .beatInterval     = 0,        // heartbeat interval milliseconds (0 = disable)
    .beaconInterval   = 3000      // full beacon interval milliseconds (0 = disable)
  });// OSC

  bat_custom();
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
  if (k32->wifi->isConnected()) {
    if (!lock) artnet.read();
    lostConnection = false;
  }// if wifi

  if ((millis() - lastRefresh) > REFRESH) {
    if (!k32->wifi->isConnected() && !lostConnection) {
      if (!lock) ledBlack();//passe led noir
      lostConnection = true;
    }
    lastRefresh = millis();
  }

  // BATTERIE
  if ((millis() - lastRefresh_bat) > REFRESH_BAT) {
    get_percentage();
    lastRefresh_bat = millis();
  }

  // MILLIS overflow protection
  if (millis() < lastRefresh) lastRefresh = millis();
  if (millis() < lastRefresh_bat) lastRefresh_bat = millis();

  check_button();// 4 buttons
  eff_modulo();
}//loop
