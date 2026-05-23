#ifndef SERIAL_PARSER_H
#define SERIAL_PARSER_H

#include <stddef.h>
#include <stdint.h>

typedef struct SerialFrame {
    uint8_t id;
    uint8_t payload[8];
    size_t length;
} SerialFrame;

typedef struct SerialParser {
    uint8_t buffer[16];
    size_t index;
    size_t expected;
    int in_frame;
} SerialParser;

void serial_parser_init(SerialParser *parser);
int serial_parser_feed(SerialParser *parser, uint8_t byte, SerialFrame *out_frame);

#endif
