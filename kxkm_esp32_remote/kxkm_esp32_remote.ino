/////////////////////////////////////////ID/////////////////////////////////////////
#define REMOTE 1
#define VERSION 1


/**************************************************************************/
/*!
    @file     DMX_node_riri
    @author   Claude Heintz
    @license  BSD (see LXDMXWiFi.h)
    @copyright 2017 by Claude Heintz All Rights Reserved

           https://github.com/claudeheintz/LXESP32DMX
*/
/**************************************************************************/
/////////////////////////////////////////Debug///////////////////////////////////////
#define DEBUG 1
#define DEBUGbtnp 1

/////////////////////////////////// variables////////////////////////////////////
int is;
uint8_t wifi_start;
uint8_t wifi_end;
int n;
uint8_t ligne = 0;
uint8_t menu = 0;
int mode_test = 1;

#include "EEPROM.h"
#define EEPROM_SIZE 64
int dmx_start;
int mode_start;
int wifichannel;
int hidden;
int hiddens;

//// BTN
uint8_t pr = 0;
uint8_t bt = 0;
uint8_t button = 0;
#define BT_T 100
int sensorValue = 0;
int som_Value = 0;
int Moy_sensor = 0;

#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"` v 3.2.7
#include "OLEDDisplayUi.h"// Include the UI lib

///////////////////////////////  SCREEN    //////////////////////////////
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"` v 3.2.7
#include "OLEDDisplayUi.h"// Include the UI lib
#include "font.h"// include specifique font
SSD1306  display(0x3c, 32, 27);
OLEDDisplayUi ui     ( &display );


uint8_t init_btn9 = 0;
uint8_t init_btn8 = 0;
uint8_t init_btn7 = 0;
uint8_t init_btn6 = 0;

int frameCount = 7;
int frameCountnow = 0;
int enter = 0;

#define bat_check 1000
unsigned long last_bat_check_time = 0 ;
#define SCREEN_TIMEOUT 90000
unsigned long last_screen_check_time = 0;
uint8_t screen = 1;
unsigned long now;

int mode_start_value = 0;

#include <LXESP32DMX.h>
#include <UID.h>
#include <TOD.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "LXDMXWiFi.h"
#include <LXWiFiArtNet.h>
#include <LXWiFiSACN.h>
#include "LXDMXWiFiConfig.h"
#include "freertos/task.h"

#define DIRECTION_PIN 4         // pin for output direction enable on MAX481 chip

char ssid[32];
char password[32];

/*
    Edit the LXDMXWiFiConfig.initConfig() function in LXDMXWiFiConfig.cpp to configure the WiFi connection and protocol options
*/

// dmx protocol interfaces for parsing packets (created in setup)
LXWiFiArtNet* artNetInterface;
LXWiFiSACN*   sACNInterface;

// EthernetUDP instances to let us send and receive UDP packets
WiFiUDP aUDP;
WiFiUDP sUDP;

// direction output from network/input to network
uint8_t dmx_direction = 0;

// Output mode: received packet contained dmx
int art_packet_result = 0;
int acn_packet_result = 0;

// Input mode:  received slots when inputting dmx to network
int got_dmx = 0;

UID lower(0, 0, 0, 0, 0, 0);
UID upper(0, 0, 0, 0, 0, 0);
UID mid(0, 0, 0, 0, 0, 0);
UID found(0, 0, 0, 0, 0, 0);

