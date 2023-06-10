/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:31:34 by lkavalia          #+#    #+#             */
/*   Updated: 2023/06/10 12:19:14 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * FUNCTION: (death_checker) this function checks if Philosopher is dead or not
 * 			this is made sure by the folowing steps:
 * 1. Locking the death mutex so we could acces the shared information
 * 			if anyone before has died.
 * 2. Line 30-34 Checks if any previous philosopher has died so that other
 * 			Philosophers could end the simulation.
 * 3. Line 37-51 If Philosopher has taken longer than the time to die.
 * 			It locks the message mutex prints out the message.
 * 			Unlocks everything and increases the death_counter.
 * RETURN_VALUES:
 * -------- 0 In case nothing it just went through the function
 * 			  Without accessing the if statements.
 * -------- 1 if in any case they went to the if statements it
 * 			  returns  the according value.
 */
int	death_checker(t_philosophers *philo)
{
	long long c_time;

	pthread_mutex_lock(&philo->philo_info->death);
	if (philo->philo_info->death_counter > 0)
	{
		pthread_mutex_unlock(&philo->philo_info->death);
		return (1);
	}
	if ((get_time() - philo->last_time_ate) >= philo->t_death)
	{
		if (philo->philo_info->death_counter > 0)
		{
			pthread_mutex_unlock(&philo->philo_info->death);
			return (1);
		}
		pthread_mutex_lock(&philo->philo_info->message);
		c_time = get_time() - philo->start_of_the_program;
		printf("%lld %d \033[0;31m Philo is dead\n", c_time, philo->index);
		pthread_mutex_unlock(&philo->philo_info->message);
		philo->philo_info->death_counter++;
		pthread_mutex_unlock(&philo->philo_info->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->philo_info->death);
	return (0);
}

/**
 * FUNCTION: (taking_forks) takes care of giving the forks (locking certain mutexxes)
 * 			to the philosophers. It consistss of a few major steps:
 * 1. Locking the right fork.
 * 2. Updating the time the philosopher has taken a fork.
 * 3. Checking if Philosopher died while taking the forks and if not
 * 			printing out the message that the Philosopher has taken a fork.
 * 4. This is course of action is repeated with the left fork.
 */
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
		pthread_mutex_unlock(philo->right_fork);				//Do I really need to unlock them?
		pthread_mutex_unlock(philo->left_fork);					//Because they go into the eating
		pthread_mutex_unlock(&philo->philo_info->message);
		return;
	}
	printf("%lld %d Has taken a left fork\n", current_time, philo->index);
	pthread_mutex_unlock(&philo->philo_info->message);
}

/**
 * FUNCTION: (eating) the purpose of this function is to make philosophers
 * 			eat which involves them:
 * 1. Printing out the message that they eat.
 * 2. Eat which is achieved by making them sleep for a certain amount of
 * 			by the while loop. Which just uses small intervals of uslee.
 * 3. Update the time they last time ate.
 * 4. Unlock the forks and increase the eaten meals.
 */
void	eating(t_philosophers *philo)
{
	long long	future_time;
	long long	c_time;

	c_time = get_time() - philo->start_of_the_program;
	pthread_mutex_lock(&philo->philo_info->message);
	if (death_checker(philo) == 1)
	{
		pthread_mutex_unlock(&philo->philo_info->message);
		return;
	}
	printf("%lld %d Philo is eating\n", c_time, philo->index);
	pthread_mutex_unlock(&philo->philo_info->message);
	future_time = get_time() + philo->t_eat;
	while (get_time() <= future_time)
	{
		if (death_checker(philo) == 1)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return;
		}
		usleep(200);
	}
	philo->last_time_ate = get_time();
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->eaten_meals++;
}

/**
 * FUNCTION: (sleeping) makes philosopher sleep for a certain specified
 * 			amount of time. This involves the following steps"
 * 1. Locking the message mutex.
 * 2. Updating the current time.
 * 3. Printing out the message that Philosopher is sleeping and
 * 			unlocking the message mutex.
 * 4. Making it sleep with the while loop that uses small increments of
 * 			usleep which adds up to the predicted time.
 * 5. Death check  just in case the Philosopher has died while sleeping.
 */
void	sleeping(t_philosophers *philo)
{
	long long	c_time;
	long long	future_time;

	pthread_mutex_lock(&philo->philo_info->message);
	c_time = get_time() - philo->start_of_the_program;
	if (death_checker(philo) == 1)
	{
		pthread_mutex_unlock(&philo->philo_info->message);
		return;
	}
	printf("%lld %d Philo is sleeping\n", c_time, philo->index);
	pthread_mutex_unlock(&philo->philo_info->message);
	future_time = get_time() + philo->t_sleep;
	while (get_time() <= future_time)
	{
		if (get_time() - philo->last_time_ate >= philo->t_death)
			break;
		usleep(200);
	}
	if (death_checker(philo) == 1)
		return;
}

/**
 * FUNCTION: (thinking) is just a function that prints out
 * 			that Philosopher is sleeping while waiting
 * 			to take the forks as soon as they are available.
 */
void	thinking(t_philosophers *philo)
{
	long long	c_time;

	pthread_mutex_lock(&philo->philo_info->message);
	if (death_checker(philo) == 1)
	{
		pthread_mutex_unlock(&philo->philo_info->message);
		return;
	}
	c_time = get_time() - philo->start_of_the_program;
	printf("%lld %d Philo is thinking\n", c_time, philo->index);
	pthread_mutex_unlock(&philo->philo_info->message);
}