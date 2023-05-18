#include <stdlib.h>
#include "../lib/machine.h"

#define VAR_ID_SIZE 8

/**
 * @brief Sets a variable
 * 
 * @param machine     Pointer to the state machine
 * @param variable    Variable including ID and value
 * @return unsigned : Acknowledgement 
 */
unsigned __set(state_machine * machine, machine_var variable) {
    machine_var * var_ptr = __get_var_ptr(machine, variable.data.identifier);
    if (var_ptr != NULL) { // Variable already exists
        return SMREP_FAILURE;
    } else { // Create variable
        __add_state_entry(machine, variable);
        return SMREP_SUCCESS;
    }
}

/**
 * @brief Sets a variable
 * 
 * @param machine     Pointer to the state machine
 * @param variable    Variable including ID and value
 * @return unsigned : Acknowledgement 
 */
unsigned __put(state_machine * machine, machine_var variable) {
    machine_var * var_ptr = __get_var_ptr(machine, variable.data.identifier);
    if (var_ptr != NULL) { // Update variable
        var_ptr->data.value = variable.data.value;
        return SMREP_SUCCESS;
    } else { // Variable not found
        return SMREP_FAILURE;
    }
}

/**
 * @brief Increments a variable
 * 
 * @param machine     Pointer to the state machine
 * @param identifier  ID of the variable (8-bit)
 * @return unsigned : Acknowledgement
 */
unsigned __inc(state_machine * machine, unsigned identifier) {
    machine_var * var_ptr = __get_var_ptr(machine, identifier);
    if (var_ptr != NULL) { // Increment value
        var_ptr->data.value = var_ptr->data.value + 1;
        return SMREP_SUCCESS;
    } else { // Variable not found
        return SMREP_FAILURE;
    }
}

/**
 * @brief Decrements a variable
 * 
 * @param machine     Pointer to the state machine
 * @param identifier  ID of the variable (8-bit)
 * @return unsigned : Acknowledgement
 */
unsigned __dec(state_machine * machine, unsigned identifier) {
    machine_var * var_ptr = __get_var_ptr(machine, identifier);
    if (var_ptr != NULL) { // Decrement value
        var_ptr->data.value = var_ptr->data.value - 1;
        return SMREP_SUCCESS;
    } else { // Variable not found
        return SMREP_FAILURE;
    }
}

/**
 * @brief Gets a variable by its ID
 * 
 * @param machine     Pointer to the state machine
 * @param identifier  ID of the variable (8-bit)
 * @return unsigned : Acknowledgement (value of the varible)
 */
unsigned __get(state_machine * machine, unsigned identifier) {
    machine_var * var_ptr = __get_var_ptr(machine, identifier);
    if (var_ptr != NULL) { // Read value
        return var_ptr->data.value; 
    } else { // Variable not found
        return SMREP_FAILURE;
    }
}

/**
 * @brief Returns all the keys stored in the machine
 * 
 * @param machine    : Pointer to the state machine
 * @return unsigned* : Array of keys
 */
/*unsigned * __keys(state_machine * machine) {
    unsigned * keys = (unsigned *) malloc(VAR_ID_SIZE * machine->state_size);
    unsigned idx;
    for (idx=0; idx<machine->state_size; idx++) {
        keys[idx] = machine->state[idx].data.identifier;
    }
    return keys;
}*/

/**
 * @brief Return the number of key-value pairs
 * 
 * @param machine   : Pointer to the state machine
 * @return unsigned : Number of key-value pairs
 */
unsigned __size(state_machine * machine) {
    return machine->state_size;
}

/**
 * @brief Removes a variable by its ID
 * 
 * @param machine     Pointer to the state machine
 * @param identifier  ID of the variable (8-bit)
 * @return unsigned : Acknowledgement
 */
unsigned __del(state_machine * machine, unsigned identifier) {
    machine_var * var_ptr = __get_var_ptr(machine, identifier);
    if (var_ptr != NULL) { // Delete variable
        __remove_state_entry(machine, identifier);
    }
    return SMREP_SUCCESS;
}

/**
 * @brief Executes a transition by its event ID
 * 
 * @param machine   Pointer to the state machine
 * @param event     The triggering event
 * @return void * : Generic pointer (for custom structures)
 */
void * __run(state_machine * machine, machine_event event) {
    machine_trans * trans_ptr = __get_trans_ptr(machine, event.data.identifier);
    if (trans_ptr != NULL && trans_ptr->data.callback != NULL) { // Execute transition
        return (trans_ptr->data.callback)();
    }
    // No callback is defined
    return NULL;
}