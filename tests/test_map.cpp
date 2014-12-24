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

BOOST_AUTO_TEST_CASE(test_encode_decode_fixmap)
{
  char buffer[32] = { 0 };
  mpack_map_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.size = 0;
  BOOST_CHECK(mpack_encode_map(&encoder, value) == 1);

  value.size = 15;
  BOOST_CHECK(mpack_encode_map(&encoder, value) == 1);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 2);

  value.size = 0;
  BOOST_CHECK(mpack_decode_map(&decoder, &value) == 1);
  BOOST_CHECK(value.size == 0);

  value.size = 0;
  BOOST_CHECK(mpack_decode_map(&decoder, &value) == 1);
  BOOST_CHECK(value.size == 15);

  value.size = 0;
  BOOST_CHECK(mpack_decode_map(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_map16)
{
  char buffer[32] = { 0 };
  mpack_map_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.size = 16;
  BOOST_CHECK(mpack_encode_map(&encoder, value) == 3);

  value.size = 65535;
  BOOST_CHECK(mpack_encode_map(&encoder, value) == 3);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 6);

  value.size = 0;
  BOOST_CHECK(mpack_decode_map(&decoder, &value) == 3);
  BOOST_CHECK(value.size == 16);

  value.size = 0;
  BOOST_CHECK(mpack_decode_map(&decoder, &value) == 3);
  BOOST_CHECK(value.size == 65535);

  value.size = 0;
  BOOST_CHECK(mpack_decode_map(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_map32)
{
  char buffer[32] = { 0 };
  mpack_map_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.size = 65536;
  BOOST_CHECK(mpack_encode_map(&encoder, value) == 5);

  value.size = 4294967295U;
  BOOST_CHECK(mpack_encode_map(&encoder, value) == 5);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 10);

  value.size = 0;
  BOOST_CHECK(mpack_decode_map(&decoder, &value) == 5);
  BOOST_CHECK(value.size == 65536);

  value.size = 0;
  BOOST_CHECK(mpack_decode_map(&decoder, &value) == 5);
  BOOST_CHECK(value.size == 4294967295U);

  value.size = 0;
  BOOST_CHECK(mpack_decode_map(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}
