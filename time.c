/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 06:11:22 by myoung            #+#    #+#             */
/*   Updated: 2017/01/19 02:22:56 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	ft_get_time(struct timespec *ts)
{
	clock_serv_t		cclock;
	mach_timespec_t		mts;

	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
}

void	update_time(t_view *v)
{
	struct timespec	ts;
	int				moment;
   
	moment	= (int)(v->cur_time / 100000000);
	ft_get_time(&ts);
	//hack to count the time passed in seconds	
	if (!v->past && moment == 9)
	{
		v->cur_sec++;
		v->past = 1;
	}
	if (v->past && moment == 0)
		v->past = 0;

	//timeing for input and FPS counter
	v->old_time = v->cur_time;
	v->cur_time = ts.tv_nsec;
	v->frame_time = (double)(v->cur_time - v->old_time) / 1000000000.0;
	if (v->frame_time > 0)
	{
		//constant value in squares/second
		v->move_speed = (v->frame_time * 3.7);
		//constant value in radians/second	
		v->rot_speed = ((double)M_PI * v->frame_time / 1.25);
	}
}
