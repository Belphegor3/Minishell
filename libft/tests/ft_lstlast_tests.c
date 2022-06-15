#include <criterion/criterion.h>
#include "../libft.h"

Test(ft_lstlast, empty_list)
{
	t_list	*head;

	head = NULL;
	cr_assert(ft_lstlast(head) == NULL);
}

Test(ft_lstlast, one_element)
{
	t_list	*head;

	head = NULL;
	ft_lstadd_front(&head, ft_lstnew("Lorem"));
	cr_assert_str_eq(ft_lstlast(head)->content, "Lorem");
	cr_assert(ft_lstlast(head)->next == NULL);
	ft_lstclear(&head, NULL);
}

Test(ft_lstlast, multiple_elements)
{
	t_list	*head;

	head = NULL;
	ft_lstadd_front(&head, ft_lstnew("Lorem"));
	ft_lstadd_front(&head, ft_lstnew("Ipsum"));
	ft_lstadd_front(&head, ft_lstnew("Dolor"));
	cr_assert_str_eq(ft_lstlast(head)->content, "Lorem");
	cr_assert(ft_lstlast(head)->next == NULL);
	ft_lstclear(&head, NULL);
}
