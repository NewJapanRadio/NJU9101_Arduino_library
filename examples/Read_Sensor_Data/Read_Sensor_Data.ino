#include <NJU9101.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  NJU9101.begin();
  // configure NJU9101
  config();

  Serial.println("Start Sensor Data Measurement");
}

void loop() {
  // put your main code here, to run repeatedly:

  uint8_t wd[1] = { };
  uint8_t rd[2] = { };
  // start temperature measurement
  wd[0] = CTRL_MEAS_SEL_AMP | CTRL_MEAS_ON;
  NJU9101.write(NJU9101_ADDRESS_CTRL, wd, 1);
  // wait end of measurement
  if (NJU9101.wait_eoc()) {
    NJU9101.read(NJU9101_ADDRESS_AMPDATA0, rd, 2);
  }
  else {
    config();
  }

  uint16_t raw = (rd[0] << 8) + rd[1];
  Serial.println(raw);

  delay(1000);
}

void config() {
  uint8_t wd[8] = { };
  uint8_t rd[2] = { };

  NJU9101.reset();
  NJU9101.awake_osc();

  // coefficient setting
  wd[0] = 0x2A;
  wd[1] = 0xAB;
  wd[2] = 0x2A;
  wd[3] = 0xAB;
  wd[4] = 0x2A;
  wd[5] = 0xAB;
  wd[6] = 0x2A;
  wd[7] = 0xAB;
  NJU9101.write(NJU9101_ADDRESS_SCAL1B0, wd, 8);
  // register configuration
  wd[0] = ANAGAIN_ADC_GAIN_X4 | ANAGAIN_PRE_GAIN_X4;
  wd[1] = BLKCONN0_BIASSWA_CONNECT | BLKCONN0_BIASSWB_CONNECT;
  wd[2] = BLKCONN1_OPA_BIAS_0P3V | BLKCONN1_OPB_BIAS_1P65V;
  wd[3] = BLKCONN2_BIASSWN_BIASRES | BLKCONN2_PAMPSEL_ENABLE;
  wd[4] = BLKCTRL_OSC_POWER_DOWN_AUTO |
          BLKCTRL_OPA_POWER_DOWN_NEVER |
          BLKCTRL_OPB_POWER_DOWN_NEVER |
          BLKCTRL_BIASRES_POWER_DOWN_NEVER;
  NJU9101.write(NJU9101_ADDRESS_ANAGAIN, wd, 5);
}
