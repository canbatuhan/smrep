#include <stdlib.h>
#include "../lib/machine.h"

#define MAX_VAR_COUNT   256
#define MAX_EVENT_COUNT 32

/**
 * @brief Initializes an empty state machine
 * 
 * @return state_machine : State machine struct
 */
state_machine init_machine() {
    state_machine new_machine;
    new_machine.state            = NULL;
    new_machine.state_size       = 0;
    new_machine.transitions      = NULL;
    new_machine.transitions_size = 0;
    return new_machine;
}

/**
 * @brief Sets the transition object
 * 
 * @param machine  Pointer to the state machine
 * @param event    The triggering event
 * @param callback Callback to run during transition 
 */
void set_transition(state_machine * machine, machine_event event, void * callback()) {
    if (machine->transitions_size < MAX_EVENT_COUNT) {
        machine->transitions = realloc(machine->transitions, sizeof(machine_trans)*(machine->transitions_size+1));
        machine->transitions[machine->transitions_size] = init_transition(event, callback);
        machine->transitions_size++;
    }
}

/**
 * @brief Sends the message to the state machine
 * 
 * @param machine        Pointer to the state machine
 * @param message        Message carrying event and variable data
 * @return machine_ack : Message including the callback result and ack
 */
machine_ack send(state_machine * machine, machine_msg message) {
    void * ret_st = __run(machine, message.data.event);
    unsigned ack;

    switch (message.data.event.data.command) {
        case SMREP_SET:
            ack =__set(machine, message.data.variable);
            break;
        case SMREP_PUT:
            ack =__put(machine, message.data.variable);
            break;
        case SMREP_INC:
            ack = __inc(machine, message.data.variable.data.identifier);
            break;
        case SMREP_DEC:
            ack = __dec(machine, message.data.variable.data.identifier);
            break;
        case SMREP_GET:
            ack =__get(machine, message.data.variable.data.identifier);
            break;
        /*case SMREP_KEYS:
            ack =__keys(machine);
            break;*/
        case SMREP_SIZE:
            ack =__size(machine);
            break;
        case SMREP_DEL:
            ack =__del(machine, message.data.variable.data.identifier);
            break;
        default:
            ack = SMREP_FAILURE;
            break;
    }

    return init_ack(ret_st, ack);
}

/**
 * @brief Destroys the state machine
 * 
 * @param machine State machine struct
 */
void destroy_machine(state_machine machine) {
    free(machine.state);
    machine.state_size = 0;
    free(machine.transitions);
    machine.transitions_size = 0;
}