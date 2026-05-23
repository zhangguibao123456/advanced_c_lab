#include "serial_parser.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const uint8_t stream[] = {
        0x00, 0xAA, 0x10, 0x03, 'C',  'H', '4', (uint8_t)(0x10 + 0x03 + 'C' + 'H' + '4'),
        0xAA, 0x20, 0x01, 0x99, 0x00,
    };

    SerialParser parser;
    SerialFrame frame;
    serial_parser_init(&parser);

    size_t frames = 0;
    for (size_t i = 0; i < sizeof(stream); ++i) {
        if (serial_parser_feed(&parser, stream[i], &frame)) {
            frames++;
            printf("frame id=0x%02X len=%zu\n", frame.id, frame.length);
        }
    }

    return frames == 1U && frame.id == 0x10U && frame.length == 3U ? EXIT_SUCCESS : EXIT_FAILURE;
}
