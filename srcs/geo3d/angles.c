/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:55:45 by kdouveno          #+#    #+#             */
/*   Updated: 2018/04/10 10:55:45 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo3d.h"

double	rad(double deg)
{
	return (deg * M_PI / 180);
}

double	deg(double rad)
{
	return (rad * 180 / M_PI);
}
