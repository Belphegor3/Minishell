#include <criterion/criterion.h>
#include "../libft.h"

Test(ft_lstnew, test_integer)
{
	t_list	*head;
	int		n;

	n = 15;
	head = ft_lstnew(&n);
	cr_assert(*(int*)(head->content) == 15);
	cr_assert(head->next == 0);
	ft_lstclear(&head, NULL);
}

Test(ft_lstnew, test_string)
{
	t_list	*head;
	char	*str = "Lorem Ipsum";

	head = ft_lstnew(str);
	cr_assert_str_eq((head->content), "Lorem Ipsum");
	cr_assert(head->next == 0);
	ft_lstclear(&head, NULL);
}
