//
// Created by Owner on 25/05/20.
//
#include "SDCard.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdspi_host.h"
#include "esp_log.h"

static const char* TAG = "SDCard";

SDCard::SDCard() : mount_point("/sdcard") {}

esp_err_t SDCard::init(SPIPins p, const char* mount) {
    pins = p;
    mount_point = mount;

    esp_vfs_fat_sdspi_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = pins.MOSI,
        .miso_io_num = pins.MISO,
        .sclk_io_num = pins.SCK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    spi_bus_initialize(SPI2_HOST, &bus_cfg, SDSPI_DEFAULT_DMA);

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.host_id = SPI2_HOST;
    slot_config.gpio_cs = pins.CS;

    sdmmc_card_t* card;
    return esp_vfs_fat_sdspi_mount(mount_point, &slot_config, &mount_config, &card);
}
#include <stdio.h>   // ← FILE型を使うときに必要
#include <string.h>  // ← strcatやstrlenを使う場合に便利

esp_err_t SDCard::write_file(const char* filename, const char* data) {
    std::string path = std::string(mount_point) + filename;
    FILE* f = fopen(path.c_str(), "w");  // "w" は書き込みモード（上書き）

    if (!f) {
        ESP_LOGE(TAG, "ファイルを開けませんでした: %s", path.c_str());
        return ESP_FAIL;
    }

    fprintf(f, "%s\n", data);  // 文字列を書き込む
    fclose(f);                 // 終わったら閉じる
    ESP_LOGI(TAG, "ファイルに書き込みました: %s", path.c_str());

    return ESP_OK;
}
