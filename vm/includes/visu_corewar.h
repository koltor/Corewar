/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visu_corewar.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 14:14:54 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 17:13:24 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VISU_COREWAR_H
# define VISU_COREWAR_H

# include "SDL_ttf.h"
# include "SDL_mixer.h"
# include "SDL_image.h"
# include "SDL.h"
# include "corewar.h"

# define WIN_SIZE_X 2000
# define WIN_SIZE_Y 1200

# define RESOURCES_VISU_IMG ".resources_visu/img/"
# define RESOURCES_VISU_FONT ".resources_visu/font/"
# define RESOURCES_VISU_SOUND ".resources_visu/sounds/"

typedef struct	s_arena
{
	int			square_size_x;
	int			square_size_y;
	int			space;
	SDL_Rect	rect[MEM_SIZE];

}				t_arena;

typedef struct	s_win_size
{
	int	x;
	int	y;
}				t_win_size;

typedef struct	s_env
{
	SDL_Window			*pwindow;
	SDL_Surface			*screen;
	char				*visu_path;
	struct s_win_size	win_size;
	long long			time;
	t_bool				pause;
	TTF_Font			*police2;
	TTF_Font			*police1;
	struct s_arena		arena;
	int					champ_live[MAX_PLAYERS + 1];
	char				foot_print[MEM_SIZE];
	Mix_Chunk			*sound[16];
	t_bool				forced_to_quit;
}				t_env;

t_env			*g_env(t_env *env_src);
t_bool			init_sdl(char *path);
char			*get_assets_path(char *name, int type);
void			init_foot_print(t_data *data);
void			visu_interface(t_data *data, unsigned long cycle_local);
void			print_arena(t_data *data);
void			live_bar(t_data *data);
void			intro(void);
char			sdl_loop(unsigned long time, t_data *data,
											unsigned long cycle_local);
t_bool			loop_corewar(t_data *data, unsigned long cycle_local);
void			show_the_winner(t_data *data, unsigned long cycle_local);
void			print_variable(t_data *data, unsigned long cycle_local);
void			quit_sdl();
void			init_arena();
void			print_value(int value, SDL_Rect *rect, SDL_Color color,
														TTF_Font *font);
void			print_value_hexa(int value, SDL_Rect *rect, SDL_Color color,
																TTF_Font *font);
void			print_text(char *string, SDL_Rect *rect, SDL_Color color,
															TTF_Font *font);
void			print_image(SDL_Rect *pos, char *img_name);
void			draw_empty_rect(SDL_Rect *origin, int color, int thickness);
void			highlight_process(t_data *data);
void			info_process(int x, int y, t_data *data,
									unsigned long cycle_local);
void			process_present(t_list *begin, unsigned int pos_process);
void			show_metadata_process(t_process *process);
void			show_metadata_process2(t_process *process);
void			show_metadata_process_title(void);
void			set_live_visu_bzero();
void			set_live_visu(char id);

int				my_rand(int value);
void			sound_bank_init(void);
void			play_music(void);
void			play_sound(char opc);
t_bool			check_visu_ressource(void);
#endif
