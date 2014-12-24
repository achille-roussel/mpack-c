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

BOOST_AUTO_TEST_CASE(test_encode_decode_fixext1)
{
  std::string buffer;
  std::string string;
  buffer.resize(100);

  mpack_extended_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, const_cast<char*>(buffer.data()), buffer.size());

  string.insert(0, 1, 'a');
  value.data = string.data();
  value.size = string.size();
  value.type = 42;
  BOOST_CHECK(mpack_encode_extended(&encoder, value) == 3);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer.data(), 3);

  value.data = NULL;
  value.size = 0;
  value.type = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == 3);
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(value.type == 42);
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_fixext2)
{
  std::string buffer;
  std::string string;
  buffer.resize(100);

  mpack_extended_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, const_cast<char*>(buffer.data()), buffer.size());

  string.insert(0, 2, 'a');
  value.data = string.data();
  value.size = string.size();
  value.type = 42;
  BOOST_CHECK(mpack_encode_extended(&encoder, value) == 4);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer.data(), 4);

  value.data = NULL;
  value.size = 0;
  value.type = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == 4);
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(value.type == 42);
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_fixext4)
{
  std::string buffer;
  std::string string;
  buffer.resize(100);

  mpack_extended_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, const_cast<char*>(buffer.data()), buffer.size());

  string.insert(0, 4, 'a');
  value.data = string.data();
  value.size = string.size();
  value.type = 42;
  BOOST_CHECK(mpack_encode_extended(&encoder, value) == 6);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer.data(), 6);

  value.data = NULL;
  value.size = 0;
  value.type = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == 6);
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(value.type == 42);
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_fixext8)
{
  std::string buffer;
  std::string string;
  buffer.resize(100);

  mpack_extended_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, const_cast<char*>(buffer.data()), buffer.size());

  string.insert(0, 8, 'a');
  value.data = string.data();
  value.size = string.size();
  value.type = 42;
  BOOST_CHECK(mpack_encode_extended(&encoder, value) == 10);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer.data(), 10);

  value.data = NULL;
  value.size = 0;
  value.type = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == 10);
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(value.type == 42);
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_fixext16)
{
  std::string buffer;
  std::string string;
  buffer.resize(100);

  mpack_extended_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, const_cast<char*>(buffer.data()), buffer.size());

  string.insert(0, 16, 'a');
  value.data = string.data();
  value.size = string.size();
  value.type = 42;
  BOOST_CHECK(mpack_encode_extended(&encoder, value) == 18);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer.data(), 18);

  value.data = NULL;
  value.size = 0;
  value.type = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == 18);
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(value.type == 42);
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_ext8)
{
  std::string buffer;
  std::string string;
  buffer.resize(100000);

  mpack_extended_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, const_cast<char*>(buffer.data()), buffer.size());

  string.insert(0, 100, 'a');
  value.data = string.data();
  value.size = string.size();
  value.type = 42;
  BOOST_CHECK(mpack_encode_extended(&encoder, value) == 103);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer.data(), 103);

  value.data = NULL;
  value.size = 0;
  value.type = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == 103);
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(value.type == 42);
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_ext16)
{
  std::string buffer;
  std::string string;
  buffer.resize(100000);

  mpack_extended_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, const_cast<char*>(buffer.data()), buffer.size());

  string.insert(0, 20000, 'a');
  value.data = string.data();
  value.size = string.size();
  value.type = 42;
  BOOST_CHECK(mpack_encode_extended(&encoder, value) == 20004);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer.data(), 20004);

  value.data = NULL;
  value.size = 0;
  value.type = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == 20004);
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(value.type == 42);
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_ext32)
{
  std::string buffer;
  std::string string;
  buffer.resize(100000);

  mpack_extended_t value;
  
  mpack_encoder_t encoder;
  mpack_encoder_init(&encoder, const_cast<char*>(buffer.data()), buffer.size());

  string.insert(0, 80000, 'a');
  value.data = string.data();
  value.size = string.size();
  value.type = 42;
  BOOST_CHECK(mpack_encode_extended(&encoder, value) == 80006);

  mpack_decoder_t decoder;
  mpack_decoder_init(&decoder, buffer.data(), 80006);

  value.data = NULL;
  value.size = 0;
  value.type = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == 80006);
  BOOST_CHECK(value.data != NULL);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(value.type == 42);
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = NULL;
  value.size = 0;
  BOOST_CHECK(mpack_decode_extended(&decoder, &value) == -1);
  BOOST_CHECK(errno == EAGAIN);

  mpack_decoder_term(&decoder);
  mpack_encoder_term(&encoder);
}
