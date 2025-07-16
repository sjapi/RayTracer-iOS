float	ft_atof(char *str)
{
	float	result;
	float	fraction;
	float	divisor;
	int	sign;

	result = 0.0f;
	fraction = 0.0f;
	divisor = 1.0f;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0f + (*str - '0');
		str++;
	}
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
	    fraction = fraction * 10.0f + (*str - '0');
	    divisor *= 10.0f;
	    str++;
	}
	result += fraction / divisor;
	return (result * sign);
}
