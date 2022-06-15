int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	if (nptr[0] == '-' || nptr[0] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	if (nptr[0] == '-')
		result = -result;
	return (result);
}
