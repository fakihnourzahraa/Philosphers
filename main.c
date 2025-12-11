/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:47:09 by nfakih            #+#    #+#             */
/*   Updated: 2025/12/11 22:06:02 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	tie(t_philosophers **philos, t_rules *in, int philo_amount)
{
	int	i;

	i = 0;
	while (i < philo_amount)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	pthread_join(in->monitor, NULL);
	kill_philo(philos);
}

void	philo(t_rules *in)
{
	t_philosophers	**philos;
	int				i;
	int				philo_amount;

	philo_amount = in->philo_amount;
	philos = fill_philo(in);
	in->philos = philos;
	i = 0;
	pthread_create(&in->monitor, NULL, monitor_thread, in);
	if (philo_amount == 1)
	{
		pthread_create(&philos[i]->thread, NULL, single_routine, philos[i]);
		pthread_join(philos[0]->thread, NULL);
		pthread_join(in->monitor, NULL);
		kill_philo(philos);
		return ;
	}
	while (i < philo_amount)
	{
		pthread_create(&philos[i]->thread, NULL, philos_routine, philos[i]);
		i++;
	}
	tie(philos, in, philo_amount);
}

int	main(int argc, char **argv)
{
	t_rules			*in;

	if (argc != 6 && argc != 5)
		return (1);
	in = init_in();
	if (!fill_in(in, argv))
	{
		kill_rules(in);
		return (1);
	}
	philo(in);
	return (0);
}
