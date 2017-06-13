#include <BLE_API.h>
#include <NJU9101.h>

#define TXRX_BUF_LEN 20

BLE ble;
Ticker ticker;

static const uint8_t local_name[] = "NJU9101";
static const uint8_t device_name[] = "CO Sensor";

static boolean meas_enabled = true;

// The UUID of service and characteristics
// meaning of `| 0xC0` is that
// "Static Address" requires that 2MSB is `0b11`.
// see also: Bluetooth Core Spec. v4.1, Vol 3, Part C, 10.8.1
static const uint8_t nju9101_uuid[]     = { 0xD1, 0xA9, 0x68, 0xB0, 0x42, 0xBA, 0x11, 0xE7, 0xFF, 0xFF,
                                            (NRF_FICR->DEVICEADDR[1] >>  8) & 0xFF | 0xC0,
                                            (NRF_FICR->DEVICEADDR[1]      ) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >> 24) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >> 16) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >>  8) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0]      ) & 0xFF
                                          };
static const uint8_t service1_uuid[]    = { 0xD1, 0xA9, 0x68, 0xB0, 0x42, 0xBA, 0x11, 0xE7, 0x00, 0x00,
                                            (NRF_FICR->DEVICEADDR[1] >>  8) & 0xFF | 0xC0,
                                            (NRF_FICR->DEVICEADDR[1]      ) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >> 24) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >> 16) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >>  8) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0]      ) & 0xFF
                                          };
static const uint8_t service1_tx_uuid[] = { 0xD1, 0xA9, 0x68, 0xB0, 0x42, 0xBA, 0x11, 0xE7, 0x00, 0x01,
                                            (NRF_FICR->DEVICEADDR[1] >>  8) & 0xFF | 0xC0,
                                            (NRF_FICR->DEVICEADDR[1]      ) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >> 24) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >> 16) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >>  8) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0]      ) & 0xFF
                                          };
static const uint8_t service1_rx_uuid[] = { 0xD1, 0xA9, 0x68, 0xB0, 0x42, 0xBA, 0x11, 0xE7, 0x00, 0x02,
                                            (NRF_FICR->DEVICEADDR[1] >>  8) & 0xFF | 0xC0,
                                            (NRF_FICR->DEVICEADDR[1]      ) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >> 24) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >> 16) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0] >>  8) & 0xFF,
                                            (NRF_FICR->DEVICEADDR[0]      ) & 0xFF
                                          };
uint8_t tx_value[TXRX_BUF_LEN] = { };
uint8_t rx_value[TXRX_BUF_LEN] = { };

// Create characteristic
GattCharacteristic characteristic1(service1_tx_uuid, tx_value, 1, TXRX_BUF_LEN, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE_WITHOUT_RESPONSE);
GattCharacteristic characteristic2(service1_rx_uuid, rx_value, 1, TXRX_BUF_LEN, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY);
GattCharacteristic *nju9101Chars[] = {&characteristic1, &characteristic2};
GattService nju9101Service(service1_uuid, nju9101Chars, sizeof(nju9101Chars) / sizeof(GattCharacteristic *));

void connectionCallBack(const Gap::ConnectionCallbackParams_t *params) {
  ble.stopAdvertising();
  ticker.attach(m_status_check_handle, 5);
}
void disconnectionCallBack(const Gap::DisconnectionCallbackParams_t *params) {
  ticker.detach();
  ble.startAdvertising();
}

void gattServerWriteCallBack(const GattWriteCallbackParams *Handler) {
  uint8_t buf[TXRX_BUF_LEN];
  uint16_t bytesRead, index;

  if (Handler->handle == characteristic1.getValueAttribute().getHandle()) {
    ble.readCharacteristicValue(characteristic1.getValueAttribute().getHandle(), buf, &bytesRead);
    if (buf[0] == 0x00) {
      if (buf[1] == 0x00) {
        meas_enabled = false;
      }
      else {
        meas_enabled = true;
      }
    }
  }
}

