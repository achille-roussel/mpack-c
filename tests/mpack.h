/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Achille Roussel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MPACK_H
#define MPACK_H

#ifdef __cplusplus
# include <cstdbool>
# include <cstddef>
# include <cstdint>
extern "C" {
#else
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
#endif /* __cplusplus */

enum {
  MPACK_1BIT_MASK = (1 << 7),
  MPACK_2BIT_MASK = (1 << 6) | MPACK_1BIT_MASK,
  MPACK_3BIT_MASK = (1 << 5) | MPACK_2BIT_MASK,
  MPACK_4BIT_MASK = (1 << 4) | MPACK_3BIT_MASK,
  MPACK_POSITIVE_FIXNUM_MASK = MPACK_1BIT_MASK,
  MPACK_NEGATIVE_FIXNUM_MASK = MPACK_3BIT_MASK,
  MPACK_FIXSTR_MASK = MPACK_3BIT_MASK,
  MPACK_FIXARRAY_MASK = MPACK_4BIT_MASK,
  MPACK_FIXMAP_MASK = MPACK_4BIT_MASK,
};

typedef enum mpack_format {
  MPACK_NIL = 0xc0,
  MPACK_TRUE = 0xc2,
  MPACK_FALSE = 0xc3,
  MPACK_POSITIVE_FIXNUM = 0,
  MPACK_NEGATIVE_FIXNUM = 0xe0,
  MPACK_INT8 = 0xd0,
  MPACK_INT16 = 0xd1,
  MPACK_INT32 = 0xd2,
  MPACK_INT64 = 0xd3,
  MPACK_UINT8 = 0xcc,
  MPACK_UINT16 = 0xcd,
  MPACK_UINT32 = 0xce,
  MPACK_UINT64 = 0xcf,
  MPACK_FLOAT32 = 0xca,
  MPACK_FLOAT64 = 0xcb,
  MPACK_FIXSTR = 0xa0,
  MPACK_STR8 = 0xd9,
  MPACK_STR16 = 0xda,
  MPACK_STR32 = 0xdb,
  MPACK_BIN8 = 0xc4,
  MPACK_BIN16 = 0xc5,
  MPACK_BIN32 = 0xc6,
  MPACK_FIXARRAY = 0x90,
  MPACK_ARRAY16 = 0xdc,
  MPACK_ARRAY32 = 0xdd,
  MPACK_FIXMAP = 0x80,
  MPACK_MAP16 = 0xde,
  MPACK_MAP32 = 0xdf,
  MPACK_FIXEXT1 = 0xd4,
  MPACK_FIXEXT2 = 0xd5,
  MPACK_FIXEXT4 = 0x6,
  MPACK_FIXEXT8 = 0xd7,
  MPACK_FIXEXT16 = 0xd8,
  MPACK_EXT8 = 0xc7,
  MPACK_EXT16 = 0xc8,
  MPACK_EXT32 = 0xc9,
} mpack_format_t;

typedef enum mpack_type {
  MPACK_NONE,
  MPACK_BOOLEAN,
  MPACK_INTEGER,
  MPACK_NUMBER,
  MPACK_STRING,
  MPACK_BINARY,
  MPACK_ARRAY,
  MPACK_MAP,
  MPACK_EXTENDED,
} mpack_type_t;

typedef struct mpack_decoder {
  const char *begin;
  const char *end;
  const char *pos;
} mpack_decoder_t;

typedef struct mpack_encoder {
  char *begin;
  char *end;
  char *pos;
} mpack_encoder_t;

typedef struct mpack_string {
  const char *data;
  size_t size;
} mpack_string_t;

typedef struct mpack_binary {
  const void *data;
  size_t size;
} mpack_binary_t;

typedef struct mpack_array {
  size_t size;
} mpack_array_t;

typedef struct mpack_map {
  size_t size;
} mpack_map_t;

typedef struct mpack_extended {
  const void *data;
  size_t size;
  int8_t type;
} mpack_extended_t;

typedef union mpack_any {
  bool boolean;
  signed long integer;
  double number;
  mpack_string_t string;
  mpack_binary_t binary;
  mpack_array_t array;
  mpack_map_t map;
  mpack_extended_t extended;
} mpack_any_t;

typedef struct mpack_object {
  mpack_type_t type;
  mpack_any_t data;
} mpack_object_t;

void mpack_decoder_init(mpack_decoder_t *decoder, const void *data, size_t size);
void mpack_decoder_term(mpack_decoder_t *decoder);
bool mpack_decoder_read_uint8(mpack_decoder_t *decoder, uint8_t *value);
bool mpack_decoder_read_uint16(mpack_decoder_t *decoder, uint16_t *value);
bool mpack_decoder_read_uint32(mpack_decoder_t *decoder, uint32_t *value);
bool mpack_decoder_read_uint64(mpack_decoder_t *decoder, uint64_t *value);
bool mpack_decoder_read_int8(mpack_decoder_t *decoder, int8_t *value);
bool mpack_decoder_read_int16(mpack_decoder_t *decoder, int16_t *value);
bool mpack_decoder_read_int32(mpack_decoder_t *decoder, int32_t *value);
bool mpack_decoder_read_int64(mpack_decoder_t *decoder, int64_t *value);
bool mpack_decoder_read_bytes(mpack_decoder_t *decoder, void *data, size_t size);
bool mpack_decoder_skip_bytes(mpack_decoder_t *decoder, size_t size);

void mpack_encoder_init(mpack_encoder_t *encoder, void *data, size_t size);
void mpack_encoder_term(mpack_encoder_t *encoder);
void mpack_encoder_write_uint8(mpack_encoder_t *encoder, uint8_t value);
void mpack_encoder_write_uint16(mpack_encoder_t *encoder, uint16_t value);
void mpack_encoder_write_uint32(mpack_encoder_t *encoder, uint32_t value);
void mpack_encoder_write_uint64(mpack_encoder_t *encoder, uint64_t value);
void mpack_encoder_write_int8(mpack_encoder_t *encoder, int8_t value);
void mpack_encoder_write_int16(mpack_encoder_t *encoder, int16_t value);
void mpack_encoder_write_int32(mpack_encoder_t *encoder, int32_t value);
void mpack_encoder_write_int64(mpack_encoder_t *encoder, int64_t value);
void mpack_encoder_write_bytes(mpack_encoder_t *encoder, const void *data, size_t size);

int mpack_decode_nil(mpack_decoder_t *decoder);
int mpack_decode_true(mpack_decoder_t *decoder);
int mpack_decode_false(mpack_decoder_t *decoder);
int mpack_decode_boolean(mpack_decoder_t *decoder, bool *value);
int mpack_decode_signed(mpack_decoder_t *decoder, signed long *value);
int mpack_decode_unsigned(mpack_decoder_t *decoder, unsigned long *value);
int mpack_decode_float(mpack_decoder_t *decoder, float *value);
int mpack_decode_double(mpack_decoder_t *decoder, double *value);
int mpack_decode_string(mpack_decoder_t *decoder, mpack_string_t *value);
int mpack_decode_binary(mpack_decoder_t *decoder, mpack_binary_t *value);
int mpack_decode_array(mpack_decoder_t *decoder, mpack_array_t *value);
int mpack_decode_map(mpack_decoder_t *decoder, mpack_map_t *value);
int mpack_decode_extended(mpack_decoder_t *decoder, mpack_extended_t *value);
int mpack_decode_object(mpack_decoder_t *decoder, mpack_object_t *value);

int mpack_encode_nil(mpack_encoder_t *encoder);
int mpack_encode_true(mpack_encoder_t *encoder);
int mpack_encode_false(mpack_encoder_t *encoder);
int mpack_encode_boolean(mpack_encoder_t *encoder, bool value);
int mpack_encode_signed(mpack_encoder_t *encoder, signed long value);
int mpack_encode_unsigned(mpack_encoder_t *encoder, unsigned long value);
int mpack_encode_float(mpack_encoder_t *encoder, float value);
int mpack_encode_double(mpack_encoder_t *encoder, double value);
int mpack_encode_string(mpack_encoder_t *encoder, mpack_string_t value);
int mpack_encode_binary(mpack_encoder_t *encoder, mpack_binary_t value);
int mpack_encode_array(mpack_encoder_t *encoder, mpack_array_t value);
int mpack_encode_map(mpack_encoder_t *encoder, mpack_map_t value);
int mpack_encode_extended(mpack_encoder_t *encoder, mpack_extended_t value);
int mpack_encode_object(mpack_encoder_t *encoder, mpack_object_t value);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* MPACK_H */
