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

#include <errno.h>
#include <mpack.h>
#include <string.h>

typedef union mpack_anyint {
  int8_t i8;
  int16_t i16;
  int32_t i32;
  int64_t i64;
  uint8_t u8;
  uint16_t u16;
  uint32_t u32;
  uint64_t u64;
} mpack_anyint_t;

#define MPACK_DECODE_BEGIN(self)            \
  do {                                      \
    void *save_pos = (void *)((self)->pos)

#define MPACK_DECODE_END(self)                                       \
    return ((const char *)((self)->pos)) - ((const char *)save_pos); \
  fail:                                                              \
    (self)->pos = save_pos;                                          \
    return -1;                                                       \
  } while (0)

#define MPACK_DECODE_FAIL(err) \
  do {                         \
    errno = (err);             \
    goto fail;                 \
  } while (0)

#define MPACK_DECODE_CHECK(expr) \
  do {                           \
    if (!(expr)) {               \
      MPACK_DECODE_FAIL(EAGAIN); \
    }                            \
  } while (0)

#define MPACK_DECODE_ASSERT(expr) \
  do {                            \
    if ((expr) < 0) {             \
      goto fail;                  \
    }                             \
  } while (0)

#if defined(__BYTE_ORDER__) && defined(__BIG_ENDIAN__) && (__BYTE_ORDER__ == __BIG_ENDIAN__)
static uint16_t be16(uint16_t x)
{ return x; }

static uint32_t be32(uint32_t x)
{ return x; }

static uint64_t be64(uint64_t x)
{ return x; }
#else
static uint16_t be16(uint16_t x)
{ return __builtin_bswap16(x); }

static uint32_t be32(uint32_t x)
{ return __builtin_bswap32(x); }

static uint64_t be64(uint64_t x)
{ return __builtin_bswap64(x); }
#endif /* __BYTE_ORDER__ */

void mpack_decoder_init(mpack_decoder_t *decoder, const void *data, size_t size)
{
  decoder->begin = data;
  decoder->end = data + size;
  decoder->pos = data;
}

void mpack_decoder_term(mpack_decoder_t *decoder)
{ (void)decoder; }

bool mpack_decoder_read_uint8(mpack_decoder_t *decoder, uint8_t *value)
{ return mpack_decoder_read_bytes(decoder, value, 1); }

bool mpack_decoder_read_uint16(mpack_decoder_t *decoder, uint16_t *value)
{
  uint16_t buffer;

  if (!mpack_decoder_read_bytes(decoder, &buffer, 2)) {
    return false;
  }

  *value = be16(buffer);
  return true;
}

bool mpack_decoder_read_uint32(mpack_decoder_t *decoder, uint32_t *value)
{
  uint32_t buffer;

  if (!mpack_decoder_read_bytes(decoder, &buffer, 4)) {
    return false;
  }

  *value = be32(buffer);
  return true;
}

bool mpack_decoder_read_uint64(mpack_decoder_t *decoder, uint64_t *value)
{
  uint64_t buffer;

  if (!mpack_decoder_read_bytes(decoder, &buffer, 8)) {
    return false;
  }

  *value = be64(buffer);
  return true;
}

bool mpack_decoder_read_int8(mpack_decoder_t *decoder, int8_t *value)
{ return mpack_decoder_read_uint8(decoder, (uint8_t *)value); }

bool mpack_decoder_read_int16(mpack_decoder_t *decoder, int16_t *value)
{ return mpack_decoder_read_uint16(decoder, (uint16_t *)value); }

bool mpack_decoder_read_int32(mpack_decoder_t *decoder, int32_t *value)
{ return mpack_decoder_read_uint32(decoder, (uint32_t *)value); }

bool mpack_decoder_read_int64(mpack_decoder_t *decoder, int64_t *value)
{ return mpack_decoder_read_uint64(decoder, (uint64_t *)value); }

bool mpack_decoder_read_bytes(mpack_decoder_t *decoder, void *data, size_t size)
{
  const char *pos = decoder->pos;

  if (!mpack_decoder_skip_bytes(decoder, size)) {
    return false;
  }

  memmove(data, pos, size);
  return true;
}

