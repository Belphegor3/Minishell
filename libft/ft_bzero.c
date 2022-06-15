#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	i = 0;
	while (n > i)
		((char *)s)[i++] = 0;
}
