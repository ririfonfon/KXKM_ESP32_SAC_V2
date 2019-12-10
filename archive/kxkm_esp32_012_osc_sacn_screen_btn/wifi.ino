/////////////////////////////////////////Wifi settings/////////////////////////////////////
//const char ssid[] = "kxkm-wifi";
//const char password[] = "KOMPLEXKAPHARNAUM";
//const char ssid[] = "kxkm24lulu";
//const char password[] = "";
//const char ssid[] = "riri_new";
//const char password[] = "B2az41opbn6397";
const char* KNOWN_SSID[] = {"kxkm-wifi", "kxkm24lulu", "riri_new", "SSID3"};
const char* KNOWN_PASSWORD[] = {"KOMPLEXKAPHARNAUM", "", "B2az41opbn6397", "PassW3rd"};

const int   KNOWN_SSID_COUNT = sizeof(KNOWN_SSID) / sizeof(KNOWN_SSID[0]); // number of known networks


bool wifi_available = false;

IPAddress ip(2, 0, 0, BAR_HS_NUMBER + 100); // Static IP
IPAddress gateway(2, 0, 0, 1);
IPAddress subnet(255, 0, 0, 0);

void ConnectWifi() {
  int i, n;
  display.clear();
  display.setFont(Dialog_plain_18);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  // ----------------------------------------------------------------
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  // ----------------------------------------------------------------
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // ----------------------------------------------------------------
  // WiFi.scanNetworks will return the number of networks found
  // ----------------------------------------------------------------
#ifdef DEBUGwifi
  Serial.println("Setup done");
  Serial.println(F("scan start"));
  Serial.println(F("scan done"));
#endif
  display.drawString(0, 0, "Setup done");
  display.drawString(0, 22, "scan start");
  display.drawString(0, 44, "scan done");
  display.display();

  int nbVisibleNetworks = WiFi.scanNetworks();
  if (nbVisibleNetworks == 0) {
#ifdef DEBUGwifi
    Serial.println(F("no networks found. Reset to try again"));
#endif
    display.drawString(0, 44, "scan not done");
    display.display();
    while (true); // no need to go further, hang in there, will auto launch the Soft WDT reset
  }

  // ----------------------------------------------------------------
  // if you arrive here at least some networks are visible
  // ----------------------------------------------------------------
#ifdef DEBUGwifi
  Serial.print(nbVisibleNetworks);
  Serial.println(" network(s) found");
#endif
  display.clear();
  display.drawString(0, 0, String(nbVisibleNetworks));
  display.drawString(20, 0, " network(s)");
  display.drawString(0, 22, "");
  display.drawString(0, 44, "");
  display.display();
  delay(3000);
  // ----------------------------------------------------------------
  // check if we recognize one by comparing the visible networks
  // one by one with our list of known networks
  // ----------------------------------------------------------------
  for (i = 0; i < nbVisibleNetworks; ++i) {
#ifdef DEBUGwifi
    Serial.println(WiFi.SSID(i)); // Print current SSID
#endif
    display.drawString(0, 22, "Connect To");
    display.drawString(0, 44, String(WiFi.SSID(i)));
    display.display();
    delay(3000);
    for (n = 0; n < KNOWN_SSID_COUNT; n++) { // walk through the list of known SSID and check for a match
      if (strcmp(KNOWN_SSID[n], WiFi.SSID(i).c_str())) {
#ifdef DEBUGwifi
        Serial.print(F("\tNot matching "));
        Serial.println(KNOWN_SSID[n]);
#endif
      } else { // we got a match
        wifi_available = true;
        break; // n is the network index we found
      }
    } // end for each known wifi SSID
    if (wifi_available) break; // break from the "for each visible network" loop
  } // end for each visible network

  if (!wifi_available) {
#ifdef DEBUGwifi
    Serial.println(F("no Known network identified. Reset to try again"));
#endif
    display.clear();
    display.drawString(0, 0, "no Known network");
    display.drawString(0, 22, "identified.");
    display.drawString(0, 44, "Reset to try again");
    display.display();

    while (true); // no need to go further, hang in there, will auto launch the Soft WDT reset
  }

  // ----------------------------------------------------------------
  // if you arrive here you found 1 known SSID
  // ----------------------------------------------------------------
#ifdef DEBUGwifi
  Serial.print(F("\nConnecting to "));
  Serial.println(KNOWN_SSID[n]);
#endif

  // ----------------------------------------------------------------
  // We try to connect to the WiFi network we found
  // ----------------------------------------------------------------
  WiFi.begin(KNOWN_SSID[n], KNOWN_PASSWORD[n]);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef DEBUGwifi
    Serial.print(".");
#endif
  }

  // ----------------------------------------------------------------
  // SUCCESS, you are connected to the known WiFi network
  // ----------------------------------------------------------------
#ifdef DEBUGwifi
  Serial.println("");
  Serial.println(F("WiFi connected, your IP address is "));
  Serial.println(WiFi.localIP());
#endif
  IPAddress myIP = WiFi.localIP();
  String ipStr = String(myIP[0]) + "." + String(myIP[1]) + "." + String(myIP[2]) + "." + String(myIP[3]);
  display.clear();
  display.drawString(0, 0, String(KNOWN_SSID[n]));
  display.drawString(0, 22, "with IP:");
  display.drawString(0, 44, ipStr);
  display.display();
  delay (500);
}//ConnectWifi

void wifi_event(WiFiEvent_t event) {
  static byte retry = 0;
  static byte maxRetry = 15;

  switch (event) {
    case SYSTEM_EVENT_STA_DISCONNECTED:
      master = 0;
      rr = 0;
      gg = 0;
      bb = 0;
      ww = 0;
      mod = 0;
      pix_mod = 0;
      pix_start = 0;
      modulo = 0;
      str_ws = 0;
      pix_center = 0;
      srr = 0;
      sgg = 0;
      sbb = 0;
      sww = 0;
      color_mode = 0;
      mirror = 0;
      ledChannelOne = 0;
      ledChannelTwo = 0;
      break;
  }

#ifdef DEBUG
  switch (event) {
    case SYSTEM_EVENT_STA_CONNECTED:
      Serial.print("WiFi connected - ");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.print("Got IP - ");
      Serial.println(WiFi.localIP());
      break;
    case SYSTEM_EVENT_STA_LOST_IP:
      Serial.print("Lost IP..");
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.print("WiFi lost connection... ");
      break;
  }
#endif

  if (event == SYSTEM_EVENT_STA_DISCONNECTED) {
    wifi_available = false;
    retry += 1;

#ifdef DEBUG
    Serial.print(" reconnecting ");
    Serial.print(retry);
    Serial.print("/");
    Serial.println(maxRetry);
#endif

    if (retry < maxRetry) {
      WiFi.reconnect();
    } else if (retry >= maxRetry) {
      WiFi.mode(WIFI_OFF);
      retry = 0;
#ifdef DEBUG
      Serial.print(" max ");
#endif
    }

  }
  else if (event == SYSTEM_EVENT_STA_GOT_IP) {
    wifi_available = true;
    retry = 0;
  }
}// wifi_event

bool wifi_isok() {
  return wifi_available;
}//wifi_isok()
