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
  }//modein
  else if (frameCountnow == 5) {
    hidd();
  }//modein
  else if (frameCountnow == 6) {
    menu = 1;
    wifiscan();
  }//info
  else if (frameCountnow == 7) {
    menu = 10;
    test();
  }//info
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

void check_btn() {

  if (Moy_sensor > BT_T) {
    Moy_sensor = 0;
    som_Value = 0;
  }
  int sen_Value = analogRead(35);

  if (sen_Value > 1) {
    som_Value += sen_Value;
    Moy_sensor += 1;
  } else {
    som_Value = 0;
    Moy_sensor = 0;
  }

  if (Moy_sensor != 0) {
    sensorValue =  som_Value / Moy_sensor;
  } else {
    sensorValue = 0;
  }

#ifdef DEBUGbtnp
  Serial.print("sen_Value = ");
  Serial.print(sen_Value);
  Serial.print(" // sensorValue = ");
  Serial.print(sensorValue);
  Serial.print(" // pr = ");
  Serial.print(pr);
  Serial.print("  // bt = ");
  Serial.print(bt);
  Serial.print("  // Moy_sensor = ");
  Serial.print(Moy_sensor);
  Serial.print("  // som_Value = ");
  Serial.println(som_Value);
#endif



  if (sensorValue < 200) {
    pr = 0; // relache btn
  }

  if (pr == 0 && bt == 0) {
    if (sensorValue > 1650 && sensorValue < 1700) {
      pr = 1; bt = 1; // bt1
#ifdef DEBUGbtnp
      Serial.println("bt1");
#endif
    } else if (sensorValue > 910 && sensorValue < 1000) {
      pr = 1; bt = 2; // bt2
#ifdef DEBUGbtnp
      Serial.println("bt2");
#endif
    } else if (sensorValue > 500 && sensorValue < 600) {
      pr = 1; bt = 3; // bt3
#ifdef DEBUGbtnp
      Serial.println("bt3");
#endif
    } else if (sensorValue > 290 && sensorValue < 390) {
      pr = 1; bt = 4; //bt4
#ifdef DEBUGbtnp
      Serial.println("bt4");
#endif
    }
  }// pr !=1

  if (pr == 1) {
    if (sensorValue > 1590 && sensorValue < 1610) {
      pr = 2; bt = 12;// bt1 2
#ifdef DEBUGbtnp
      Serial.println("bt1 2");
#endif
    } else if (sensorValue > 1460 && sensorValue < 1490) {
      pr = 2; bt = 13;// bt1 3
#ifdef DEBUGbtnp
      Serial.println("bt1 3");
#endif
    } else if (sensorValue > 1170 && sensorValue < 1200) {
      pr = 2; bt = 14;// bt1 4
#ifdef DEBUGbtnp
      Serial.println("bt1 4");
#endif
    } else if (sensorValue > 840 && sensorValue < 870) {
      pr = 2; bt = 23;// bt2 3
#ifdef DEBUGbtnp
      Serial.println("bt2 3");
#endif
    } else if (sensorValue > 640 && sensorValue < 680) {
      pr = 2; bt = 24;// bt2 4
#ifdef DEBUGbtnp
      Serial.println("bt2 4");
#endif
    } else if (sensorValue > 410 && sensorValue < 450) {
      pr = 2; bt = 34;// bt3 4
#ifdef DEBUGbtnp
      Serial.println("bt3 4");
#endif
    }
  }// pr > 1

  if (pr == 0 && bt != 0) {
    if (bt == 1) {
      gotTouch9();
      Serial.println("bt1");
    } else if (bt == 2) {
      gotTouch8();
      Serial.println("bt2");
    } else if  (bt == 3) {
      gotTouch7();
      Serial.println("bt3");
    } else if  (bt == 4) {
      gotTouch6();
      Serial.println("bt4");
    } else if  (bt == 12) {
      display.displayOn();
      enter = 0;
      frameCountnow = 1;
      screen = 1;
      last_screen_check_time = now;
      info();
      gotTouch9();
      Serial.println("bt1 2 ");
    } else if  (bt == 13) {
      display.displayOff();
      enter = 0;
      screen = 0;
      last_screen_check_time = now;
      Serial.println("bt1 3");
    } else if  (bt == 14) {
      Serial.println("bt1 4");
    } else if  (bt == 23) {
      Serial.println("bt2 3");
    } else if  (bt == 24) {
      Serial.println("bt2 4");
    } else if  (bt == 34) {
      Serial.println("bt3 4");
    }
    bt = 0;
    last_screen_check_time = now;
  }//if (pr==0 && bt!=0)

}// check_btn
