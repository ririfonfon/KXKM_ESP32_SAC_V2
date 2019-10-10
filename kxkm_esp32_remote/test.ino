int M0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int M1[] = {127, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int M2[] = {127, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int M3[] = {127, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int M4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 0, 0, 0, 0, 0, 0};

void test() {
  DisplayClear16 ();
  display.drawString(20, 0, "Test");
  display.display();
}//test

void testenter() {
  DisplayClear16 ();
  display.drawString(30, 0, "Test");
  if (mode_test == 1) {
    display.drawString(45, 16, "Red");
  }//mode test 1
  else if (mode_test == 2) {
    display.drawString(45, 16, "Green");
  }//mode test 2
  else if (mode_test == 3) {
    display.drawString(45, 16, "Blue");
  }//mode test 3
  else if (mode_test == 4) {
    display.drawString(45, 16, "Leds");
  }//mode test 3
  display.display();
  test_btn();
}//testenter

void test_btn() {
  while (menu == 10) {
    check_button();
    if (button == 1) {
      display.normalDisplay();
      test_0(artNetInterface, &aUDP, 0);
      screen = 1;
      last_screen_check_time = millis();
      menu = 0;
      info();
      button = 0;
    }//menu
    else if (button == 2) {
      display.normalDisplay();
      mode_test += 1;
      if (mode_test >= 5) mode_test = 1;
      testenter();
      button = 0;
    }//up
    else if (button == 3) {
      display.normalDisplay();
      mode_test -= 1;
      if (mode_test <= 0) mode_test = 4;
      testenter();
      button = 0;
    }//down
    else if (button == 4) {
      display.invertDisplay();
      if (mode_test == 1) {
        test_r(artNetInterface, &aUDP, 0);
      }//red
      else if (mode_test == 2) {
        test_g(artNetInterface, &aUDP, 0);
      }//green
      else if (mode_test == 3) {
        test_b(artNetInterface, &aUDP, 0);
      }//blue
      else if (mode_test == 4) {
        test_l(artNetInterface, &aUDP, 0);
      }//leds
      button = 0;
    }//enter
  }//menu == 10
}//test_btn

void test_0(LXDMXWiFi* interface, WiFiUDP* iUDP, uint8_t multicast) {
  interface->setNumberOfSlots(512);
  for (int k = 0; k < 17 ; k++) {
    interface->setSlot(k + 1, M0[k]);
    interface->setSlot(k + 18, M0[k]);
    interface->setSlot(k + 35, M0[k]);
  }//for
  xSemaphoreGive( ESP32DMX.lxDataLock );
  if ( multicast ) {
    interface->sendDMX(iUDP, DMXWiFiConfig.inputAddress(), WiFi.localIP());
  } else {
    interface->sendDMX(iUDP, DMXWiFiConfig.inputAddress(), INADDR_NONE);
  }

}//test_0

void test_r(LXDMXWiFi* interface, WiFiUDP* iUDP, uint8_t multicast) {
  interface->setNumberOfSlots(512);
  for (int k = 0; k < 17 ; k++) {
    interface->setSlot(k + 1, M1[k]);
    interface->setSlot(k + 18, M1[k]);
    interface->setSlot(k + 35, M1[k]);
  }//for
  xSemaphoreGive( ESP32DMX.lxDataLock );
  if ( multicast ) {
    interface->sendDMX(iUDP, DMXWiFiConfig.inputAddress(), WiFi.localIP());
  } else {
    interface->sendDMX(iUDP, DMXWiFiConfig.inputAddress(), INADDR_NONE);
  }

}//test_r

void test_g(LXDMXWiFi* interface, WiFiUDP* iUDP, uint8_t multicast) {
  interface->setNumberOfSlots(512);
  for (int k = 0; k < 17 ; k++) {
    interface->setSlot(k + 1, M2[k]);
    interface->setSlot(k + 18, M2[k]);
    interface->setSlot(k + 35, M2[k]);
  }//for
  xSemaphoreGive( ESP32DMX.lxDataLock );
  if ( multicast ) {
    interface->sendDMX(iUDP, DMXWiFiConfig.inputAddress(), WiFi.localIP());
  } else {
    interface->sendDMX(iUDP, DMXWiFiConfig.inputAddress(), INADDR_NONE);
  }

}//test_g

void test_b(LXDMXWiFi* interface, WiFiUDP* iUDP, uint8_t multicast) {
  interface->setNumberOfSlots(512);
  for (int k = 0; k < 17 ; k++) {
    interface->setSlot(k + 1, M3[k]);
    interface->setSlot(k + 18, M3[k]);
    interface->setSlot(k + 35, M3[k]);
  }//for
  xSemaphoreGive( ESP32DMX.lxDataLock );
  if ( multicast ) {
    interface->sendDMX(iUDP, DMXWiFiConfig.inputAddress(), WiFi.localIP());
  } else {
    interface->sendDMX(iUDP, DMXWiFiConfig.inputAddress(), INADDR_NONE);
  }

}//test_b

void test_l(LXDMXWiFi* interface, WiFiUDP* iUDP, uint8_t multicast) {
  interface->setNumberOfSlots(512);
  for (int k = 0; k < 17 ; k++) {
    interface->setSlot(k + 1, M4[k]);
    interface->setSlot(k + 18, M4[k]);
    interface->setSlot(k + 35, M4[k]);
  }//for
  xSemaphoreGive( ESP32DMX.lxDataLock );
  if ( multicast ) {
    interface->sendDMX(iUDP, DMXWiFiConfig.inputAddress(), WiFi.localIP());
  } else {
    interface->sendDMX(iUDP, DMXWiFiConfig.inputAddress(), INADDR_NONE);
  }
}//test_l
