#include <stdlib.h>
#include "../lib/machine.h"

#define MAX_VAR_COUNT   256
#define MAX_EVENT_COUNT 32

/**
 * @brief Gets the pointer of a variable by its ID
 * 
 * @param machine         Pointer to the state machine
 * @param identifier      ID of the variable (8-bit)
 * @return machine_var* : Pointer to the variable
 */
machine_var * __get_var_ptr(state_machine * machine, unsigned identifier) {
    unsigned short idx;
    for (idx=0; idx<machine->state_size; idx++) {
        if (identifier == machine->state[idx].data.identifier) {
            // Variable found
            return &(machine->state[idx]);
        }
    }
    // Variable not found
    return NULL;
}

/**
 * @brief Gets the pointer of a transition by the event ID
 * 
 * @param machine           Pointer to the state machine
 * @param identifier        ID of the event (8-bit)
 * @return machine_trans* : Pointer to the transition
 */
machine_trans * __get_trans_ptr(state_machine * machine, unsigned identifier) {
    unsigned short idx;
    for (idx=0; idx<machine->transitions_size; idx++) {
        if (identifier == machine->transitions[idx].data.event.data.identifier) {
            // Transition found
            return &(machine->transitions[idx]);
        }
    }
    // Transition not found
    return NULL;
}

/**
 * @brief Adds a new entry to the state
 * 
 * @param machine  Pointer to the state machine
 * @param variable Variable including ID and value
 */
void __add_state_entry(state_machine * machine, machine_var variable) {
    if (machine->state_size < MAX_VAR_COUNT) {
        machine->state = realloc(machine->state, sizeof(machine_var)*(machine->state_size+1));
        machine->state[machine->state_size] = variable;
        machine->state_size++;
    }
}

/**
 * @brief Deletes an entry from the state by its ID
 * 
 * @param machine    Pointer to the state machine
 * @param identifier ID of the variable (8-bit)
 */
void __remove_state_entry(state_machine * machine, unsigned identifier) {
    unsigned short idx;
    for (idx=0; idx<machine->state_size; idx++) {
        if (identifier == machine->state[idx].data.identifier) {
            machine->state[idx] = machine->state[machine->state_size-1];
            realloc(machine->state, sizeof(machine_var)*(machine->state_size-1));
            machine->state_size--;
            return;
        }
    }
}