bool mpack_decoder_skip_bytes(mpack_decoder_t *decoder, size_t size)
{
  const char *end = decoder->end;
  const char *pos = decoder->pos + size;

  if (pos > end) {
    return false;
  }

  decoder->pos = pos;
  return true;
}

void mpack_encoder_init(mpack_encoder_t *encoder, void *data, size_t size)
{
  encoder->begin = data;
  encoder->end = data + size;
  encoder->pos = data;
}

void mpack_encoder_term(mpack_encoder_t *encoder)
{ (void)encoder; }

void mpack_encoder_write_uint8(mpack_encoder_t *encoder, uint8_t value)
{ mpack_encoder_write_bytes(encoder, &value, 1); }

void mpack_encoder_write_uint16(mpack_encoder_t *encoder, uint16_t value)
{
  value = be16(value);
  mpack_encoder_write_bytes(encoder, &value, 2);
}

void mpack_encoder_write_uint32(mpack_encoder_t *encoder, uint32_t value)
{
  value = be32(value);
  mpack_encoder_write_bytes(encoder, &value, 4);
}

void mpack_encoder_write_uint64(mpack_encoder_t *encoder, uint64_t value)
{
  value = be64(value);
  mpack_encoder_write_bytes(encoder, &value, 8);
}

void mpack_encoder_write_int8(mpack_encoder_t *encoder, int8_t value)
{ mpack_encoder_write_uint8(encoder, value); }

void mpack_encoder_write_int16(mpack_encoder_t *encoder, int16_t value)
{ mpack_encoder_write_uint16(encoder, value); }

void mpack_encoder_write_int32(mpack_encoder_t *encoder, int32_t value)
{ mpack_encoder_write_uint32(encoder, value); }

void mpack_encoder_write_int64(mpack_encoder_t *encoder, int64_t value)
{ mpack_encoder_write_uint64(encoder, value); }

void mpack_encoder_write_bytes(mpack_encoder_t *encoder, const void *data, size_t size)
{
  char *end = encoder->end;
  char *pos = encoder->pos;
  char *ptr = pos + size;

  if (ptr <= end) {
    memmove(pos, data, size);
  }
  
  encoder->pos = ptr;
}

static int mpack_decode_tag(mpack_decoder_t *decoder, int *tag)
{
  const char *pos = decoder->pos;
  const char *end = decoder->end;
  
  if (pos == end) {
    errno = EAGAIN;
    return -1;
  }

  *tag = *(const uint8_t *)pos;
  ++(decoder->pos);
  return 1;
}

static int mpack_decode_tag_equal(mpack_decoder_t *decoder, int tag)
{
  const char *pos = decoder->pos;
  const char *end = decoder->end;
  
  if (pos == end) {
    errno = EAGAIN;
    return -1;
  }

  if (((uint8_t)(*pos)) != ((uint8_t)tag)) {
    errno = EINVAL;
    return -1;
  }

  ++(decoder->pos);
  return 1;
}

int mpack_decode_nil(mpack_decoder_t *decoder)
{ return mpack_decode_tag_equal(decoder, MPACK_NIL); }

int mpack_decode_true(mpack_decoder_t *decoder)
{ return mpack_decode_tag_equal(decoder, MPACK_TRUE); }

int mpack_decode_false(mpack_decoder_t *decoder)
{ return mpack_decode_tag_equal(decoder, MPACK_FALSE); }

int mpack_decode_boolean(mpack_decoder_t *decoder, bool *value)
{
  if (mpack_decode_true(decoder) > 0) {
    *value = true;
    return 1;
  }

  if (mpack_decode_false(decoder) > 0) {
    *value = false;
    return 1;
  }

  return -1;
}

