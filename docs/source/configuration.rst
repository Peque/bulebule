*************
Configuration
*************


Microcontroller
===============

The microcontroller used is an `STM32F411CEU6`_. For more information have a
look at the `STM32F411xx Reference Manual`_.

The following considerations have been taken into account for the
microcontroller connections:

- Pins are 5V tolerant except when in analog mode or oscillator mode (for PC14,
  PC15, PH0 and PH1)
- PC13, PC14, PC15 and PI8 are supplied through the power switch. Since the
  switch only sinks a limited amount of current (3 mA), the use of GPIOs PC13
  to PC15 and PI8 in output mode is limited:

  - The speed should not exceed 2 MHz with a maximum load of 30 pF
  - These I/Os must not be used as a current source (e.g. to drive an LED)

Notes:

- Receivers are connected to PA0..PA3, with ADC and the 32-bits TIM5
- Air602 to PA4..PA7, with SPI1 at max. 50 MHx (also able to reprogram the flash memory)
- Driver to PA8..PA11, with the advanced timer TIM1
- Battery and motor voltages to PB0 and PB1
- Encoder 0 to PB4 and PB5, with the 16-bits TIM3 (channels 1 and 2)
- Encoder 1 to PB6 and PB7, with the 16-bits TIM4 (channels 1 and 2)
- Speaker to PB8, with TIM10_CH1
- Gyro to PB12..PB15, with SPI2 at max. 25 MHz

=========  ===========  ================================  =============================================================================
Name       Using        Connected to                      Functions
=========  ===========  ================================  =============================================================================
PA0        ADC1_0       Receiver front right              ADC1_0, WKUP1, TIM2_CH1/TIM2_ET, TIM5_CH1, USART2_CTS
PA1        ADC1_1       Receiver side right               ADC1_1, TIM2_CH2, TIM5_CH2, SPI4_MOSI/I2S4_SD, USART2_RTS
PA2        ADC1_2       Receiver side left                ADC1_2, TIM2_CH3, TIM5_CH3, TIM9_CH1, I2S2_CKIN, USART2_TX
PA3        ADC1_3       Receiver front left               ADC1_3, TIM2_CH4, TIM5_CH4, TIM9_CH2, I2S2_MCK, USART2_RX
PA4        SPI1_NSS     Air602 RTS (SPI-CS)               ADC1_4, SPI1_NSS/I2S1_WS, SPI3_NSS/I2S3_WS, USART2_CK
PA5        SPI1_SCK     Air602 PB8 (SPI-CK)               ADC1_5, TIM2_CH1/TIM2_ET, SPI1_SCK/I2S1_CK
PA6        SPI1_MISO    Air602 TX1 (SPI-DO)               ADC1_6, TIM1_BKIN, TIM3_CH1, SPI1_MISO, I2S2_MCK, SDIO_CMD
PA7        SPI1_MOSI    Air602 RX1 (SPI-DI)               ADC1_7, TIM1_CH1N, TIM3_CH2, SPI1_MOSI/I2S1_SD
PA8        TIM1_CH1     Motor driver IN4 (right)          MCO_1, TIM1_CH1, I2C3_SCL, USART1_CK, USB_FS_SOF, SDIO_D1
PA9        TIM1_CH2     Motor driver IN3 (right)          OTG_FS_VBUS, TIM1_CH2, I2C3_SMBA, USART1_TX, USB_FS_VBUS, SDIO_D2
PA10       TIM1_CH3     Motor driver IN2 (left)           TIM1_CH3, SPI5_MOSI/I2S5_SD, USART1_RX, USB_FS_ID
PA11       TIM1_CH4     Motor driver IN1 (left)           TIM1_CH4, SPI4_MISO, USART1_CTS, USART6_TX, USB_FS_DM
PA12       Output       Emitter front left                TIM1_ETR, SPI5_MISO, USART1_RTS, USART6_RX, USB_FS_DP
PA15       Output       Emitter side right                JTDI, TIM2_CH1/TIM2_ETR, SPI1_NSS/I2S1_WS, SPI3_NSS/I2S3_WS, USART1_TX
PB0        ADC1_8       Battery voltage                   ADC1_8, TIM1_CH2N, TIM3_CH3, SPI5_SCK/I2S5_CK
PB1        ADC1_9       Motor voltage                     ADC1_9, TIM1_CH3N, TIM3_CH4, SPI5_NSS/I2S5_WS
PB2        Input        User button                       BOOT1, I/O
PB3        Output       Emitter front right               JTDO-SWO, TIM2_CH2, SPI1_SCK/I2S1_CK, SPI3_SCK/I2S3_CK, USART1_RX, I2C2_SDA
PB4        TIM3_CH1     Encoder left, channel A           JTRST, TIM3_CH1, SPI1_MISO, SPI3_MISO, I2S3ext_SD, I2C3_SDA, SDIO_D0
PB5        TIM3_CH2     Encoder left, channel B           TIM3_CH2, I2C1_SMBA, SPI1_MOSI/I2S1_SD, SPI3_MOSI/I2S3_SD, SDIO_D3
PB6        TIM4_CH1     Encoder right, channel B          TIM4_CH1, I2C1_SCL, USART1_TX
PB7        TIM4_CH2     Encoder right, channel A          TIM4_CH2, I2C1_SDA, USART1_RX, SDIO_D0
PB8        TIM10_CH1    Speaker                           TIM4_CH3, TIM10_CH1, I2C1_SCL, SPI5_MOSI/I2S5_SD, I2C3_SDA, SDIO_D4
PB9        TIM11_CH1    User LED                          TIM4_CH4, TIM11_CH1, I2C1_SDA, SPI2_NSS/I2S2_WS, I2C2_SDA, SDIO_D5
PB10       Output       Emitter side left                 TIM2_CH3, I2C2_SCL, SPI2_SCK/I2S2_CK, I2S3_MCK, SDIO_D7
PB12       SPI2_NSS     Gyroscope NCS (SPI-CS)            TIM1_BKIN, I2C2_SMBA, SPI2_NSS/I2S2_WS, SPI4_NSS/I2S4_WS, SPI3_SCK/I2S3_CK
PB13       SPI2_SCK     Gyroscope SCL (SPI-SCLK)          TIM1_CH1N, SPI2_SCK/I2S2_CK, SPI4_SCK/I2S4_CK
PB14       SPI2_MISO    Gyroscope AD0 (SPI-SDO)           TIM1_CH2N, SPI2_MISO, I2S2ext_SD, SDIO_D6
PB15       SPI2_MOSI    Gyroscope SDA (SPI-SDI)           RTC_50Hz, TIM1_CH3N, SPI2_MOSI/I2S2_SD, SDIO_CK
PC13       -            *Not connected*                   RTC_AMP1, RTC_OUT, RTC_TS
PC14       -            *Not connected*                   OSC32_IN
PC15       -            *Not connected*                   OSC32_OUT
=========  ===========  ================================  =============================================================================


