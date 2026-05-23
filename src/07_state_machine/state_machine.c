#include "state_machine.h"

void door_init(DoorController *door) {
    door->state = DOOR_CLOSED;
    door->transitions = 0;
}

DoorState door_handle(DoorController *door, DoorEvent event) {
    DoorState next = door->state;

    switch (door->state) {
    case DOOR_CLOSED:
        next = event == EVENT_BUTTON ? DOOR_OPENING : DOOR_CLOSED;
        break;
    case DOOR_OPENING:
        if (event == EVENT_LIMIT_OPEN) {
            next = DOOR_OPEN;
        } else if (event == EVENT_TIMEOUT || event == EVENT_OBSTACLE) {
            next = DOOR_ERROR;
        }
        break;
    case DOOR_OPEN:
        next = event == EVENT_BUTTON ? DOOR_CLOSING : DOOR_OPEN;
        break;
    case DOOR_CLOSING:
        if (event == EVENT_LIMIT_CLOSED) {
            next = DOOR_CLOSED;
        } else if (event == EVENT_OBSTACLE) {
            next = DOOR_OPENING;
        } else if (event == EVENT_TIMEOUT) {
            next = DOOR_ERROR;
        }
        break;
    case DOOR_ERROR:
        next = DOOR_ERROR;
        break;
    }

    if (next != door->state) {
        door->transitions++;
    }
    door->state = next;
    return door->state;
}

const char *door_state_name(DoorState state) {
    switch (state) {
    case DOOR_CLOSED:
        return "closed";
    case DOOR_OPENING:
        return "opening";
    case DOOR_OPEN:
        return "open";
    case DOOR_CLOSING:
        return "closing";
    case DOOR_ERROR:
        return "error";
    }
    return "unknown";
}
