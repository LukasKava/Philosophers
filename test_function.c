/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:55:43 by lkavalia          #+#    #+#             */
/*   Updated: 2022/09/05 15:15:48 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void printf_everything(t_info info)
{
	printf("number of philos %d\n", info.number_of_philo);
	printf("time to die %lld\n", info.time_to_die);
	printf("time to eat %lld\n", info.time_to_eat);
	printf("time to sleep %lld\n", info.time_to_sleep);
	printf("number of meals %d\n", info.amount_of_meals);
	printf("death counter %d\n", info.death_counter);
	printf("Start of the program %lld\n", info.start);
}