int mpack_decode_signed(mpack_decoder_t *decoder, signed long *value)
{
  MPACK_DECODE_BEGIN(decoder);
  int tag;
  mpack_anyint_t var;

  MPACK_DECODE_ASSERT(mpack_decode_tag(decoder, &tag));
  var.u64 = 0;

  if ((tag & MPACK_POSITIVE_FIXNUM_MASK) == MPACK_POSITIVE_FIXNUM) {
    *value = (int8_t)tag;
    return 1;
  }

  if ((tag & MPACK_NEGATIVE_FIXNUM_MASK) == MPACK_NEGATIVE_FIXNUM) {
    *value = (int8_t)tag;
    return 1;
  }

  switch (tag) {
  case MPACK_INT8:
    MPACK_DECODE_CHECK(mpack_decoder_read_int8(decoder, &var.i8));
    var.i64 = var.i8;
    break;

  case MPACK_INT16:
    MPACK_DECODE_CHECK(mpack_decoder_read_int16(decoder, &var.i16));
    var.i64 = var.i16;
    break;

  case MPACK_INT32:
    MPACK_DECODE_CHECK(mpack_decoder_read_int32(decoder, &var.i32));
    var.i64 = var.i32;
    break;

  case MPACK_INT64:
    MPACK_DECODE_CHECK(mpack_decoder_read_int64(decoder, &var.i64));
    break;

  case MPACK_UINT8:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint8(decoder, &var.u8));
    break;

  case MPACK_UINT16:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint16(decoder, &var.u16));
    break;

  case MPACK_UINT32:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint32(decoder, &var.u32));
    break;

  case MPACK_UINT64:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint64(decoder, &var.u64));
    if (var.u64 > INT64_MAX)
      MPACK_DECODE_FAIL(ERANGE);
    break;

  default:
    MPACK_DECODE_FAIL(EINVAL);
  }

  *value = var.i64;
  MPACK_DECODE_END(decoder);
}

int mpack_decode_unsigned(mpack_decoder_t *decoder, unsigned long *value)
{
  MPACK_DECODE_BEGIN(decoder);
  int tag;
  mpack_anyint_t var;

  MPACK_DECODE_ASSERT(mpack_decode_tag(decoder, &tag));
  var.u64 = 0;

  if ((tag & MPACK_POSITIVE_FIXNUM_MASK) == 0) {
    *value = tag;
    return 1;
  }

  if ((tag & MPACK_NEGATIVE_FIXNUM_MASK) == MPACK_NEGATIVE_FIXNUM) {
    MPACK_DECODE_FAIL(ERANGE);
  }

  switch (tag) {
  case MPACK_INT8:
    MPACK_DECODE_CHECK(mpack_decoder_read_int8(decoder, &var.i8));
    if (var.i8 < 0)
      MPACK_DECODE_FAIL(ERANGE);
    break;

  case MPACK_INT16:
    MPACK_DECODE_CHECK(mpack_decoder_read_int16(decoder, &var.i16));
    if (var.i16 < 0)
      MPACK_DECODE_FAIL(ERANGE);
    break;

  case MPACK_INT32:
    MPACK_DECODE_CHECK(mpack_decoder_read_int32(decoder, &var.i32));
    if (var.i32 < 0)
      MPACK_DECODE_FAIL(ERANGE);
    break;

  case MPACK_INT64:
    MPACK_DECODE_CHECK(mpack_decoder_read_int64(decoder, &var.i64));
    if (var.i64 < 0)
      MPACK_DECODE_FAIL(ERANGE);
    break;

  case MPACK_UINT8:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint8(decoder, &var.u8));
    break;

  case MPACK_UINT16:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint16(decoder, &var.u16));
    break;

  case MPACK_UINT32:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint32(decoder, &var.u32));
    break;

  case MPACK_UINT64:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint64(decoder, &var.u64));
    break;

  default:
    MPACK_DECODE_FAIL(EINVAL);
  }

  *value = var.u64;
  MPACK_DECODE_END(decoder);
}

