void wifiscan () {
  DisplayClear16 ();
  display.drawString(20, 0, "Wifi Scan");
  display.display();
}//wifiscan

void wifiscanenter () {
  //  display.invertDisplay();
  DisplayClear16 ();
  display.drawString(20, 0, "Wifi Scan Start");
  display.display();
  WiFi.disconnect();
  delay(100);
  scan_wifi();
}//wifiscanenter

void scan_wifi() {
  bt = 0;
  ligne = 0;
  DisplayClear16 ();
  display.drawString(20, 0, "Scan Start");
  display.display();
#ifdef DEBUG
  Serial.println("Scan Start");
#endif
  n = WiFi.scanNetworks();
  wifi_start = 0;
  wifi_end = 5;
  DisplayClear16 ();
  display.drawString(20, 0, "Scan Done");
  display.display();
#ifdef DEBUG
  Serial.println("Scan Done");
#endif
  if (n == 0) {
    DisplayClear16 ();
    display.drawString(20, 0, "No Networks Found");
    display.display();
    delay(2000);
    wifi_list();
#ifdef DEBUG
    Serial.println("No Networks Found");
#endif
  } else {
    wifi_start -= 5;
    wifi_end -= 5;
    ligne = 0;
    wifi_list();
  }
}//scan_wifi

void wifi() {
  display.drawString(0, ligne, String(is + 1));
  display.drawString(10, ligne, String(WiFi.channel(is)));
  display.drawString(20, ligne, String(WiFi.SSID(is)));
  display.drawString(110, ligne, String(WiFi.RSSI(is)));
#ifdef DEBUG
  Serial.print(is + 1);
  Serial.print("-");
  Serial.print(WiFi.channel(is));
  Serial.print("-");
  Serial.print(WiFi.SSID(is));
  Serial.print("-");
  Serial.println(WiFi.RSSI(is));
#endif
}//wifi

void wifi_list() {
  wifi_base();
  //  if (n >= wifi_end) {
  wifi_list_next ();
//check_btn();
  while (menu == 1) {
    check_button();

    if (button == 1) {
      WiFi.softAP(DMXWiFiConfig.SSID(), DMXWiFiConfig.password(), wifichannel, hiddens);
#ifdef DEBUG
      Serial.print(" created access point at ");
      Serial.print(DMXWiFiConfig.apIPAddress());
      Serial.print(" accessPoint SSID ");
      Serial.println(DMXWiFiConfig.SSID());
      Serial.print(", ");
#endif
      WiFi.softAPConfig(DMXWiFiConfig.apIPAddress(), DMXWiFiConfig.apGateway(), DMXWiFiConfig.apSubnet());
      screen = 1;
      last_screen_check_time = millis();
      menu = 0;
      info();
      button = 0;
    }
    if (button == 2) {
      wifi_list_back ();
      button = 0;
    }
    if (button == 3) {
      wifi_list_next ();
      button = 0;
    }
    if (button == 4) {
      button = 0;
    }
  }//menu == 1
}//tftprint_wifilist

void wifi_list_next () {
  wifi_base();
  wifi_start += 5;
  wifi_end += 5;
  if (ligne >= 50) ligne = 0;
#ifdef DEBUG
  Serial.print(" ligne  ");
  Serial.print(ligne);
  Serial.print("wifi_start ");
  Serial.println(wifi_start);
  Serial.print("wifi_end ");
  Serial.println(wifi_end);
#endif
  for ( is = wifi_start; is < wifi_end; ++is) {
    ligne += 10;
    wifi();
  }
  display.display();
}//wifi_list_next

void wifi_list_back () {
  wifi_base();
  wifi_start -= 5;
  wifi_end -= 5;
  if (ligne >= 50) ligne = 0;
#ifdef DEBUG
  Serial.print(" ligne  ");
  Serial.print(ligne);
  Serial.print("wifi_start ");
  Serial.println(wifi_start);
  Serial.print("wifi_end ");
  Serial.println(wifi_end);
#endif
  for ( is = wifi_start; is < wifi_end; ++is) {
    ligne += 10;
    wifi();
  }
  display.display();
}//wifi_list_back

void wifi_base() {
  DisplayClear10 ();
  display.drawString(0, 0, String(n));
  display.drawString(15, 0, "Networks Found");
}//wifi_base()
