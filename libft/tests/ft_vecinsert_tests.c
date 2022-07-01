#include <stdio.h>
#include <criterion/criterion.h>
#include "../libft.h"

Test(vecinsert, test_with_char)
{
	t_vector	v;

	v = ft_veccreate(4, sizeof(char));
	ft_vecadd(&v, "a");
	ft_vecadd(&v, "b");
	ft_vecadd(&v, "\0");
	cr_assert(v.length == 3);
	cr_assert(v.capacity == 4);
	cr_assert(v.item_size == 1);
	cr_assert_str_eq(v.buffer, "ab");
	ft_vecremove(&v, 1, 1);
	cr_assert(v.length == 2);
	cr_assert(v.capacity == 4);
	cr_assert_str_eq(v.buffer, "a");
	ft_vecinsert(&v, 1, "b", 1);
	cr_assert_str_eq(v.buffer, "ab");
	cr_assert(v.length == 3);
	cr_assert(v.capacity == 4);
	ft_vecinsert(&v, 1, "defb", 4);
	cr_assert_str_eq(v.buffer, "adefbb");
	cr_assert(v.length == 7);
	cr_assert(v.capacity == 8);
	ft_vecdestroy(&v);
}
