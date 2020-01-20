#pragma once

//
//  Copyright (C) 2020 Pharap (@Pharap)
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include <stdint.h>

struct CharTriple
{
private:
	static constexpr uint16_t highBit = (1 << 15);

	static constexpr uint16_t charMask = ((1 << 5) - 1);

	static constexpr uint16_t c0Shift = (5 * 2);
	static constexpr uint16_t c1Shift = (5 * 1);
	static constexpr uint16_t c2Shift = (5 * 0);

private:
	uint16_t value;

private:
	static constexpr uint16_t make_value(char c0, char c1 = '\0', char c2 = '\0')
	{
		return
			((((c0 - 'a') + 1) & charMask) << c0Shift) |
			((((c1 - 'a') + 1) & charMask) << c1Shift) |
			((((c2 - 'a') + 1) & charMask) << c2Shift);
	}

	static constexpr char mapBits(uint16_t value)
	{
		return (value == 0) ? '\0' : ('a' + (value - 1));
	}

public:
	constexpr explicit CharTriple(uint16_t value) :
		value(value)
	{
	}

	constexpr CharTriple(char c0) :
		value(highBit | make_value(c0))
	{
	}

	constexpr CharTriple(char c0, char c1) :
		value(highBit | make_value(c0, c1))
	{
	}

	constexpr CharTriple(char c0, char c1, char c3) :
		value(make_value(c0, c1, c3))
	{
	}

	constexpr CharTriple(char c0, char c1, char c3, bool final) :
		value((final ? highBit : 0) | make_value(c0, c1, c3))
	{
	}

	constexpr bool is_last() const
	{
		return ((this->value & highBit) != 0);
	}

	constexpr char get_c0() const
	{
		return mapBits((this->value >> c0Shift) & charMask);
	}

	constexpr char get_c1() const
	{
		return mapBits((this->value >> c1Shift) & charMask);
	}

	constexpr char get_c2() const
	{
		return mapBits((this->value >> c2Shift) & charMask);
	}

	constexpr uint16_t get_value() const
	{
		return this->value;
	}

	constexpr operator uint16_t() const
	{
		return this->value;
	}
};