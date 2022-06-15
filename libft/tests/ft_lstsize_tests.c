#include <criterion/criterion.h>
#include "../libft.h"

Test(ft_lstsize, size_0)
{
	t_list	*head;

	head = NULL;
	cr_assert(ft_lstsize(head) == 0);
}

Test(ft_lstsize, regular_size)
{
	t_list	*head;

	head = NULL;
	cr_assert(ft_lstsize(head) == 0);
	ft_lstadd_front(&head, ft_lstnew("Lorem"));
	cr_assert(ft_lstsize(head) == 1);
	ft_lstadd_front(&head, ft_lstnew("Lorem"));
	cr_assert(ft_lstsize(head) == 2);
	ft_lstadd_front(&head, ft_lstnew("Lorem"));
	cr_assert(ft_lstsize(head) == 3);
	ft_lstclear(&head, NULL);
}
