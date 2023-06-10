/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:19:25 by lkavalia          #+#    #+#             */
/*   Updated: 2023/06/10 12:18:55 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * FUNCTION: (passing_arguments) it takes care of passing the information
 * 			to the main stuct called info. It works by:
 * 1. Converting certain line command arguments from strings to numbers.
 * 2. It assings it to the certain place in the info stuct.
 * 			also it initializes also other information used in the simulation.
 */
void	passing_arguments(int argc, char **argv, t_info *info)
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

/**
 * FUNCTION: (init_philosophers) takes care of initializing the certain
 * 			information for each philosopher.
 */
void	init_philosophers(t_info *info, t_philosophers *philo)
{
	int i;

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
		i++;
	}
}

/**
 * FUNCTION: (init_mutexes) takes care of creating the mutexes by following
 * 			simple steps:
 * 1. It mallocs the needed amount of forks and checks if it was succesfull.
 * 2. Using a while loop it uses a pthread_mutex_init to initialize each fork.
 * 3. Initializes the other needed mutexes like message and death.
 * RETURN_VALUE:
 * --------- 0 In case everything went well.
 * --------- 1 In case malloc or pthread_mutex_init fails.
 */
int	init_mutexes(t_info *info)
{
	int i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
	if (info->forks == NULL)
	{
		printf("Error(function init_mutexes): there was a failure while mallocing forks!\n");
		return (1);
	}
	while (i < info->number_of_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			printf("Error(function init_mutexes): pthread_mutex_init has failed!\n");
			return (1);
		}
		i++;
	}
	pthread_mutex_init(&info->message, NULL);
	pthread_mutex_init(&info->death, NULL);
	return (0);
}

/**
 * FUNCTION: (destroy_mutexes) This function takes care of getting rid
 * 			of the mutexes using the function pthread_mutex_destroy.
 * 			It destroys each for message mutex and the death mutex.
 * RETURN_VALUES:
 * -------- 0 In case everything went succesfully.
 * --------	1 In case anything went wrong with the pthread_mutex_destroy.
 */
int	destroy_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		if (pthread_mutex_destroy(&info->forks[i]) != 0)
		{
			printf("Error(function destroy_mutexes): pthread_mutex_destroy has failed!\n");
			return (1);
		}
		i++;
	}
	if (pthread_mutex_destroy(&info->message) != 0)
		printf("error message!\n");
	if (pthread_mutex_destroy(&info->death) != 0)
		printf("error death");
	return (0);
}
