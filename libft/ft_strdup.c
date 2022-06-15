#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;

	d = malloc(ft_strlen(s) + 1);
	if (d)
		ft_strlcpy(d, s, ft_strlen(s) + 1);
	return (d);
}
