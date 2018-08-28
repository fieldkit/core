#include <cstdarg>

#include <Wire.h>
#include <wiring_private.h>
#include <FuelGauge.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <SerialFlash.h>
#include <WiFi101.h>
#include <Adafruit_NeoPixel.h>

#include <alogging/alogging.h>

#include <phylum/phylum.h>
#include <backends/arduino_sd/arduino_sd.h>

#ifdef FK_CORE_GENERATION_2

static constexpr uint8_t PIN_RADIO_CS = 5;
static constexpr uint8_t PIN_RADIO_DIO0 = 2;
static constexpr uint8_t PIN_SD_CS = 12;
static constexpr uint8_t PIN_WINC_CS = 7;
static constexpr uint8_t PIN_WINC_IRQ = 16;
static constexpr uint8_t PIN_WINC_RST = 15;
static constexpr uint8_t PIN_WINC_EN = 38;
static constexpr uint8_t PIN_WINC_WAKE = 8;
static constexpr uint8_t PIN_PERIPH_ENABLE = (25u); // PIN_LED_RXL;
static constexpr uint8_t PIN_GPS_ENABLE = A4;
static constexpr uint8_t PIN_FLASH_CS = (26u); // PIN_LED_TXL;

Uart Serial2(&sercom1, 11, 10, SERCOM_RX_PAD_0, UART_TX_PAD_2);

void SERCOM1_Handler() {
    Serial2.IrqHandler();
}

void gpsSerialBegin(int32_t baud) {
    Serial2.begin(baud);

    // Order is very important here. This has to happen after the call to begin.
    pinPeripheral(10, PIO_SERCOM);
    pinPeripheral(11, PIO_SERCOM);
}

Uart& gpsSerial = Serial2;

#else

static constexpr uint8_t PIN_RADIO_CS = 5;
static constexpr uint8_t PIN_RADIO_DIO0 = 2;
static constexpr uint8_t PIN_SD_CS = 12;
static constexpr uint8_t PIN_FLASH_CS = 4;
static constexpr uint8_t PIN_WINC_CS = 7;
static constexpr uint8_t PIN_WINC_IRQ = 9;
static constexpr uint8_t PIN_WINC_RST = 10;
static constexpr uint8_t PIN_WINC_EN = 11;
static constexpr uint8_t PIN_WINC_WAKE = 8;

Uart& gpsSerial = Serial1;

void gpsSerialBegin(int32_t baud) {
    Serial1.begin(9600);
}

#endif

constexpr const char LogName[] = "Check";

using Log = SimpleLog<LogName>;

