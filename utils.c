/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:34:06 by lkavalia          #+#    #+#             */
/*   Updated: 2023/06/10 12:22:06 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

void	error_message(char *message)
{
	int	i;

	i = ft_strlen(message) + 1;
	write(1, message, i);
	exit(EXIT_FAILURE);
}

/*
This function converts the string to an integer
*/
int	ft_atoi(const char *str)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || \
			str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' && str[i] != '\0')
		error_message("ERROR: No negative numbers!\n");
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		b = b * 10 + (str[i] - '0');
		i++;
	}
	if (b == 0)
		error_message("EEROR: value has to be more than 0!\n");
	return (b);
}

long long	get_time(void)
{
	struct timeval	time_stmp;

	if (gettimeofday(&time_stmp, NULL) < 0)
	{
		printf("ERROR(get_time() in utils.c): gettimeofday has failed!\n");
		return (1);
	}
	return ((time_stmp.tv_usec / 1000) + (time_stmp.tv_sec * 1000));
}

