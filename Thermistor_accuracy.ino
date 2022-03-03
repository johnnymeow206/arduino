int16_t ADCvalue;

void setup(){
  Serial.begin(9600);
}

void loop() {
  ADCvalue = analogRead(A0);
  Thermistor(ADCvalue);
}

void Thermistor(int16_t ADCvalue)
{
  double T, Temp;
  double T0 = 301.15;  // 273.15 + 28 (room temperature) 室溫換成絕對溫度
  double lnR;
  int16_t R;          // Thermistor resistence 
  int16_t R0 = 8805;  // calibrated by reading R at room temperature (=28 degree Celsius )
  int16_t B  = 3950;
  int16_t Pullup = 9930; // 10K ohm
  
  // R / (Pullup + R)   = adc / 4096
  V = ReadVoltage(A0); // ADC accuracy improved for ESP32
  R = 9990 * V / (5 - V); // assuming 9990 is the measured resistance of 10K resistor by a multi-meter.
  
  // B = (log(R) - log(R0)) / (1/T - 1/T0) 
  T = 1 / (1/T0 + (log(R)-log(R0)) / B ); // R0=8805 measured in room tempature at 28 celsius degree.
  Temp = T - 273.15;  
    
  Serial.println(Temp);
}
