#include "protocol_parser.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *stream = "noise\n"
                         "CH4=120.5;TEMP=25.0\n"
                         "BAD=1\n"
                         "CH4=260.0;TEMP=31.2\n";

    SensorFrame frames[4];
    const size_t count = parse_stream(stream, frames, 4);
    for (size_t i = 0; i < count; ++i) {
        printf("frame[%zu] ch4=%.1f temp=%.1f\n", i, frames[i].ch4_ppm, frames[i].temp_c);
    }

    return count == 2U && frames[0].valid && frames[1].ch4_ppm > 200.0 ? EXIT_SUCCESS
                                                                       : EXIT_FAILURE;
}