void m_status_check_handle() {
  uint8_t buf[4] = { };

  if (meas_enabled) {
    meas(buf);
    ble.updateCharacteristicValue(characteristic2.getValueAttribute().getHandle(), buf, 4);
  }
}

void setup() {
  // put your setup code here, to run once:

  // for power consumption
  NRF_POWER->DCDCEN = 0x00000001;

  int uuid_len = 16; // sizeof(nju9101_uuid)/sizeof(uint8_t) = 16
  uint8_t uuid[uuid_len];
  for (int i = 0; i < uuid_len; i++) {
    uuid[i] = nju9101_uuid[uuid_len-1-i];
  }

  ble.init();
  ble.onConnection(connectionCallBack);
  ble.onDisconnection(disconnectionCallBack);
  ble.onDataWritten(gattServerWriteCallBack);

  // setup adv_data and srp_data
  ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED);
  ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME,
                                   local_name, sizeof(local_name) - 1);
  ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_128BIT_SERVICE_IDS,
                                   (const uint8_t *)uuid, sizeof(uuid));
  // set adv_type
  ble.setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
  // add service
  ble.addService(nju9101Service);
  // set device name
  ble.setDeviceName(device_name);
  // set tx power,valid values are -40, -20, -16, -12, -8, -4, 0, 4
  ble.setTxPower(-16);
  // set adv_interval, 5120ms in multiples of 0.625ms.
  ble.setAdvertisingInterval(3200);
  // set adv_timeout, in seconds
  ble.setAdvertisingTimeout(0);
  // start advertising
  ble.startAdvertising();

  NJU9101.begin();
  config();

  // for power consumption
  NRF_TWI0->ENABLE = TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos;
}

void loop() {
  // put your main code here, to run repeatedly:

  ble.waitForEvent();
}

void config() {
  uint8_t wd[8] = { };
  uint8_t rd[2] = { };

  NRF_TWI0->ENABLE = TWI_ENABLE_ENABLE_Enabled << TWI_ENABLE_ENABLE_Pos;

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
  wd[0] = BLKCONN0_BIASSWA_CONNECT | BLKCONN0_BIASSWB_CONNECT;
  wd[1] = BLKCONN1_OPA_BIAS_GND | BLKCONN1_OPB_BIAS_GND; // TODO : determine bias level
  wd[2] = BLKCONN2_BIASSWN_BIASRES | BLKCONN2_PAMPSEL_ENABLE;
  wd[3] = BLKCTRL_OSC_POWER_DOWN_AUTO |
          BLKCTRL_OPA_POWER_DOWN_NEVER |
          BLKCTRL_OPB_POWER_DOWN_NEVER |
          BLKCTRL_BIASRES_POWER_DOWN_NEVER;
  NJU9101.write(NJU9101_ADDRESS_BLKCONN0, wd, 4);

  NRF_TWI0->ENABLE = TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos;
}

void meas(uint8_t *buf) {
  uint8_t wd[1] = { };

  NRF_TWI0->ENABLE = TWI_ENABLE_ENABLE_Enabled << TWI_ENABLE_ENABLE_Pos;

  // measure temperature
  wd[0] = CTRL_MEAS_SEL_TEMP | CTRL_MEAS_ON;
  NJU9101.write(NJU9101_ADDRESS_CTRL, wd, 1);
  if (NJU9101.wait_eoc()) {
    NJU9101.read(NJU9101_ADDRESS_TMPDATA0, buf, 2);
  }
  else {
    config();
  }

  // measure sensor data
  wd[0] = CTRL_MEAS_SEL_AMP | CTRL_MEAS_ON;
  NJU9101.write(NJU9101_ADDRESS_CTRL, wd, 1);
  if (NJU9101.wait_eoc()) {
    NJU9101.read(NJU9101_ADDRESS_AMPDATA0, &buf[2], 2);
  }
  else {
    config();
  }

  NRF_TWI0->ENABLE = TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos;
}
