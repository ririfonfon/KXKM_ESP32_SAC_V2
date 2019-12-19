
void k32_settings() {

  // Save to EEPROM if DEFINE
#ifdef LULU_ID
  k32->system->preferences.putUInt("LULU_id", LULU_ID);
#endif
#ifdef LULU_TYPE
  k32->system->preferences.putUInt("LULU_type", LULU_TYPE);
#endif
#ifdef LULU_UNI
  k32->system->preferences.putUInt("LULU_uni", LULU_UNI);
#endif
#ifdef RUBAN_TYPE
  k32->system->preferences.putUInt("RUBAN_type", RUBAN_TYPE);
#endif
#ifdef R_TYPE
  k32->system->preferences.putString("R_type", R_TYPE);
#endif
#ifdef L_TYPE
  k32->system->preferences.putString("L_type", L_TYPE);
#endif
#ifdef NUM_LEDS_PER_STRIP_MAX
  k32->system->preferences.putUInt("NUM_leds", NUM_LEDS_PER_STRIP_MAX);
#endif

  // Load from EEPROM
  LULU_id = k32->system->preferences.getUInt("LULU_id", 1);
  LULU_type = k32->system->preferences.getUInt("LULU_type", 5);
  LULU_uni = k32->system->preferences.getUInt("LULU_uni", 0);
  RUBAN_type = k32->system->preferences.getUInt("RUBAN_type", LED_SK6812W_V1);
  R_type = k32->system->preferences.getString("R_type", "_SK");
  L_type = k32->system->preferences.getString("L_type", "Flex");
  NUM_LEDS_PER_STRIP_max = k32->system->preferences.getUInt("NUM_leds", 186);

  // Calculate adr // channels
  adr = (1 + (LULU_id - 1) * (LULU_PATCHSIZE));
  numberOfChannels = NUM_STRIPS * NUM_LEDS_PER_STRIP_max * 4;
  maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
  startUniverse = LULU_uni;

  // Calculate NUM leds MAX & L/R TYPE
  NUM_LEDS_PER_STRIP = NUM_LEDS_PER_STRIP_max;
  N_L_P_S = NUM_LEDS_PER_STRIP_max;

  // Make name and PINS
  nodeName += L_type + R_type + "-" + String(LULU_id) + "-v" + String(LULU_VER);
  PINS[0] = k32->system->ledpin(0);
  PINS[1] = k32->system->ledpin(1);

}//k32_settings()
