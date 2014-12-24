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

BOOST_AUTO_TEST_CASE(test_encode_decode_float)
{
  char buffer[32] = { 0 };
  float value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  BOOST_CHECK(mpack_encode_float(&encoder, 0.0f) == 5);
  BOOST_CHECK(mpack_encode_float(&encoder, 1.234f) == 5);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 10);

  BOOST_CHECK(mpack_decode_float(&decoder, &value) == 5);
  BOOST_CHECK(value == 0.0f);

  BOOST_CHECK(mpack_decode_float(&decoder, &value) == 5);
  BOOST_CHECK(value == 1.234f);
  
  BOOST_CHECK(mpack_decode_float(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_double)
{
  char buffer[32] = { 0 };
  double value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  BOOST_CHECK(mpack_encode_double(&encoder, 0.0) == 9);
  BOOST_CHECK(mpack_encode_double(&encoder, 1.234) == 9);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 18);

  BOOST_CHECK(mpack_decode_double(&decoder, &value) == 9);
  BOOST_CHECK(value == 0.0);

  BOOST_CHECK(mpack_decode_double(&decoder, &value) == 9);
  BOOST_CHECK(value == 1.234);
  
  BOOST_CHECK(mpack_decode_double(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_convert_integer_to_float)
{
  char buffer[32] = { 0 };
  float value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  BOOST_CHECK(mpack_encode_signed(&encoder, -42) == 2);
  BOOST_CHECK(mpack_encode_unsigned(&encoder, 42) == 1);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 3);

  BOOST_CHECK(mpack_decode_float(&decoder, &value) == 2);
  BOOST_CHECK(value == -42.0f);

  BOOST_CHECK(mpack_decode_float(&decoder, &value) == 1);
  BOOST_CHECK(value == 42.0f);
  
  BOOST_CHECK(mpack_decode_float(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_convert_integer_to_double)
{
  char buffer[32] = { 0 };
  double value;

  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  BOOST_CHECK(mpack_encode_signed(&encoder, -42) == 2);
  BOOST_CHECK(mpack_encode_unsigned(&encoder, 42) == 1);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 3);

  BOOST_CHECK(mpack_decode_double(&decoder, &value) == 2);
  BOOST_CHECK(value == -42.0f);

  BOOST_CHECK(mpack_decode_double(&decoder, &value) == 1);
  BOOST_CHECK(value == 42.0f);
  
  BOOST_CHECK(mpack_decode_double(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}
