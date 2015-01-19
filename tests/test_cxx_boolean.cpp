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

BOOST_AUTO_TEST_CASE(test_encode_decode_boolean_success_true)
{
  char buffer[32] = { 0 };
  bool value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(true) == 1);
  mpack::decoder decoder { buffer, 1 };

  BOOST_CHECK(decoder.decode(value) == 1);
  BOOST_CHECK(value == true);
  
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_boolean_success_false)
{
  char buffer[32] = { 0 };
  bool value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode(false) == 1);

  mpack::decoder decoder { buffer, 1 };

  BOOST_CHECK(decoder.decode(value) == 1);
  BOOST_CHECK(value == false);
  
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_boolean_failure)
{
  char buffer[32] = { 0 };
  bool value;

  mpack::encoder encoder { buffer, sizeof(buffer) };

  BOOST_CHECK(encoder.encode_nil() == 1);

  mpack::decoder decoder { buffer, 1 };

  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EINVAL);
}