int mpack_decode_float(mpack_decoder_t *decoder, float *value)
{
  union { long s; unsigned long u; } conv;
  union { uint32_t u; float f; } var;
  int size;
  
  MPACK_DECODE_BEGIN(decoder);

  if ((size = mpack_decode_unsigned(decoder, &conv.u)) > 0) {
    if (conv.u > 8388608) {
      MPACK_DECODE_FAIL(ERANGE);
    }
    *value = conv.u;
    return size;
  }

  if ((size = mpack_decode_signed(decoder, &conv.s)) > 0) {
    if ((conv.s > 8388608) || (conv.s < -8388608)) {
      MPACK_DECODE_FAIL(ERANGE);
    }
    *value = conv.s;
    return size;
  }

  MPACK_DECODE_ASSERT(mpack_decode_tag_equal(decoder, MPACK_FLOAT32));
  MPACK_DECODE_CHECK(mpack_decoder_read_uint32(decoder, &var.u));
  *value = var.f;
  MPACK_DECODE_END(decoder);
}

int mpack_decode_double(mpack_decoder_t *decoder, double *value)
{
  union { long s; unsigned long u; float f; } conv;
  union { uint64_t u; double f; } var;
  int size;
  
  MPACK_DECODE_BEGIN(decoder);

  if ((size = mpack_decode_unsigned(decoder, &conv.u)) > 0) {
    if (conv.u > 9007199254740992) {
      MPACK_DECODE_FAIL(ERANGE);
    }
    *value = conv.u;
    return size;
  }

  if ((size = mpack_decode_signed(decoder, &conv.s)) > 0) {
    if ((conv.s > 9007199254740992) || (conv.s < -9007199254740992)) {
      MPACK_DECODE_FAIL(ERANGE);
    }
    *value = conv.s;
    return size;
  }

  if ((size = mpack_decode_float(decoder, &conv.f)) > 0) {
    *value = conv.f;
    return size;
  }
  
  MPACK_DECODE_ASSERT(mpack_decode_tag_equal(decoder, MPACK_FLOAT64));
  MPACK_DECODE_CHECK(mpack_decoder_read_uint64(decoder, &var.u));
  *value = var.f;
  MPACK_DECODE_END(decoder);
}

int mpack_decode_string(mpack_decoder_t *decoder, mpack_string_t *value)
{
  MPACK_DECODE_BEGIN(decoder);
  int tag;
  size_t size;
  mpack_anyint_t var;

  MPACK_DECODE_ASSERT(mpack_decode_tag(decoder, &tag));

  if ((tag & MPACK_FIXSTR_MASK) == MPACK_FIXSTR) {
    size = tag & ~MPACK_FIXSTR_MASK;
  }
  else {
    switch (tag) {
    case MPACK_STR8:
      MPACK_DECODE_CHECK(mpack_decoder_read_uint8(decoder, &var.u8));
      size = var.u8;
      break;

    case MPACK_STR16:
      MPACK_DECODE_CHECK(mpack_decoder_read_uint16(decoder, &var.u16));
      size = var.u16;
      break;

    case MPACK_STR32:
      MPACK_DECODE_CHECK(mpack_decoder_read_uint32(decoder, &var.u32));
      size = var.u32;
      break;

    default:
      MPACK_DECODE_FAIL(EINVAL);
    }
  }

  value->data = decoder->pos;
  value->size = size;
  MPACK_DECODE_CHECK(mpack_decoder_skip_bytes(decoder, size));
  MPACK_DECODE_END(decoder);
}

int mpack_decode_binary(mpack_decoder_t *decoder, mpack_binary_t *value)
{
  MPACK_DECODE_BEGIN(decoder);
  int tag;
  size_t size;
  mpack_anyint_t var;

  MPACK_DECODE_ASSERT(mpack_decode_tag(decoder, &tag));

  switch (tag) {
  case MPACK_BIN8:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint8(decoder, &var.u8));
    size = var.u8;
    break;

  case MPACK_BIN16:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint16(decoder, &var.u16));
    size = var.u16;
    break;

  case MPACK_BIN32:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint32(decoder, &var.u32));
    size = var.u32;
    break;

  default:
    MPACK_DECODE_FAIL(EINVAL);
  }

  value->data = decoder->pos;
  value->size = size;
  MPACK_DECODE_CHECK(mpack_decoder_skip_bytes(decoder, size));
  MPACK_DECODE_END(decoder);
}

