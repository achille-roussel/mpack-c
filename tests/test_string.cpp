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
#include <string>
#include <boost/test/unit_test.hpp>
#include <mpack.h>

BOOST_AUTO_TEST_CASE(test_encode_decode_fixstr)
{
  char buffer[32] = { 0 };
  mpack_string_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, buffer, sizeof(buffer));

  value.data = "";
  value.size = 0;
  BOOST_CHECK(mpack_encode_string(&encoder, value) == 1);

  value.data = "Hello World!";
  value.size = 12;
  BOOST_CHECK(mpack_encode_string(&encoder, value) == 13);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer, 14);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_string(&decoder, &value) == 1);
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_string(&decoder, &value) == 13);
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == 12);
  BOOST_CHECK(memcmp(value.data, "Hello World!", 12) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_string(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_str8)
{
  std::string buffer;
  std::string string;
  buffer.resize(100000);

  mpack_string_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, const_cast<char*>(buffer.data()), buffer.size());

  string.insert(0, 200, 'a');
  value.data = string.data();
  value.size = string.size();
  BOOST_CHECK(mpack_encode_string(&encoder, value) == static_cast<int>(value.size + 2));

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer.data(), value.size + 2);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_string(&decoder, &value) == static_cast<int>(value.size + 2));
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_string(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_str16)
{
  std::string buffer;
  std::string string;
  buffer.resize(100000);

  mpack_string_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, const_cast<char*>(buffer.data()), buffer.size());

  string.insert(0, 10000, '*');
  value.data = string.data();
  value.size = string.size();
  BOOST_CHECK(mpack_encode_string(&encoder, value) == static_cast<int>(value.size + 3));

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer.data(), value.size + 3);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_string(&decoder, &value) == static_cast<int>(value.size + 3));
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_string(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_str32)
{
  std::string buffer;
  std::string string;
  buffer.resize(100000);

  mpack_string_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, const_cast<char*>(buffer.data()), buffer.size());

  string.insert(0, 80000, '+');
  value.data = string.data();
  value.size = string.size();
  BOOST_CHECK(mpack_encode_string(&encoder, value) == static_cast<int>(value.size + 5));

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer.data(), value.size + 5);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_string(&decoder, &value) == static_cast<int>(value.size + 5));
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_string(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}
