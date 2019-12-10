void do_zoom() {
  for (int i = 0 ; i < NUM_LEDS_PER_STRIP_MAX ; i++) {
        if (i <= offset) strands[1]->pixels[i] = pixelFromRGBW(0, 0, 0, 0);
        else if (i <= offset + zoom && i >= offset + 1) strands[1]->pixels[i] = pixelFromRGBW((zo_pi_n_1_r[i - offset]  * master / 255), (zo_pi_n_1_g[i - offset]  * master / 255), (zo_pi_n_1_b[i - offset]  * master / 255), (zo_pi_n_1_w[i - offset] * master / 255));
        else if (i <= NUM_LEDS_PER_STRIP_MAX && i >= offset + zoom + 1) strands[1]->pixels[i] = pixelFromRGBW(0, 0, 0, 0);
//    strands[1]->pixels[i] = pixelFromRGBW((zo_pi_n_1_r[i]  * master / 255), (zo_pi_n_1_g[i]  * master / 255), (zo_pi_n_1_b[i]  * master / 255), (zo_pi_n_1_w[i] * master / 255));
  }//for i
}// do_zoom()
