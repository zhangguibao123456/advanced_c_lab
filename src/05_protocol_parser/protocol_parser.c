#include "protocol_parser.h"

#include <stdio.h>
#include <string.h>

int parse_sensor_frame(const char *line, SensorFrame *frame) {
    double ch4 = 0.0;
    double temp = 0.0;
    if (sscanf(line, "CH4=%lf;TEMP=%lf", &ch4, &temp) == 2) {
        frame->ch4_ppm = ch4;
        frame->temp_c = temp;
        frame->valid = 1;
        return 1;
    }
    frame->valid = 0;
    return 0;
}

size_t parse_stream(const char *stream, SensorFrame *frames, size_t frame_capacity) {
    size_t count = 0;
    const char *line = stream;

    while (*line != '\0' && count < frame_capacity) {
        const char *end = strchr(line, '\n');
        const size_t len = end == 0 ? strlen(line) : (size_t)(end - line);
        char scratch[96];

        if (len < sizeof(scratch)) {
            memcpy(scratch, line, len);
            scratch[len] = '\0';
            count += parse_sensor_frame(scratch, &frames[count]) ? 1U : 0U;
        }

        if (end == 0) {
            break;
        }
        line = end + 1;
    }

    return count;
}
