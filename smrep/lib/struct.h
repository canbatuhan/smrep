#ifndef SMREP_STRUCTS_H
#define SMREP_STRUCTS_H

typedef union variable {
    unsigned alignment : 24;
    struct {
        unsigned identifier : 8;
        unsigned value      : 16;
    } data;
} machine_var;

typedef union event {
    unsigned alignment : 8;
    struct {
        unsigned command    : 3;
        unsigned identifier : 5;
    } data;
} machine_event;

typedef union transition  {
    unsigned alignment : 24;
    struct {
        machine_event event;
        void *        (*callback)();
    } data;
} machine_trans;

typedef union message {
    unsigned alignment : 32;
    struct {
        machine_event event;
        machine_var   variable;
    } data;
} machine_msg;

typedef struct ack {
    void *   st;
    unsigned ack;
} machine_ack;

machine_var   init_variable(unsigned, unsigned);
machine_event init_event(unsigned, unsigned);
machine_trans init_transition(machine_event, void * (*)());
machine_msg   init_message(machine_event, machine_var);
machine_ack   init_ack(void *, unsigned);

#endif