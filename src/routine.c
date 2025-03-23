/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:45:58 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/23 19:35:52 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	lock_forks(t_philo *philo)
{
	long	time;

	time = 0;
	if (philo->num % 2 == 0)//if even grab own fork first
	{
		pthread_mutex_lock(&(*philo->mutex_own_fork)); //todo secure
		*philo->own_fork = 0;
		time = get_time_ms();
		printf("%ld %i has taken a fork\n", time - *philo->start_time, philo->num);
		pthread_mutex_lock(&(*philo->mutex_fork_right));//todo secure
		*philo->fork_right = 0;
		time = get_time_ms();
		printf("%ld %i has taken a fork\n", time - *philo->start_time, philo->num);
	}
	else
	{
		pthread_mutex_lock(&(*philo->mutex_fork_right));//todo secure
		*philo->fork_right = 0;
		time = get_time_ms();
		printf("%ld %i has taken a fork\n", time - *philo->start_time, philo->num);
		pthread_mutex_lock(&(*philo->mutex_own_fork));//todo secure
		*philo->own_fork = 0;
		time = get_time_ms();
		printf("%ld %i has taken a fork\n", time - *philo->start_time, philo->num);
	}
}

void	unlock_forks(t_philo *philo)
{
	if (philo->num % 2 == 0)//if even grab own fork first
	{
		pthread_mutex_unlock(&(*philo->mutex_own_fork)); //todo secure
		*philo->own_fork = 1;
		pthread_mutex_unlock(&(*philo->mutex_fork_right));//todo secure
		*philo->fork_right = 1;
	}
	else
	{
		pthread_mutex_unlock(&(*philo->mutex_fork_right));//todo secure
		*philo->fork_right = 1;
		pthread_mutex_unlock(&(*philo->mutex_own_fork));//todo secure
		*philo->own_fork = 1;
	}
	philo->end_last_meal = get_time_ms();
}

void	*routine(void *arg)
{
	t_philo *philo;
	long	time;

	philo = (t_philo *)arg;
	time = get_time_ms();
	printf("%ld ===== Hello from philo no %i\n", time - *philo->start_time, philo->num);
	
	while (*philo->dead_flag == 0)
	{
		//grab forks and lock
		lock_forks(philo);

		//eat for time to eat
		eat(philo);
		//sleep for time to sleep
		go_sleep(philo);
		//think
		if (philo->dead == 0)
		{
			time = get_time_ms();
			printf("%ld %i is thinking\n", time - *philo->start_time, philo->num);
		}
	}
	return (NULL);
}

void	go_sleep(t_philo *philo)
{
	long	time;

	if (philo->dead == 0)
	{
		time = get_time_ms();
		printf("%ld %i is sleeping\n", time - *philo->start_time, philo->num);
		usleep(philo->time_sleep * 1000);
	}
}

void	eat(t_philo *philo)
{
	long	time;

	time = get_time_ms();
	if (time - philo->end_last_meal >= philo->time_die)
	{
		*philo->dead_flag = 1;
		philo->dead = 1;
		return ;
	}
	printf("%ld %i is eating\n", time - *philo->start_time, philo->num);
	usleep(philo->time_eat * 1000);

	pthread_mutex_lock(&(philo->mutex_times_eaten)); //todo secure
	philo->times_eaten++;
	// printf("%i has eaten %i times\n", philo->num, philo->times_eaten);
	pthread_mutex_unlock(&(philo->mutex_times_eaten)); //todo secure
	
	unlock_forks(philo);
}