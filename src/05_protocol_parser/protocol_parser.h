#ifndef PROTOCOL_PARSER_H
#define PROTOCOL_PARSER_H

#include <stddef.h>

typedef struct SensorFrame {
    double ch4_ppm;
    double temp_c;
    int valid;
} SensorFrame;

int parse_sensor_frame(const char *line, SensorFrame *frame);
size_t parse_stream(const char *stream, SensorFrame *frames, size_t frame_capacity);

#endif
