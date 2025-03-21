/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:50:32 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/21 15:19:26 by lgottsch         ###   ########.fr       */
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
		free(array[i]);
		i--;
	}
	//then free array of ptrs
	free(array);
}