int mpack_decode_array(mpack_decoder_t *decoder, mpack_array_t *value)
{
  MPACK_DECODE_BEGIN(decoder);
  int tag;
  size_t size;
  mpack_anyint_t var;

  MPACK_DECODE_ASSERT(mpack_decode_tag(decoder, &tag));

  if ((tag & MPACK_FIXARRAY_MASK) == MPACK_FIXARRAY) {
    size = tag & ~MPACK_FIXARRAY_MASK;
  }
  else {
    switch (tag) {
    case MPACK_ARRAY16:
      MPACK_DECODE_CHECK(mpack_decoder_read_uint16(decoder, &var.u16));
      size = var.u16;
      break;

    case MPACK_ARRAY32:
      MPACK_DECODE_CHECK(mpack_decoder_read_uint32(decoder, &var.u32));
      size = var.u32;
      break;

    default:
      MPACK_DECODE_FAIL(EINVAL);
    }
  }

  value->size = size;
  MPACK_DECODE_END(decoder);
}

int mpack_decode_map(mpack_decoder_t *decoder, mpack_map_t *value)
{
  MPACK_DECODE_BEGIN(decoder);
  int tag;
  size_t size;
  mpack_anyint_t var;

  MPACK_DECODE_ASSERT(mpack_decode_tag(decoder, &tag));

  if ((tag & MPACK_FIXMAP_MASK) == MPACK_FIXMAP) {
    size = tag & ~MPACK_FIXMAP_MASK;
  }
  else {
    switch (tag) {
    case MPACK_MAP16:
      MPACK_DECODE_CHECK(mpack_decoder_read_uint16(decoder, &var.u16));
      size = var.u16;
      break;

    case MPACK_MAP32:
      MPACK_DECODE_CHECK(mpack_decoder_read_uint32(decoder, &var.u32));
      size = var.u32;
      break;

    default:
      MPACK_DECODE_FAIL(EINVAL);
    }
  }

  value->size = size;
  MPACK_DECODE_END(decoder);
}

int mpack_decode_extended(mpack_decoder_t *decoder, mpack_extended_t *value)
{
  MPACK_DECODE_BEGIN(decoder);
  int tag;
  size_t size;
  mpack_anyint_t var;

  MPACK_DECODE_ASSERT(mpack_decode_tag(decoder, &tag));

  switch (tag) {
  case MPACK_FIXEXT1:
    size = 1;
    break;

  case MPACK_FIXEXT2:
    size = 2;
    break;

  case MPACK_FIXEXT4:
    size = 4;
    break;

  case MPACK_FIXEXT8:
    size = 8;
    break;

  case MPACK_FIXEXT16:
    size = 16;
    break;

  case MPACK_EXT8:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint8(decoder, &var.u8));
    size = var.u8;
    break;

  case MPACK_EXT16:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint16(decoder, &var.u16));
    size = var.u16;
    break;

  case MPACK_EXT32:
    MPACK_DECODE_CHECK(mpack_decoder_read_uint32(decoder, &var.u32));
    size = var.u32;
    break;

  default:
    MPACK_DECODE_FAIL(EINVAL);
  }

  MPACK_DECODE_CHECK(mpack_decoder_read_int8(decoder, &var.i8));  
  value->data = decoder->pos;
  value->size = size;
  value->type = var.i8;
  MPACK_DECODE_CHECK(mpack_decoder_skip_bytes(decoder, size));
  MPACK_DECODE_END(decoder);
}

