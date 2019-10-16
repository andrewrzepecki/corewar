/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrzepec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:37:08 by anrzepec          #+#    #+#             */
/*   Updated: 2019/10/15 14:37:15 by anrzepec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void		live(t_env *env, int id)
{
	if (id < env->nb_players)
	{
		ft_printf("Player %s (%d) is alive!\n", env->player[id].name, id);
		env->player[id].live = 1;
	}
	else
		ft_printf("Player with id %d doesn't exist: error\n", id);
	
}

void		direct_load(t_env *env, )