#include <wolf.h>

static void init_view_vars(t_view *view)
{
	view->pos.x = view->map.height / 2;
	view->pos.y = view->map.width / 2;
	view->dir.x = -1;
	view->dir.y = 0;
	view->plane.x = 0;
	view->plane.y = .66;
	view->past = 0;
	view->cur_sec = 0;
	view->cur_time = 0;
	view->old_time = 0;
	view->mouse_x = 0;
	view->mouse_y = 0;
	view->rot_speed = 0.00016666;
	view->move_speed = 0.00016666;
}

void	init_view(int w, int h, char *title)
{
	t_view *view;
	view = (t_view*)malloc(sizeof(t_view));
	view->mlx = mlx_init();
	view->map = parse_map("maps/demo.map");
	view->window = mlx_new_window(view->mlx, w, h, title);
	view->w = w;
	view->h = h;
	view->z_buff = (double*)malloc(WINDOW_WIDTH * sizeof(double));
	init_view_vars(view);
	keys_init(&view->key);
	set_hooks(view);
	texture_init(view);
	create_minimap(view);
	mlx_loop_hook(view->mlx, loop_hook, view);
	mlx_loop(view->mlx);
}
