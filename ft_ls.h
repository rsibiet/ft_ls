/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 11:26:23 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/25 17:11:59 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef struct passwd	t_pwd;
typedef struct group	t_gid;

/*
** n[0][i] = nb of hard links / i file
** n[1][i] = total size, in bytes / i file
** ac = nb of paramater without opt (Ralrt)
** nb_f = number of files / directory
** d = nb of current directory in av;
** av = parameter without opt
** opt[nb_opt] : 0 <= nb_opt <= 4 , opt[nb_opt] = 0 || 1
*/

typedef struct	s_data
{
	int			**n;
	int			ac;
	int			i;
	int			j;
	int			sp_tp;
	int			nb_f;
	int			d;
	long		sec;
	char		**av;
	int			space[6];
	int			opt[5];
	char		*doc;
}				t_data;

typedef struct	s_age
{
	char		***cd;
	char		**ch;
	int			n;
	long		*t_d;
	int			tp;
}				t_age;

/*
** main -> def_opt -> ls_opt
**                 -> cut_opt
**      -> pt_illegal_opt
**      -> print_error
**      -> rd_files -> sort_files -> dp_ls -> dp_lls ...
**                                 -> take_data -> def_older_file -> (*)
** (*) -> calc_tfile -> sort_tfiles
**                   -> compt_month
**                                              -> malloc_to_add_data -> ...
**      -> sort_av -> check_opt -> ft_ls -> print_error
**                                       -> rd_files -> sort_files -> ...
**                              -> ft_lsr -> ...
*/

/*
** Fonctions in ft_ls file
*/

void			cut_opt(int ac, char **av, t_data *d, int j);
void			sort_files(t_data *d, char ***dir, int i, int j);
char			def_opt(int ac, char **av, t_data *d, int i);
int				ls_opt(char **av, int *i, int *j, t_data *d);

/*
** Fonctions in dp_ls file
*/

void			sort_av(t_data *d, int i, int j, int tp);
char			***malloc_dir(t_data *d, DIR *rep, int *i);
void			rd_files(DIR *rep, t_data *d, int j, int i);
void			ft_lsr(t_data *d, int i, t_stat *s);
void			ft_ls(t_data *d, int i, t_stat *s);

/*
** Fonctions in dp_ls2 file
*/

void			calc_tfile(t_data *d, char ***dir, t_age *a, int i);
void			def_older_file(t_data *d, char ***dir, int i);
void			take_data(t_data *d, char ***dir, int i);
void			check_opt(t_data *d);
void			dp_ls(t_data *d, char ***dir, int i);

/*
** Fonctions in ls_data file
*/

void			compt_spaces(t_data *d, char ***dir, int *i, t_stat *s);
void			add_data(t_data *d, char ***dir, int *i, t_stat *s);
void			malloc_to_add_data(t_data *d, char ***dir, int i);
void			compt_month(t_age *a, int i);
void			sort_tfiles(char ***dir, t_age *a, int i);

/*
** Fonctions in ls_error
*/

void			sort_just_files(t_data *d, int *tp, int *i, t_stat *s);
void			one_file(t_data *d, char *c, int j);
void			pt_illegal_opt(char opt);
void			print_error2(char *c, t_data *d);
void			print_error(void);

/*
** Fonctions in dp_lls file
*/

void			last_free_and_recursive(t_data *d, char ***dir);
void			dp_mode(t_stat *s);
void			dp_slink(char ***dir, int *i);
void			dp_lls(t_data *d, char ***dir, int *i, int tp);
void			dp_total_nb_blocs(t_data *d, char ***dir, int i);

/*
** Fonctions in l-spaces file
*/

void			dp_date(char ***dir, int *i, int j);
void			dp_space_four(t_data *d, char ***dir, int *i);
void			dp_space_three(t_data *d, int *i);
void			dp_space_two(t_data *d, char ***dir, int *i);
void			dp_space_one(t_data *d, int *i);

/*
** Fonctions in l_space_two file
*/

void			test_dir(char ***dir, t_data *d, DIR *rep, int i);
void			dp_av_name(DIR *rep, t_data *d, int i);
void			dp_avr_name(DIR *rep, t_data *d, int i);
void			free_if_lopt(t_data *d, char ***dir);
void			dp_space_five(t_data *d, int *i);

/*
** Fonctions in finish_to_sort file
*/

void			final_sort_av(t_data *d, int i, int *tp, char *c);
void			sort_tfiles_ascii(char ***dir, t_age *a, int i, char *c);
void			sub_sort_tfiles(char ***dir, int i, char *c, t_age *a);
void			sub_sort_av(t_data *d, int *i, int *j, char *c);
void			sub_sort_files(char ***dir, int *i, int *j, char *c);

/*
** Fonctions in ls_recursive file
*/

void			recall_rd_files(DIR *rep, t_data d, int j, char ***dir);
void			ls_finish_to_del(t_data *d, DIR *rep, char ***dir, int i);
void			ls_recursive(t_data *d, char ***dir);
void			ls_r_recursive(t_data *d, char ***dir, int i);

/*
** Fonctions in ls_final_recursive file
*/

void			ls_ta_final_recurs(t_data *d, char ***dir, int i, DIR *rep);
void			ls_rta_final_recurs(t_data *d, char ***dir, int i, DIR *rep);
void			final_take_data(t_data *d, char ***dir, int i);

/*
** Fonctions in ls_special_device file
*/

int				atoi_hex_to_ten(char *c, int i, int nb);
void			min_maj_special_device(t_data *d, char *c, int j, int *i);
void			ft_itoa_hex(t_data *d, int nb, int j, int *i);

/*
** Fonctions in cut_to_norme_ls file
*/

void			compt_spaces2(t_data *d, char ***dir, int *i);
void			calc_tfile1(t_data *d, char ***dir, t_age *a, int i);
void			dp_lls2(t_data *d, int *i, char ***dir);

#endif
