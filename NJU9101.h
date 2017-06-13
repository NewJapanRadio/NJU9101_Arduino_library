#ifndef __NJU9101_H__
#define __NJU9101_H__

#include <Arduino.h>
#include <Wire.h>

class NJU9101Class {
  private:
    uint8_t slaveAddress;

  public:
    /**
     * @brief Register Address
     */
    enum Address {
      CTRL      = 0x00,
      STATUS    = 0x01,
      AMPDATA0  = 0x02,
      AMPDATA1  = 0x03,
      AUXDATA0  = 0x04,
      AUXDATA1  = 0x05,
      TMPDATA0  = 0x06,
      TMPDATA1  = 0x07,
      ID        = 0x08,
      ROMADR0   = 0x09,
      ROMADR1   = 0x0A,
      ROMDATA   = 0x0B,
      ROMCTRL   = 0x0C,
      TEST      = 0x0D,
      ANAGAIN   = 0x0E,
      BLKCONN0  = 0x0F,
      BLKCONN1  = 0x10,
      BLKCONN2  = 0x11,
      BLKCTRL   = 0x12,
      ADCCONV   = 0x13,
      SYSPRESET = 0x14,
      SCAL1A0   = 0x15,
      SCAL1A1   = 0x16,
      SCAL2A0   = 0x17,
      SCAL2A1   = 0x18,
      SCAL3A0   = 0x19,
      SCAL3A1   = 0x1A,
      SCAL4A0   = 0x1B,
      SCAL4A1   = 0x1C,
      SCAL1B0   = 0x1D,
      SCAL1B1   = 0x1E,
      SCAL2B0   = 0x1F,
      SCAL2B1   = 0x20,
      SCAL3B0   = 0x21,
      SCAL3B1   = 0x22,
      SCAL4B0   = 0x23,
      SCAL4B1   = 0x24,
      OCAL1A0   = 0x25,
      OCAL1A1   = 0x26,
      OCAL2A0   = 0x27,
      OCAL2A1   = 0x28,
      OCAL3A0   = 0x29,
      OCAL3A1   = 0x2A,
      OCAL4A0   = 0x2B,
      OCAL4A1   = 0x2C,
      OCAL1B0   = 0x2D,
      OCAL1B1   = 0x2E,
      OCAL2B0   = 0x2F,
      OCAL2B1   = 0x30,
      OCAL3B0   = 0x31,
      OCAL3B1   = 0x32,
      OCAL4B0   = 0x33,
      OCAL4B1   = 0x34,
      SCAL1     = 0x35,
      SCAL2     = 0x36,
      SCAL3     = 0x37,
      OCAL1     = 0x38,
      OCAL2     = 0x39,
      OCAL3     = 0x3A,
      AUXSCAL0  = 0x3B,
      AUXSCAL1  = 0x3C,
      AUXOCAL0  = 0x3D,
      AUXOCAL1  = 0x3E,
      CHKSUM    = 0x3F
    };

    /**
     * @brief Constructor
     *
     * @param [in] slvAddrBase
     *      I2C slave address base
     */
    NJU9101Class(uint8_t slvAddrBase = 0x48);

    ~NJU9101Class();

    /**
     * @brief Initialize the NJU9101
     *
     * @param [in] slvAddr
     *      External pin setting part of I2C slave address
     *      @arg : 0 ~ 7
     */
    void begin(uint8_t slvAddr = 0x0);

    /**
     * @brief Disable the NJU9101
     */
    void end();

    /**
     * @brief Read register via I2C
     *
     * @param [in] address
     *      register address
     *
     * @param [out] data[]
     *      read data buffer
     *
     * @param [in] length
     *      read byte length
     */
    void read(Address address, uint8_t data[], size_t length);

    /**
     * @brief Write register via I2C
     *
     * @param [in] address
     *      register address
     *
     * @param [in] data[]
     *      write data
     *
     * @param [in] length
     *      write byte length
     */
    void write(Address address, uint8_t data[], size_t length);

    /**
     * @brief Reset the device
     */
    bool reset();

    /**
     * @brief Awake internal oscillator
     */
    bool awake_osc();

    /**
     * @brief Wait for end of conversion
     */
    bool wait_eoc();
};

/**
 * @defgroup ADDRESS Register Address
 * @{
 */
