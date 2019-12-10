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
      Serial.println("**bt1");
#endif
    } else if (sensorValue > 910 && sensorValue < 1000) {
      pr = 1; bt = 2; // bt2
#ifdef DEBUGbtnp
      Serial.println("**bt2");
#endif
    } else if (sensorValue > 500 && sensorValue < 600) {
      pr = 1; bt = 3; // bt3
#ifdef DEBUGbtnp
      Serial.println("**bt3");
#endif
    } else if (sensorValue > 290 && sensorValue < 390) {
      pr = 1; bt = 4; //bt4
#ifdef DEBUGbtnp
      Serial.println("**bt4");
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
#ifdef DEBUG
    Serial.print("if (pr == 0 && bt != 0) { ");
#endif
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
      //      display.displayOn();
      //      enter = 0;
      //      frameCountnow = 1;
      //      screen = 1;
      //      last_screen_check_time = now;
      //      info();
      //      gotTouch9();
      Serial.println("bt1 2 ");
    } else if  (bt == 13) {
      //      display.displayOff();
      //      enter = 0;
      //      screen = 0;
      //      last_screen_check_time = now;
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



//*************************************************************************************

void check_button () {

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
    } else if (sensorValue > 910 && sensorValue < 1000) {
      pr = 1; bt = 2; // bt2
    } else if (sensorValue > 500 && sensorValue < 600) {
      pr = 1; bt = 3; // bt3
    }  else if (sensorValue > 290 && sensorValue < 390) {
      pr = 1; bt = 4; //bt4
    }
  }// pr !=1

  if (pr == 1) {
    if (sensorValue > 1590 && sensorValue < 1610) {
      pr = 2; bt = 12;// bt1 2
    } else if (sensorValue > 1460 && sensorValue < 1490) {
      pr = 2; bt = 13;// bt1 3
    } else if (sensorValue > 1170 && sensorValue < 1200) {
      pr = 2; bt = 14;// bt1 4
    } else if (sensorValue > 840 && sensorValue < 870) {
      pr = 2; bt = 23;// bt2 3
    } else if (sensorValue > 640 && sensorValue < 680) {
      pr = 2; bt = 24;// bt2 4
    } else if (sensorValue > 410 && sensorValue < 450) {
      pr = 2; bt = 34;// bt3 4
    }
  }// pr > 1

  if (pr == 0 && bt != 0) {
    if (bt == 1) {
      button = 1;
      Serial.println("/////bt1");
    } else if (bt == 2) {
      button = 2;
      Serial.println("/////bt2");
    } else if  (bt == 3) {
      button = 3;
      Serial.println("/////bt3");
    } else if  (bt == 4) {
      button = 4;
      Serial.println("/////bt4");
    }
    bt = 0;
  }//if (pr == 0 && bt != 0)
}// check_button
