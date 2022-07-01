#include <stdio.h>
#include <criterion/criterion.h>
#include "../libft.h"

Test(vecdestroy, test_with_int)
{
	t_vector	v;
	int			nb;

	nb = 97;
	v = ft_veccreate(2, sizeof(int));
	ft_memcpy(v.buffer, (void*)&nb, sizeof(int));
	cr_assert(((int*)v.buffer)[0] == 97);
	nb = -13870;
	ft_memcpy(v.buffer + sizeof(int), (void*)&nb, sizeof(int));
	cr_assert(*((int*)(v.buffer + sizeof(int))) == -13870);
	ft_vecdestroy(&v);
	cr_assert(v.item_size == 0);
	cr_assert(v.length == 0);
	cr_assert(v.capacity == 0);
	cr_assert(v.buffer == NULL);
}
