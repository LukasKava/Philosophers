/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:15:14 by lkavalia          #+#    #+#             */
/*   Updated: 2022/09/05 18:15:59 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/* void test_mutex()
{
	
} */

void *routine(t_philosophers *philo)
{
	printf("Haloo\n");
	long long	current_time;

	current_time = get_time() - philo->philo_info->start;;
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->philo_info->message);
	
	printf("%lld %d Has taken a right fork\n", current_time, philo->index);
	pthread_mutex_unlock(&philo->philo_info->message);
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->philo_info->message);
	printf("Has taken a left fork\n");

	//Eating

	pthread_mutex_unlock(&philo->philo_info->message);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	
	//Sleeping

	return (0);
}

static int	create_philosophers(t_info info, t_philosophers *philo)
{
	int	i;
	
	i = 0;
	while (i < info.number_of_philo)
	{
		int *a = malloc(sizeof(int)); //Not needed
		*a = i;							//Not needed
		if (pthread_create(&philo[i].philosopher, NULL, (void *)routine, &philo[i]) != 0)
		{
			printf("Error(function: create_philosophers): pthread_create has failed! \n");
			return (1);
		}
		i++;
		free(a); //Not needed
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
		printf("Finished the thread %d\n", i);
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
	int i;
	long long time;
	//First stage to check all of the inputs
	if (argc < 5 || argc > 6)
		error_message("ERROR: Wrong amount of arguments!\n");
	passing_arguments(argc, argv, &info);  							//Passed the args
	printf_everything(info);			   							//Print everything out
	//--------------------------------------
	i = 0;
	if (init_mutexes(&info) != 0)		   							//Initialized the forks
		return (1);
	philo = malloc(sizeof(t_philosophers) * info.number_of_philo);	//malloced tthe philosophers
	init_philosophers(&info, philo);								//Initializing philosophers
	printf("---------\n");											//Finished initializing stuff
	i = 0;
	time = get_time();
	printf("time: %lld & i: %d\n", time, i);	
	//Second stage creating philosophers
	create_philosophers(info, philo);								//Creating philosophers
	
	
	
	//Waiting for them to finish their stuff
	join_the_philosophers(info, philo);							//Killing philosophers
	if (destroy_mutexes(&info) != 0)								//Throwing away the forks
		return (1);
	printf("Succesfully destroyed the mutexes!\n");
	free(philo);
	free(info.forks);
	return (0);
}