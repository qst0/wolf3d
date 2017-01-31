/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 06:11:22 by myoung            #+#    #+#             */
/*   Updated: 2017/01/27 02:23:40 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void			ft_get_time(struct timespec *ts)
{
	clock_serv_t		cclock;
	mach_timespec_t		mts;

	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
}

/* hack to count the time passed in seconds */
static void		view_check_moment(t_view *v)
{
	int				moment;
   
	moment	= (int)(v->cur_time / 100000000);
	if (!v->past && moment == 9)
	{
		v->cur_sec++;
		v->past = 1;
	}
	if (v->past && moment == 0)
		v->past = 0;
}

/* set the frame time and the move and rot speed using it */
static void		calc_view_fps(t_view *v)
{
	v->frame_time = (double)(v->cur_time - v->old_time) / 1000000000.0;
	if (v->frame_time > 0)
	{
		v->move_speed = (v->frame_time * 3.7);
		v->rot_speed = ((double)M_PI * v->frame_time / 1.25);
	}
}

void	update_time(t_view *v)
{
	struct timespec	ts;
	view_check_moment(v);	
	ft_get_time(&ts);
	v->old_time = v->cur_time;
	v->cur_time = ts.tv_nsec;
	calc_view_fps(v);	
}