int mpack_decode_object(mpack_decoder_t *decoder, mpack_object_t *value)
{
  const char *end = decoder->end;
  const char *pos = decoder->pos;
  int tag;
  float x;

  if (pos == end) {
    errno = EAGAIN;
    return -1;
  }

  tag = (uint8_t)(*pos);

  if ((tag & MPACK_POSITIVE_FIXNUM_MASK) == MPACK_POSITIVE_FIXNUM) {
    value->type = MPACK_INTEGER;
    return mpack_decode_signed(decoder, &(value->data.integer));
  }

  if ((tag & MPACK_NEGATIVE_FIXNUM_MASK) == MPACK_NEGATIVE_FIXNUM) {
    value->type = MPACK_INTEGER;
    return mpack_decode_signed(decoder, &(value->data.integer));
  }

  if ((tag & MPACK_FIXSTR_MASK) == MPACK_FIXSTR) {
    value->type = MPACK_STRING;
    return mpack_decode_string(decoder, &(value->data.string));
  }

  if ((tag & MPACK_FIXARRAY_MASK) == MPACK_FIXARRAY) {
    value->type = MPACK_ARRAY;
    return mpack_decode_array(decoder, &(value->data.array));
  }

  if ((tag & MPACK_FIXMAP_MASK) == MPACK_FIXMAP) {
    value->type = MPACK_MAP;
    return mpack_decode_map(decoder, &(value->data.map));
  }

  switch (tag) {
  case MPACK_NIL:
    value->type = MPACK_NONE;
    return mpack_decode_nil(decoder);

  case MPACK_TRUE:
  case MPACK_FALSE:
    value->type = MPACK_BOOLEAN;
    return mpack_decode_boolean(decoder, &(value->data.boolean));

  case MPACK_INT8:
  case MPACK_INT16:
  case MPACK_INT32:
  case MPACK_INT64:
  case MPACK_UINT8:
  case MPACK_UINT16:
  case MPACK_UINT32:
  case MPACK_UINT64:
    value->type = MPACK_INTEGER;
    return mpack_decode_signed(decoder, &(value->data.integer));

  case MPACK_FLOAT32:
    value->type = MPACK_NUMBER;
    if (mpack_decode_float(decoder, &x) < 0)
      return -1;
    value->data.number = x;
    return 5;

  case MPACK_FLOAT64:
    value->type = MPACK_NUMBER;
    return mpack_decode_double(decoder, &(value->data.number));

  case MPACK_STR8:
  case MPACK_STR16:
  case MPACK_STR32:
    value->type = MPACK_STRING;
    return mpack_decode_string(decoder, &(value->data.string));

  case MPACK_BIN8:
  case MPACK_BIN16:
  case MPACK_BIN32:
    value->type = MPACK_BINARY;
    return mpack_decode_binary(decoder, &(value->data.binary));

  case MPACK_ARRAY16:
  case MPACK_ARRAY32:
    value->type = MPACK_ARRAY;
    return mpack_decode_array(decoder, &(value->data.array));

  case MPACK_MAP16:
  case MPACK_MAP32:
    value->type = MPACK_MAP;
    return mpack_decode_map(decoder, &(value->data.map));

  case MPACK_FIXEXT1:
  case MPACK_FIXEXT2:
  case MPACK_FIXEXT4:
  case MPACK_FIXEXT8:
  case MPACK_FIXEXT16:
  case MPACK_EXT8:
  case MPACK_EXT16:
  case MPACK_EXT32:
    value->type = MPACK_EXTENDED;
    return mpack_decode_extended(decoder, &(value->data.extended));

  default:
    errno = EINVAL;
    return -1;
  }
}

int mpack_encode_nil(mpack_encoder_t *encoder)
{
  mpack_encoder_write_uint8(encoder, MPACK_NIL);
  return 1;
}

int mpack_encode_true(mpack_encoder_t *encoder)
{
  mpack_encoder_write_uint8(encoder, MPACK_TRUE);
  return 1;
}

int mpack_encode_false(mpack_encoder_t *encoder)
{
  mpack_encoder_write_uint8(encoder, MPACK_FALSE);
  return 1;
}

int mpack_encode_boolean(mpack_encoder_t *encoder, bool value)
{ return value ? mpack_encode_true(encoder) : mpack_encode_false(encoder); }

