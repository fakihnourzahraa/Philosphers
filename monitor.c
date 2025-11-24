/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:50:47 by nour              #+#    #+#             */
/*   Updated: 2025/11/23 19:55:52 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_thread(void *arg)
{
	t_rules *rules;
	long long	time;
	int			i;

	i = 0;
	rules = (t_rules *)arg;
	while (1)
	{
		while (rules->finish_all && i < rules->num)
		{
			pthread_mutex_lock(rules->print);
			time = get_time - rules->start_time;			
			if (time > rules->t_to_die)
			{
				dying(rules->philos[i]);
				pthread_mutex_lock(rules->death);
				rules->finish_all = 1;
				pthread_mutex_unlock(rules->death);
			}
			pthread_mutex_unlock(rules->print);
			i++;
		}
	}
}