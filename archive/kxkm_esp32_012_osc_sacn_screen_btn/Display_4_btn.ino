/************************************************************************
 ****************               display                ******************
 ************************************************************************/
char buf[2];
char bufi[2];
char bufa[2];

//void info () {
//  DisplayClear10 ();
//  display.drawString(0, 0, "AP Mode ");
////  display.drawString(55, 0, DMXWiFiConfig.SSID());
//  display.drawString(0, 10, "AP IP at ");
//  IPAddress myIP = WiFi.localIP();
//  String ipStr = String(myIP[0]) + "." + String(myIP[1]) + "." + String(myIP[2]) + "." + String(myIP[3]);
//  display.drawString(55, 10, ipStr );
//  display.drawString(0, 20, "Wifi Chan ");
//  display.drawString(55, 20, String(wifichannel));
//  if (hidden == 1) {
//    display.drawString(75, 20, "Cacher");
//  }//hidden 1
//  else if (hidden == 2) {
//    display.drawString(75, 20, "Visible");
//  }//hidden 2
//  display.drawString(0, 30, "DMX Input");
//  display.drawString(65, 30, String(dmx_start));
//  display.drawString(0, 40, "Mode Start ");
//
//  if (mode_start == 1) {
//    display.drawString(65, 40, "FULL");
//  }//mode start 1
//  else if (mode_start == 2) {
//    display.drawString(65, 40, "CLUB");
//  }//mode start 2
//  else if (mode_start == 3) {
//    display.drawString(65, 40, "MINI");
//  }//mode start 3
//  display.drawString(0, 50, "Bat : ");
//  sprintf (buf, "%d", level);
//  display.drawString(65, 50, buf);
//  display.drawString(85, 50, "%");
//  display.display();
//}//info
//
void shutdown_screen () {
  DisplayClear18 ();
  display.drawString(0, 0, "DIPLAY OFF");
  display.drawString(0, 22, "MENU+UP=>ON");
  display.drawString(0, 44, "MENU+DOWN=>OFF");
  display.display();
  if (now - last_screen_check_time > S_TIMEOUT + 3000) {
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
    //    info();
  }//info
  else if (frameCountnow == 2) {
    //    setin();
  }//setin
  else if (frameCountnow == 3) {
    //    modein();
  }//modein
  else if (frameCountnow == 4) {
    //    wifichan();
  }//modein
  else if (frameCountnow == 5) {
    //    hidd();
  }//modein
  else if (frameCountnow == 6) {
    menu = 1;
    //    wifiscan();
  }//info
  else if (frameCountnow == 7) {
    menu = 10;
    initTest();
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
      //      dmx_start = dmx_start + 1;
      //      if (dmx_start > 512) {
      //        dmx_start = 1;
      //      }
      //      setinenter();
    }//setin
    else if (frameCountnow == 3) {
      //      mode_start = mode_start + 1;
      //      if (mode_start >= 4) {
      //        mode_start = 1;
      //      }// mode_start>=4
      //      modeinenter();
    }//modein
    else if (frameCountnow == 4) {
      //      wifichannel = wifichannel + 1;
      //      if (wifichannel >= 14) {
      //        wifichannel = 1;
      //      }// wifichannel >=14
      //      wifichan();
    }//wifichan
    else if (frameCountnow == 5) {
      //      hidden = hidden + 1;
      //      if (hidden >= 3) {
      //        hidden = 1;
      //      }//hidden >= 3
      //      hidd();
    }//hidden
  }//enter true
}//up

void gotTouch7() {
  if (enter == 1) {
    if (frameCountnow == 1) {

    }//info
    else if (frameCountnow == 2) {
      //      dmx_start = dmx_start - 1;
      //      if (dmx_start <= 0) {
      //        dmx_start = 512;
      //      }
      //      setinenter();
    }//setin
    else if (frameCountnow == 3) {
      //      mode_start = mode_start - 1;
      //      if (mode_start <= 0) {
      //        mode_start = 3;
      //      }// mode_start>4
      //      modeinenter();
    }//modein
    else if (frameCountnow == 4) {
      //        wifichannel = wifichannel - 1;
      //        if (wifichannel <= 0) {
      //          wifichannel = 13;
      //        }// wifichannel <=0
      //        wifichan();
    }//channel
    else if (frameCountnow == 5) {
      //      hidden = hidden - 1;
      //      if (hidden <= 0) {
      //        hidden = 2;
      //      }//hidden <= 0
      //      hidd();
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
      //      setinenter();
    }//setin
    else if (frameCountnow == 3) {
      //      modeinenter();
    }//modein
    else if (frameCountnow == 4) {
      //      wifichanenter();
    }//channel
    else if (frameCountnow == 5) {
      //      hiddenter();
    }//hidden
    else if (frameCountnow == 6) {
      //      wifiscanenter ();
    }//wifiscan
    else if (frameCountnow == 7) {
      //      testenter ();
    }//checkenter
  }// enter = 1
  else if (enter == 2) {
    if (frameCountnow == 1) {

    }//info
    else if (frameCountnow == 2) {
      //      setinstore();
    }//setin
    else if (frameCountnow == 3) {
      //      modeinstore();
    }//modein
    else if (frameCountnow == 4) {
      //      wifichanstore();
    }//channel
    else if (frameCountnow == 5) {
      //      hiddstore();
    }//hidden
  }//enter = 2
  else if (enter >= 3) {
    enter = 0;
  }// enter >= 3
}//enter

