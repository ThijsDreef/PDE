#pragma once

const inline uint64_t hash(const char* str) {
    uint64_t hash = 5381;
    uint64_t c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
