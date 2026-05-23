#include "state_machine.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    DoorController door;
    door_init(&door);

    door_handle(&door, EVENT_BUTTON);
    door_handle(&door, EVENT_LIMIT_OPEN);
    door_handle(&door, EVENT_BUTTON);
    door_handle(&door, EVENT_OBSTACLE);
    door_handle(&door, EVENT_LIMIT_OPEN);

    printf("state=%s transitions=%u\n", door_state_name(door.state), door.transitions);
    return door.state == DOOR_OPEN && door.transitions == 5U ? EXIT_SUCCESS : EXIT_FAILURE;
}
