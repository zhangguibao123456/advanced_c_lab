#include "serial_parser.h"

#define FRAME_START 0xAAU

static uint8_t checksum(const uint8_t *data, size_t count) {
    uint8_t sum = 0;
    for (size_t i = 0; i < count; ++i) {
        sum = (uint8_t)(sum + data[i]);
    }
    return sum;
}

void serial_parser_init(SerialParser *parser) {
    parser->index = 0;
    parser->expected = 0;
    parser->in_frame = 0;
}

int serial_parser_feed(SerialParser *parser, uint8_t byte, SerialFrame *out_frame) {
    if (!parser->in_frame) {
        if (byte == FRAME_START) {
            parser->in_frame = 1;
            parser->index = 0;
            parser->expected = 0;
        }
        return 0;
    }

    parser->buffer[parser->index++] = byte;
    if (parser->index == 2U) {
        parser->expected = (size_t)parser->buffer[1] + 3U;
        if (parser->buffer[1] > sizeof(out_frame->payload) ||
            parser->expected > sizeof(parser->buffer)) {
            parser->in_frame = 0;
            return 0;
        }
    }

    if (parser->expected != 0U && parser->index == parser->expected) {
        const uint8_t got = parser->buffer[parser->index - 1U];
        const uint8_t want = checksum(parser->buffer, parser->index - 1U);
        parser->in_frame = 0;
        if (got != want) {
            return 0;
        }

        out_frame->id = parser->buffer[0];
        out_frame->length = parser->buffer[1];
        for (size_t i = 0; i < out_frame->length; ++i) {
            out_frame->payload[i] = parser->buffer[2U + i];
        }
        return 1;
    }

    return 0;
}
