#include <alogging/alogging.h>

#include "check_core.h"
#include "board_definition.h"

using namespace fk;

constexpr const char LogName[] = "Check";

using Log = SimpleLog<LogName>;

void setup() {
    Serial5.begin(115200);
    Serial.begin(115200);

    while (!Serial && millis() < 2 * 1000) {
        delay(100);
    }

    if (!Serial) {
        // The call to end here seems to free up some memory.
        Serial.end();
        log_uart_set(Serial5);
    }

    CheckCore check;
    check.setup();

    check.check();

    while (true) {
        check.task();
        delay(10);
    }
}

void loop() {

}
