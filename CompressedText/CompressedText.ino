#include <Arduboy2.h>

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

#include "CompressedText.h"

Arduboy2 arduboy;

const uint16_t words[] PROGMEM
{
	CharTriple('m', 'a', 'r'),
	CharTriple('i', 'm', 'b'),
	CharTriple('a'),
};

void print(Print & printer, const uint16_t * word)
{
	const uint16_t * next = word;
	while(true)
	{
		const CharTriple c = CharTriple(pgm_read_word(next));

		const char c0 = c.get_c0();

		if(c0 != '\0')
			printer.print(c0);

		const char c1 = c.get_c1();

		if(c1 != '\0')
			printer.print(c1);

		const char c2 = c.get_c2();

		if(c2 != '\0')
			printer.print(c2);

		if(c.is_last())
			break;

		++next;
	}
}

void setup()
{
	arduboy.begin();
	arduboy.clear();
	print(arduboy, &words[0]);
	arduboy.display();
	while(true);
}

void loop()
{
	if(!arduboy.nextFrame())
		return;

	arduboy.clear();

	arduboy.display();
}