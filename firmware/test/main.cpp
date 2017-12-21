#include <cstdarg>

#include <Wire.h>
#include <FuelGauge.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <SerialFlash.h>
#include <WiFi101.h>
#include <SD.h>

const uint8_t PIN_RADIO_CS = 5;
const uint8_t PIN_RADIO_DIO0 = 2;
const uint8_t PIN_SD_CS = 12;
const uint8_t PIN_FLASH_CS = 4;
const uint8_t PIN_WINC_CS = 7;
const uint8_t PIN_WINC_IRQ = 9;
const uint8_t PIN_WINC_RST = 10;
const uint8_t PIN_WINC_EN = 11;
const uint8_t PIN_WINC_WAKE = 8;

#define DEBUG_LINE_MAX 256

void debugf(const char *f, ...) {
    char buffer[DEBUG_LINE_MAX];
    va_list args;

    va_start(args, f);
    vsnprintf(buffer, DEBUG_LINE_MAX, f, args);
    va_end(args);

    Serial5.print(buffer);
}

void debugfln(const char *f, ...) {
    char buffer[DEBUG_LINE_MAX];
    va_list args;

    va_start(args, f);
    auto w = vsnprintf(buffer, DEBUG_LINE_MAX - 2, f, args);
    va_end(args);

    buffer[w] = '\r';
    buffer[w + 1] = '\n';
    buffer[w + 2] = 0;

    Serial5.print(buffer);
}

class Check {
private:
    const char * id2chip(const unsigned char *id) {
        if (id[0] == 0xEF) {
            // Winbond
            if (id[1] == 0x40) {
                if (id[2] == 0x14) return "W25Q80BV";
                if (id[2] == 0x15) return "W25Q16DV";
                if (id[2] == 0x17) return "W25Q64FV";
                if (id[2] == 0x18) return "W25Q128FV";
                if (id[2] == 0x19) return "W25Q256FV";
            }
        }
        if (id[0] == 0x01) {
            // Spansion
            if (id[1] == 0x02) {
                if (id[2] == 0x16) return "S25FL064A";
                if (id[2] == 0x19) return "S25FL256S";
                if (id[2] == 0x20) return "S25FL512S";
            }
            if (id[1] == 0x20) {
                if (id[2] == 0x18) return "S25FL127S";
            }
            if (id[1] == 0x40) {
                if (id[2] == 0x15) return "S25FL116K";
            }
        }
        if (id[0] == 0xC2) {
            // Macronix
            if (id[1] == 0x20) {
                if (id[2] == 0x18) return "MX25L12805D";
            }
        }
        if (id[0] == 0x20) {
            // Micron
            if (id[1] == 0xBA) {
                if (id[2] == 0x20) return "N25Q512A";
                if (id[2] == 0x21) return "N25Q00AA";
            }
            if (id[1] == 0xBB) {
                if (id[2] == 0x22) return "MT25QL02GC";
            }
        }
        if (id[0] == 0xBF) {
            // SST
            if (id[1] == 0x25) {
                if (id[2] == 0x02) return "SST25WF010";
                if (id[2] == 0x03) return "SST25WF020";
                if (id[2] == 0x04) return "SST25WF040";
                if (id[2] == 0x41) return "SST25VF016B";
                if (id[2] == 0x4A) return "SST25VF032";
            }
            if (id[1] == 0x25) {
                if (id[2] == 0x01) return "SST26VF016";
                if (id[2] == 0x02) return "SST26VF032";
                if (id[2] == 0x43) return "SST26VF064";
            }
        }
        return "(unknown chip)";
    }

public:
    void setup() {
        pinMode(13, OUTPUT);
        pinMode(A3, OUTPUT);
        pinMode(A4, OUTPUT);
        pinMode(A5, OUTPUT);

        leds(true);

        pinMode(PIN_FLASH_CS, INPUT_PULLUP);
        pinMode(PIN_RADIO_CS, INPUT_PULLUP);
        pinMode(PIN_SD_CS, INPUT_PULLUP);
        pinMode(PIN_WINC_CS, INPUT_PULLUP);

        pinMode(PIN_WINC_EN, OUTPUT);
        digitalWrite(PIN_WINC_EN, LOW);

        pinMode(PIN_WINC_RST, OUTPUT);
        digitalWrite(PIN_WINC_RST, LOW);

        pinMode(PIN_FLASH_CS, OUTPUT);
        pinMode(PIN_RADIO_CS, OUTPUT);
        pinMode(PIN_SD_CS, OUTPUT);
        pinMode(PIN_WINC_CS, OUTPUT);

        digitalWrite(PIN_FLASH_CS, HIGH);
        digitalWrite(PIN_RADIO_CS, HIGH);
        digitalWrite(PIN_SD_CS, HIGH);
        digitalWrite(PIN_WINC_CS, HIGH);

        SPI.begin();
    }

