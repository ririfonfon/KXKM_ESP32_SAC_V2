
void eff_modulo() {
  float fade_coef = 10;
  unsigned long t_now = millis();

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////// modulo 30 -> 36  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if ( type_modulo == 30 ) {
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));
      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
      }
    }//for i
  }//modulo 30

  else if ( type_modulo == 31) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
      }
    }//for i
  }//modulo 31

  else if (type_modulo == 32) {
    if (str_ws <= 0) str_ws = 1;
    float time_modulo = str_ws * fade_coef;
    int t_modulo = str_ws * fade_coef;
    float module = 2 * abs( (t_now % t_modulo) - time_modulo / 2) / time_modulo;
    module *= module;
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));
      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
      }
    }//for i
  }// modulo 32

  else if ( type_modulo == 33 ) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }
    int n_led_to_show = (min(NUM_LEDS_PER_STRIP - 8, S_seuil));
    
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , NUM_LEDS_PER_STRIP );
        
      } while (strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].r != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].g != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].b != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].w != 0);

      if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S) {
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }
    }//for i
  }//modulo 33

  else if ( type_modulo == 34) {
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }
    }//for i
  }//modulo 34

  else if ( type_modulo == 35 ) {
    int S_seuil_B;
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }
    int n_led_to_show = min(NUM_LEDS_PER_STRIP - 8, S_seuil);
    
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , NUM_LEDS_PER_STRIP );
        
      } while (strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].r != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].g != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].b != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].w != 0 );

      if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S) {
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }
    }//for i
  }//modulo 35

  else if ( type_modulo == 36 ) {
    if (old_S_seuil != S_seuil) {
      Black();
      old_S_seuil = S_seuil;
    }
    int S_seuil_B;
    int n_led_to_show = min(NUM_LEDS_PER_STRIP - 8, S_seuil);
    
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , NUM_LEDS_PER_STRIP );
        
      } while (strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].r != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].g != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].b != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].w != 0 );

      if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S) {
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * 0)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * 0)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * 0)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * 0)] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), N_L_P_S + 1, N_L_P_S * 2, N_L_P_S, 0);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 3) + 1, N_L_P_S * 4, N_L_P_S, 0);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      }
    }//for i
    old_S_seuil = S_seuil - 1;
  }//modulo 36



  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////// modulo 60 -> 66 /////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  else if ( type_modulo == 60 ) {
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[i] / 255) * master), ((pi_n_1_g[i] / 255) * master), ((pi_n_1_b[i] / 255) * master), ((pi_n_1_w[i] / 255) * master));
      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * master), ((pi_n_1_g[di] / 255) * master), ((pi_n_1_b[di] / 255) * master), ((pi_n_1_w[di] / 255) * master));
      }
    }//for i
  }//modulo 60

  else if ( type_modulo == 61) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * str * master), ((pi_n_1_g[di] / 255) * str * master), ((pi_n_1_b[di] / 255) * str * master), ((pi_n_1_w[di] / 255) * str * master));
      }
    }//for i
  }//modulo 61

  else if (type_modulo == 62) {
    if (str_ws <= 0) str_ws = 1;
    float time_modulo = str_ws * fade_coef;
    int t_modulo = str_ws * fade_coef;
    float module = 2 * abs( (t_now % t_modulo) - time_modulo / 2) / time_modulo;
    module *= module;
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * module * master / 255), (pi_n_1_g[i] * module * master / 255), (pi_n_1_b[i] * module * master / 255), (pi_n_1_w[i] * module * master / 255));
      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW(((pi_n_1_r[di] / 255) * module * master), ((pi_n_1_g[di] / 255) * module * master), ((pi_n_1_b[di] / 255) * module * master), ((pi_n_1_w[di] / 255) * module * master));
      }
    }//for i
  }// modulo 62

  else if ( type_modulo == 63 ) {
    if (str == 0 && t_now - str_ws_last > str_ws) {
      str_ws_last = t_now;
      str = 1;
    } else if (str == 1 && t_now - str_ws_last > STROB_ON_MS) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }
    int n_led_to_show = (min(NUM_LEDS_PER_STRIP - 8, S_seuil));
    
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , NUM_LEDS_PER_STRIP );
        
      } while (strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].r != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].g != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].b != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].w != 0);

      if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S) {
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }
    }//for i
  }//modulo 63

  else if ( type_modulo == 64) {
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
    } else {
      return;
    }
    for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
      if (i <= N_L_P_S) {
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[i] * str * master / 255), (pi_n_1_g[i] * str * master / 255), (pi_n_1_b[i] * str * master / 255), (pi_n_1_w[i] * str * master / 255));
      } else if (i <= N_L_P_S * 2 & i >= N_L_P_S) {
        int di = map(i, N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (i <= N_L_P_S * 3 & i >= N_L_P_S * 2) {
        int di = map(i, (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (i <= N_L_P_S * 4 & i >= N_L_P_S * 3) {
        int di = map(i, (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
        strands[1]->pixels[i] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }
    }//for i
  }//modulo 64

  else if ( type_modulo == 65 ) {
    int S_seuil_B;
    if (str == 0 && str_ws_last < t_now && t_now - str_ws_last > str_ws / (str_blind_ws * str_blind_ws)) {
      str_ws_last = t_now;
      str = 1;
      str_blind_ws = str_blind_ws + 0.05;
      if (str_blind_ws >= 3) {
        str_blind_ws = 1;
        // Noir pendant 1 sec (dans le futur)
        str = 0;
        str_ws_last = t_now + 1000;
      }
    } else if (str == 1 && str_ws_last < t_now && t_now - str_ws_last > (STROB_ON_MS)) {
      str_ws_last = t_now;
      str = 0;
      Black();
    } else {
      return;
    }
    int n_led_to_show = min(NUM_LEDS_PER_STRIP - 8, S_seuil);
    
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , NUM_LEDS_PER_STRIP );
        
      } while (strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].r != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].g != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].b != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].w != 0 );

      if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S) {
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * 0)] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * str * master / 255), (pi_n_1_g[di] * str * master / 255), (pi_n_1_b[di] * str * master / 255), (pi_n_1_w[di] * str * master / 255));
      }
    }//for i
  }//modulo 65

  else if ( type_modulo == 66 ) {
    if (old_S_seuil != S_seuil) {
      Black();
      old_S_seuil = S_seuil;
    }
    int S_seuil_B;
    int n_led_to_show = min(NUM_LEDS_PER_STRIP - 8, S_seuil);
    
    for (int i = 0; i < n_led_to_show ; i ++) {
      do {
        a = random( 0 , NUM_LEDS_PER_STRIP );
        
      } while (strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].r != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].g != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].b != 0 || strands[0]->pixels[a - (NUM_LEDS_PER_STRIP * 0)].w != 0 );

      if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S) {
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[a - (NUM_LEDS_PER_STRIP * 0)] * master / 255), (pi_n_1_g[a - (NUM_LEDS_PER_STRIP * 0)] * master / 255), (pi_n_1_b[a - (NUM_LEDS_PER_STRIP * 0)] * master / 255), (pi_n_1_w[a - (NUM_LEDS_PER_STRIP * 0)] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 2 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), N_L_P_S + 1, N_L_P_S * 2, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 3 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 2)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 2) + 1, N_L_P_S * 3, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      } else if (a - (NUM_LEDS_PER_STRIP * 0) <= N_L_P_S * 4 & a - (NUM_LEDS_PER_STRIP * 0 >= N_L_P_S * 3)) {
        int di = map(a - (NUM_LEDS_PER_STRIP * 0), (N_L_P_S * 3) + 1, N_L_P_S * 4, 0, N_L_P_S);
        strands[1]->pixels[a - (NUM_LEDS_PER_STRIP * 0)] = pixelFromRGBW((pi_n_1_r[di] * master / 255), (pi_n_1_g[di] * master / 255), (pi_n_1_b[di] * master / 255), (pi_n_1_w[di] * master / 255));
      }
    }//for i
    old_S_seuil = S_seuil - 1;
  }//modulo 66

}//eff_modulo
