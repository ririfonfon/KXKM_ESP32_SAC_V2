void effet() {
  if (type_effet == 0)
    do_effet_0();
  else if (type_effet == 11)
    do_effet_11();
  else if (type_effet == 12)
    do_effet_12();

  leds_show();
}//effet
