void bat_custom() {
  // serial stm_32
  Serial.begin(115200, SERIAL_8N1);
  Serial.setTimeout(10);
  //init_seuil_bat
  sendSerialCommand(KXKM_STM32_Energy::SET_BATTERY_VOLTAGE_LOW, 21700);
  sendSerialCommand(KXKM_STM32_Energy::SET_BATTERY_VOLTAGE_1, 23100);
  sendSerialCommand(KXKM_STM32_Energy::SET_BATTERY_VOLTAGE_2, 23500);
  sendSerialCommand(KXKM_STM32_Energy::SET_BATTERY_VOLTAGE_3, 24500);
  sendSerialCommand(KXKM_STM32_Energy::SET_BATTERY_VOLTAGE_6, 29400);
}// void bat_custom()