#define NJU9101_ADDRESS_CTRL      NJU9101Class::CTRL
#define NJU9101_ADDRESS_STATUS    NJU9101Class::STATUS
#define NJU9101_ADDRESS_AMPDATA0  NJU9101Class::AMPDATA0
#define NJU9101_ADDRESS_AMPDATA1  NJU9101Class::AMPDATA1
#define NJU9101_ADDRESS_AUXDATA0  NJU9101Class::AUXDATA0
#define NJU9101_ADDRESS_AUXDATA1  NJU9101Class::AUXDATA1
#define NJU9101_ADDRESS_TMPDATA0  NJU9101Class::TMPDATA0
#define NJU9101_ADDRESS_TMPDATA1  NJU9101Class::TMPDATA1
#define NJU9101_ADDRESS_ID        NJU9101Class::ID
#define NJU9101_ADDRESS_ROMADR0   NJU9101Class::ROMADR0
#define NJU9101_ADDRESS_ROMADR1   NJU9101Class::ROMADR1
#define NJU9101_ADDRESS_ROMDATA   NJU9101Class::ROMDATA
#define NJU9101_ADDRESS_ROMCTRL   NJU9101Class::ROMCTRL
#define NJU9101_ADDRESS_TEST      NJU9101Class::TEST
#define NJU9101_ADDRESS_ANAGAIN   NJU9101Class::ANAGAIN
#define NJU9101_ADDRESS_BLKCONN0  NJU9101Class::BLKCONN0
#define NJU9101_ADDRESS_BLKCONN1  NJU9101Class::BLKCONN1
#define NJU9101_ADDRESS_BLKCONN2  NJU9101Class::BLKCONN2
#define NJU9101_ADDRESS_BLKCTRL   NJU9101Class::BLKCTRL
#define NJU9101_ADDRESS_ADCCONV   NJU9101Class::ADCCONV
#define NJU9101_ADDRESS_SYSPRESET NJU9101Class::SYSPRESET
#define NJU9101_ADDRESS_SCAL1A0   NJU9101Class::SCAL1A0
#define NJU9101_ADDRESS_SCAL1A1   NJU9101Class::SCAL1A1
#define NJU9101_ADDRESS_SCAL2A0   NJU9101Class::SCAL2A0
#define NJU9101_ADDRESS_SCAL2A1   NJU9101Class::SCAL2A1
#define NJU9101_ADDRESS_SCAL3A0   NJU9101Class::SCAL3A0
#define NJU9101_ADDRESS_SCAL3A1   NJU9101Class::SCAL3A1
#define NJU9101_ADDRESS_SCAL4A0   NJU9101Class::SCAL4A0
#define NJU9101_ADDRESS_SCAL4A1   NJU9101Class::SCAL4A1
#define NJU9101_ADDRESS_SCAL1B0   NJU9101Class::SCAL1B0
#define NJU9101_ADDRESS_SCAL1B1   NJU9101Class::SCAL1B1
#define NJU9101_ADDRESS_SCAL2B0   NJU9101Class::SCAL2B0
#define NJU9101_ADDRESS_SCAL2B1   NJU9101Class::SCAL2B1
#define NJU9101_ADDRESS_SCAL3B0   NJU9101Class::SCAL3B0
#define NJU9101_ADDRESS_SCAL3B1   NJU9101Class::SCAL3B1
#define NJU9101_ADDRESS_SCAL4B0   NJU9101Class::SCAL4B0
#define NJU9101_ADDRESS_SCAL4B1   NJU9101Class::SCAL4B1
#define NJU9101_ADDRESS_OCAL1A0   NJU9101Class::OCAL1A0
#define NJU9101_ADDRESS_OCAL1A1   NJU9101Class::OCAL1A1
#define NJU9101_ADDRESS_OCAL2A0   NJU9101Class::OCAL2A0
#define NJU9101_ADDRESS_OCAL2A1   NJU9101Class::OCAL2A1
#define NJU9101_ADDRESS_OCAL3A0   NJU9101Class::OCAL3A0
#define NJU9101_ADDRESS_OCAL3A1   NJU9101Class::OCAL3A1
#define NJU9101_ADDRESS_OCAL4A0   NJU9101Class::OCAL4A0
#define NJU9101_ADDRESS_OCAL4A1   NJU9101Class::OCAL4A1
#define NJU9101_ADDRESS_OCAL1B0   NJU9101Class::OCAL1B0
#define NJU9101_ADDRESS_OCAL1B1   NJU9101Class::OCAL1B1
#define NJU9101_ADDRESS_OCAL2B0   NJU9101Class::OCAL2B0
#define NJU9101_ADDRESS_OCAL2B1   NJU9101Class::OCAL2B1
#define NJU9101_ADDRESS_OCAL3B0   NJU9101Class::OCAL3B0
#define NJU9101_ADDRESS_OCAL3B1   NJU9101Class::OCAL3B1
#define NJU9101_ADDRESS_OCAL4B0   NJU9101Class::OCAL4B0
#define NJU9101_ADDRESS_OCAL4B1   NJU9101Class::OCAL4B1
#define NJU9101_ADDRESS_SCAL1     NJU9101Class::SCAL1
#define NJU9101_ADDRESS_SCAL2     NJU9101Class::SCAL2
#define NJU9101_ADDRESS_SCAL3     NJU9101Class::SCAL3
#define NJU9101_ADDRESS_OCAL1     NJU9101Class::OCAL1
#define NJU9101_ADDRESS_OCAL2     NJU9101Class::OCAL2
#define NJU9101_ADDRESS_OCAL3     NJU9101Class::OCAL3
#define NJU9101_ADDRESS_AUXSCAL0  NJU9101Class::AUXSCAL0
#define NJU9101_ADDRESS_AUXSCAL1  NJU9101Class::AUXSCAL1
#define NJU9101_ADDRESS_AUXOCAL0  NJU9101Class::AUXOCAL0
#define NJU9101_ADDRESS_AUXOCAL1  NJU9101Class::AUXOCAL1
#define NJU9101_ADDRESS_CHKSUM    NJU9101Class::CHKSUM
/* @} ADDRESS */

