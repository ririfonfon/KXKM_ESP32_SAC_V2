//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// onDmxFrame //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data) {
  boolean tail = false;

#ifdef DEBUG_dmx
  Serial.print("master = ");
  Serial.println(master);
  Serial.print("r = ");
  Serial.println(r);
  Serial.print("g = ");
  Serial.println(g);
  Serial.print("b = ");
  Serial.println(b);
  Serial.print("w = ");
  Serial.println(w);
  Serial.print("pix_mod = ");
  Serial.println(pix_mod);
  Serial.print("pix_start = ");
  Serial.println(pix_start);
  Serial.print("pix_center = ");
  Serial.println(pix_center);
  Serial.print("pix_end = ");
  Serial.println(pix_end);
  Serial.print("pix_pos = ");
  Serial.println(pix_pos);
  Serial.print("modulo = ");
  Serial.println(modulo);
  Serial.print("str_ws = ");
  Serial.println(str_ws);
  Serial.print("M_g = ");
  Serial.println(M_g);
#endif

  master = data[adr - 1];
  rr = (data[adr] * data[adr]) / 255;
  gg = (data[adr + 1] * data[adr + 1]) / 255;
  bb = (data[adr + 2] * data[adr + 2]) / 255;
  ww = (data[adr + 3] * data[adr + 3]) / 255;
  pix_mod = data[adr + 4];
  pix_start = data[adr + 5] - 1;

  pix_end = pix_start + pix_start;
  if (pix_mod >= 11 && pix_mod <= 20 || pix_mod >= 31 && pix_mod <= 60 ) {
    pix_pos = (((pix_start + NUM_LEDS_PER_STRIP + pix_end) * data[adr + 6]) / 255) - (pix_end + 1);
  } else if (pix_mod >= 21 && pix_mod <= 30 || pix_mod >= 61 && pix_mod <= 90) {
    pix_pos = (((pix_start + NUM_LEDS_PER_STRIP + pix_end) * data[adr + 6]) / 255) - (pix_end + 1);
  }
  modulo = data[adr + 7];
  str_ws = (data[adr + 8] * data[adr + 8]) / 33;
  pix_center = ((pix_start) / 2) + pix_pos;

  smaster = data[adr + 9];
  srr = (data[adr + 10] * data[adr + 10]) / 255;
  sgg = (data[adr + 11] * data[adr + 11]) / 255;
  sbb = (data[adr + 12] * data[adr + 12]) / 255;
  sww = (data[adr + 13] * data[adr + 13]) / 255;


  if ((modulo >= 0) && modulo <= 10) {
    type_modulo = 0;
  } else if ((modulo >= 11) && modulo <= 20) {
    type_modulo = 1;
  } else if ((modulo >= 21) && modulo <= 30) {
    type_modulo = 2;
  } else if ((modulo >= 31) && modulo <= 110) {
    Black();
    type_modulo = 3;
    S_seuil = (modulo - 30) * 4;
    type_effet = 255;
  } else if ((modulo >= 111) && modulo <= 120) {
    type_modulo = 4;
  } else if ((modulo >= 121) && modulo <= 200) {
    Black();
    type_modulo = 5;
    S_seuil = (modulo - 120) * 4;
    type_effet = 255;
  } else if ((modulo >= 201) && modulo <= 255) {
    type_modulo = 6;
    S_seuil = (modulo - 200) * 4;
    type_effet = 255;
  }

  previousDataLength = length;

  if (sendFrame) {
    // Reset universeReceived to 0
    memset(universesReceived, 0, maxUniverses);
  }
}//onframedmx
