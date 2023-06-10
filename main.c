/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:15:14 by lkavalia          #+#    #+#             */
/*   Updated: 2023/06/10 12:18:36 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * FUNCTION: (routine) functions like a job plan  it takes care that each thread
 * 			would do its job. Which consist of few main steps:
 * 1. Taking forks.
 * 2. Eating.
 * 3. Sleeping.
 * 4. Thinking.
 * 			A little note from line 132 till 139  code takes care that when there
 * 			are alot of threads that they would not get into the deadlock by
 * 			telling the Philosophers that have the even number as index to 
 * 			sleep for a little bit so that Philosophers which have odd number
 * 			as their index could grab the forks.
 * 
 * 			Also death checkers maake sure that in case the Philosopher dies
 * 			it would get out of the routine function.
 */
void	*routine(t_philosophers *philo)
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

/**
 * FUNCTION: (create_philosophers) is responsible for creating the threads
 * 			it is just a simple while loop which creates a thread
 * 			representing the philosopher using the pthread_create
 * 			and executes the function routine which makes
 * 			the thread do its job.
 * RETURN_VALUES:
 * if the funtion is succefull it returns 0 if the pthread_create fails
 * it returns an error message and 1.
 */
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

/**
 * FUNCTION: (join_the_philosophers) is responsible for joining the threads.
 * 			to simplify it uses the pthread_join which basically waits for
 * 			the thread to finish and terminates it. It is simimllar to waitpid().
 * RETURN_VALUE:
 * it returns 0 if it is succesful and 1 if pthread_join fails.
 */
static int	join_the_philosophers(t_info info, t_philosophers *philo)
{
	int	i;

	i = 0;
	while (i < info.number_of_philo)
	{
		if (pthread_join(philo[i].philosopher, NULL) != 0)
		{
			printf("ERROR (join_the_philosophers): pthread_join has failed!\n");
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 *  FUNCTION: (main)  it is responsible of connecting all of the actions together:
 * 1. Passing the arguments into the structs called info.
 * 2. Initiliazing the mutexes which can be perceived as forks for Philosophers.
 * 			Also initializing message and death mutexes so that we could access this info
 * 			Through Philosophers.
 * 3. Creating memory space for Philosophers and  initializing the information
 *			in t_philosophers struct.
 * 4. Creating Philosophers with create_philosophers function.
 * 5. Killing the philosophers with the function join_the_philosophers.
 * 6. Trowing forks into the garbage bin and also burning the message and death mutexes.
 * 7. Freeing the memory of Philosophers and freeing the forks.
 */
int	main(int argc, char *argv[])
{
	t_info			info;
	t_philosophers	*philo;

	if (argc < 5 || argc > 6)
		error_message("ERROR: Wrong amount of arguments!\n");
	passing_arguments(argc, argv, &info);  							//Passed the args
	if (init_mutexes(&info) != 0)		   							//Initialized the forks
		return (1);
	philo = malloc(sizeof(t_philosophers) * info.number_of_philo);	//malloced tthe philosophers
	init_philosophers(&info, philo);								//Initializing philosophers
	create_philosophers(info, philo);								//Creating philosophers
	//Waiting for them to finish their stuff
	join_the_philosophers(info, philo);								//Killing philosophers
	if (destroy_mutexes(&info) != 0)								//Throwing away the forks
		return (1);
	free(philo);
	free(info.forks);
	return (0);
}