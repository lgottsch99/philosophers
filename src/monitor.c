/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:02:06 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/23 19:22:20 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	*monitoring(void *arg)
{
	// printf("----MONITORING STARTET----\n");
	t_program *program;

	program = (t_program *)arg;
	//constantly check if sb died
	did_sb_die(program);
	//smae with nr times eaten
	//did_all_eat(program);
	
	//if yes stop and free program

	return (NULL);
}

void	did_sb_die(t_program *program)
{		
	// printf("--- DID SB DIE-----\n");

	int		i;
	int		y;
	long	time;

	while (*program->dead_flag == 0)
	{
		//TOdo calcullations for each philo time now vs since last meal 
		i = 0;
		y = 0;
		while (i < program->num_philos) //check each philo
		{
			time = get_time_ms();
			if (time - program->philos[i]->end_last_meal >= program->philos[i]->time_die)
			{
				*program->dead_flag = 1;
				printf("%ld %i has died\n", time - *program->philos[i]->start_time, program->philos[i]->num);
				//free stop everything
				exit(0); //remove
			}
			pthread_mutex_lock(&(program->philos[i]->mutex_times_eaten)); //todo secure
			if (program->philos[i]->times_eaten >= program->times_to_eat)
				y++;
			pthread_mutex_unlock(&(program->philos[i]->mutex_times_eaten)); //todo secure
			i++;
		}
		if (y == program->num_philos)
		{
			// time = get_time_ms();
			// printf("%ld all ate enough\n", time - program->start_time);
			*program->dead_flag = 1;
			break;
		}
		




		// if (*program->dead_flag == 1)
		// {
		// 	i = 0;
		// 	while (i < program->num_philos)
		// 	{
		// 		if (program->philos[i] && program->philos[i]->dead == 1)
		// 			break ;
		// 		i++;
		// 	}
		// 	time = get_time_ms();
		// 	printf("%ld %i has died\n", time - *program->philos[i]->start_time, program->philos[i]->num);

		// 	//free everythnig?
		// 	exit (0);
		// }
	}
	exit(0);
}

void	did_all_eat(t_program *program)
{ printf("---DID ALL EAT?---\n");
	int i;
	int y;

	if (program && program->times_to_eat != -1)
	{
		printf("--monitoring times to eTA---\n");
		while (1)
		{

			i = 0;
			y = 0;
			//go trhu all philos and check times_eaten, if all > times_to eat dead_flag = 1
			while (i < program->num_philos)
			{
				if (program->philos[i]->times_eaten < program->times_to_eat)
					y++;
				i++;
			}
			if (y == program->num_philos - 1) //all of them passed check
			{
				printf("all ate enough\n");
				*program->dead_flag = 1;
			}
		}
	}
}


