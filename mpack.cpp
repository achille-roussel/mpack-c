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

#include <limits>
#include <mpack.h>

namespace mpack {

  decoder::decoder() noexcept
  { mpack_decoder_init(this, nullptr, 0); }

  decoder::decoder(const void *data, size_t size) noexcept
  { mpack_decoder_init(this, data, size); }

  template < typename T >
  int decoder::decode_signed(T &value) noexcept
  {
    signed long x;
    MPACK_DECODE_BEGIN(this);

    this->decode(x);

    if ((x < static_cast<signed long>(std::numeric_limits<T>::min())) ||
        (x > static_cast<signed long>(std::numeric_limits<T>::max()))) {
      MPACK_DECODE_FAIL(ERANGE);
    }

    value = x;
    MPACK_DECODE_END(this);
  }

  template < typename T >
  int decoder::decode_unsigned(T &value) noexcept
  {
    unsigned long x;
    MPACK_DECODE_BEGIN(this);

    this->decode(x);

    if (x > static_cast<unsigned long>(std::numeric_limits<T>::max())) {
      MPACK_DECODE_FAIL(ERANGE);
    }

    value = x;
    MPACK_DECODE_END(this);
  }

  int decoder::decode(std::nullptr_t &value) noexcept
  {
    value = nullptr;
    return mpack_decode_nil(this);
  }

  int decoder::decode(bool &value) noexcept
  { return mpack_decode_boolean(this, &value); }

  int decoder::decode(signed char &value) noexcept
  { return this->decode_signed(value); }

  int decoder::decode(signed short &value) noexcept
  { return this->decode_signed(value); }

  int decoder::decode(signed int &value) noexcept
  { return this->decode_signed(value); }

  int decoder::decode(signed long &value) noexcept
  { return mpack_decode_signed(this, &value); }

  int decoder::decode(unsigned char &value) noexcept
  { return this->decode_unsigned(value); }

  int decoder::decode(unsigned short &value) noexcept
  { return this->decode_unsigned(value); }

  int decoder::decode(unsigned int &value) noexcept
  { return this->decode_unsigned(value); }

  int decoder::decode(unsigned long &value) noexcept
  { return mpack_decode_unsigned(this, &value); }

  int decoder::decode(float &value) noexcept
  { return mpack_decode_float(this, &value); }

  int decoder::decode(double &value) noexcept
  { return mpack_decode_double(this, &value); }

  int decoder::decode(string &value) noexcept
  { return mpack_decode_string(this, &value); }

  int decoder::decode(binary &value) noexcept
  { return mpack_decode_binary(this, &value); }

  int decoder::decode(array &value) noexcept
  { return mpack_decode_array(this, &value); }

  int decoder::decode(map &value) noexcept
  { return mpack_decode_map(this, &value); }

  int decoder::decode(extended &value) noexcept
  { return mpack_decode_extended(this, &value); }

  int decoder::decode_nil() noexcept
  { return mpack_decode_nil(this); }

  int decoder::decode_true() noexcept
  { return mpack_decode_true(this); }

  int decoder::decode_false() noexcept
  { return mpack_decode_false(this); }

  encoder::encoder() noexcept
  { mpack_encoder_init(this, nullptr, 0); }

  encoder::encoder(void *data, size_t size) noexcept
  { mpack_encoder_init(this, data, size); }

  int encoder::encode(std::nullptr_t) noexcept
  { return mpack_encode_nil(this); }

  int encoder::encode(bool value) noexcept
  { return mpack_encode_boolean(this, value); }

  int encoder::encode(signed char value) noexcept
  { return mpack_encode_signed(this, value); }

  int encoder::encode(signed short value) noexcept
  { return mpack_encode_signed(this, value); }

  int encoder::encode(signed int value) noexcept
  { return mpack_encode_signed(this, value); }

  int encoder::encode(signed long value) noexcept
  { return mpack_encode_signed(this, value); }

  int encoder::encode(unsigned char value) noexcept
  { return mpack_encode_unsigned(this, value); }

  int encoder::encode(unsigned short value) noexcept
  { return mpack_encode_unsigned(this, value); }

  int encoder::encode(unsigned int value) noexcept
  { return mpack_encode_unsigned(this, value); }

  int encoder::encode(unsigned long value) noexcept
  { return mpack_encode_unsigned(this, value); }

  int encoder::encode(float value) noexcept
  { return mpack_encode_float(this, value); }

  int encoder::encode(double value) noexcept
  { return mpack_encode_double(this, value); }

  int encoder::encode(string value) noexcept
  { return mpack_encode_string(this, value); }

  int encoder::encode(binary value) noexcept
  { return mpack_encode_binary(this, value); }

  int encoder::encode(array value) noexcept
  { return mpack_encode_array(this, value); }

  int encoder::encode(map value) noexcept
  { return mpack_encode_map(this, value); }

  int encoder::encode(extended value) noexcept
  { return mpack_encode_extended(this, value); }

  int encoder::encode_nil() noexcept
  { return mpack_encode_nil(this); }

  int encoder::encode_true() noexcept
  { return mpack_encode_true(this); }

  int encoder::encode_false() noexcept
  { return mpack_encode_false(this); }

}
