# Arduino library for NJU9101

## Installation

1. Download a zip archive from [Release Page](https://github.com/NewJapanRadio/NJU9101_Arduino_library/releases)
2. Install to Arduino as library from the zip archive.  
   see also [Installing Additional Arduino Libraries](https://www.arduino.cc/en/Guide/Libraries)

## Example

```cpp
#include <NJU9101.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  NJU9101.begin();
  // reset NJU9101
  NJU9101.reset();

  Serial.println("Start Temperature Measurement");
}

void loop() {
  // put your main code here, to run repeatedly:

  uint8_t wd[1] = { };
  uint8_t rd[2] = { };
  // start temperature measurement
  wd[0] = CTRL_MEAS_SEL_TEMP | CTRL_MEAS_ON;
  NJU9101.write(NJU9101_ADDRESS_CTRL, wd, 1);
  // wait end of measurement
  if (NJU9101.wait_eoc()) {
    NJU9101.read(NJU9101_ADDRESS_TMPDATA0, rd, 2);
  }
  else {
    NJU9101.reset();
  }

  float t = rd[0] + rd[1] / 256.0;
  Serial.println(t, 2);

  delay(1000);
}
```
