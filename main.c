/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:47:09 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/14 16:07:02 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	fill_in(t_rules *in, char **argv)
{
	printf("hi");
	if (argv[1] && ft_atoi(argv[1]))
		in->philos = ft_atoi(argv[1]);
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
int	main(int argc, char **argv)
{
	t_rules in;

	if (argc != 7 && argc != 6 )
	{
		return (1);
	}
		printf("hi");
	if (argv[1] && ft_atoi(argv[1]))
		in.philos = ft_atoi(argv[1]);
	else
		return (0);
	if (argv[2] && ft_atoi(argv[2]))
		in.t_to_die = ft_atoi(argv[2]);
	else
		return (0);
	if (argv[3] && ft_atoi(argv[3]))
		in.t_to_eat = ft_atoi(argv[3]);
	else
		return (0);
	if (argv[4] && ft_atoi(argv[4]))
		in.t_to_sleep = ft_atoi(argv[4]);
	else
		return (0);
	if (argv[5] && ft_atoi(argv[5]))
		in.must_eat = ft_atoi(argv[5]);
	else
		in.must_eat = -1;
	printf("%d\n%lld\n%lld\n%d\n",in.philos, in.t_to_die, in.t_to_eat, in.must_eat);
		return (1);

}
