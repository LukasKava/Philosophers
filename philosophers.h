/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:23:37 by lkavalia          #+#    #+#             */
/*   Updated: 2022/09/05 17:46:36 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_info
{
	int				number_of_philo;
	long long		time_to_die;		//miliseconds
	long long		time_to_eat;		//miliseconds
	long long		time_to_sleep;	//miliseconds
	long long		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t message;
	pthread_mutex_t	death;
	int				amount_of_meals;
	int				death_counter;
} t_info;

typedef struct s_philosophers
{
	pthread_t 		philosopher;
	int				index;
	int				eaten_meals;
	long long		last_time_ate;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	t_info			*philo_info;
	
} t_philosophers;

/*---- Functions from init.c ---------------------------------*/ 
void		passing_arguments(int argc, char **argv, t_info *info);
void		init_philosophers(t_info *info, t_philosophers *philosophers);
int			init_mutexes(t_info *info);
int			destroy_mutexes(t_info *info);

/*---- Functions from utils.c --------------------------------*/
size_t ft_strlen(const char *c);
void		error_message(char *message);
int			ft_atoi(const char *str);
long long	get_time();

/*---- Functions from test_function.c ------------------------*/
void		printf_everything(t_info info);
