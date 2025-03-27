/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:45:58 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/27 18:03:38 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

//if daed flag on -> stop and clean thread?
void	*routine(void *arg)
{
	t_philo *philo;
	long	time;
	// int i;

	philo = (t_philo *)arg;
	time = get_time_ms();
	printf("%ld ===== Hello from philo no %i\n", time - philo->start_time, philo->num);
	
	while (time <= philo->start_time)
	{
		usleep(100);
		time = get_time_ms();
	}
	// i = 0;
	while (philo->dead == 0)
	{
		// printf("start sim\n");
		//eat for time to eat
		eat(philo);
		if (philo->dead == 1)
		{
			pthread_detach(philo->thread);
			return (NULL);
		}
		//sleep for time to sleep
		go_sleep(philo);
		//think
		if (philo->dead == 0)
		{
			time = get_time_ms();
			printf("%ld %i is thinking\n", time - philo->start_time, philo->num);
		}
		// i++;
	}
	// exit(0);
	pthread_detach(philo->thread);
	return (NULL);
}

void	go_sleep(t_philo *philo)
{
	long	time;

	if (philo->dead == 0)
	{
		time = get_time_ms();
		printf("%ld %i is sleeping\n", time - philo->start_time, philo->num);
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
		printf("SB DIED\n");
		// exit(0);
		return ;
	}
	//grab forks and lock
	lock_forks(philo);
	printf("%ld %i is eating\n", time - philo->start_time, philo->num);

	pthread_mutex_lock(&(philo->mutex_end_last_meal)); //reset end time bc he just startet eating
	philo->end_last_meal = get_time_ms();
	pthread_mutex_unlock(&(philo->mutex_end_last_meal));

	usleep(philo->time_eat * 1000);

	pthread_mutex_lock(&(philo->mutex_times_eaten)); //todo secure
	philo->times_eaten++;
	// printf("%i has eaten %i times\n", philo->num, philo->times_eaten);
	pthread_mutex_unlock(&(philo->mutex_times_eaten)); //todo secure
	
	pthread_mutex_lock(&(philo->mutex_end_last_meal));
	philo->end_last_meal = get_time_ms();
	pthread_mutex_unlock(&(philo->mutex_end_last_meal));
	
	unlock_forks(philo);
}