void Black() {
  for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
    strands[1]->pixels[i] = pixelFromRGBW(0, 0, 0, 0);
  }//for i
}
