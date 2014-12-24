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

#include <cstring>
#include <boost/test/unit_test.hpp>
#include <mpack.h>

BOOST_AUTO_TEST_CASE(test_read_write_bytes)
{
  char buffer[32] = { 0 };
  mpack_decoder_t decoder;
  mpack_encoder_t encoder;

  mpack_decoder_init(&decoder, buffer, sizeof(buffer));
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  mpack_encoder_write_bytes(&encoder, "Hello World!", 12);

  char string[16] = { 0 };
  BOOST_CHECK(mpack_decoder_read_bytes(&decoder, string, 12));
  BOOST_CHECK(strcmp(string, "Hello World!") == 0);

  mpack_encoder_term(&encoder);
  mpack_decoder_term(&decoder);
}

BOOST_AUTO_TEST_CASE(test_read_write_uint8)
{
  char buffer[32] = { 0 };
  mpack_decoder_t decoder;
  mpack_encoder_t encoder;

  mpack_decoder_init(&decoder, buffer, sizeof(buffer));
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  mpack_encoder_write_uint8(&encoder, 42);

  uint8_t value = 0;
  BOOST_CHECK(mpack_decoder_read_uint8(&decoder, &value));
  BOOST_CHECK(value == 42);

  mpack_encoder_term(&encoder);
  mpack_decoder_term(&decoder);
}

BOOST_AUTO_TEST_CASE(test_read_write_uint16)
{
  char buffer[32] = { 0 };
  mpack_decoder_t decoder;
  mpack_encoder_t encoder;

  mpack_decoder_init(&decoder, buffer, sizeof(buffer));
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  mpack_encoder_write_uint16(&encoder, 42);

  uint16_t value = 0;
  BOOST_CHECK(mpack_decoder_read_uint16(&decoder, &value));
  BOOST_CHECK(value == 42);

  mpack_encoder_term(&encoder);
  mpack_decoder_term(&decoder);
}

BOOST_AUTO_TEST_CASE(test_read_write_uint32)
{
  char buffer[32] = { 0 };
  mpack_decoder_t decoder;
  mpack_encoder_t encoder;

  mpack_decoder_init(&decoder, buffer, sizeof(buffer));
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  mpack_encoder_write_uint32(&encoder, 42);

  uint32_t value = 0;
  BOOST_CHECK(mpack_decoder_read_uint32(&decoder, &value));
  BOOST_CHECK(value == 42);

  mpack_encoder_term(&encoder);
  mpack_decoder_term(&decoder);
}

BOOST_AUTO_TEST_CASE(test_read_write_uint64)
{
  char buffer[32] = { 0 };
  mpack_decoder_t decoder;
  mpack_encoder_t encoder;

  mpack_decoder_init(&decoder, buffer, sizeof(buffer));
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  mpack_encoder_write_uint64(&encoder, 42);

  uint64_t value = 0;
  BOOST_CHECK(mpack_decoder_read_uint64(&decoder, &value));
  BOOST_CHECK(value == 42);

  mpack_encoder_term(&encoder);
  mpack_decoder_term(&decoder);
}

BOOST_AUTO_TEST_CASE(test_read_write_int8)
{
  char buffer[32] = { 0 };
  mpack_decoder_t decoder;
  mpack_encoder_t encoder;

  mpack_decoder_init(&decoder, buffer, sizeof(buffer));
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  mpack_encoder_write_int8(&encoder, 42);

  int8_t value = 0;
  BOOST_CHECK(mpack_decoder_read_int8(&decoder, &value));
  BOOST_CHECK(value == 42);

  mpack_encoder_term(&encoder);
  mpack_decoder_term(&decoder);
}

BOOST_AUTO_TEST_CASE(test_read_write_int16)
{
  char buffer[32] = { 0 };
  mpack_decoder_t decoder;
  mpack_encoder_t encoder;

  mpack_decoder_init(&decoder, buffer, sizeof(buffer));
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  mpack_encoder_write_int16(&encoder, 42);

  int16_t value = 0;
  BOOST_CHECK(mpack_decoder_read_int16(&decoder, &value));
  BOOST_CHECK(value == 42);

  mpack_encoder_term(&encoder);
  mpack_decoder_term(&decoder);
}

BOOST_AUTO_TEST_CASE(test_read_write_int32)
{
  char buffer[32] = { 0 };
  mpack_decoder_t decoder;
  mpack_encoder_t encoder;

  mpack_decoder_init(&decoder, buffer, sizeof(buffer));
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  mpack_encoder_write_int32(&encoder, 42);

  int32_t value = 0;
  BOOST_CHECK(mpack_decoder_read_int32(&decoder, &value));
  BOOST_CHECK(value == 42);

  mpack_encoder_term(&encoder);
  mpack_decoder_term(&decoder);
}

BOOST_AUTO_TEST_CASE(test_read_write_int64)
{
  char buffer[32] = { 0 };
  mpack_decoder_t decoder;
  mpack_encoder_t encoder;

  mpack_decoder_init(&decoder, buffer, sizeof(buffer));
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  mpack_encoder_write_int64(&encoder, 42);

  int64_t value = 0;
  BOOST_CHECK(mpack_decoder_read_int64(&decoder, &value));
  BOOST_CHECK(value == 42);

  mpack_encoder_term(&encoder);
  mpack_decoder_term(&decoder);
}