/************************************************************************

  Setup creates the WiFi connection.

  It also creates the network protocol object,
  either an instance of LXWiFiArtNet or LXWiFiSACN.

  if OUTPUT_FROM_NETWORK_MODE:
     Starts listening on the appropriate UDP port.

     And, it starts the ESP32DMX sending serial DMX via the UART1 TX pin.
     (see the LXESP32DMX library documentation for driver details)

   if INPUT_TO_NETWORK_MODE:
     Starts ESP32DMX listening for DMX ( received as serial on UART0 RX pin. )

*************************************************************************/

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  Serial.setDebugOutput(1); //use uart0 for debugging
#endif

  ///////////////////////////////////////////////// SCREEN  //////////////////////////////////////
  ui.init();// Initialising the UI will init the display too.
  display.flipScreenVertically();
  display.displayOn();
  display.setFont(Dialog_plain_20);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "HELLO");
  display.drawString(0, 30, "WORD");
  display.display();
  delay (2000);

  check_EEPROM ();

  pinMode(DIRECTION_PIN, OUTPUT);

  uint8_t bootStatus = DMXWiFiConfig.begin(1);//aparently need to read from persistent to be able to write to it
  uint8_t dhcpStatus = 0;                     //hence, read in begin and replace below if startup pin is low


  DMXWiFiConfig.initConfig();

  dmx_direction = DMXWiFiConfig.inputToNetworkMode();

  if ( DMXWiFiConfig.APMode() ) {            // WiFi startup
#ifdef DEBUG
    Serial.print("AP_MODE ");
    Serial.print(DMXWiFiConfig.SSID());
#endif

    WiFi.mode(WIFI_AP);
    WiFi.softAP(DMXWiFiConfig.SSID(), DMXWiFiConfig.password(), wifichannel, hiddens);

#ifdef DEBUG
    Serial.print(" created access point at ");
    Serial.print(DMXWiFiConfig.apIPAddress());
    Serial.print(" accessPoint SSID ");
    Serial.println(DMXWiFiConfig.SSID());
    Serial.print(", ");
#endif

    WiFi.softAPConfig(DMXWiFiConfig.apIPAddress(), DMXWiFiConfig.apGateway(), DMXWiFiConfig.apSubnet());

  } else {
#ifdef DEBUG
    Serial.print("wifi connecting to ");
    Serial.print(DMXWiFiConfig.SSID());
    Serial.print("... ");
#endif

    WiFi.mode(WIFI_STA);
    strcpy(ssid, DMXWiFiConfig.SSID());
    strcpy(password, DMXWiFiConfig.password());
    WiFi.begin((const char*)ssid, (const char*)password);

    // static IP otherwise uses DHCP
    if ( DMXWiFiConfig.staticIPAddress() ) {
#ifdef DEBUG
      Serial.print("static IP");
#endif

      WiFi.config(DMXWiFiConfig.stationIPAddress(), DMXWiFiConfig.stationGateway(), DMXWiFiConfig.stationSubnet());

    } else {
      dhcpStatus = 1;
    }

    while (WiFi.status() != WL_CONNECTED)  {
      delay(100);

    }
#ifdef DEBUG
    Serial.print("wifi started ");
    Serial.println(WiFi.localIP());
#endif
  }
  display.clear();
  display.drawString(0, 0, "WIFI OK");
  display.display();
  delay(1000);

  //------------------- Initialize serialDMX  -------------------

  if ( dmx_direction == OUTPUT_FROM_NETWORK_MODE ) {                // DMX Driver startup based on direction flag
#ifdef DEBUG
    Serial.println("starting DMX");
#endif
  } else {
#ifdef DEBUG
    Serial.println("starting DMX input");
#endif
    ESP32DMX.setDirectionPin(DIRECTION_PIN);
    ESP32DMX.setDataReceivedCallback(&gotDMXCallback);
#ifdef HELTEC
    ESP32DMX.startInput(18);// U2_RX Gpio 18
#endif
#ifdef OLED
    ESP32DMX.startInput();// U2_RX Gpio 16 default
#endif
  }

  //------------------- Initialize network<->DMX interfaces -------------------

  sACNInterface = new LXWiFiSACN();
  sACNInterface->setUniverse(DMXWiFiConfig.sACNUniverse());

  artNetInterface = new LXWiFiArtNet(WiFi.localIP(), WiFi.subnetMask());
  artNetInterface->setUniverse(DMXWiFiConfig.artnetPortAddress());	//setUniverse for LXArtNet class sets complete Port-Address
  artNetInterface->setArtAddressReceivedCallback(&artAddressReceived);
  artNetInterface->setArtIpProgReceivedCallback(&artIpProgReceived);
  char* nn = DMXWiFiConfig.nodeName();
  if ( nn[0] != 0 ) {
    strcpy(artNetInterface->longName(), nn);
  }
  artNetInterface->setStatus2Flag(ARTNET_STATUS2_SACN_CAPABLE, 1);
  artNetInterface->setStatus2Flag(ARTNET_STATUS2_DHCP_CAPABLE, 1);
  if ( dhcpStatus ) {
    artNetInterface->setStatus2Flag(ARTNET_STATUS2_DHCP_USED, 1);
  }
  if ( bootStatus ) {
    artNetInterface->setStatus1Flag(ARTNET_STATUS1_FACTORY_BOOT, 1);
  }
