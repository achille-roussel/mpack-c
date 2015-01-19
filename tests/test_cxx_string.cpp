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
  
  mpack::string value;  
  mpack::encoder encoder { buffer, sizeof(buffer) };

  value.data = "";
  value.size = 0;
  BOOST_CHECK(encoder.encode(value) == 1);

  value.data = "Hello World!";
  value.size = 12;
  BOOST_CHECK(encoder.encode(value) == 13);

  mpack::decoder decoder { buffer, 14 };

  value.data = nullptr;
  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == 1);
  BOOST_CHECK(value.data != nullptr);
  BOOST_CHECK(value.size == 0);

  value.data = nullptr;
  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == 13);
  BOOST_CHECK(value.data != nullptr);
  BOOST_CHECK(value.size == 12);
  BOOST_CHECK(memcmp(value.data, "Hello World!", 12) == 0);

  value.data = nullptr;
  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_str8)
{
  std::string buffer;
  std::string string;
  buffer.resize(100000);

  mpack::string value;  
  mpack::encoder encoder { const_cast<char*>(buffer.data()), buffer.size() };

  string.insert(0, 200, 'a');
  value.data = string.data();
  value.size = string.size();
  BOOST_CHECK(encoder.encode(value) == static_cast<int>(value.size + 2));

  mpack::decoder decoder { buffer.data(), value.size + 2 };

  value.data = nullptr;
  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == static_cast<int>(value.size + 2));
  BOOST_CHECK(value.data != nullptr);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = nullptr;
  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_str16)
{
  std::string buffer;
  std::string string;
  buffer.resize(100000);

  mpack::string value;  
  mpack::encoder encoder { const_cast<char*>(buffer.data()), buffer.size() };

  string.insert(0, 10000, '*');
  value.data = string.data();
  value.size = string.size();
  BOOST_CHECK(encoder.encode(value) == static_cast<int>(value.size + 3));

  mpack::decoder decoder { buffer.data(), value.size + 3 };

  value.data = nullptr;
  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == static_cast<int>(value.size + 3));
  BOOST_CHECK(value.data != nullptr);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = nullptr;
  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}

BOOST_AUTO_TEST_CASE(test_encode_decode_str32)
{
  std::string buffer;
  std::string string;
  buffer.resize(100000);

  mpack::string value;  
  mpack::encoder encoder { const_cast<char*>(buffer.data()), buffer.size() };

  string.insert(0, 80000, '+');
  value.data = string.data();
  value.size = string.size();
  BOOST_CHECK(encoder.encode(value) == static_cast<int>(value.size + 5));

  mpack::decoder decoder { buffer.data(), value.size + 5 };

  value.data = nullptr;
  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == static_cast<int>(value.size + 5));
  BOOST_CHECK(value.data != nullptr);
  BOOST_CHECK(value.size == string.size());
  BOOST_CHECK(memcmp(value.data, string.data(), string.size()) == 0);

  value.data = nullptr;
  value.size = 0;
  BOOST_CHECK(decoder.decode(value) == -1);
  BOOST_CHECK(errno == EAGAIN);
}
