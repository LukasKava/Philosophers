/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:31:34 by lkavalia          #+#    #+#             */
/*   Updated: 2022/09/09 17:44:12 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	taking_forks(t_philosophers *philo)
{
	long long	current_time;
	
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->philo_info->message);
	current_time = get_time() - philo->start_of_the_program;
	if (death_checker(philo) == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->philo_info->message);
		return;
	}
	printf("%lld %d Has taken a right fork\n", current_time, philo->index);
	pthread_mutex_unlock(&philo->philo_info->message);

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->philo_info->message);
	current_time = get_time() - philo->start_of_the_program;
	if (death_checker(philo) == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->philo_info->message);
		return;
	}
	printf("%lld %d Has taken a left fork\n", current_time, philo->index);
	pthread_mutex_unlock(&philo->philo_info->message);
}

/* void taking_left_fork(t_philosophers *philo)
{
	long long current_time;
	current_time = get_time() - philo->start_of_the_program;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->philo_info->message);
	printf("%lld %d Has taken a left fork\n", current_time, philo->index);
	pthread_mutex_unlock(&philo->philo_info->message);
} */