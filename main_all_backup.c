/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:40:45 by magostin          #+#    #+#             */
/*   Updated: 2020/01/28 22:59:39 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "your_printf/srcs/printf.h"
#include "gnl/get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		ft_testarg(char *s)
{
	int		i;
	int		accu;
	int		width;

	accu = 0;
	width = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '*' && s[i - 1] != '.')
			width = 1;
		else if (s[i] == '*' && s[i - 1] == '.')
			accu = 1;
	}
	if (width == 1 && accu == 0)
		return (3);
	if (width == 0 && accu == 1)
		return (4);
	if (width == 1 && accu == 1)
		return (12);
	return (-1);
}

int		ft_comparelines(char *s1, char *s2)
{
	int		i = 0;

	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int			ft_checkline(int fd_user, int fd_printf, int fd_stdout, int ret_pf, int ret_ft, int toggleok)
{
	int		ret_val = 0;
	char	*line_user = NULL;
	char	*line_printf = NULL;

	dup2(fd_stdout, 1);
	get_next_line(fd_user, &line_user);
	get_next_line(fd_printf, &line_printf);
	//printf("\nline_user =   |%s| %d\n", line_user, fd_user);
	//printf("line_printf = |%s| %d\n", line_printf, fd_printf);
	(void)ret_ft;
	(void)ret_pf;
	if (!(ft_comparelines(line_user, line_printf) && ret_pf == ret_ft))
	{
		printf("\033[0;31m");
		printf("\nDIFF!\n");
		printf("\033[0m");
		printf("|\tft_printf: {%s} returned %d\n|\t   printf: {%s} returned %d\n", line_user, ret_ft - 3, line_printf, ret_pf - 3);
		ret_val = 1;
	}
	else if (toggleok != 0)
	{
		printf("\033[0;32m");
		printf("OK  ");
		printf("\033[0m");
		if (toggleok == 1)
			printf("\n|\tft_printf: {%s} returned %d\n|\t   printf: {%s} returned %d\n", line_user, ret_ft - 3, line_printf, ret_pf - 3);
	}
	dup2(fd_user, 1);
	free(line_printf);
	free(line_user);
	return (ret_val);
}

int main(int ac, char **av)
{
	int		all;
	int		ret_pf = 0;
	int		ret_ft = 0;
	int		i_arg;
	int		i_width;
	int		i_accu;
	int		i_string;
	int		fd_user;
	int		fd_printf;
	int		test_checked = 0;
	int		fd_stdout = dup(1);
	char	*arg_char[7] =
	{
		"|%c|\n",
		"|%5c|\n",
		"|%-5c|\n",
		"|%0c|\n",
		"|%-----5c|\n",
		"|%*c|\n",
		NULL
	};
	char	*strings[3] =
	{
		"Coco Toto",
		"",
		NULL
	};
	char	*arg_string[32] =
	{
		"|%s|\n",
		"|%15s|\n",
		"|%-15s|\n",
		"|%0s|\n",
		"|%-----5s|\n",
		"|%015s|\n",
		"|%-015s|\n",
		"|%0-15s|\n",
		"|%.s|\n",
		"|%.3s|\n",
		"|%.20s|\n",
		"|%.0s|\n",
		"|%15.6s|\n",
		"|%15.20s|\n",
		"|%15.0s|\n",
		"|%15.s|\n",
		"|%*s|\n",
		"|%-*s|\n",
		"|%0*s|\n",
		"|%0-*s|\n",
		"|%-0*s|\n",
		"|%.*s|\n",
		"|%-.*s|\n",
		"|%0.*s|\n",
		"|%0-.*s|\n",
		"|%-0.*s|\n",
		"|%*.*s|\n",
		"|%0*.*s|\n",
		"|%-*.*s|\n",
		"|%0-*.*s|\n",
		"|%-0*.*s|\n",
		NULL
	};
	char	*arg_int[32] =
	{
		"|%d|\n",
		"|%15d|\n",
		"|%-15d|\n",
		"|%0d|\n",
		"|%-----5d|\n",
		"|%015d|\n",
		"|%-015d|\n",
		"|%0-15d|\n",
		"|%.d|\n",
		"|%.3d|\n",
		"|%.20d|\n",
		"|%.0d|\n",
		"|%15.6d|\n",
		"|%15.20d|\n",
		"|%15.0d|\n",
		"|%15.d|\n",
		"|%*d|\n",
		"|%-*d|\n",
		"|%0*d|\n",
		"|%0-*d|\n",
		"|%-0*d|\n",
		"|%.*d|\n",
		"|%-.*d|\n",
		"|%0.*d|\n",
		"|%0-.*d|\n",
		"|%-0.*d|\n",
		"|%*.*d|\n",
		"|%0*.*d|\n",
		"|%-*.*d|\n",
		"|%0-*.*d|\n",
		"|%-0*.*d|\n",
		NULL
	};
	char	*arg_int2[32] =
	{
		"|%i|\n",
		"|%15i|\n",
		"|%-15i|\n",
		"|%0i|\n",
		"|%-----5i|\n",
		"|%015i|\n",
		"|%-015i|\n",
		"|%0-15i|\n",
		"|%.i|\n",
		"|%.3i|\n",
		"|%.20i|\n",
		"|%.0i|\n",
		"|%15.6i|\n",
		"|%15.20i|\n",
		"|%15.0i|\n",
		"|%15.i|\n",
		"|%*i|\n",
		"|%-*i|\n",
		"|%0*i|\n",
		"|%0-*i|\n",
		"|%-0*i|\n",
		"|%.*i|\n",
		"|%-.*i|\n",
		"|%0.*i|\n",
		"|%0-.*i|\n",
		"|%-0.*i|\n",
		"|%*.*i|\n",
		"|%0*.*i|\n",
		"|%-*.*i|\n",
		"|%0-*.*i|\n",
		"|%-0*.*i|\n",
		NULL
	};
	int		ints[3] =
	{
		2147483647,
		-2147483648,
		0
	};
	int		arg_w[3] = {-15, 0, 15};
	int		arg_a[3] = {-6, 0, 6};

	all = 0;
	if (ac == 1)
		all = 1;
	if (all == 1 || ft_strchr(av[1], 'c'))
	{
		printf("CONVERSION C:\n");
		i_arg = -1;
		while (arg_char[++i_arg])
		{
			if (ft_testarg(arg_char[i_arg]) == -1)
			{
				fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
				system(": > output_user.txt");
				dup2(fd_user, 1);
				fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
				system(": > output_printf.txt");
				ret_pf = dprintf(fd_printf, arg_char[i_arg], 42);
				ret_ft = ft_printf(arg_char[i_arg], 42);
				close(fd_user);
				fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
				close(fd_printf);
				fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
				if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
					dup2(fd_stdout, 1);printf("-->\t%.*s, 42\n", (int)ft_strlen(arg_char[i_arg]) - 1, arg_char[i_arg]);dup2(fd_user, 1);}
				close(fd_user);
				close(fd_printf);
				test_checked++;
			}
			else if (ft_testarg(arg_char[i_arg]))
			{
				i_width = -1;
				while (++i_width < 3)
				{
					fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					system(": > output_user.txt");
					dup2(fd_user, 1);
					fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					system(": > output_printf.txt");
					ret_pf = dprintf(fd_printf, arg_char[i_arg], arg_w[i_width], 42);
					ret_ft = ft_printf(arg_char[i_arg], arg_w[i_width], 42);
					close(fd_user);
					fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					close(fd_printf);
					fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
						dup2(fd_stdout, 1);printf("-->\t%.*s, %d, 42 \n", (int)ft_strlen(arg_char[i_arg]) - 1, arg_char[i_arg], arg_w[i_width]);dup2(fd_user, 1);}
					close(fd_user);
					close(fd_printf);
					test_checked++;
				}
			}
		}
	}




	if (all == 1 || ft_strchr(av[1], 's'))
	{
		dup2(fd_stdout, 1);printf("\t\t\nCONVERSION S:\n");dup2(fd_user, 1);
		i_string = -1;
		while (++i_string != 3)
		{
			i_arg = -1;
			while (arg_string[++i_arg])
			{
				if (ft_testarg(arg_string[i_arg]) == -1)
				{
					fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					system(": > output_user.txt");
					dup2(fd_user, 1);
					fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					system(": > output_printf.txt");
					ret_pf = dprintf(fd_printf, arg_string[i_arg], strings[i_string]);
					ret_ft = ft_printf(arg_string[i_arg], strings[i_string]);
					close(fd_user);
					fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					close(fd_printf);
					fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
						dup2(fd_stdout, 1);printf("-->\t%.*s, |%s|\n", (int)ft_strlen(arg_string[i_arg]) - 1, arg_string[i_arg], strings[i_string] ? strings[i_string] : "(null)");dup2(fd_user, 1);}
					close(fd_user);
					close(fd_printf);
					test_checked++;
				}
				else if (!(ft_testarg(arg_string[i_arg])%3) && (ft_testarg(arg_string[i_arg])%4))
				{
					i_width = -1;
					while (++i_width < 3)
					{
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_user.txt");
						dup2(fd_user, 1);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_printf.txt");
						ret_pf = dprintf(fd_printf, arg_string[i_arg], arg_w[i_width], strings[i_string]);
						ret_ft = ft_printf(arg_string[i_arg], arg_w[i_width], strings[i_string]);
						close(fd_user);
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						close(fd_printf);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
							dup2(fd_stdout, 1);printf("-->\t%.*s, %d, |%s|\n", (int)ft_strlen(arg_string[i_arg]) - 1, arg_string[i_arg], arg_w[i_width], strings[i_string]);dup2(fd_user, 1);}
						close(fd_user);
						close(fd_printf);
						test_checked++;
					}
				}
				else if (!(ft_testarg(arg_string[i_arg])%4) && (ft_testarg(arg_string[i_arg])%3))
				{
					i_accu = -1;
					while (++i_accu < 3)
					{
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_user.txt");
						dup2(fd_user, 1);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_printf.txt");
						ret_pf = dprintf(fd_printf, arg_string[i_arg], arg_a[i_accu], strings[i_string]);
						ret_ft = ft_printf(arg_string[i_arg], arg_a[i_accu], strings[i_string]);
						close(fd_user);
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						close(fd_printf);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
							dup2(fd_stdout, 1);printf("-->\t%.*s, %d, |%s|\n", (int)ft_strlen(arg_string[i_arg]) - 1, arg_string[i_arg], arg_a[i_accu], strings[i_string]);dup2(fd_user, 1);}
						close(fd_user);
						close(fd_printf);
						test_checked++;
					}
				}
				else
				{
					i_width = -1;
					while (++i_width < 3)
					{
						i_accu = -1;
						while (++i_accu < 3)
						{
							fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							system(": > output_user.txt");
							dup2(fd_user, 1);
							fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							system(": > output_printf.txt");
							ret_pf = dprintf(fd_printf, arg_string[i_arg], arg_w[i_width], arg_a[i_accu], strings[i_string]);
							ret_ft = ft_printf(arg_string[i_arg], arg_w[i_width], arg_a[i_accu], strings[i_string]);
							close(fd_user);
							fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							close(fd_printf);
							fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
								dup2(fd_stdout, 1);printf("-->\t%.*s, %d, %d, |%s|\n", (int)ft_strlen(arg_string[i_arg]) - 1, arg_string[i_arg], arg_w[i_width], arg_a[i_accu], strings[i_string]);dup2(fd_user, 1);}
							close(fd_user);
							close(fd_printf);
							test_checked++;
						}
					}
				}
			}
		}
	}



	if (all == 1 || ft_strchr(av[1], 'd'))
	{
		dup2(fd_stdout, 1);printf("\t\t\nCONVERSION D:\n");dup2(fd_user, 1);
		i_string = -1;
		while (++i_string != 3)
		{
			i_arg = -1;
			while (arg_int[++i_arg])
			{
				if (ft_testarg(arg_int[i_arg]) == -1)
				{
					fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					system(": > output_user.txt");
					dup2(fd_user, 1);
					fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					system(": > output_printf.txt");
					ret_pf = dprintf(fd_printf, arg_int[i_arg], ints[i_string]);
					ret_ft = ft_printf(arg_int[i_arg], ints[i_string]);
					close(fd_user);
					fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					close(fd_printf);
					fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
						dup2(fd_stdout, 1);printf("-->\t%.*s, |%d|\n", (int)ft_strlen(arg_int[i_arg]) - 1, arg_int[i_arg], ints[i_string]);dup2(fd_user, 1);}
					close(fd_user);
					close(fd_printf);
					test_checked++;
				}
				else if (!(ft_testarg(arg_int[i_arg])%3) && (ft_testarg(arg_int[i_arg])%4))
				{
					i_width = -1;
					while (++i_width < 3)
					{
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_user.txt");
						dup2(fd_user, 1);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_printf.txt");
						ret_pf = dprintf(fd_printf, arg_int[i_arg], arg_w[i_width], ints[i_string]);
						ret_ft = ft_printf(arg_int[i_arg], arg_w[i_width], ints[i_string]);
						close(fd_user);
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						close(fd_printf);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
							dup2(fd_stdout, 1);printf("-->\t%.*s, %d, |%d|\n", (int)ft_strlen(arg_int[i_arg]) - 1, arg_int[i_arg], arg_w[i_width], ints[i_string]);dup2(fd_user, 1);}
						close(fd_user);
						close(fd_printf);
						test_checked++;
					}
				}
				else if (!(ft_testarg(arg_int[i_arg])%4) && (ft_testarg(arg_int[i_arg])%3))
				{
					i_accu = -1;
					while (++i_accu < 3)
					{
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_user.txt");
						dup2(fd_user, 1);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_printf.txt");
						ret_pf = dprintf(fd_printf, arg_int[i_arg], arg_a[i_accu], ints[i_string]);
						ret_ft = ft_printf(arg_int[i_arg], arg_a[i_accu], ints[i_string]);
						close(fd_user);
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						close(fd_printf);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
							dup2(fd_stdout, 1);printf("-->\t%.*s, %d, |%d|\n", (int)ft_strlen(arg_int[i_arg]) - 1, arg_int[i_arg], arg_a[i_accu], ints[i_string]);dup2(fd_user, 1);}
						close(fd_user);
						close(fd_printf);
						test_checked++;
					}
				}
				else
				{
					i_width = -1;
					while (++i_width < 3)
					{
						i_accu = -1;
						while (++i_accu < 3)
						{
							fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							system(": > output_user.txt");
							dup2(fd_user, 1);
							fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							system(": > output_printf.txt");
							ret_pf = dprintf(fd_printf, arg_int[i_arg], arg_w[i_width], arg_a[i_accu], ints[i_string]);
							ret_ft = ft_printf(arg_int[i_arg], arg_w[i_width], arg_a[i_accu], ints[i_string]);
							close(fd_user);
							fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							close(fd_printf);
							fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
								dup2(fd_stdout, 1);printf("-->\t%.*s, %d, %d, |%d|\n", (int)ft_strlen(arg_int[i_arg]) - 1, arg_int[i_arg], arg_w[i_width], arg_a[i_accu], ints[i_string]);dup2(fd_user, 1);}
							close(fd_user);
							close(fd_printf);
							test_checked++;
						}
					}
				}
			}
		}
	}




	if (all == 1 || ft_strchr(av[1], 'i'))
	{
		dup2(fd_stdout, 1);printf("\t\t\nCONVERSION I:\n");dup2(fd_user, 1);
		i_string = -1;
		while (++i_string != 3)
		{
			i_arg = -1;
			while (arg_int2[++i_arg])
			{
				if (ft_testarg(arg_int2[i_arg]) == -1)
				{
					fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					system(": > output_user.txt");
					dup2(fd_user, 1);
					fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					system(": > output_printf.txt");
					ret_pf = dprintf(fd_printf, arg_int2[i_arg], ints[i_string]);
					ret_ft = ft_printf(arg_int2[i_arg], ints[i_string]);
					close(fd_user);
					fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					close(fd_printf);
					fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
						dup2(fd_stdout, 1);printf("-->\t%.*s, |%d|\n", (int)ft_strlen(arg_int2[i_arg]) - 1, arg_int2[i_arg], ints[i_string]);dup2(fd_user, 1);}
					close(fd_user);
					close(fd_printf);
					test_checked++;
				}
				else if (!(ft_testarg(arg_int2[i_arg])%3) && (ft_testarg(arg_int2[i_arg])%4))
				{
					i_width = -1;
					while (++i_width < 3)
					{
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_user.txt");
						dup2(fd_user, 1);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_printf.txt");
						ret_pf = dprintf(fd_printf, arg_int2[i_arg], arg_w[i_width], ints[i_string]);
						ret_ft = ft_printf(arg_int2[i_arg], arg_w[i_width], ints[i_string]);
						close(fd_user);
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						close(fd_printf);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
							dup2(fd_stdout, 1);printf("-->\t%.*s, %d, |%d|\n", (int)ft_strlen(arg_int2[i_arg]) - 1, arg_int2[i_arg], arg_w[i_width], ints[i_string]);dup2(fd_user, 1);}
						close(fd_user);
						close(fd_printf);
						test_checked++;
					}
				}
				else if (!(ft_testarg(arg_int2[i_arg])%4) && (ft_testarg(arg_int2[i_arg])%3))
				{
					i_accu = -1;
					while (++i_accu < 3)
					{
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_user.txt");
						dup2(fd_user, 1);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_printf.txt");
						ret_pf = dprintf(fd_printf, arg_int2[i_arg], arg_a[i_accu], ints[i_string]);
						ret_ft = ft_printf(arg_int2[i_arg], arg_a[i_accu], ints[i_string]);
						close(fd_user);
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						close(fd_printf);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
							dup2(fd_stdout, 1);printf("-->\t%.*s, %d, |%d|\n", (int)ft_strlen(arg_int2[i_arg]) - 1, arg_int2[i_arg], arg_a[i_accu], ints[i_string]);dup2(fd_user, 1);}
						close(fd_user);
						close(fd_printf);
						test_checked++;
					}
				}
				else
				{
					i_width = -1;
					while (++i_width < 3)
					{
						i_accu = -1;
						while (++i_accu < 3)
						{
							fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							system(": > output_user.txt");
							dup2(fd_user, 1);
							fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							system(": > output_printf.txt");
							ret_pf = dprintf(fd_printf, arg_int2[i_arg], arg_w[i_width], arg_a[i_accu], ints[i_string]);
							ret_ft = ft_printf(arg_int2[i_arg], arg_w[i_width], arg_a[i_accu], ints[i_string]);
							close(fd_user);
							fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							close(fd_printf);
							fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, av[2][0] - '0') || ft_strchr("12", av[2][0])){
								dup2(fd_stdout, 1);printf("-->\t%.*s, %d, %d, |%d|\n", (int)ft_strlen(arg_int2[i_arg]) - 1, arg_int2[i_arg], arg_w[i_width], arg_a[i_accu], ints[i_string]);dup2(fd_user, 1);}
							close(fd_user);
							close(fd_printf);
							test_checked++;
						}
					}
				}
			}
		}
	}
}