/**
 * @defgroup REGISTER Register Values
 * @{
 */

/**
 * @defgroup CTRL_REG CTRL
 * @{
 */

/**
 * @name MEAS_SC
 * @{
 */
#define CTRL_MEAS_SC_SINGLE     (0)
#define CTRL_MEAS_SC_CONTINUOUS (1)
/* @} MEAS_SC */

/**
 * @name MEAS_SEL[1:0]
 * @{
 */
#define CTRL_MEAS_SEL_TEMP      (0 << 1)
#define CTRL_MEAS_SEL_AMP       (1 << 1)
#define CTRL_MEAS_SEL_AUX       (2 << 1)
/* @} MEAS_SEL[1:0] */

/**
 * @name MEAS
 * @{
 */
#define CTRL_MEAS_OFF           (0 << 3)
#define CTRL_MEAS_ON            (1 << 3)
/* @} MEAS */

/**
 * @name SENSCK[1:0]
 * @{
 */
#define CTRL_SENSCK_OFF         (0 << 4)
#define CTRL_SENSCK_PLUS        (1 << 4)
#define CTRL_SENSCK_MINUS       (2 << 4)
/* @} SENSCK[1:0] */

/**
 * @name RST
 * @{
 */
#define CTRL_RST                (1 << 6)
/* @} RST */

/* @} CTRL_REG */

/**
 * @defgroup STATUS_REG STATUS
 * @{
 */

/**
 * @name OFOV
 * @{
 */
#define STATUS_OFOV   (0x01)
/* @} OFOV */

/**
 * @name CERR
 * @{
 */
#define STATUS_CERR   (0x02)
/* @} CERR */

/**
 * @name OV
 * @{
 */
#define STATUS_OV     (0x04)
/* @} OV */

/**
 * @name RDYB
 * @{
 */
#define STATUS_RDYB   (0x08)
/* @} RDYB */

/**
 * @name CLKRUN
 * @{
 */
#define STATUS_CLKRUN (0x10)
/* @} CLKRUN */

/**
 * @name BOOT
 * @{
 */
#define STATUS_BOOT   (0x20)
/* @} BOOT */

/* @} STATUS_REG */

/**
 * @defgroup ROMCTRL_REG ROMCTRL
 * @{
 */

/**
 * @name ROMMODE[1:0]
 * @{
 */
#define ROMCTRL_ROMMODE_READ  (0)
#define ROMCTRL_ROMMODE_WRITE (1)
#define ROMCTRL_ROMMODE_LOAD  (2)
#define ROMCTRL_ROMMODE_STORE (3)
/* @} ROMMODE[1:0] */

/**
 * @name ROMACT
 * @{
 */
#define ROMCTRL_ROMACT        (1 << 2)
/* @} ROMACT */

/**
 * @name ROMSTOP
 * @{
 */
#define ROMCTRL_ROMSTOP       (1 << 3)
/* @} ROMSTOP */

/**
 * @name ROMBUSY
 * @{
 */
