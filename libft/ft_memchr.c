#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (((unsigned char *)s)[i] != c && i < n)
		i++;
	if (((unsigned char *)s)[i] == c)
		return (&((unsigned char *)s)[i]);
	return (0);
}
