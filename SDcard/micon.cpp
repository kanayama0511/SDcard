//
// Created by Owner on 25/05/20.
//
extern "C" {
    void app_main(void);
}

#include "SDCard.h"

void app_main() {
    SDCard sd;
    SPIPins pins = {11, 13, 12, 10}; // MOSI, MISO, SCK, CS

    if (sd.init(pins) == ESP_OK) {
        printf("SDカード初期化成功！\n");
    } else {
        printf("SDカード初期化失敗...\n");
    }
}
void app_main() {
    SDCard sd;
    SPIPins pins = {11, 13, 12, 10};  // MOSI, MISO, SCK, CS

    if (sd.init(pins) == ESP_OK) {
        printf("SDカード初期化成功！\n");

        sd.write_file("/log.txt", "CanSatデータ記録スタート！");
    } else {
        printf("SDカード初期化失敗...\n");
    }
}