#define ROMCTRL_ROMBUSY       (1 << 4)
/* @} ROMBUSY */

/**
 * @name ROMERR
 * @{
 */
#define ROMCTRL_ROMERR        (1 << 5)
/* @} ROMERR */

/* @} ROMCTRL_REG */

/**
 * @defgroup ANAGAIN_REG ANAGAIN
 * @{
 */

/**
 * @name ADC_GAIN[1:0]
 * @{
 */
#define ANAGAIN_ADC_GAIN_X1 (0)
#define ANAGAIN_ADC_GAIN_X2 (1)
#define ANAGAIN_ADC_GAIN_X4 (2)
#define ANAGAIN_ADC_GAIN_X8 (3)
/* @} ADC_GAIN[1:0] */

/**
 * @name PRE_GAIN[1:0]
 * @{
 */
#define ANAGAIN_PRE_GAIN_X1 (0 << 2)
#define ANAGAIN_PRE_GAIN_X2 (1 << 2)
#define ANAGAIN_PRE_GAIN_X4 (2 << 2)
#define ANAGAIN_PRE_GAIN_X8 (3 << 2)
/* @} PRE_GAIN[1:0] */

/* @} ANAGAIN_REG */

/**
 * @defgroup BLKCONN0_REG BLKCONN0
 * @{
 */

/**
 * @name PRE_BIAS[3:0]
 * @{
 */
#define BLKCONN0_PRE_BIAS_GND    (0)
#define BLKCONN0_PRE_BIAS_0P3V   (1)
#define BLKCONN0_PRE_BIAS_0P4V   (2)
#define BLKCONN0_PRE_BIAS_0P5V   (3)
#define BLKCONN0_PRE_BIAS_0P6V   (4)
#define BLKCONN0_PRE_BIAS_0P7V   (5)
#define BLKCONN0_PRE_BIAS_0P8V   (6)
#define BLKCONN0_PRE_BIAS_0P9V   (7)
#define BLKCONN0_PRE_BIAS_1P0V   (8)
#define BLKCONN0_PRE_BIAS_1P1V   (9)
#define BLKCONN0_PRE_BIAS_1P2V   (10)
#define BLKCONN0_PRE_BIAS_1P3V   (11)
#define BLKCONN0_PRE_BIAS_1P4V   (12)
#define BLKCONN0_PRE_BIAS_1P5V   (13)
#define BLKCONN0_PRE_BIAS_1P6V   (14)
#define BLKCONN0_PRE_BIAS_1P7V   (15)
/* @} PRE_BIAS[3:0] */

/**
 * @name BIASSWB
 * @{
 */
#define BLKCONN0_BIASSWB_OPEN    (0 << 4)
#define BLKCONN0_BIASSWB_CONNECT (1 << 4)
/* @} BIASSWB */

/**
 * @name BIASSWA
 * @{
 */
#define BLKCONN0_BIASSWA_OPEN    (0 << 5)
#define BLKCONN0_BIASSWA_CONNECT (1 << 5)
/* @} BIASSWA */

/* @} BLKCONN0_REG */

/**
 * @defgroup BLKCONN1_REG BLKCONN1
 * @{
 */

/**
 * @name OPB_BIAS[4:0]
 * @{
 */
#define BLKCONN1_OPB_BIAS_GND   (0)
#define BLKCONN1_OPB_BIAS_0P25V (1)
#define BLKCONN1_OPB_BIAS_0P30V (2)
#define BLKCONN1_OPB_BIAS_0P35V (3)
#define BLKCONN1_OPB_BIAS_0P40V (4)
#define BLKCONN1_OPB_BIAS_0P45V (5)
#define BLKCONN1_OPB_BIAS_0P50V (6)
#define BLKCONN1_OPB_BIAS_0P55V (7)
#define BLKCONN1_OPB_BIAS_0P60V (8)
#define BLKCONN1_OPB_BIAS_0P65V (9)
#define BLKCONN1_OPB_BIAS_0P70V (10)
#define BLKCONN1_OPB_BIAS_0P75V (11)
#define BLKCONN1_OPB_BIAS_0P80V (12)
#define BLKCONN1_OPB_BIAS_0P85V (13)
#define BLKCONN1_OPB_BIAS_0P90V (14)
#define BLKCONN1_OPB_BIAS_0P95V (15)
#define BLKCONN1_OPB_BIAS_1P00V (16)
#define BLKCONN1_OPB_BIAS_1P05V (17)
#define BLKCONN1_OPB_BIAS_1P10V (18)
#define BLKCONN1_OPB_BIAS_1P15V (19)
#define BLKCONN1_OPB_BIAS_1P20V (20)
#define BLKCONN1_OPB_BIAS_1P25V (21)
#define BLKCONN1_OPB_BIAS_1P30V (22)
#define BLKCONN1_OPB_BIAS_1P35V (23)
#define BLKCONN1_OPB_BIAS_1P40V (24)
#define BLKCONN1_OPB_BIAS_1P45V (25)
#define BLKCONN1_OPB_BIAS_1P50V (26)
#define BLKCONN1_OPB_BIAS_1P55V (27)
#define BLKCONN1_OPB_BIAS_1P60V (28)
#define BLKCONN1_OPB_BIAS_1P65V (29)
#define BLKCONN1_OPB_BIAS_1P70V (30)
#define BLKCONN1_OPB_BIAS_1P75V (31)
/* @} OPB_BIAS[4:0] */