#ifdef DEBUG
  Serial.print("interfaces created ");
#endif

  // if output from network, start wUDP listening for packets
  if ( dmx_direction == OUTPUT_FROM_NETWORK_MODE ) {
    if ( DMXWiFiConfig.multicastMode() ) {
      if ( DMXWiFiConfig.APMode() ) {
        sUDP.beginMulticast(DMXWiFiConfig.multicastAddress(), sACNInterface->dmxPort());  //WiFi.softAPIP(),
      } else {
        sUDP.beginMulticast(DMXWiFiConfig.multicastAddress(), sACNInterface->dmxPort());  //WiFi.localIP(),
      }
    } else {
      sUDP.begin(sACNInterface->dmxPort());
    }

    aUDP.begin(artNetInterface->dmxPort());
    artNetInterface->send_art_poll_reply(&aUDP);
#ifdef DEBUG
    Serial.print("udp started listening,");
#endif
  }
#ifdef DEBUG
  Serial.println(" setup complete.");
#endif

  // increase the priority of this task (main.cpp sets it at 1);
  vTaskPrioritySet(xTaskGetCurrentTaskHandle(), 2);
#ifdef DEBUG
  Serial.print("number of tasks is ");
  Serial.println(uxTaskGetNumberOfTasks());
#endif

  info();

} //setup



/************************************************************************

  Main loop

  if OUTPUT_FROM_NETWORK_MODE:
    checks for and reads packets from WiFi UDP socket
    connection.  readDMXPacket() returns true when a DMX packet is received.

    If dmx is received on either interface, copy from both (HTP) to dmx output.

    If the packet is an CONFIG_PACKET_IDENT packet, the config struct is modified and stored in EEPROM

  if INPUT_TO_NETWORK_MODE:
    if serial dmx has been received, sends an sACN or Art-Net packet containing the dmx data.
    Note:  does not listen for incoming packets for remote configuration in this mode.

*************************************************************************/

void loop() {
  now = millis();
//  if (screen == 1) {
//    if (now - last_screen_check_time > SCREEN_TIMEOUT) {
//#ifdef DEBUG
//      Serial.print("shutdown screen... ");
//#endif
//      shutdown_screen();
//    }
//  }//if (screen==1)

  if ( dmx_direction == OUTPUT_FROM_NETWORK_MODE ) {

    art_packet_result = artNetInterface->readDMXPacket(&aUDP);
    if ( art_packet_result == RESULT_NONE ) {
      checkConfigReceived(artNetInterface, &aUDP);
    }
    vTaskDelay(1);

    acn_packet_result = sACNInterface->readDMXPacket(&sUDP);
    if ( acn_packet_result == RESULT_NONE ) {
      checkConfigReceived(sACNInterface, &sUDP);
    }
    vTaskDelay(1);

    if ( (art_packet_result == RESULT_DMX_RECEIVED) || (acn_packet_result == RESULT_DMX_RECEIVED) ) {
      copyDMXToOutput();
      Serial.println ("art_packet ");
    } else {
      Serial.println ("art_packet else ");
    }

  } else {    //direction is input to network

    if ( DMXWiFiConfig.sACNMode() ) {
      checkInput(sACNInterface, &sUDP, DMXWiFiConfig.multicastMode());
    } else {
      checkInput(artNetInterface, &aUDP, 0);
    }

  }

  vTaskDelay(1);
  check_btn();

}// loop()
