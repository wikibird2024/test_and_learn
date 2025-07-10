#include "my_i2c.h"

esp_err_t my_i2c_init(void) {
  i2c_config_t conf = {
      .mode = I2C_MODE_MASTER,
      .sda_io_num = MY_I2C_SDA_IO,
      .scl_io_num = MY_I2C_SCL_IO,
      .sda_pullup_en = GPIO_PULLUP_ENABLE,
      .scl_pullup_en = GPIO_PULLUP_ENABLE,
      .master.clk_speed = MY_I2C_FREQ_HZ,
  };
  ESP_ERROR_CHECK(i2c_param_config(MY_I2C_PORT, &conf));
  return i2c_driver_install(MY_I2C_PORT, conf.mode, 0, 0, 0);
}

esp_err_t my_i2c_write(uint8_t dev_addr, uint8_t *data, size_t len) {
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE,
                        true); // Shift one bit read/write to get read address
  i2c_master_write(cmd, data, len, true);
  i2c_master_stop(cmd);
  esp_err_t ret = i2c_master_cmd_begin(MY_I2C_PORT, cmd, pdMS_TO_TICKS(1000));
  i2c_cmd_link_delete(cmd);
  return ret;
}

esp_err_t my_i2c_read(uint8_t dev_addr, uint8_t *data, size_t len) {
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);
  i2c_master_read(cmd, data, len, I2C_MASTER_LAST_NACK);
  i2c_master_stop(cmd);
  esp_err_t ret = i2c_master_cmd_begin(MY_I2C_PORT, cmd, pdMS_TO_TICKS(1000));
  i2c_cmd_link_delete(cmd);
  return ret;
}
