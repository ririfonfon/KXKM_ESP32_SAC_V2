void bat_custom() {
  int Ulow = 21700;
  int U1 = 23100;
  int U2 = 23500;
  int U3 = 24500;
  int U4 = 26500;
  int U5 = 28000;
  int Umax = 29400;

  k32->system->stm32->custom( Ulow, U1,  U2, U3, U4, U5, Umax);// set CUSTOM profile

}// void bat_custom()
