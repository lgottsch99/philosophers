/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:20:55 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/25 18:50:29 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	int	num;

	num = 0;
	neg = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	return (num * neg);
}


long	get_time_ms()
{
	//try only get time of day
	struct timeval time;
	long	sec;
	long	microsec;
	long	millisec;

	gettimeofday(&time, NULL);

	sec = time.tv_sec;
	microsec = time.tv_usec;
	millisec = (sec * 1000) + (microsec / 1000);
	// printf("start time in millisec: %ld\n", millisec);
	return (millisec);
}


void	print_philo(t_philo *philo)
{
	printf("num: %i\n", philo->num);
	printf("time_die: %i\n", philo->time_die);
	printf("time_eat: %i\n", philo->time_eat);
	printf("time_sleep: %i\n", philo->time_sleep);
	// printf("times_to eat: %i\n", philo->times_to_eat);
	printf("dead: %i\n", philo->dead);
	printf("times eaten: %i\n", philo->times_eaten);
	printf("dead flag: %i\n", *philo->dead_flag);
	printf("start time: %ld\n", philo->start_time);
	printf("own fork: %p\n", (void *)philo->own_fork);
	printf("mutex own fork: %p\n", (void *)philo->mutex_own_fork);

	printf("right fork: %p\n", (void *)philo->fork_right);
	printf("mutex right fork: %p\n", (void *)philo->mutex_fork_right);

}

void	lock_forks(t_philo *philo)
{
	long	time;

	time = 0;
	if (philo->num % 2 == 0)//if even grab own fork first
	{
		pthread_mutex_lock(&(*philo->mutex_own_fork)); //todo secure
		*philo->own_fork = 0;
		time = get_time_ms();
		printf("%ld %i has taken a fork\n", time - philo->start_time, philo->num);
		pthread_mutex_lock(&(*philo->mutex_fork_right));//todo secure
		*philo->fork_right = 0;
		time = get_time_ms();
		printf("%ld %i has taken a fork\n", time - philo->start_time, philo->num);
	}
	else
	{
		pthread_mutex_lock(&(*philo->mutex_fork_right));//todo secure
		*philo->fork_right = 0;
		time = get_time_ms();
		printf("%ld %i has taken a fork\n", time - philo->start_time, philo->num);
		pthread_mutex_lock(&(*philo->mutex_own_fork));//todo secure
		*philo->own_fork = 0;
		time = get_time_ms();
		printf("%ld %i has taken a fork\n", time - philo->start_time, philo->num);
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
}
