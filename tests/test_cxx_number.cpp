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

BOOST_AUTO_TEST_CASE(test_encode_decode)
{
  char buffer[32] = { 0 };
  float value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(0.0f) == 5);
  BOOST_CHECK(encoder.encode(1.234f) == 5);

  mpack::decoder decoder { buffer, 10 };

  BOOST_CHECK(decoder.decode(value) == 5);
  BOOST_CHECK(value == 0.0f);

  BOOST_CHECK(decoder.decode(value) == 5);
  BOOST_CHECK(value == 1.234f);
  
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_double)
{
  char buffer[32] = { 0 };
  double value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(0.0) == 9);
  BOOST_CHECK(encoder.encode(1.234) == 9);

  mpack::decoder decoder { buffer, 18 };

  BOOST_CHECK(decoder.decode(value) == 9);
  BOOST_CHECK(value == 0.0);

  BOOST_CHECK(decoder.decode(value) == 9);
  BOOST_CHECK(value == 1.234);
  
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_convert_integer_to)
{
  char buffer[32] = { 0 };
  float value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(-42) == 2);
  BOOST_CHECK(encoder.encode(42U) == 1);

  mpack::decoder decoder { buffer, 3 };

  BOOST_CHECK(decoder.decode(value) == 2);
  BOOST_CHECK(value == -42.0f);

  BOOST_CHECK(decoder.decode(value) == 1);
  BOOST_CHECK(value == 42.0f);
  
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_convert_integer_to_double)
{
  char buffer[32] = { 0 };
  double value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(-42) == 2);
  BOOST_CHECK(encoder.encode(42U) == 1);

  mpack::decoder decoder { buffer, 3 };

  BOOST_CHECK(decoder.decode(value) == 2);
  BOOST_CHECK(value == -42.0f);

  BOOST_CHECK(decoder.decode(value) == 1);
  BOOST_CHECK(value == 42.0f);
  
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_convert_to_double)
{
  char buffer[32] = { 0 };
  double value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(-42.0f) == 5);
  BOOST_CHECK(encoder.encode(42.0f) == 5);

  mpack::decoder decoder { buffer, 10 };

  BOOST_CHECK(decoder.decode(value) == 5);
  BOOST_CHECK(value == -42.0);

  BOOST_CHECK(decoder.decode(value) == 5);
  BOOST_CHECK(value == 42.0);
  
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}
