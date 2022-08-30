/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:34:06 by lkavalia          #+#    #+#             */
/*   Updated: 2022/08/30 01:54:26 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long get_time()
{
	struct timeval time_stmp;
	if (gettimeofday(&time_stmp, NULL) < 0)
	{
		printf("ERROR(get_time() in utils.c): gettimeofday has failed!\n");
		return (1);
	}
//	printf("time_stmp %ld\n", time_stmp.tv_usec / 1000);
	return (time_stmp.tv_usec / 1000);
}