Clocks
======

The microcontroller is configured to use the External High Speed clock (HSE),
at 8 MHz, and set the SYSCLK at 72 MHz. The AHB is at 72 MHz as well (the AHB
divider is set to 1 by default). The AHB clock is used to generate the SysTick
interruptions. For more information have a look at the `STM32F10xxx Reference
Manual`_.


Encoders
========

Timers 1 and 4 are configured to read quadrature encoders (and thus, connected
to the `IE2-512 encoder`_ channels A and B). They are both configured to count
on both TI1 and TI2 edges.


Gyroscope
=========

Gyros are selected as the clock source for accuracy (versus the internal
relaxation oscillator suitable for lower power consumption when only
accelerometer is being used).

The MPU-6500 gyro features the following SPI operational features:

- Data is delivered MSB first and LSB last.
- Data is latched on the rising edge of SCLK.
- Data should be transitioned on the falling edge of SCLK.
- The maximum frequency of SCLK is 1 MHz. Although the sensor and interrupt
  registers may be read using SPI at 20 MHz.
- Read/write operations are completed in 16+ cycles (2+ bytes).
- First byte contains the SPI address, and the following the SPI data.
- First bit of the first byte contains the Read (1) / Write (0) bit.
- The following 7 bits contain the Register Address.
- In cases of multiple-byte read/writes, data is two or more bytes.

=====  ========  ==============================
Pin    Function  Connected to
=====  ========  ==============================
SCL    SPI-SCLK  *Defined in Bluepill pinout*
SDA    SPI-SDI   *Defined in Bluepill pinout*
EDA    N/A       *Not connected*
ECL    N/A       *Not connected*
AD0    SPI-SDO   *Defined in Bluepill pinout*
INT    N/A       *Not connected*
NCS    SPI-CS    *Defined in Bluepill pinout*
FSYNC  N/A       *Not connected*
VCC    Power     5V
GND    Power     GND
=====  ========  ==============================


Motor driver
============

====  ========================================
Pin   Connected to
====  ========================================
IN1   *Defined in Bluepill pinout*
IN2   *Defined in Bluepill pinout*
IN3   *Defined in Bluepill pinout*
IN4   *Defined in Bluepill pinout*
OUT1  Motor left + (pin 2)
OUT2  Motor left - (pin 1)
OUT3  Motor right - (pin 1)
OUT4  Motor right + (pin 2)
EEP   50 kΩ pull-up to 5V (J2 jumper is open)
ULT   *Not connected*
VCC   Vmot
GND   GND
====  ========================================


Exceptions
==========

The configuration for interruptions (IRQ) and SysTick exceptions has been
deduced taking into account that:

- The priority is configurable, the exception and the IRQ numbers are fixed.

- If the software does not configure any priority, then all exceptions with a
  configurable priority have a priority of 0. We didn't find any reference on
  the documentation but for experience it seems that by default SysTick
  exception has higher priority than any interruption.

- For System Handlers, the lowest priority value has precedence over the
  lowest exception number value.

- For Interrupt service routines (ISR) the precedence is: lowest group priority
  value, lowest subpriority value and lowest IRQ number value. For now, there
  are not any subpriority value configured for this project.

- The preemption happens just for higher priority exceptions (nothing to do
  with exception number or subpriority).

For more information have a look at the `STM32F10xxx/20xxx/21xxx/L1xxxx
Cortex®-M3 programming manual`_.

==========  ========  =========  =======  ========  ======================
Exceptions  Handler   Excep num  IRQ num  Priority  Functionality
==========  ========  =========  =======  ========  ======================
SysTick     System    15         -1       1         Control and algorithm
ADC1_2      ISR       N/A        18       1         Battery low level
TIM1_UP     ISR       N/A        25       0         Infrared state machine
USART3      ISR       N/A        39       1         Bluetooth
==========  ========  =========  =======  ========  ======================


References
==========

.. target-notes::

.. _`HC-05 serial bluetooth`:
   https://athena-robots.readthedocs.io/en/latest/hc05_bluetooth.html
.. _`STM32F405RGT6`:
   https://www.st.com/resource/en/datasheet/stm32f411ce.pdf
.. _`STM32F411xx reference manual`:
   https://www.st.com/resource/en/reference_manual/dm00119316.pdf
.. _`IE2-512 encoder`:
   https://www.faulhaber.com/fileadmin/Import/Media/EN_IE2-1024_DFF.pdf
