# # TFT Gauge Display with Needle and Alert Indicator

This Arduino project displays a dynamic analog-style gauge using an ST7789 240x280 TFT display. The gauge includes:

- A sweeping needle that animates values from 0 to 100
- Tick marks every 45 degrees
- An alert indicator circle that turns red when the value exceeds a setpoint


## Hardware

- ST7789 240x280 TFT display
- Arduino-compatible board (tested with RP2040)

## Wiring

| Signal | Pin    |
|--------|--------|
| CS     | 17     |
| RST    | 20     |
| DC     | 21     |
| MOSI   | Board SPI MOSI |
| SCK    | Board SPI SCK  |
| GND    | GND    |
| VCC    | 3.3V |

## Dependencies

Install the following libraries via Library Manager:

- `Adafruit_GFX`
- `Adafruit_ST7789`
