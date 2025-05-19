#pragma once

#include "driver/sdspi_host.h"
#include "esp_err.h"

struct SPIPins {
    int MOSI;
    int MISO;
    int SCK;
    int CS;
};

class SDCard {
public:
    SDCard();
    esp_err_t init(SPIPins pins, const char* mount_point = "/sdcard");

private:
    SPIPins pins;
    const char* mount_point;
};
esp_err_t write_file(const char* filename, const char* data);
