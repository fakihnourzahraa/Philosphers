/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:47:09 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/15 15:36:08 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	fill_in(t_rules *in, char **argv)
{
	if (argv[1] && ft_atoi(argv[1]))
		in->num = ft_atoi(argv[1]);
	else
		return (0);
	if (argv[2] && ft_atoi(argv[2]))
		in->t_to_die = ft_atoi(argv[2]);
	else
		return (0);
	if (argv[3] && ft_atoi(argv[3]))
		in->t_to_eat = ft_atoi(argv[3]);
	else
		return (0);
	if (argv[4] && ft_atoi(argv[4]))
		in->t_to_sleep = ft_atoi(argv[4]);
	else
		return (0);
	if (argv[5] && ft_atoi(argv[5]))
		in->must_eat = ft_atoi(argv[5]);
	else
		in->must_eat = -1;
	return (1);
}


t_philospher	*new_philo(t_rules in, int i)
{
	t_philospher	*philo;
	t_rules			*rules;
	
	philo = malloc(sizeof(t_philospher));
	philo->index = i;
	philo->alive = true;
	philo->ate = false;
	philo->left = NULL;
	philo->right = NULL;
	philo->rules = NULL;
	philo->thread = NULL;
	rules = malloc(sizeof(t_rules));
	rules->monitor = in.monitor;
	rules->must_eat = in.must_eat;
	rules->num = in.num;
	rules->t_start = in.t_start;
	rules->t_to_die = in.t_to_die;
	rules->t_to_eat = in.t_to_eat;
	rules->t_to_sleep = in.t_to_sleep;
	philo->rules = rules;
	return (philo);
}

void	init_philo(t_philospher *philos[], t_rules in)
{
	int	i;
	int	num;

	i = 0;
	num = in.num;
	while (i < num)
	{
		philos[i] = new_philo(in, i);
		i++;
	}
}

t_rules	*init_in(char **argv)
{
	pthread_t id;
	t_rules	 *in;

	in = malloc(sizeof(t_rules));
	in->num = 0;
	in->t_to_die = 0;
	in->t_to_eat = 0;
	in->t_to_sleep = 0;
	in->t_start = 0;
	in->must_eat = 0;
	return (in);
	//in->monitor = pthread_create(&id, 
}

void	philo(t_rules *in)
{
	t_philospher philos[in->num];

	init_philo(&philos, *in);
}

int	main(int argc, char **argv)
{
	t_rules *in;

	if (argc != 6 && argc != 5 )
		return (1);
	in = init_in(argv);
	fill_in(in, argv);
	philo(in);
	return(0);
}