/**
 * @name OPA_BIAS[2:0]
 * @{
 */
#define BLKCONN1_OPA_BIAS_GND   (0 << 5)
#define BLKCONN1_OPA_BIAS_0P3V  (1 << 5)
#define BLKCONN1_OPA_BIAS_0P5V  (2 << 5)
#define BLKCONN1_OPA_BIAS_0P7V  (3 << 5)
#define BLKCONN1_OPA_BIAS_1P0V  (4 << 5)
#define BLKCONN1_OPA_BIAS_1P3V  (5 << 5)
#define BLKCONN1_OPA_BIAS_1P5V  (6 << 5)
#define BLKCONN1_OPA_BIAS_1P7V  (7 << 5)
/* @} OPA_BIAS[4:0] */

/* @} BLKCONN1_REG */

/**
 * @defgroup BLKCONN2_REG BLKCONN2
 * @{
 */

/**
 * @name VREFSEL
 * @{
 */
#define BLKCONN2_VREFSEL_INTERNAL        (0)
#define BLKCONN2_VREFSEL_EXTERNAL        (1)
/* @} VREFSEL */

/**
 * @name BIASSEL
 * @{
 */
#define BLKCONN2_BIASSEL_INTERNAL        (0 << 1)
#define BLKCONN2_BIASSEL_EXTERNAL        (1 << 1)
/* @} BIASSEL */

/**
 * @name PAMPSEL
 * @{
 */
#define BLKCONN2_PAMPSEL_DISABLE         (0 << 2)
#define BLKCONN2_PAMPSEL_ENABLE          (1 << 2)
/* @} PAMPSEL */

/**
 * @name BIASSWN
 * @{
 */
#define BLKCONN2_BIASSWN_OBP_AUX         (0 << 3)
#define BLKCONN2_BIASSWN_BIASRES         (1 << 3)
/* @} BIASSWN */

/**
 * @name ANASW
 * @{
 */
#define BLKCONN2_ANASW_OFF               (0 << 4)
#define BLKCONN2_ANASW_ON                (1 << 4)
/* @} ANASW */

/**
 * @name INPSWB
 * @{
 */
#define BLKCONN2_INPSWB_GND              (0 << 5)
#define BLKCONN2_INPSWB_BINP             (1 << 5)
/* @} INPSWB */

/**
 * @name INPSWA
 * @{
 */
#define BLKCONN2_INPSWA_GND              (0 << 6)
#define BLKCONN2_INPSWA_AINP             (1 << 6)
/* @} INPSWA */

/**
 * @name PREMODE
 * @{
 */
#define BLKCONN2_PREMODE_NON_INVERTED    (0 << 7)
#define BLKCONN2_PREMODE_INSTRUMENTATION (1 << 7)
/* @} PREMODE */

/* @} BLKCONN2_REG */

/**
 * @defgroup BLKCTRL_REG BLKCTRL
 * @{
 */

/**
 * @name TEMP_SENSOR_POWER_DOWN
 * @{
 */
#define BLKCTRL_TEMP_SENSOR_POWER_DOWN_AUTO  (0)
#define BLKCTRL_TEMP_SENSOR_POWER_DOWN_NEVER (1)
/* @} TEMP_SENSOR_POWER_DOWN */

/**
 * @name ADC_POWER_DOWN
 * @{
 */
#define BLKCTRL_ADC_POWER_DOWN_AUTO          (0<<1)
#define BLKCTRL_ADC_POWER_DOWN_NEVER         (1<<1)
/* @} ADC_POWER_DOWN */

