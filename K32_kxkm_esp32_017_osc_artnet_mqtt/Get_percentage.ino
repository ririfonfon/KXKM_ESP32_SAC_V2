
void get_percentage() {
  percentage = engine->stm32->battery();
  if (percentage > 50) {
    //3ledverte
    for (int i = 0 ; i < 3 ; i++) {
      strands[0]->pixels[i] = pixelFromRGB(0, led_niv, 0);
    }//for i
  }
  else if (percentage > 33) {
    //3ledorange
    for (int i = 0 ; i < 3 ; i++) {
      strands[0]->pixels[i] = pixelFromRGB(led_niv, (led_niv / 3), 0);
    }//for i
  }
  else if (percentage > 16) {
    //3ledrouge
    for (int i = 0 ; i < 3 ; i++) {
      strands[0]->pixels[i] = pixelFromRGB(127, 0, 0);
    }//for i
  }
  else  {
    //3ledrouge clignote
    if (etat_r != 1) {
      for (int i = 0 ; i < 3 ; i++) {
        strands[0]->pixels[i] = pixelFromRGB(255, 0, 0);
      }
      etat_r = 1;
    }
    else if (etat_r != 0) {
      for (int i = 0 ; i < 3 ; i++) {
        strands[0]->pixels[i] = pixelFromRGB(0, 0, 0);
      }
      etat_r = 0;
    }
  }
}
