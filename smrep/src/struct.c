#include <stdlib.h>
#include <assert.h>
#include "../lib/struct.h"

#define VAR_ID_LIMIT      0xFF
#define EVENT_ID_LIMIT    0b11111
#define VALUE_UPPER_LIMIT 0xFFFF
#define VALUE_LOWER_LIMIT 0x0000
#define COMMAND_LIMIT     0b111

/**
 * @brief Initializes a variable
 * 
 * @param identifier     ID of the variable (8-bit)
 * @param value          Value of the variable (16-bit)
 * @return machine_var : Variable struct
 */
machine_var init_variable(unsigned identifier, unsigned value) {
    assert(identifier <= VAR_ID_LIMIT && value <= VALUE_UPPER_LIMIT);
    machine_var new_variable;
    new_variable.data.identifier = identifier;
    new_variable.data.value      = value;
    return new_variable;
}

/**
 * @brief Initializes an event
 * 
 * @param command          Command type (3-bit)
 * @param identifier       ID of the event (5-bit)
 * @return machine_event : Event struct
 */
machine_event init_event(unsigned command, unsigned identifier) {
    assert(identifier <= EVENT_ID_LIMIT && command <= COMMAND_LIMIT);
    machine_event new_event;
    new_event.data.command    = command;
    new_event.data.identifier = identifier;
    return new_event;
}

/**
 * @brief Initializes a transition
 * 
 * @param event            Event struct
 * @param callback         A function pointer
 * @return machine_trans : Transition struct
 */
machine_trans init_transition(machine_event event, void * (*callback)()) {
    machine_trans new_transition;
    new_transition.data.event    = event;
    new_transition.data.callback = callback;
    return new_transition;
}

/**
 * @brief Initializes a message
 * 
 * @param event          Event struct
 * @param variable       Variable struct
 * @return machine_msg : Message struct
 */
machine_msg init_message(machine_event event, machine_var variable) {
    machine_msg new_message;
    new_message.data.event    = event;
    new_message.data.variable = variable;
    return new_message;
}

/**
 * @brief Initializes an acknowledgement
 * @attention Do not forget to destroy it after using
 * 
 * @param st             Struct carrying the result of the transition
 * @param ack            Acknowledgement value
 * @return machine_ack : Acknowledgement struct
 */
machine_ack init_ack(void * st, unsigned ack) {
    machine_ack new_ack;
    new_ack.st  = st;
    new_ack.ack = ack;
    return new_ack;
}

/**
 * @brief Destroys the acknowledgement
 * 
 * @param ack Acknowledgement struct
 */
void destroy_ack(machine_ack ack) {
    free(ack.st);
}