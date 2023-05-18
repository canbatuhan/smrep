// #include <smrep.h>
#include <stdlib.h>
#include "../smrep/lib/smrep.h"

#define SYSTEM_BOOT 0b00000
#define INIT_SENSOR 0b00001
#define SWITCH_MODE 0b00010
#define HEARTBEAT   0b00011

#define ANALOG_MODE  0b0
#define DIGITAL_MODE 0b1

int sensor_pin = 1;
int mode       = 0;

void * init_sensor() {
    printf("Sensor in PIN:%d is started", sensor_pin);
}

void * switch_mode() {
    printf("Sensor mode switched from ");
    if (mode == ANALOG_MODE) {
        printf("ANALOG to DIGITAL");
        mode = DIGITAL_MODE;
    } else {
        printf("DIGITAL to ANALOG");
    }
}

void build(state_machine * machine) {
    set_transition(machine, init_event(SMREP_SET, SYSTEM_BOOT), NULL);
    set_transition(machine, init_event(SMREP_SET, INIT_SENSOR), init_sensor);
    set_transition(machine, init_event(SMREP_PUT, SWITCH_MODE), switch_mode);
    set_transition(machine, init_event(SMREP_INC, HEARTBEAT),   NULL);
}

int main() {
    state_machine machine = init_machine();
    build(&machine);

    // Implement runner
}