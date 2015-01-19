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

BOOST_AUTO_TEST_CASE(test_encode_decode_positive_fixnum)
{
  char buffer[32] = { 0 };
  long value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(0) == 1);
  BOOST_CHECK(encoder.encode(127) == 1);

  mpack::decoder decoder { buffer, 2 };

  BOOST_CHECK(decoder.decode(value) == 1);
  BOOST_CHECK(value == 0);

  BOOST_CHECK(decoder.decode(value) == 1);
  BOOST_CHECK(value == 127);

  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_negative_fixnum)
{
  char buffer[32] = { 0 };
  long value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(-1) == 1);
  BOOST_CHECK(encoder.encode(-31) == 1);

  mpack::decoder decoder { buffer, 2 };

  BOOST_CHECK(decoder.decode(value) == 1);
  BOOST_CHECK(value == -1);

  BOOST_CHECK(decoder.decode(value) == 1);
  BOOST_CHECK(value == -31);

  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_int8)
{
  char buffer[32] = { 0 };
  long value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(-32) == 2);
  BOOST_CHECK(encoder.encode(-128) == 2);

  mpack::decoder decoder { buffer, 4 };

  BOOST_CHECK(decoder.decode(value) == 2);
  BOOST_CHECK(value == -32);

  BOOST_CHECK(decoder.decode(value) == 2);
  BOOST_CHECK(value == -128);

  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_int16)
{
  char buffer[32] = { 0 };
  long value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(-129) == 3);
  BOOST_CHECK(encoder.encode(-32768) == 3);

  mpack::decoder decoder { buffer, 6 };

  BOOST_CHECK(decoder.decode(value) == 3);
  BOOST_CHECK(value == -129);

  BOOST_CHECK(decoder.decode(value) == 3);
  BOOST_CHECK(value == -32768);

  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_int32)
{
  char buffer[32] = { 0 };
  long value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(-32769) == 5);
  BOOST_CHECK(encoder.encode(-2147483648) == 5);

  mpack::decoder decoder { buffer, 10 };

  BOOST_CHECK(decoder.decode(value) == 5);
  BOOST_CHECK(value == -32769);

  BOOST_CHECK(decoder.decode(value) == 5);
  BOOST_CHECK(value == -2147483648);

  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_int64)
{
  char buffer[32] = { 0 };
  long value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(-2147483649L) == 9);
  BOOST_CHECK(encoder.encode(-9223372036854775807L) == 9);

  mpack::decoder decoder { buffer, 18 };

  BOOST_CHECK(decoder.decode(value) == 9);
  BOOST_CHECK(value == -2147483649L);

  BOOST_CHECK(decoder.decode(value) == 9);
  BOOST_CHECK(value == -9223372036854775807L);

  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_uint8)
{
  char buffer[32] = { 0 };
  unsigned long value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(128) == 2);
  BOOST_CHECK(encoder.encode(255) == 2);

  mpack::decoder decoder { buffer, 4 };

  BOOST_CHECK(decoder.decode(value) == 2);
  BOOST_CHECK(value == 128);

  BOOST_CHECK(decoder.decode(value) == 2);
  BOOST_CHECK(value == 255);

  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_uint16)
{
  char buffer[32] = { 0 };
  unsigned long value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(256) == 3);
  BOOST_CHECK(encoder.encode(65535) == 3);

  mpack::decoder decoder { buffer, 6 };

  BOOST_CHECK(decoder.decode(value) == 3);
  BOOST_CHECK(value == 256);

  BOOST_CHECK(decoder.decode(value) == 3);
  BOOST_CHECK(value == 65535);

  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_uint32)
{
  char buffer[32] = { 0 };
  unsigned long value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(65536) == 5);
  BOOST_CHECK(encoder.encode(4294967295U) == 5);

  mpack::decoder decoder { buffer, 10 };

  BOOST_CHECK(decoder.decode(value) == 5);
  BOOST_CHECK(value == 65536);

  BOOST_CHECK(decoder.decode(value) == 5);
  BOOST_CHECK(value == 4294967295U);

  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_uint64)
{
  char buffer[32] = { 0 };
  unsigned long value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(4294967296UL) == 9);
  BOOST_CHECK(encoder.encode(18446744073709551615UL) == 9);

  mpack::decoder decoder { buffer, 18 };

  BOOST_CHECK(decoder.decode(value) == 9);
  BOOST_CHECK(value == 4294967296UL);

  BOOST_CHECK(decoder.decode(value) == 9);
  BOOST_CHECK(value == 18446744073709551615UL);

  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}
