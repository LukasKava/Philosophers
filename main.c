/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:15:14 by lkavalia          #+#    #+#             */
/*   Updated: 2022/09/12 13:14:55 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int death_checker(t_philosophers *philo)
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

void eating(t_philosophers *philo)
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
			return ;
		}
/* 		if (get_time() - philo->last_time_ate >= philo->t_death)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return ;
		} */
		usleep(200);
	}
	philo->last_time_ate = get_time();
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->eaten_meals++;
}

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
			break ;
		usleep(200);
	}
	if (death_checker(philo) == 1)
		return ;
}

void	thinking(t_philosophers *philo)
{
	long long c_time;
	
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

void *routine(t_philosophers *philo)
{
	philo->start_of_the_thread = get_time();
	philo->last_time_ate = philo->start_of_the_thread;
	if (philo->index % 2 == 0)				// if number of philos is huge it prevents deadlock
	{										// Deadlock appears because it takes 
		if (philo->nbr_of_philo < 100)		//Create the threads
			usleep(100);
		else
			usleep(1500);
	}
	while (1)
	{
		taking_forks(philo);
		// Eating
		eating(philo);
		if (death_checker(philo) == 1)
			break ;
		if (philo->eaten_meals == philo->philo_info->amount_of_meals)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}

static int	create_philosophers(t_info info, t_philosophers *philo)
{
	int	i;
	
	i = 0;
	while (i < info.number_of_philo)
	{
		if (pthread_create(&philo[i].philosopher, NULL, (void *)routine, &philo[i]) != 0)
		{
			printf("Error(function: create_philosophers): pthread_create has failed! \n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	join_the_philosophers(t_info info, t_philosophers *philo)
{
	int	i;
	
	i = 0;
	while (i < info.number_of_philo)
	{
		if (pthread_join(philo[i].philosopher, NULL) != 0)
		{
			printf("error\n");
			return (2);
		}
		i++;
	}
	return (0);
}

// Number of philos
// Time to die
// time to eat
// time to sleep
// how many meals does it have to have
int main(int argc, char *argv[])
{
	t_info info;
	t_philosophers *philo;
	
	//First stage to check all of the inputs
	if (argc < 5 || argc > 6)
		error_message("ERROR: Wrong amount of arguments!\n");
	passing_arguments(argc, argv, &info);  							//Passed the args
	printf_everything(info);			   							//Print everything out
	//--------------------------------------
//	i = 0;
	if (init_mutexes(&info) != 0)		   							//Initialized the forks
		return (1);
	philo = malloc(sizeof(t_philosophers) * info.number_of_philo);	//malloced tthe philosophers
	init_philosophers(&info, philo);								//Initializing philosophers
//	printf("---------\n");											//Finished initializing stuff
	create_philosophers(info, philo);								//Creating philosophers
	//Waiting for them to finish their stuff
	join_the_philosophers(info, philo);							//Killing philosophers
	if (destroy_mutexes(&info, philo) != 0)					//Throwing away the forks
		return (1);
//	printf("Succesfully destroyed the mutexes!\n");
	free(philo);
	free(info.forks);
	return (0);
}