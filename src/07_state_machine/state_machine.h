#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum DoorState { DOOR_CLOSED, DOOR_OPENING, DOOR_OPEN, DOOR_CLOSING, DOOR_ERROR } DoorState;

typedef enum DoorEvent {
    EVENT_BUTTON,
    EVENT_LIMIT_OPEN,
    EVENT_LIMIT_CLOSED,
    EVENT_TIMEOUT,
    EVENT_OBSTACLE
} DoorEvent;

typedef struct DoorController {
    DoorState state;
    unsigned transitions;
} DoorController;

void door_init(DoorController *door);
DoorState door_handle(DoorController *door, DoorEvent event);
const char *door_state_name(DoorState state);

#endif
