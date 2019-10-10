void check_button () {
  int sensorValue = analogRead(35);
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
      button = 1;
      Serial.println("bt1");
    } else if (bt == 2) {
      button = 2;
      Serial.println("bt2");
    } else if  (bt == 3) {
      button = 3;
      Serial.println("bt3");
    } else if  (bt == 4) {
      button = 4;
      Serial.println("bt4");
    }
  }//if (pr == 0 && bt != 0)
}// check_button