    void leds(bool on) {
        digitalWrite(13, on ? HIGH : LOW);
        digitalWrite(A3, on ? HIGH : LOW);
        digitalWrite(A4, on ? HIGH : LOW);
        digitalWrite(A5, on ? HIGH : LOW);
    }

    void fuelGauge() {
        FuelGauge gauge;

        debugfln("test: Checking gauge...");

        Wire.begin();

        gauge.powerOn();

        debugfln("test: Gauge PASSED");
    }

    void flashMemory() {
        debugfln("test: Checking flash memory...");

        if (!SerialFlash.begin(PIN_FLASH_CS)) {
            debugfln("test: Flash memory FAILED");
            return;
        }

        uint8_t buffer[256];

        SerialFlash.readID(buffer);
        if (buffer[0] == 0) {
            debugfln("test: Flash memory FAILED");
            return;
        }

        uint32_t chipSize = SerialFlash.capacity(buffer);
        if (chipSize == 0) {
            debugfln("test: Flash memory FAILED");
            return;
        }

        debugfln("Read Chip Identification:");
        debugf("  JEDEC ID:     %x %x %x", buffer[0], buffer[1], buffer[2]);
        debugfln("  Part Nummber: %s", id2chip(buffer));
        debugfln("  Memory Size:  %d bytes Block Size: %d bytes", chipSize, SerialFlash.blockSize());
        debugfln("test: Flash memory PASSED");
    }

    void gps() {
        debugfln("test: Checking gps...");

        Serial1.begin(9600);

        uint32_t charactersRead = 0;
        uint32_t start = millis();
        while (millis() - start < 5 * 1000 && charactersRead < 100)  {
            while (Serial1.available()) {
                Serial5.print((char)Serial1.read());
                charactersRead++;
            }
        }

        debugfln("");

        if (charactersRead < 100) {
            debugfln("test: GPS FAILED");
            digitalWrite(A3, HIGH);
            digitalWrite(A4, HIGH);
            digitalWrite(A5, HIGH);
        }
        else {
            debugfln("test: GPS PASSED");
        }
    }

    void sdCard() {
        debugfln("test: Checking SD...");

        if (SD.begin(PIN_SD_CS)) {
            debugfln("test: SD PASSED");
        }
        else {
            digitalWrite(PIN_SD_CS, HIGH);

            debugfln("test: SD FAILED");
        }
    }

    void radio() {
        debugfln("test: Checking radio...");

        RH_RF95 rf95(PIN_RADIO_CS, PIN_RADIO_DIO0);

        if (!rf95.init()) {
            debugfln("test: Radio FAILED");
        }
        else {
            digitalWrite(PIN_RADIO_CS, HIGH);

            debugfln("test: Radio PASSED");
        }
    }

    void wifi() {
        debugfln("test: Checking wifi...");

        delay(500);

        digitalWrite(PIN_WINC_RST, HIGH);

        WiFi.setPins(PIN_WINC_CS, PIN_WINC_IRQ, PIN_WINC_RST);

        digitalWrite(PIN_WINC_EN, LOW);
        delay(50);

        digitalWrite(PIN_WINC_EN, HIGH);

        delay(50);

        if (WiFi.status() == WL_NO_SHIELD) {
            debugfln("test: Wifi FAILED");
        }
        else {
            debugfln("test: Wifi firmware version: ");
            String fv = WiFi.firmwareVersion();
            debugfln("Version: %s", fv.c_str());
            debugfln("test: Wifi PASSED");
        }
    }
};

void setup() {
    Serial.begin(115200);

    Serial5.begin(115200);

    Check check;
    check.setup();
    check.leds(false);

    while (!Serial && millis() < 2 * 1000) {
        delay(100);
    }

    delay(100);

    check.flashMemory();
    check.radio();
    check.gps();
    check.sdCard();
    check.fuelGauge();
    check.wifi();

    while (true) {
        delay(100);
        check.leds(false);
        delay(100);
        check.leds(true);
    }
}

void loop() {

}
