/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:02:06 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/28 18:04:02 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	*monitoring(void *arg)
{
	// printf("----MONITORING STARTET----\n");
	t_program *program;


	program = (t_program *)arg;
	//need to ckeck:
		//sb died (time since last meal > time to die?)
		//all ate eough?
	// if (program->times_to_eat == -1)
	// 	printf("no max eat times\n");
	// else
	// 	printf("everybody should eat %i times\n", program->times_to_eat);

	did_sb_die(program); //OLD VERSION 

	// printf("returned in monitor\n");
	pthread_detach(program->monitor);
	return (NULL);
}

void	detach_all_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		// printf("inloop\n");
		pthread_detach(program->philos[i]->thread);
		i++;
	}
}


void	did_sb_die(t_program *program)
{		
	// printf("--- DID SB DIE-----\n");

	int		i;
	int		y;
	long	time;

	while (1)
	{
		//TOdo calcullations for each philo time now vs since last meal 
		i = 0;
		y = 0;
		while (i < program->num_philos) //check each philo death
		{
			time = get_time_ms();
			pthread_mutex_lock(&(program->philos[i]->mutex_end_last_meal));
			if (time - program->philos[i]->end_last_meal >= program->time_die)
			{
				pthread_mutex_unlock(&(program->philos[i]->mutex_end_last_meal));
				pthread_mutex_lock(&program->mutex_dead_flag);
				*program->dead_flag = 1;
				pthread_mutex_unlock(&program->mutex_dead_flag);
				pthread_mutex_lock(&program->write_lock); //no unlocking here 
				printf("%ld %i has died\n", time - program->philo_start, i + 1); //program->philos[i]->num);
				
				//free stop everything


				
				//try to detach all philos?
				detach_all_philos(program);

				return ;
			}
			pthread_mutex_unlock(&(program->philos[i]->mutex_end_last_meal));
			
			
			if (program->times_to_eat != -1)
			{
				pthread_mutex_lock(&(program->philos[i]->mutex_times_eaten)); //todo secure
				if (program->philos[i]->times_eaten >= program->times_to_eat)
					y++;
				pthread_mutex_unlock(&(program->philos[i]->mutex_times_eaten)); //todo secure
			}
			i++;
		}
		if (y == program->num_philos) //all ate enough
		{
			time = get_time_ms();
			// printf("%ld ALL ATE ENOUGH ------- \n", time - program->start_time);
			pthread_mutex_lock(&program->mutex_dead_flag);
			*program->dead_flag = 1;
			pthread_mutex_unlock(&program->mutex_dead_flag);

			pthread_mutex_lock(&(program->write_lock)); //no unlocking here 
		// for (int u = 0; u < program->num_philos; u++)
			// {
			// 	pthread_mutex_lock(&(program->philos[u]->mutex_times_eaten)); //todo secure
			// 	printf("philo %i ate %i times\n", program->philos[u]->num, program->philos[u]->times_eaten);
			// 	pthread_mutex_unlock(&(program->philos[u]->mutex_times_eaten)); //todo secure

			// }

			//try to detach all philos?
			detach_all_philos(program);
			return ;

		}
	}
}


