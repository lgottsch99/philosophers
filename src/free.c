/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:50:32 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/28 17:16:10 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	free_philos(t_philo **array, int i)
{
	// printf("freeing philos\n");

	i = i - 1; //index at 0
	//go from back and free each struct
	while (i >= 0)
	{
		//need to free pthread_t too?
		//free(array[i]->thread);
		pthread_mutex_destroy(&array[i]->mutex_times_eaten);
		pthread_mutex_destroy(&array[i]->mutex_end_last_meal);
		array[i]->mutex_own_fork = NULL;
		array[i]->mutex_fork_right = NULL;
		free(array[i]);//freeing single philo struct?
		array[i] = NULL;
		i--;
	}
}


void	free_fork_mutexes(pthread_mutex_t **fork_mutexes, int num_philos)
{
	// printf("freeing fork mutexes\n");
		//todo
	//loop and destroy each
	//then free each
	// (void)num_philos;
	int	i;
	pthread_mutex_t *tmp;

	tmp = *fork_mutexes;
	i = 0;
	// i = num_philos;
	// while (i >= 0)
	while (i < num_philos)
	{
		// printf("in loop\n");
		// pthread_mutex_destroy(fork_mutexes[i]);
		pthread_mutex_destroy(tmp);
		i++;
		tmp++;
	}
	tmp = NULL;
	free(*fork_mutexes);
	*fork_mutexes = NULL;
}

void	free_program(t_program *program)
{
	// printf("freeing program\n");
	//go thru all structs and free everything malloced/destroy mutex
	free_philos(program->philos, program->num_philos);
	free(program->philos);
	program->philos = NULL;
	free_fork_mutexes(&program->fork_mutexes, program->num_philos); //todo
	program->fork_mutexes = NULL;
	program = NULL;
}