void check_btn() {
  int sensorValue = analogRead(35);

#ifdef DEBUGbtnp
  //  Serial.println(sensorValue);
  if (sensorValue > 1600 && sensorValue < 1650) {
    Serial.println("bt1");
  } else if (sensorValue > 1500 && sensorValue < 1600) {
    Serial.println("bt1 2");
  } else if (sensorValue > 1400 && sensorValue < 1500) {
    Serial.println("bt1 3");
  } else if (sensorValue > 1100 && sensorValue < 1200) {
    Serial.println("bt1 4");
  } else if (sensorValue > 900 && sensorValue < 950) {
    Serial.println("bt2");
  } else if (sensorValue > 800 && sensorValue < 850) {
    Serial.println("bt2 3");
  } else if (sensorValue > 600 && sensorValue < 650) {
    Serial.println("bt2 4");
  } else if (sensorValue > 500 && sensorValue < 600) {
    Serial.println("bt3");
  } else if (sensorValue > 400 && sensorValue < 450) {
    Serial.println("bt3 4");
  } else if (sensorValue > 250 && sensorValue < 350) {
    Serial.println("bt4");
  }
  Serial.print("pr = ");
  Serial.print(pr);
  Serial.print("   bt = ");
  Serial.println(bt);
#endif



  if (sensorValue < 200) {
    pr = 0; // relache btn
  }

  if (pr == 0 && bt == 0) {
    if (sensorValue > 1600 && sensorValue < 1650) {
      pr = 1; bt = 1; // bt1
    } else if (sensorValue > 900 && sensorValue < 950) {
      pr = 1; bt = 2; // bt2
    } else if (sensorValue > 500 && sensorValue < 600) {
      pr = 1; bt = 3; // bt3
    }  else if (sensorValue > 250 && sensorValue < 350) {
      pr = 1; bt = 4; //bt4
    }
  }// pr !=1

  if (pr == 1) {
    if (sensorValue > 1500 && sensorValue < 1550) {
      pr = 2; bt = 12;// bt1 2
    } else if (sensorValue > 1400 && sensorValue < 1500) {
      pr = 2; bt = 13;// bt1 3
    } else if (sensorValue > 1100 && sensorValue < 1200) {
      pr = 2; bt = 14;// bt1 4
    } else if (sensorValue > 800 && sensorValue < 850) {
      pr = 2; bt = 23;// bt2 3
    } else if (sensorValue > 600 && sensorValue < 650) {
      pr = 2; bt = 24;// bt2 4
    } else if (sensorValue > 400 && sensorValue < 450) {
      pr = 2; bt = 34;// bt3 4
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
      //      info();
      Serial.println("bt1 2 ");
    } else if  (bt == 13) {
      //      display.displayOff();
      shutdown_screen ();
      enter = 0;
      screen = 0;
      Serial.println("bt1 3");
    } else if  (bt == 14) {
      initTest();
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




  //  //menu
  //  if (button9.onPressed()) {
  //    digitalWrite(TOUCH_LED, HIGH);
  //  }
  //  if (button9.onReleased() && button8.isReleased() || button9.onReleased() && button7.isReleased()) {
  //    if (init_btn9 == 0) {
  //      init_btn9 = 1;
  //      return;
  //    }
  //    digitalWrite(TOUCH_LED, LOW);
  //#ifdef DEBUG
  //    Serial.println("Button9 Released MENU");
  //#endif
  //    last_screen_check_time = now;
  //    gotTouch9();
  //  }// 9 8 release 9 7 release
  //
  //  //menu up
  //  if (button9.isPressed() && button8.isPressed()) {
  //    display.displayOn();
  //    enter = 0;
  //    frameCountnow = 1;
  //    screen = 1;
  //    last_screen_check_time = now;
  //    info();
  //    gotTouch9();
  //  }// display on
  //
  //  //menu down
  //  if (button9.isPressed() && button7.isPressed()) {
  //    display.displayOff();
  //    enter = 0;
  //    screen = 0;
  //    last_screen_check_time = now;
  //  }// display off
  //
  //  //up
  //  if (button8.onPressed()) {
  //    last_screen_check_time = now;
  //  }
  //  if (button8.onReleased()) {
  //    if (init_btn8 == 0) {
  //      init_btn8 = 1;
  //      return;
  //    }
  //#ifdef DEBUG
  //    Serial.println("Button8 Released UP");
  //#endif
  //    gotTouch8();
  //  }//button.8
  //
  //  //down
  //  if (button7.onPressed()) {
  //    last_screen_check_time = now;
  //  }
  //  if (button7.onReleased()) {
  //    if (init_btn7 == 0) {
  //      init_btn7 = 1;
  //      return;
  //    }
  //#ifdef DEBUG
  //    Serial.println("Button7 Released DOWN");
  //#endif
  //    gotTouch7();
  //  }//button.7
  //
  //  // Enter
  //  if (button6.onPressed()) {
  //    last_screen_check_time = now;
  //  }
  //  if (button6.onReleased()) {
  //    if (init_btn6 == 0) {
  //      init_btn6 = 1;
  //      return;
  //    }
  //#ifdef DEBUG
  //    Serial.println("Button6 Released ENTER");
  //#endif
  //    gotTouch6();
  //  }//button.6
  //
  //
}// check_btn
