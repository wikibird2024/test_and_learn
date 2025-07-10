#pragma once

#include "driver/i2c.h"
#include "esp_err.h"

#define MY_I2C_PORT I2C_NUM_0
#define MY_I2C_SCL 22
#define MY_I2C_SDA 21
#define MY_I2C_FREQ_HZ 400000

sp_err_t my_i2c_init(void);
esp_err_t my_i2c_write(uint8_t dev_addr, uint8_t *data, size_t len);
esp_err_t my_i2c_read(Uint8_t dev_addr, uint8_t *data, size_t len);
