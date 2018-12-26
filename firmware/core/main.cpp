/**
 * @file
 */
#include <Arduino.h>

#include <fk-core.h>

#include "platform.h"
#include "restart_wizard.h"
#include "initialized.h"
#include "take_readings.h"

#include "seed.h"
#include "config.h"

extern "C" {

namespace fk {

class ConfigureDevice : public fk::MainServicesState {
public:
    const char *name() const override {
        return "ConfigureDevice";
    }

public:
    void entry() override {
        #if defined(FK_CONFIG_WIFI_1_SSID) && defined(FK_CONFIG_WIFI_2_SSID)
        fk::NetworkInfo networks[2] = {
            {
                FK_CONFIG_WIFI_1_SSID,
                FK_CONFIG_WIFI_1_PASSWORD,
            },
            {
                FK_CONFIG_WIFI_2_SSID,
                FK_CONFIG_WIFI_2_PASSWORD,
            }
        };

        services().state->configure(fk::NetworkSettings{ false, networks });

        log("Configured compile time networks.");
        #endif

        transit<fk::Initialized>();
    }
};

}

static void setup_serial();
static void setup_env();

void setup() {
    #ifdef FK_DEBUG_MTB_ENABLE
    REG_MTB_POSITION = ((uint32_t) (mtb - REG_MTB_BASE)) & 0xFFFFFFF8;
    REG_MTB_FLOW = ((uint32_t) mtb + DEBUG_MTB_SIZE * sizeof(uint32_t)) & 0xFFFFFFF8;
    REG_MTB_MASTER = 0x80000000 + 6;
    #endif

    setup_serial();
    setup_env();

    fk::restartWizard.startup();
}

void loop() {
    fk::ConfigurableStates states{
        fk::CoreFsm::deferred<fk::ConfigureDevice>(),
        fk::CoreFsm::deferred<fk::TakeReadings>()
    };
    fk::CoreModule coreModule(states);
    coreModule.run();
}

static void setup_serial() {
    Serial.begin(115200);

    while (!Serial) {
        delay(100);

        #ifndef FK_DEBUG_UART_REQUIRE_CONSOLE
        if (fk::fk_uptime() > 2000) {
            break;
        }
        #endif
    }

    #ifdef FK_DEBUG_UART_FALLBACK
    if (!Serial) {
        // The call to end here seems to free up some memory.
        Serial.end();
        Serial5.begin(115200);
        log_uart_set(Serial5);
    }
    #endif
}

static void setup_env() {
    randomSeed(RANDOM_SEED);
    firmware_version_set(FIRMWARE_GIT_HASH);
    firmware_build_set(FIRMWARE_BUILD);
    firmware_compiled_set(DateTime(__DATE__, __TIME__).unixtime());
}

#ifdef FK_DEBUG_MTB_ENABLE

#define DEBUG_MTB_SIZE 256
__attribute__((__aligned__(DEBUG_MTB_SIZE * sizeof(uint32_t)))) uint32_t mtb[DEBUG_MTB_SIZE];

void HardFault_Handler(void) {
    // Turn off the micro trace buffer so we don't fill it up in the infinite loop below.
    REG_MTB_MASTER = 0x00000000 + 6;
    while (true) {
    }
}

#endif

}