int mpack_encode_signed(mpack_encoder_t *encoder, signed long value)
{
  if (value >= 0) {
    return mpack_encode_unsigned(encoder, value);
  }

  if (value >= -31) {
    mpack_encoder_write_int8(encoder, value);
    return 1;
  }

  if (value >= INT8_MIN) {
    mpack_encoder_write_uint8(encoder, MPACK_INT8);
    mpack_encoder_write_int8(encoder, value);
    return 2;
  }

  if (value >= INT16_MIN) {
    mpack_encoder_write_uint8(encoder, MPACK_INT16);
    mpack_encoder_write_int16(encoder, value);
    return 3;
  }

  if (value >= INT32_MIN) {
    mpack_encoder_write_uint8(encoder, MPACK_INT32);
    mpack_encoder_write_int32(encoder, value);
    return 5;
  }

  mpack_encoder_write_uint8(encoder, MPACK_INT64);
  mpack_encoder_write_int64(encoder, value);
  return 9;
}

int mpack_encode_unsigned(mpack_encoder_t *encoder, unsigned long value)
{
  if (value <= INT8_MAX) {
    mpack_encoder_write_uint8(encoder, value);
    return 1;
  }

  if (value <= UINT8_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_UINT8);
    mpack_encoder_write_uint8(encoder, value);
    return 2;
  }

  if (value <= UINT16_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_UINT16);
    mpack_encoder_write_uint16(encoder, value);
    return 3;
  }

  if (value <= UINT32_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_UINT32);
    mpack_encoder_write_uint32(encoder, value);
    return 5;
  }

  mpack_encoder_write_uint8(encoder, MPACK_UINT64);
  mpack_encoder_write_uint64(encoder, value);
  return 9;
}

int mpack_encode_float(mpack_encoder_t *encoder, float value)
{
  union { uint32_t u; float f; } var;
  var.f = value;
  mpack_encoder_write_uint8(encoder, MPACK_FLOAT32);
  mpack_encoder_write_uint32(encoder, var.u);
  return 5;
}

int mpack_encode_double(mpack_encoder_t *encoder, double value)
{
  union { uint64_t u; double f; } var;
  var.f = value;
  mpack_encoder_write_uint8(encoder, MPACK_FLOAT64);
  mpack_encoder_write_uint64(encoder, var.u);
  return 9;
}

int mpack_encode_string(mpack_encoder_t *encoder, mpack_string_t value)
{
  if (value.size <= 15) {
    mpack_encoder_write_uint8(encoder, MPACK_FIXSTR | value.size);
    mpack_encoder_write_bytes(encoder, value.data, value.size);
    return value.size + 1;
  }

  if (value.size <= UINT8_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_STR8);
    mpack_encoder_write_uint8(encoder, value.size);
    mpack_encoder_write_bytes(encoder, value.data, value.size);
    return value.size + 2;
  }

  if (value.size <= UINT16_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_STR16);
    mpack_encoder_write_uint16(encoder, value.size);
    mpack_encoder_write_bytes(encoder, value.data, value.size);
    return value.size + 3;
  }

  if (value.size <= UINT32_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_STR32);
    mpack_encoder_write_uint32(encoder, value.size);
    mpack_encoder_write_bytes(encoder, value.data, value.size);
    return value.size + 5;
  }

  errno = ERANGE;
  return -1;
}

int mpack_encode_binary(mpack_encoder_t *encoder, mpack_binary_t value)
{
  if (value.size <= UINT8_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_BIN8);
    mpack_encoder_write_uint8(encoder, value.size);
    mpack_encoder_write_bytes(encoder, value.data, value.size);
    return value.size + 2;
  }

  if (value.size <= UINT16_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_BIN16);
    mpack_encoder_write_uint16(encoder, value.size);
    mpack_encoder_write_bytes(encoder, value.data, value.size);
    return value.size + 3;
  }

  if (value.size <= UINT32_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_BIN32);
    mpack_encoder_write_uint32(encoder, value.size);
    mpack_encoder_write_bytes(encoder, value.data, value.size);
    return value.size + 5;
  }

  errno = ERANGE;
  return -1;
}

int mpack_encode_array(mpack_encoder_t *encoder, mpack_array_t value)
{
  if (value.size <= 15) {
    mpack_encoder_write_uint8(encoder, value.size | MPACK_FIXARRAY);
    return 1;
  }

  if (value.size <= UINT16_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_ARRAY16);
    mpack_encoder_write_uint16(encoder, value.size);
    return 3;
  }

  if (value.size <= UINT32_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_ARRAY32);
    mpack_encoder_write_uint32(encoder, value.size);
    return 5;
  }

  errno = ERANGE;
  return -1;
}

