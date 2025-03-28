/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:45:58 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/28 17:41:00 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	check_deaths(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_dead_flag);
	if (*philo->dead_flag != 1)
		return (1);
	pthread_mutex_unlock(philo->mutex_dead_flag);
	return (0);
}

//if daed flag on -> stop and clean thread?
void	*routine(void *arg)
{
	t_philo *philo;
	long	time;

	philo = (t_philo *)arg;
	time = get_time_ms();
	// printf("%ld ===== Hello from philo no %i\n", time - philo->start_time, philo->num);
	
	while (time <= philo->start_time)
	{
		usleep(100);
		time = get_time_ms();
	}

	while (philo->dead == 0)
	{
		pthread_mutex_lock(philo->mutex_dead_flag);
		if (*philo->dead_flag == 1)
			break ;
		pthread_mutex_unlock(philo->mutex_dead_flag);
		// if (check_deaths(philo) == 1)
		// 	break ;

		//eat for time to eat
		eat(philo);
		if (philo->dead == 1)
			break ;
		// if (check_deaths(philo) == 1)
		// 	break ;
	
		//sleep for time to sleep
		go_sleep(philo);
		//think
		// if (check_deaths(philo) == 1)
		// 	break ;
		if (philo->dead == 0)
		{
			time = get_time_ms();
			pthread_mutex_lock(philo->write_lock);

			printf("%ld %i is thinking\n", time - philo->start_time, philo->num);
			pthread_mutex_unlock(philo->write_lock);
		}		
	}
	pthread_detach(philo->thread);
	return (NULL);
}

void	go_sleep(t_philo *philo)
{
	long	time;

	if (philo->dead == 0)
	{
		time = get_time_ms();
		pthread_mutex_lock(philo->write_lock);

		printf("%ld %i is sleeping\n", time - philo->start_time, philo->num);
		pthread_mutex_unlock(philo->write_lock);

		usleep(philo->time_sleep * 1000);
	}
}

void	eat(t_philo *philo)
{
	long	time;

	time = get_time_ms();
	if (time - philo->end_last_meal >= philo->time_die)
	{
		// pthread_mutex_lock(philo->mutex_dead_flag);
		*philo->dead_flag = 1;
		// pthread_mutex_unlock(philo->mutex_dead_flag);
		philo->dead = 1;
		// printf("SB DIED\n");
		// exit(0);
		return ;
	}
	// //grab forks and lock
	// if (*philo->dead_flag != 1)
	// {
	lock_forks(philo);
	pthread_mutex_lock(philo->write_lock);
	time = get_time_ms();
	printf("%ld %i is eating\n", time - philo->start_time, philo->num);
	pthread_mutex_unlock(philo->write_lock);

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