/*
 * @file tempbuffer.c
 * @author XueShuming
 * @date 2021/08/27
 * @brief The impl of tempbuffer.
 *
 * Copyright (C) 2021 FMSoft <https://www.fmsoft.cn>
 *
 * This file is a part of PurC (short for Purring Cat), an HVML interpreter.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "config.h"
#include "purc-utils.h"
#include "purc-errors.h"
#include "private/errors.h"
#include "tempbuffer.h"

#define MIN_BUFFER_CAPACITY 32

static size_t get_buffer_size (size_t sz)
{
    size_t sz_buf = pcutils_get_next_fibonacci_number(sz);
    return sz_buf < MIN_BUFFER_CAPACITY ? MIN_BUFFER_CAPACITY : sz_buf;
}

struct temp_buffer* temp_buffer_new (size_t sz_init)
{
    struct temp_buffer* buffer = (struct temp_buffer*) calloc(
            1, sizeof(struct temp_buffer));
    sz_init = get_buffer_size(sz_init);
    buffer->base = (uint8_t*) calloc (1, sz_init + 1);
    buffer->here = buffer->base;
    buffer->stop = buffer->base + sz_init;
    buffer->sz_char = 0;
    return buffer;
}

bool temp_buffer_is_empty (struct temp_buffer* buffer)
{
    return buffer->here == buffer->base;
}

size_t temp_buffer_get_memory_size (struct temp_buffer* buffer)
{
    return buffer->here - buffer->base;
}

size_t temp_buffer_get_char_size (struct temp_buffer* buffer)
{
    return buffer->sz_char;
}

void temp_buffer_append (struct temp_buffer* buffer,
        const char* bytes, size_t nr_bytes, wchar_t wc)
{
    uint8_t* newpos = buffer->here + nr_bytes;
    if ( newpos > buffer->stop ) {
        size_t new_size = get_buffer_size(buffer->stop - buffer->base);
        off_t here_offset = buffer->here - buffer->base;

        uint8_t* newbuf = (uint8_t*) realloc(buffer->base, new_size + 1);
        if (newbuf == NULL) {
            pcinst_set_error(PURC_ERROR_OUT_OF_MEMORY);
            return;
        }

        buffer->base = newbuf;
        buffer->here = buffer->base + here_offset;
        buffer->stop = buffer->base + new_size;
    }

    memcpy(buffer->here, bytes, nr_bytes);
    buffer->here += nr_bytes;
    buffer->last_wc = wc;
    buffer->sz_char++;
}

const char* temp_buffer_get_buffer (
        struct temp_buffer* buffer)
{
    return (const char*)buffer->base;
}

bool temp_buffer_end_with (struct temp_buffer* buffer,
        const char* bytes, size_t nr_bytes)
{
    size_t sz = temp_buffer_get_memory_size(buffer);
    return (sz >= nr_bytes 
            && memcmp(buffer->here - nr_bytes, bytes, nr_bytes) == 0);
}

bool temp_buffer_is_equal (struct temp_buffer* buffer,
        const char* bytes, size_t nr_bytes)
{
    size_t sz = temp_buffer_get_memory_size(buffer);
    return (sz == nr_bytes && memcmp(buffer->base, bytes, sz) == 0);
}

wchar_t temp_buffer_get_last_wchar_t (struct temp_buffer* buffer)
{
    return buffer->last_wc;
}

void temp_buffer_reset (struct temp_buffer* buffer)
{
    buffer->here = buffer->base;
    buffer->last_wc = 0;
    buffer->sz_char = 0;
}

void temp_buffer_destroy (struct temp_buffer* buffer)
{
    if (buffer) {
        free(buffer->base);
        free(buffer);
    }
}
