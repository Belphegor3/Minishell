#include <criterion/criterion.h>
#include "../libft.h"
#include <stdlib.h>
#include <stdio.h>

Test(ft_lstdelone, regular_test)
{
	t_list	*head;
	t_list	*tmp;

	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(strdup("Lorem")));
	ft_lstadd_back(&head, ft_lstnew(strdup("Ipsum")));
	ft_lstadd_back(&head, ft_lstnew(strdup("Dolor")));
	tmp = head->next;
	head->next = tmp->next;
	ft_lstdelone(tmp, &free);
	cr_assert_str_eq(head->content, "Lorem");
	cr_assert(head->next->next == NULL);
	ft_lstclear(&head, &free);
}
