/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:11:10 by nfakih            #+#    #+#             */
/*   Updated: 2025/12/11 20:11:34 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_to_die_exceeded(t_rules *rules)
{
	int			i;
	long long	current_time;
	long long	time_since_last_meal;
	long long	timestamp;

	i = 0;
	while (i < rules->philo_amount)
	{
		current_time = get_time();
		time_since_last_meal = current_time - rules->philos[i]->last_meal;
		if (time_since_last_meal >= rules->t_to_die)
		{
			pthread_mutex_lock(rules->print);
			timestamp = get_time() - rules->start_time;
			printf("%lld %d died\n", timestamp, rules->philos[i]->index);
			pthread_mutex_unlock(rules->print);
			pthread_mutex_lock(rules->death);
			rules->finish_all = 1;
			pthread_mutex_unlock(rules->death);
			return ;
		}
		i++;
	}
}

void	all_have_eaten(t_rules *rules)
{
	int	i;
	int	all_ate;

	if (rules->must_eat == -1)
		return ;
	i = 0;
	all_ate = 1;
	while (i < rules->philo_amount)
	{
		pthread_mutex_lock(rules->print);
		if (rules->philos[i]->meals < rules->must_eat)
			all_ate = 0;
		pthread_mutex_unlock(rules->print);
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(rules->death);
		rules->finish_all = 1;
		pthread_mutex_unlock(rules->death);
	}
}

void	*monitor_thread(void *arg)
{
	t_rules	*rules;
	int		done;

	rules = (t_rules *)arg;
	done = 0;
	while (!done)
	{
		pthread_mutex_lock(rules->death);
		done = rules->finish_all;
		pthread_mutex_unlock(rules->death);
		if (!done)
		{
			t_to_die_exceeded(rules);
			all_have_eaten(rules);
			usleep(1000);
		}
	}
	return (NULL);
}
//checks every 1 ms, dont remove usleep
