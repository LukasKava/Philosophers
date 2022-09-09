/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:19:25 by lkavalia          #+#    #+#             */
/*   Updated: 2022/09/09 16:50:23 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void passing_arguments(int argc, char **argv, t_info *info)
{
	info->number_of_philo = ft_atoi(argv[1]);
	if (info->number_of_philo < 2)
		error_message("You need at least 2 philosophers to eat!\n");
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->time_to_eat + info->time_to_sleep > info->time_to_die)
		error_message("Time of eating + sleeping has to be smaller than time to die!\n");
	info->amount_of_meals = 0;
	if (argc == 6)
		info->amount_of_meals = ft_atoi(argv[5]);
	info->death_counter = 0;
	info->start = get_time();
}

void	init_philosophers(t_info *info, t_philosophers *philo)
{
	int	i;
	
	i = 0;
	while (i < info->number_of_philo)
	{
		philo[i].index = i + 1;
		philo[i].t_death = info->time_to_die;
		philo[i].t_eat = info->time_to_eat;
		philo[i].t_sleep = info->time_to_sleep;
		philo[i].eaten_meals = 0;
		philo[i].last_time_ate = info->start;
		philo[i].right_fork = &info->forks[i];
		philo[i].left_fork = &info->forks[(i + 1) % info->number_of_philo];
		philo[i].philo_info = info;
		philo[i].start_of_the_program = info->start;
		philo[i].nbr_of_philo = info->number_of_philo;
	//	printf("philos->index %d\n", philo[i].index);
	//	printf("philos %d\n", philo[i].eaten_meals);
	//	printf("right and left forks created succesfully!\n\n");
		i++;
	}
}

int init_mutexes(t_info *info)
{
	int	i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
	if (info->forks == NULL)
	{
		printf("Error(function init_mutexes): there was a failure while mallocing forks!\n");
		return (1);
	}
	while(i < info->number_of_philo)
	{
		if (pthread_mutex_init(info->forks, NULL) != 0)
		{
			printf("Error(function init_mutexes): pthread_mutex_init has failed!\n");
			return (1);
		}
//		printf("Fork: %d has been created!\n", i);
		i++;
	}
	pthread_mutex_init(&info->message, NULL);
	pthread_mutex_init(&info->death, NULL);
	return (0);
}

int	destroy_mutexes(t_info *info, t_philosophers *philo)
{
	int i;
	
	i = 0;
	while (i < info->number_of_philo)
	{
		if (pthread_mutex_destroy(&info->forks[i]) != 0)
		{
			printf("Error(function destroy_mutexes): pthread_mutex_destroy has failed!\n");
			return (1);
		}
	//	printf("Succesfully destroy philo %d\n", i);
		i++;
	}
	pthread_mutex_destroy(philo->right_fork);
	pthread_mutex_destroy(philo->left_fork);
	pthread_mutex_destroy(&info->message);
	pthread_mutex_destroy(&info->death);
	return (0);
}