/************************************************************************
 ****************               display                ******************
 ************************************************************************/
char buf[2];
char bufi[2];
char bufa[2];

void info () {
  DisplayClear10 ();
  display.drawString(0, 0, "AP Mode ");
  display.drawString(55, 0, DMXWiFiConfig.SSID());
  display.drawString(0, 10, "AP IP at ");
  IPAddress myIP = DMXWiFiConfig.apIPAddress();
  String ipStr = String(myIP[0]) + "." + String(myIP[1]) + "." + String(myIP[2]) + "." + String(myIP[3]);
  display.drawString(55, 10, ipStr );
  display.drawString(0, 20, "Wifi Chan ");
  display.drawString(55, 20, String(wifichannel));
  if (hidden == 1) {
    display.drawString(75, 20, "Cacher");
  }//hidden 1
  if (hidden == 2) {
    display.drawString(75, 20, "Visible");
  }//hidden 2
  display.drawString(0, 30, "DMX Input");
  display.drawString(65, 30, String(dmx_start));
  display.drawString(0, 40, "Mode Start ");
  if (mode_start == 1) {
    display.drawString(65, 40, "FULL");
  }//mode start 1
  if (mode_start == 2) {
    display.drawString(65, 40, "CLUB");
  }//mode start 2
  if (mode_start == 3) {
    display.drawString(65, 40, "MINI");
  }//mode start 3
  display.display();
}//info

void shutdown_screen () {
  DisplayClear10 ();
  display.drawString(0, 0, "DIPLAY OFF");
  display.drawString(0, 16, "MENU+UP=>ON");
  display.drawString(0, 32, "MENU+DOWN=>OFF");
  display.display();
  if (now - last_screen_check_time > SCREEN_TIMEOUT + 3000) {
    display.displayOff();
    screen = 0;
    last_screen_check_time = now;
  }
}//shutdown_screen

/************************************************************************
 ****************               Touch                ******************
 ************************************************************************/

void gotTouch9() {
  frameCountnow = frameCountnow + 1;
#ifdef DEBUG
  Serial.print("frameCount ");
  Serial.print(frameCount);
  Serial.print("frameCountnow ");
  Serial.println(frameCountnow);
#endif
  if (frameCountnow > frameCount) {
    frameCountnow = 1;
  }
  if (frameCountnow == 1) {
    info();
  }//info
  else if (frameCountnow == 2) {
    setin();
  }//setin
  else if (frameCountnow == 3) {
    modein();
  }//modein
  else if (frameCountnow == 4) {
    wifichan();
  }//wifichan()
  else if (frameCountnow == 5) {
    hidd();
  }//hidd()
  else if (frameCountnow == 6) {
    menu = 1;
    wifiscan();
  }//wifiscan()
  else if (frameCountnow == 7) {
    menu = 10;
    test();
  }//test()
  if (enter == 1) {
    display.normalDisplay();
  }
  enter = 0;
}//menu

void gotTouch8() {
  if (enter == 1) {
    if (frameCountnow == 1) {

    }//info
    else if (frameCountnow == 2) {
      dmx_start = dmx_start + 1;
      if (dmx_start > 512) {
        dmx_start = 1;
      }
      setinenter();
    }//setin
    else if (frameCountnow == 3) {
      mode_start = mode_start + 1;
      if (mode_start >= 4) {
        mode_start = 1;
      }// mode_start>=4
      modeinenter();
    }//modein
    else if (frameCountnow == 4) {
      wifichannel = wifichannel + 1;
      if (wifichannel >= 14) {
        wifichannel = 1;
      }// wifichannel >=14
      wifichan();
    }//wifichan
    else if (frameCountnow == 5) {
      hidden = hidden + 1;
      if (hidden >= 3) {
        hidden = 1;
      }//hidden >= 3
      hidd();
    }//hidden
  }//enter true
}//up

void gotTouch7() {
  if (enter == 1) {
    if (frameCountnow == 1) {

    }//info
    else if (frameCountnow == 2) {
      dmx_start = dmx_start - 1;
      if (dmx_start <= 0) {
        dmx_start = 512;
      }
      setinenter();
    }//setin
    else if (frameCountnow == 3) {
      mode_start = mode_start - 1;
      if (mode_start <= 0) {
        mode_start = 3;
      }// mode_start>4
      modeinenter();
    }//modein
    else if (frameCountnow == 4) {
      wifichannel = wifichannel - 1;
      if (wifichannel <= 0) {
        wifichannel = 13;
      }// wifichannel <=0
      wifichan();
    }//channel
    else if (frameCountnow == 5) {
      hidden = hidden - 1;
      if (hidden <= 0) {
        hidden = 2;
      }//hidden <= 0
      hidd();
    }//hidden
  }//enter true
}//down

void gotTouch6() {
  enter = enter + 1;
#ifdef DEBUG
  Serial.print("enter = "); Serial.println(enter) ;
#endif
  if (enter == 1) {
    if (frameCountnow == 1) {

    }//info
    else if (frameCountnow == 2) {
      setinenter();
    }//setin
    else if (frameCountnow == 3) {
      modeinenter();
    }//modein
    else if (frameCountnow == 4) {
      wifichanenter();
    }//channel
    else if (frameCountnow == 5) {
      hiddenter();
    }//hidden
    else if (frameCountnow == 6) {
      wifiscanenter ();
    }//wifiscan
    else if (frameCountnow == 7) {
      testenter ();
    }//checkenter
  }// enter = 1
  else if (enter == 2) {
    if (frameCountnow == 1) {

    }//info
    else if (frameCountnow == 2) {
      setinstore();
    }//setin
    else if (frameCountnow == 3) {
      modeinstore();
    }//modein
    else if (frameCountnow == 4) {
      wifichanstore();
    }//channel
    else if (frameCountnow == 5) {
      hiddstore();
    }//hidden
  }//enter = 2
  else if (enter >= 3) {
    enter = 0;
  }// enter >= 3
}//enter
