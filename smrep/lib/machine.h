#include "constants.h"
#include "struct.h"

#ifndef SMREP_MACHINE_H
#define SMREP_MACHINE_H

typedef struct machine {
    machine_var *   state;
    unsigned        state_size : 8;
    machine_trans * transitions;
    unsigned        transitions_size : 5;
} state_machine;


/* Util Functions: src/util.c */

machine_var *   __get_var_ptr(state_machine *, unsigned);
machine_trans * __get_trans_ptr(state_machine *, unsigned);
void            __add_state_entry(state_machine *, machine_var);
void            __remove_state_entry(state_machine *, unsigned);


/* Operation Functions: src/operation.c */

unsigned   __set(state_machine *, machine_var);
unsigned   __put(state_machine *, machine_var);
unsigned   __inc(state_machine *, unsigned);
unsigned   __dec(state_machine *, unsigned);
unsigned   __get(state_machine *, unsigned);
//unsigned * __keys(state_machine *);
unsigned   __size(state_machine *);
unsigned   __del(state_machine *, unsigned);
void *     __run(state_machine *, machine_event);


/* Machine Functions: src/machine.c */

state_machine init_machine();
void          set_transition(state_machine *, machine_event, void * ());
machine_ack   send(state_machine *, machine_msg);
void          destroy_machine(state_machine);

#endif