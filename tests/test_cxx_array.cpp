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

BOOST_AUTO_TEST_CASE(test_encode_decode_fixarray)
{
  char buffer[32] = { 0 };
  mpack::array value;
  mpack::encoder encoder { buffer, sizeof(buffer) };

  value.size = 0;
  BOOST_CHECK(encoder.encode(value) == 1);

  value.size = 15;
  BOOST_CHECK(encoder.encode(value) == 1);

  mpack::decoder decoder { buffer, 2 };

  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == 1);
  BOOST_CHECK(value.size == 0);

  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == 1);
  BOOST_CHECK(value.size == 15);

  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_array16)
{
  char buffer[32] = { 0 };
  mpack::array value;
  mpack::encoder encoder { buffer, sizeof(buffer) };

  value.size = 16;
  BOOST_CHECK(encoder.encode(value) == 3);

  value.size = 65535;
  BOOST_CHECK(encoder.encode(value) == 3);

  mpack::decoder decoder { buffer, 6 };

  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == 3);
  BOOST_CHECK(value.size == 16);

  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == 3);
  BOOST_CHECK(value.size == 65535);

  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_array32)
{
  char buffer[32] = { 0 };
  mpack::array value;
  mpack::encoder encoder { buffer, sizeof(buffer) };

  value.size = 65536;
  BOOST_CHECK(encoder.encode(value) == 5);

  value.size = 4294967295U;
  BOOST_CHECK(encoder.encode(value) == 5);

  mpack::decoder decoder { buffer, 10 };

  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == 5);
  BOOST_CHECK(value.size == 65536);

  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == 5);
  BOOST_CHECK(value.size == 4294967295U);

  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}