int mpack_encode_map(mpack_encoder_t *encoder, mpack_map_t value)
{
  if (value.size <= 15) {
    mpack_encoder_write_uint8(encoder, value.size | MPACK_FIXMAP);
    return 1;
  }

  if (value.size <= UINT16_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_MAP16);
    mpack_encoder_write_uint16(encoder, value.size);
    return 3;
  }

  if (value.size <= UINT32_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_MAP32);
    mpack_encoder_write_uint32(encoder, value.size);
    return 5;
  }

  errno = ERANGE;
  return -1;
}

int mpack_encode_extended(mpack_encoder_t *encoder, mpack_extended_t value)
{
  switch (value.size) {
  case 1:
    mpack_encoder_write_uint8(encoder, MPACK_FIXEXT1);
    mpack_encoder_write_int8(encoder, value.type);
    mpack_encoder_write_bytes(encoder, value.data, 1);
    return 3;

  case 2:
    mpack_encoder_write_uint8(encoder, MPACK_FIXEXT2);
    mpack_encoder_write_int8(encoder, value.type);
    mpack_encoder_write_bytes(encoder, value.data, 2);
    return 4;

  case 4:
    mpack_encoder_write_uint8(encoder, MPACK_FIXEXT4);
    mpack_encoder_write_int8(encoder, value.type);
    mpack_encoder_write_bytes(encoder, value.data, 4);
    return 6;

  case 8:
    mpack_encoder_write_uint8(encoder, MPACK_FIXEXT8);
    mpack_encoder_write_int8(encoder, value.type);
    mpack_encoder_write_bytes(encoder, value.data, 8);
    return 10;

  case 16:
    mpack_encoder_write_uint8(encoder, MPACK_FIXEXT16);
    mpack_encoder_write_int8(encoder, value.type);
    mpack_encoder_write_bytes(encoder, value.data, 16);
    return 18;
  }

  if (value.size <= UINT8_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_EXT8);
    mpack_encoder_write_uint8(encoder, value.size);
    mpack_encoder_write_int8(encoder, value.type);
    mpack_encoder_write_bytes(encoder, value.data, value.size);
    return value.size + 3;
  }

  if (value.size <= UINT16_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_EXT16);
    mpack_encoder_write_uint16(encoder, value.size);
    mpack_encoder_write_int8(encoder, value.type);
    mpack_encoder_write_bytes(encoder, value.data, value.size);
    return value.size + 4;
  }

  if (value.size <= UINT32_MAX) {
    mpack_encoder_write_uint8(encoder, MPACK_EXT32);
    mpack_encoder_write_uint32(encoder, value.size);
    mpack_encoder_write_int8(encoder, value.type);
    mpack_encoder_write_bytes(encoder, value.data, value.size);
    return value.size + 6;
  }

  errno = ERANGE;
  return -1;
}

int mpack_encode_object(mpack_encoder_t *encoder, mpack_object_t value)
{
  switch (value.type) {
  case MPACK_NONE:
    return mpack_encode_nil(encoder);
    
  case MPACK_BOOLEAN:
    return mpack_encode_boolean(encoder, value.data.boolean);

  case MPACK_INTEGER:
    return mpack_encode_signed(encoder, value.data.integer);

  case MPACK_NUMBER:
    return mpack_encode_double(encoder, value.data.number);

  case MPACK_STRING:
    return mpack_encode_string(encoder, value.data.string);

  case MPACK_BINARY:
    return mpack_encode_binary(encoder, value.data.binary);

  case MPACK_ARRAY:
    return mpack_encode_array(encoder, value.data.array);

  case MPACK_MAP:
    return mpack_encode_map(encoder, value.data.map);

  case MPACK_EXTENDED:
    return mpack_encode_extended(encoder, value.data.extended);

  default:
    errno = EINVAL;
    return -1;
  }
}
