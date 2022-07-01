#include <stdio.h>
#include <criterion/criterion.h>
#include "../libft.h"

Test(vecadd, test_with_int)
{
	t_vector	v;
	int			nb;

	nb = 97;
	v = ft_veccreate(2, sizeof(int));
	cr_assert(ft_vecadd(&v, &nb) == 0);
	cr_assert(((int*)v.buffer)[0] == nb);
	nb = -13870;
	cr_assert(ft_vecadd(&v, &nb) == 0);
	cr_assert(((int*)v.buffer)[1] == nb);
	cr_assert(ft_vecadd(&v, &nb) == 0);
	cr_assert(((int*)v.buffer)[2] == nb);
	cr_assert(v.length == 3);
	cr_assert(v.capacity == 4);
	ft_vecdestroy(&v);
	cr_assert(v.item_size == 0);
	cr_assert(v.length == 0);
	cr_assert(v.capacity == 0);
	cr_assert(v.buffer == NULL);
}