/**
 * @name INTVREF_POWER_DOWN
 * @{
 */
#define BLKCTRL_INTVREF_POWER_DOWN_AUTO      (0<<2)
#define BLKCTRL_INTVREF_POWER_DOWN_NEVER     (1<<2)
/* @} INTVREF_POWER_DOWN */

/**
 * @name PREAMP_POWER_DOWN
 * @{
 */
#define BLKCTRL_PREAMP_POWER_DOWN_AUTO       (0<<3)
#define BLKCTRL_PREAMP_POWER_DOWN_NEVER      (1<<3)
/* @} PREAMP_POWER_DOWN */

/**
 * @name OSC_POWER_DOWN
 * @{
 */
#define BLKCTRL_OSC_POWER_DOWN_AUTO          (0<<4)
#define BLKCTRL_OSC_POWER_DOWN_NEVER         (1<<4)
/* @} OSC_POWER_DOWN */

/**
 * @name OPA_POWER_DOWN
 * @{
 */
#define BLKCTRL_OPA_POWER_DOWN_AUTO          (0<<5)
#define BLKCTRL_OPA_POWER_DOWN_NEVER         (1<<5)
/* @} OPA_POWER_DOWN */

/**
 * @name OPB_POWER_DOWN
 * @{
 */
#define BLKCTRL_OPB_POWER_DOWN_AUTO          (0<<6)
#define BLKCTRL_OPB_POWER_DOWN_NEVER         (1<<6)
/* @} OPB_POWER_DOWN */

/**
 * @name BIASRES_POWER_DOWN
 * @{
 */
#define BLKCTRL_BIASRES_POWER_DOWN_AUTO      (0<<7)
#define BLKCTRL_BIASRES_POWER_DOWN_NEVER     (1<<7)
/* @} BIASRES_POWER_DOWN */

/* @} BLKCTRL_REG */

/**
 * @defgroup ADCONV_REG ADCONV
 * @{
 */

/**
 * @name OSR[1:0]
 * @{
 */
#define ADCCONV_OSR_00         (0)
#define ADCCONV_OSR_01         (1)
#define ADCCONV_OSR_10         (2)
#define ADCCONV_OSR_11         (3)
/* @} OSR[1:0] */

/**
 * @name REJ[1:0]
 * @{
 */
#define ADCCONV_REJ_50_60HZ    (0<<2)
#define ADCCONV_REJ_50HZ       (1<<2)
#define ADCCONV_REJ_60HZ       (2<<2)
/* @} REJ[1:0] */

/**
 * @name CLKDIV[1:0]
 * @{
 */
#define ADCCONV_CLKDIV_FOSC_2  (0 << 4)
#define ADCCONV_CLKDIV_FOSC_4  (1 << 4)
#define ADCCONV_CLKDIV_FOSC_8  (2 << 4)
#define ADCCONV_CLKDIV_FOSC_16 (3 << 4)
/* @} CLKDIV[1:0] */

/**
 * @name ADCCHOP
 * @{
 */
#define ADCCONV_ADCCHOP_OFF    (0 << 6)
#define ADCCONV_ADCCHOP_ON     (1 << 6)
/* @} ADCCHOP */

/* @} ADCONV_REG */

/**
 * @defgroup SYSPRESET SYSPRESET
 * @{
 */

/**
 * @name AMPAUX
 * @{
 */
#define SYSPRESET_AMPAUX_NORMAL              (0)
#define SYSPRESET_AMPAUX_SWAP                (1)
/* @} AMPAUX */

/**
 * @name RDYBMODE[1:0]
 * @{
 */
#define SYSPRESET_RDYBMODE_STATUS            (0 << 4)
#define SYSPRESET_RDYBMODE_STATUS_OPEN_DRAIN (1 << 4)
#define SYSPRESET_RDYBMODE_GPIO              (2 << 4)
/* @} RDYBMODE[1:0] */

/**
 * @name RDYBDAT
 * @{
 */
#define SYSPRESET_RDYBDAT_L                  (0 << 6)
#define SYSPRESET_RDYBDAT_H                  (1 << 6)
/* @} RDYBDAT */

/**
 * @name RDYBOE
 * @{
 */
#define SYSPRESET_RDYBOE_INPUT               (0 << 7)
#define SYSPRESET_RDYBOE_OUTPUT              (1 << 7)
/* @} RDYBOE */

/* @} SYSPRESET_REG */

/* @} REGISTER */

extern NJU9101Class NJU9101;

#endif // __NJU9101_H__
