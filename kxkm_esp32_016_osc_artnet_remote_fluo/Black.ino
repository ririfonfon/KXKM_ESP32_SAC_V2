void Black() {
  for (int i = 0 ; i < NUM_LEDS_PER_STRIP_MAX ; i++) {
    strands[0]->pixels[i] = pixelFromRGBW(0, 0, 0, 0);
    strands[1]->pixels[i] = pixelFromRGBW(0, 0, 0, 0);
    zo_pi_n_1_r[i] = 0;
    zo_pi_n_1_g[i] = 0;
    zo_pi_n_1_b[i] = 0;
    zo_pi_n_1_w[i] = 0;
  }//for i
}