class MacEeprom {
private:
    uint8_t address;

public:
    MacEeprom() : address(0x50) {
    }

public:
    bool read128bMac(uint8_t *id) {
        Wire.beginTransmission(address);
        Wire.write(0xf8);
        Wire.endTransmission();
        Wire.requestFrom(address, 8);

        uint8_t index = 0;
        while (Wire.available()){
            id[index++] = Wire.read();
        }

        return true;
    }
};

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

        leds(true);

        Adafruit_NeoPixel pixels(1, A3, NEO_GRB + NEO_KHZ400);
        pixels.begin();
        pixels.setPixelColor(0, pixels.Color(0, 32, 0));
        pixels.show();

        pinMode(PIN_FLASH_CS, INPUT_PULLUP);
        #ifdef FK_ENABLE_RADIO
        pinMode(PIN_RADIO_CS, INPUT_PULLUP);
        #endif
        pinMode(PIN_SD_CS, INPUT_PULLUP);
        pinMode(PIN_WINC_CS, INPUT_PULLUP);

        pinMode(PIN_WINC_EN, OUTPUT);
        digitalWrite(PIN_WINC_EN, LOW);

        pinMode(PIN_WINC_RST, OUTPUT);
        digitalWrite(PIN_WINC_RST, LOW);

        pinMode(PIN_FLASH_CS, OUTPUT);
        #ifdef FK_ENABLE_RADIO
        pinMode(PIN_RADIO_CS, OUTPUT);
        #endif
        pinMode(PIN_SD_CS, OUTPUT);
        pinMode(PIN_WINC_CS, OUTPUT);

        digitalWrite(PIN_FLASH_CS, HIGH);
        #ifdef FK_ENABLE_RADIO
        digitalWrite(PIN_RADIO_CS, HIGH);
        #endif
        digitalWrite(PIN_SD_CS, HIGH);
        digitalWrite(PIN_WINC_CS, HIGH);

        SPI.begin();
    }

    void leds(bool on) {
        digitalWrite(13, on ? HIGH : LOW);
    }

    FuelGauge gauge;

    FuelGauge &getFuelGauge() {
        return gauge;
    }

    bool fuelGauge() {
        Log::info("test: Checking gauge...");

        Wire.begin();

        gauge.powerOn();

        if (gauge.version() != 3) {
            Log::info("test: Gauge FAILED");
            return true;
        }

        Log::info("test: Gauge PASSED");

        return true;
    }

    bool flashMemory() {
        Log::info("test: Checking flash memory...");

        if (!SerialFlash.begin(PIN_FLASH_CS)) {
            Log::info("test: Flash memory FAILED");
            return false;
        }

        uint8_t buffer[256];

        SerialFlash.readID(buffer);
        if (buffer[0] == 0) {
            Log::info("test: Flash memory FAILED");
            return false;
        }

        uint32_t chipSize = SerialFlash.capacity(buffer);
        if (chipSize == 0) {
            Log::info("test: Flash memory FAILED");
            return false;
        }

        Log::info("Read Chip Identification:");
        Log::info("  JEDEC ID:     %x %x %x", buffer[0], buffer[1], buffer[2]);
        Log::info("  Part Nummber: %s", id2chip(buffer));
        Log::info("  Memory Size:  %d bytes Block Size: %d bytes", chipSize, SerialFlash.blockSize());
        Log::info("test: Flash memory PASSED");

        return true;
    }

    bool gps() {
        Log::info("test: Checking gps...");

        gpsSerialBegin(9600);

        uint32_t charactersRead = 0;
        uint32_t start = millis();
        while (millis() - start < 5 * 1000 && charactersRead < 100)  {
            while (gpsSerial.available()) {
                Serial.print((char)gpsSerial.read());
                charactersRead++;
            }
        }

        Log::info("");

        if (charactersRead < 100) {
            Log::info("test: GPS FAILED");
            return false;
        }

        Log::info("test: GPS PASSED");

        return true;
    }

    bool sdCard() {
        Log::info("test: Checking SD...");

        phylum::Geometry g;
        phylum::ArduinoSdBackend storage;
        if (!storage.initialize(g, PIN_SD_CS)) {
            Log::info("test: SD FAILED (to open)");
            return false;
        }

        if (!storage.open()) {
            Log::info("test: SD FAILED");
            return false;
        }

        digitalWrite(PIN_SD_CS, HIGH);
        Log::info("test: SD PASSED");

        return true;
    }

    bool radio() {
        Log::info("test: Checking radio...");

        RH_RF95 rf95(PIN_RADIO_CS, PIN_RADIO_DIO0);

        if (!rf95.init()) {
            Log::info("test: Radio FAILED");
            return false;
        }

        digitalWrite(PIN_RADIO_CS, HIGH);
        Log::info("test: Radio PASSED");

        return true;
    }

    bool wifi() {
        Log::info("test: Checking wifi...");

        delay(500);

        digitalWrite(PIN_WINC_RST, HIGH);

        WiFi.setPins(PIN_WINC_CS, PIN_WINC_IRQ, PIN_WINC_RST);

        digitalWrite(PIN_WINC_EN, LOW);
        delay(50);

        digitalWrite(PIN_WINC_EN, HIGH);

        delay(50);

        if (WiFi.status() == WL_NO_SHIELD) {
            Log::info("test: Wifi FAILED");
            return false;
        }

        Log::info("test: Wifi firmware version: ");
        auto fv = WiFi.firmwareVersion();
        Log::info("Version: %s", fv);
        Log::info("test: Wifi PASSED");

        return true;
    }

    bool macEeprom() {
        MacEeprom macEeprom;
        uint8_t id[8] = { 0 };

        auto success = macEeprom.read128bMac(id);
        if (!success) {
            Log::info("test: 128bMAC FAILED");
            return false;
        }

        Log::info("test: 128bMAC: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x", id[0], id[1], id[2], id[3], id[4], id[5], id[6], id[7]);

        Log::info("test: 128bMAC PASSED");

        return success;
    }

    bool check() {
        auto success = true;

        success = flashMemory() && success;
        success = fuelGauge() && success;
        success = macEeprom() && success;

        if (success) {
            Log::info("test: Top PASSED");
        }

        #ifdef FK_ENABLE_RADIO
        success = radio() && success;
        #else
        Log::info("test: Radio disabled");
        #endif
        success = gps() && success;
        success = sdCard() && success;
        success = wifi() && success;

        return success;
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

    #ifdef FK_CORE_GENERATION_2
    Log::info("test: Enabling peripherals!");
    pinMode(PIN_PERIPH_ENABLE, OUTPUT);
    pinMode(PIN_GPS_ENABLE, OUTPUT);
    digitalWrite(PIN_PERIPH_ENABLE, LOW);
    digitalWrite(PIN_GPS_ENABLE, LOW);
    digitalWrite(A4, LOW);
    delay(500);
    digitalWrite(PIN_PERIPH_ENABLE, HIGH);
    digitalWrite(PIN_GPS_ENABLE, HIGH);
    digitalWrite(A4, HIGH);
    delay(500);
    #else
    Log::info("test: Peripherals should always be on.");
    #endif

    delay(100);

    if (!check.check()) {
        #ifdef FK_CORE_GENERATION_2
        digitalWrite(PIN_PERIPH_ENABLE, LOW);
        digitalWrite(PIN_GPS_ENABLE, LOW);
        #endif

        while (true) {
            delay(100);
            check.leds(true);
            delay(100);
            check.leds(false);
        }
    }

    check.leds(true);

    auto gauge = check.getFuelGauge();

    while (true) {
        delay(5000);

        float voltage = gauge.cellVoltage();
        float stateOfCharge = gauge.stateOfCharge();

        sdebug() << "test: Battery: " << stateOfCharge << " " << voltage << endl;
    }
}

void loop() {

}
