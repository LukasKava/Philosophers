/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:23:37 by lkavalia          #+#    #+#             */
/*   Updated: 2022/08/30 01:51:50 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_info
{
	int number_of_philo;
	long long time_to_die;
	long long time_to_eat;
	long long time_to_sleep;
	int amount_of_meals;
	int death_counter;
} t_info;

typedef struct s_philosophers
{
	pthread_t philosopher;
	int	index;
	int left_fork;
	int right_fork;
//	long long last_time_ate;
	t_info philo_info;
	
} t_philosophers;

void printf_everything(t_info info);
long long get_time();
