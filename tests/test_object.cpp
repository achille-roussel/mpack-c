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

#include <cerrno>
#include <boost/test/unit_test.hpp>
#include <mpack.h>

BOOST_AUTO_TEST_CASE(test_encode_decode_object_nil)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_NONE;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 1);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 1);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 1);
  BOOST_CHECK(value.type == MPACK_NONE);
  
  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_true)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_BOOLEAN;
  value.data.boolean = true;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 1);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 1);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 1);
  BOOST_CHECK(value.type == MPACK_BOOLEAN);
  BOOST_CHECK(value.data.boolean == true);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_false)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_BOOLEAN;
  value.data.boolean = false;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 1);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 1);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 1);
  BOOST_CHECK(value.type == MPACK_BOOLEAN);
  BOOST_CHECK(value.data.boolean == false);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_positive_fixnum)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_INTEGER;
  value.data.integer = 42;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 1);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 1);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 1);
  BOOST_CHECK(value.type == MPACK_INTEGER);
  BOOST_CHECK(value.data.integer == 42);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_negative_fixnum)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_INTEGER;
  value.data.integer = -1;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 1);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 1);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 1);
  BOOST_CHECK(value.type == MPACK_INTEGER);
  BOOST_CHECK(value.data.integer == -1);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_int8)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_INTEGER;
  value.data.integer = 200;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 2);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 2);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 2);
  BOOST_CHECK(value.type == MPACK_INTEGER);
  BOOST_CHECK(value.data.integer == 200);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_int16)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_INTEGER;
  value.data.integer = 2000;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 3);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 3);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 3);
  BOOST_CHECK(value.type == MPACK_INTEGER);
  BOOST_CHECK(value.data.integer == 2000);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_int32)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_INTEGER;
  value.data.integer = 200000;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 5);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 5);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 5);
  BOOST_CHECK(value.type == MPACK_INTEGER);
  BOOST_CHECK(value.data.integer == 200000);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_int64)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_INTEGER;
  value.data.integer = 20000000000L;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 9);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 9);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 9);
  BOOST_CHECK(value.type == MPACK_INTEGER);
  BOOST_CHECK(value.data.integer == 20000000000L);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_float64)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_NUMBER;
  value.data.number = 1.234;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 9);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 9);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 9);
  BOOST_CHECK(value.type == MPACK_NUMBER);
  BOOST_CHECK(value.data.number == 1.234);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_string)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_STRING;
  value.data.string.data = "Hello World!";
  value.data.string.size = 12;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 13);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 13);

  value.type = MPACK_NONE;
  value.data.string.data = NULL;
  value.data.string.size = 0;
  
  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 13);
  BOOST_CHECK(value.type == MPACK_STRING);
  BOOST_CHECK(value.data.string.data != NULL);
  BOOST_CHECK(value.data.string.size == 12);
  BOOST_CHECK(memcmp(value.data.string.data, "Hello World!", 12) == 0);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_binary)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_BINARY;
  value.data.binary.data = "Hello World!";
  value.data.binary.size = 12;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 14);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 14);

  value.type = MPACK_NONE;
  value.data.binary.data = NULL;
  value.data.binary.size = 0;
  
  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 14);
  BOOST_CHECK(value.type == MPACK_BINARY);
  BOOST_CHECK(value.data.binary.data != NULL);
  BOOST_CHECK(value.data.binary.size == 12);
  BOOST_CHECK(memcmp(value.data.binary.data, "Hello World!", 12) == 0);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_array)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_ARRAY;
  value.data.array.size = 12;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 1);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 1);

  value.type = MPACK_NONE;
  value.data.array.size = 0;
  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 1);
  BOOST_CHECK(value.type == MPACK_ARRAY);
  BOOST_CHECK(value.data.array.size == 12);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_map)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_MAP;
  value.data.map.size = 12;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 1);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 1);

  value.type = MPACK_NONE;
  value.data.map.size = 0;
  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 1);
  BOOST_CHECK(value.type == MPACK_MAP);
  BOOST_CHECK(value.data.map.size == 12);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_object_extended)
{
  char buffer[32] = { 0 };
  mpack_object_t value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.type = MPACK_EXTENDED;
  value.data.extended.data = "Hello World!";
  value.data.extended.size = 12;
  value.data.extended.type = 42;
  BOOST_CHECK(mpack_encode_object(&encoder, value) == 15);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 15);

  value.type = MPACK_NONE;
  value.data.extended.data = NULL;
  value.data.extended.size = 0;
  value.data.extended.type = 0;
  
  BOOST_CHECK(mpack_decode_object(&decoder, &value) == 15);
  BOOST_CHECK(value.type == MPACK_EXTENDED);
  BOOST_CHECK(value.data.extended.data != NULL);
  BOOST_CHECK(value.data.extended.size == 12);
  BOOST_CHECK(value.data.extended.type == 42);
  BOOST_CHECK(memcmp(value.data.extended.data, "Hello World!", 12) == 0);

  BOOST_CHECK(mpack_decode_object(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}
