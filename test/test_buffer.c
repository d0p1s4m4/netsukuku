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

#include "buffer.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

static void
test_is_bufzero_with_6_zero_expect_true(void **state)
{
	char buff[10] = { 0, 0, 0, 0, 0, 0, 'a', 'b', 'c', 0};

	(void) state;
	assert_int_equal(is_bufzero(buff, 6), 1);
}

static void
test_is_bufzero_expect_false(void **state)
{
	char buff[10] = { 0, 0, 0, 0, 0, 0, 'a', 'b', 'c', 0};

	(void) state;
	assert_int_equal(is_bufzero(buff, 10), 0);
}

int
group_tests_buffer(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_is_bufzero_with_6_zero_expect_true),
		cmocka_unit_test(test_is_bufzero_expect_false),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
