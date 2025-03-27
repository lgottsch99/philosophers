/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:50:32 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/27 18:27:17 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	free_philos(t_philo **array, int i)
{
	//go from back and free each struct
	while (i >= 0)
	{
		//need to free pthread_t too?
		//free(array[i]->thread);
		pthread_mutex_destroy(array[i]->mutex_times_eaten);
		pthread_mutex_destroy(array[i]->mutex_end_last_meal);
		array[i]->mutex_own_fork = NULL;
		array[i]->mutex_fork_right = NULL;
		free(array[i]);
		i--;
	}
	//then free array of ptrs
	free(array);
}


void	free_fork_mutexes(pthread_mutex_t *fork_mutexes, int num_philos)
{
		//todo
	//loop and destroy each
	//then free each
	int	i;

	i = 0;
	while (i < num_philos)
	{
		
	}

	
}

void	free_program(t_program *program)
{
	//go thru all structs and free everything malloced/destroy mutex
	free_philos(program->philos, program->num_philos);
	free_fork_mutexes(program->fork_mutexes, program->num_philos); //todo

}
