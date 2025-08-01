/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:43:04 by jtoumani          #+#    #+#             */
/*   Updated: 2025/07/25 14:29:19 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atol(const char *str)
{
	int i;
	long integer;
	integer = 0;
	
	i = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		integer = (integer * 10) + (str[i] - '0');
		i++;
	}
	return integer;
	
}


bool	is_valid_nbr(char *str)
{
	if (!str || !*str)
		return (false);
	if (*str == '-')
		return (false);
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (false);
		str++;
	}
	return (true);
}

bool	parsing(int argc, char **argv)
{
	int i = 1;
	if (argc < 5 || argc > 6)
		return (wrong_input(), false);
	while (i < argc)
	{
		if (!is_valid_nbr(argv[i]))
			return (wrong_input(), false);
		i++;
	}
	return (true);
}
