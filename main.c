/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:15:14 by lkavalia          #+#    #+#             */
/*   Updated: 2022/08/30 02:17:58 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;
pthread_mutex_t mutex;

size_t ft_strlen(const char *c)
{
	int i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

static void error_message(char *message)
{
	int	i;

	i = ft_strlen(message) + 1;
	write(1, message, i);
	exit(EXIT_FAILURE);
}

/*
This function converts the string to an integer
*/
int ft_atoi(const char *str)
{
	int i;
	int b;

	i = 0;
	b = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' && str[i] != '\0')
		error_message("ERROR: No negative numbers!\n");
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		b = b * 10 + (str[i] - '0');
		i++;
	}
	if (b == 0)
		error_message("EEROR: value has to be more than 0!\n");
	return (b);
}

static void passing_arguments(int argc, char **argv, t_info *info)
{
	info->number_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->amount_of_meals = 0;
	if (argc == 6)
		info->amount_of_meals = ft_atoi(argv[5]);
	info->death_counter = 0;
}

/* void test_mutex()
{
	
} */

void *create_philo(void *i)
{
	printf("thread  %d created\n", *(int *)i);
	sleep(3);
	printf("Continue to the next thread!\n");
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		// read mails
		// increment
		// write mails
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
	passing_arguments(argc, argv, &info);
	printf_everything(info);
	//--------------------------------------
	i = 0;
	philo = malloc(sizeof(t_philosophers) * info.number_of_philo);
	while (i < info.number_of_philo)
	{
		printf("index: %d\n", philo[i].index);
		i++;
	}
	printf("---------\n");
	i = 0;
	pthread_mutex_init(&mutex, NULL);
	//Second stage creating philosophers
	while (i <  info.number_of_philo)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&philo[i].philosopher, NULL, (void *)create_philo, a) != 0)
		{
			printf("error\n");
			return (1);
		}
		i++;
	}
	//-----------------------------------
	i = 0;
	//Waiting for them to finish their stuff
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
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}