/* This file is part of Netsukuku
 * (c) Copyright 2021 d0p1 <contact@d0p1.eu>
 *
 * This source code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published 
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * Please refer to the GNU Public License for more details.
 *
 * You should have received a copy of the GNU Public License along with
 * this source code; if not, write to:
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <sys/types.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "misc.h"

static void
test_swap_ints()
{
	const unsigned  initial[] = { 1, 2, 3, 4, 5 };
	const unsigned int expected[] = { 5, 4, 3, 2, 1 };

	unsigned int a[] = { 1, 2, 3, 4, 5 };
	unsigned int b[5] = { 0 };

	swap_ints(5, a, b);

	assert_memory_equal(a, initial, 5);
	assert_memory_equal(b, expected, 5);
}

static void
test_swap_shorts()
{
	const unsigned short initial[] = { 1, 2, 3, 4, 5 };
	const unsigned short expected[] = { 5, 4, 3, 2, 1 };

	unsigned short a[] = { 1, 2, 3, 4, 5 };
	unsigned short b[5] = { 0 };

	swap_shorts(5, a, b);

	assert_memory_equal(a, initial, 5);
	assert_memory_equal(b, expected, 5);
}

static void
test_rand_range()
{
	int rand;

	rand = rand_range(5, 25);
	assert_in_range(rand, 5, 25);
}

int
group_tests_misc(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_swap_ints),
		cmocka_unit_test(test_swap_shorts),
		cmocka_unit_test(test_rand_range)
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
