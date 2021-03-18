/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:40:45 by magostin          #+#    #+#             */
/*   Updated: 2021/03/18 13:34:12 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ALLTEST 0

#include "ft_printf.h"
#include "gnl/get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

static char	*main_strchr(const char *s, int c);
int			ft_checkline(int fd_user, int fd_printf, int fd_stdout, int ret_pf, int ret_ft, int toggleok, int (*test)[4]);

void		ft_open_user(int *fd_user, int *fd_printf, int clear)
{
	*fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	*fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (clear)
	{
		system(": > output_user.txt");
		system(": > output_printf.txt");
	}
}

void		ft_close_user(int *fd_user, int *fd_printf)
{
	close(*fd_user);
	*fd_user = 0;
	close(*fd_printf);
	*fd_printf = 0;
}

void		ft_multitest(int (*test)[4], int fd_stdout, int display_toggle)
{
	int			fd_user;
	int			fd_printf;
	int			ret_ft;
	int			ret_pf;
	int			ret_val;
	char		*full_arg;

	printf("Multi-conv: ");
	ft_open_user(&fd_user, &fd_printf, 1);
	full_arg = "[%*d] [%*s] [%*x] [%*X] [%*i] [%*u]\n";
	dup2(fd_user, 1);
	ret_ft = ft_printf(full_arg, 1, 5000, 1, "hey", 10, 54700, 1, 300, 10, -55, 1, -60);
	ret_pf = dprintf(fd_printf, full_arg, 1, 5000, 1, "hey", 10, 54700, 1, 300, 10, -55, 1, -60);
	dup2(fd_stdout, 1);
	ft_close_user(&fd_user, &fd_printf);
	ft_open_user(&fd_user, &fd_printf, 0);
	if ((ret_val = ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, display_toggle, test)) || main_strchr("12", display_toggle + '0'))
		printf("-->\t\"%.*s\\n\", 1, 5000, 1, \"hey\", 10, 54700, 1, 300, 10, -55, 1, -60\n", (int)ft_strlen(full_arg) - 1, full_arg);
	
	ft_open_user(&fd_user, &fd_printf, 1);
	full_arg = "[%*.*d] [%*.*s] [%*.*x] [%*.*X] [%*.*i] [%*.*u]\n";
	dup2(fd_user, 1);
	ret_ft = ft_printf(full_arg, 0, 0, 42, 0, 0, "42", 0, 0, 42, 0, 0, 42, 0, 0, 42, 0, 0, 42);
	ret_pf = dprintf(fd_printf, full_arg, 0, 0, 42, 0, 0, "42", 0, 0, 42, 0, 0, 42, 0, 0, 42, 0, 0, 42);
	dup2(fd_stdout, 1);
	ft_close_user(&fd_user, &fd_printf);
	ft_open_user(&fd_user, &fd_printf, 0);
	if ((ret_val = ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, display_toggle, test)) || main_strchr("12", display_toggle + '0'))
		printf("-->\t\"%.*s\\n\", 0, 0, 42, 0, 0, \"42\", 0, 0, 42, 0, 0, 42, 0, 0, 42, 0, 0, 42\n", (int)ft_strlen(full_arg) - 1, full_arg);

	dup2(fd_stdout, 1);
	if ((*test)[0] == (*test)[1])
		printf(BGRN);
	else
		printf(BRED);
	printf("\t%d/%d\t  test passed\n" BWHT, (*test)[0], (*test)[1]);
	(*test)[2] += (*test)[0];
	(*test)[3] += (*test)[1];
}

static char	*main_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return ((char *)(&s[i]));
	return (0);
}

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

int			ft_checkline(int fd_user, int fd_printf, int fd_stdout, int ret_pf, int ret_ft, int toggleok, int (*test)[4])
{
	int		ret_val = 0;
	char	*line_user = NULL;
	char	*line_printf = NULL;

	dup2(fd_stdout, 1);
	get_next_line(fd_user, &line_user);
	get_next_line(fd_printf, &line_printf);
	if (!(ft_comparelines(line_user, line_printf) && ret_pf == ret_ft))
	{
		printf("\033[0;31m\nDIFF!\033[0m\n");
		printf("|\tft_printf: {%s} returned %d\n|\t   printf: {%s} returned %d\n", line_user, ret_ft - 3, line_printf, ret_pf - 3);
		ret_val = 1;
	}
	else if (toggleok != 0)
	{
		printf("\033[0;32mOK  \033[0m");
		if (toggleok == 2)
			printf("\n|\tft_printf: {%s} returned %d\n|\t   printf: {%s} returned %d\n", line_user, ret_ft - 3, line_printf, ret_pf - 3);
		(*test)[0] = (*test)[0] + 1;
	}
	else
		(*test)[0] = (*test)[0] + 1;
	(*test)[1] = (*test)[1] + 1;
	free(line_printf);
	free(line_user);
	return (ret_val);
}

int		ft_checkarg(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (main_strchr("scduixXp%", *str))
			return (0);
		str++;
	}
	return (1);
}
int			ft_check_flags_arg(char *str, char c)
{
	if (c == 'c' || c == 'p')
	{
		if (main_strchr(str, '0') || main_strchr(str, '.') || main_strchr(str, '+') || main_strchr(str, '#') || main_strchr(str, ' '))
			return (0);
	}
	else if (c == 's')
	{
		if (main_strchr(str, '0') || main_strchr(str, '+') || main_strchr(str, '#') || main_strchr(str, ' '))
			return (0);
	}
	else if (c == 'd' || c == 'i')
	{
		if (main_strchr(str, '#'))
			return (0);
	}
	else if (c == 'x' || c == 'X' || c == 'u')
	{
		if (main_strchr(str, '0') || main_strchr(str, '#'))
			return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	int		ret_pf = 0;
	int		ret_ft = 0;
	int		test[4] = {0, 0, 0, 0};
	int		i_arg;
	int		i_width;
	int		i_accu;
	int		i_string;
	int		fd_user;
	int		fd_printf;
	int		test_checked = 0;
	int		fd_stdout = dup(1);
	char	*arg[32] =
	{
		"|%",
		"|%15",
		"|%-15",
		"|%0",
		"|%-----5",
		"|%015",
		"|%-015",
		"|%0-15",
		"|%.",
		"|%.3",
		"|%.20",
		"|%.0",
		"|%15.6",
		"|%15.20",
		"|%15.0",
		"|%15.",
		"|%*",
		"|%-*",
		"|%0*",
		"|%0-*",
		"|%-0*",
		"|%.*",
		"|%-.*",
		"|%0.*",
		"|%0-.*",
		"|%-0.*",
		"|%*.*",
		"|%0*.*",
		"|%-*.*",
		"|%0-*.*",
		"|%-0*.*",
		NULL
	};
	char	*type[10] =
	{
		"c|\n",
		"s|\n",
		"d|\n",
		"i|\n",
		"u|\n",
		"x|\n",
		"X|\n",
		"p|\n",
		"%|\n",
		NULL
	};
	char	*strings[3] =
	{
		"Coco Toto",
		"",
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

	char	*full_arg;
	char	*display_toggle;
	int		i_type = 0;
	int		i_av = 0;
	int		i_detect = 0;

	display_toggle = malloc(sizeof(display_toggle) * 2);
	display_toggle[0] = '0';
	display_toggle[1] = '\0';
	printf(BWHT);
	if (ALLTEST)
		printf("\033[0;35m#define \033[0;34mALLTEST \033[0;32m1\033[1;37m\n\nALLTEST set to 1:\nTesting many undefined behavior\n\n");
	else
		printf("\033[0;35m#define \033[0;34mALLTEST \033[0;32m0\033[1;37m\n\nALLTEST set to 0:\nTesting only defined behavior\n\n");
	
	if (ac > 3)
	{
		printf("Error arg. Use only following types:\n(csduixXp%%)\t\t(Multiple choices)\n");
		printf("or only following flags:\n(012)\t\t\t(Only one)\n");
		printf("\nWorking Exemples:\n");
		printf("./Moumounator_printf.sh <path>\n");
		printf("./Moumounator_printf.sh <path> X\n");
		printf("./Moumounator_printf.sh <path> c 1\n");
		printf("./Moumounator_printf.sh <path> 0\n");
		printf("./Moumounator_printf.sh <path> 2 cdui\n\n");
		return (0);
	}
	else if (ac == 2)
	{
		if (ft_checkarg(av[1]))
		{
			if (!main_strchr("012", av[1][0]) || av[1][1] != 0)
			{
				printf("Error arg. Use only following types:\n(csduixXp%%)\t\t(Multiple choices)\n");
				printf("or only following flags:\n(012)\t\t\t(Only one)\n");
				printf("\nWorking Exemples:\n");
				printf("./Moumounator_printf.sh <path>\n");
				printf("./Moumounator_printf.sh <path> X\n");
				printf("./Moumounator_printf.sh <path> c 1\n");
				printf("./Moumounator_printf.sh <path> 0\n");
				printf("./Moumounator_printf.sh <path> 2 cdui\n\n");
				return (0);
			}
			display_toggle[0] = av[1][0];
		}
		else
		{
			i_detect = 1;
			display_toggle[0] = '0';
		}
	}
	else if (ac == 3)
	{
		if (ft_checkarg(av[1]))
		{
			if (!main_strchr("012", av[1][0]) || av[1][1] != 0)
			{
				printf("Error arg. Use only following types:\n(csduixXp%%)\t\t(Multiple choices)\n");
				printf("or only following flags:\n(012)\t\t\t(Only one)\n");
				printf("\nExemple:\n");
				printf("./Moumounator_printf.sh <path>\n");
				printf("./Moumounator_printf.sh <path> X\n");
				printf("./Moumounator_printf.sh <path> c 1\n");
				printf("./Moumounator_printf.sh <path> 0\n");
				printf("./Moumounator_printf.sh <path> 2 cdui\n\n");
				return (0);
			}
			display_toggle[0] = av[1][0];
		}
		else if (!ft_checkarg(av[1]))
		{
			i_detect = 1;
			display_toggle[0] = '0';
		}
		if (ft_checkarg(av[2]))
		{
			if (!main_strchr("012", av[2][0]) || av[2][1] != 0)
			{
				printf("Error arg. Use only following types:\n(csduixXp%%)\t\t(Multiple choices)\n");
				printf("or only following flags:\n(012)\t\t\t(Only one)\n");
				printf("\nExemple:\n");
				printf("./Moumounator_printf.sh <path>\n");
				printf("./Moumounator_printf.sh <path> X\n");
				printf("./Moumounator_printf.sh <path> c 1\n");
				printf("./Moumounator_printf.sh <path> 0\n");
				printf("./Moumounator_printf.sh <path> 2 cdui\n\n");
				return (0);
			}
			display_toggle[0] = av[2][0];
		}
		else if (!ft_checkarg(av[2]))
		{
			i_detect = 2;
			display_toggle[0] = '0';
		}
	}
	while ((i_detect == 0 && type[i_type]) || (i_detect >= 1 && av[i_detect][i_av]))
	{
		if (i_detect >= 1)
		{
			i_type = 0;
			while (type[i_type] && type[i_type][0] != av[i_detect][i_av])
				i_type++;
		}
		dup2(fd_stdout, 1);
		printf("Conversion %c:", type[i_type][0]);
		dup2(fd_user, 1);
		i_string = -1;
		while (++i_string != 3)
		{
			i_arg = -1;
			while (arg[++i_arg])
			{
				while (arg[i_arg] && !ft_check_flags_arg(arg[i_arg], type[i_type][0]) && !ALLTEST)
					i_arg++;
				if (!arg[i_arg])
					break;
				full_arg = ft_strjoin(arg[i_arg], type[i_type]);
				if (ft_testarg(full_arg) == -1)
				{
					fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					system(": > output_user.txt");
					dup2(fd_user, 1);
					fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					system(": > output_printf.txt");
					if (!main_strchr("dcuixX", type[i_type][0]))
					{
						ret_pf = dprintf(fd_printf, full_arg, strings[i_string]);
						ret_ft = ft_printf(full_arg, strings[i_string]);
					}
					else
					{
						ret_pf = dprintf(fd_printf, full_arg, ints[i_string]);
						ret_ft = ft_printf(full_arg, ints[i_string]);
					}
					close(fd_user);
					fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					close(fd_printf);
					fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
					if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, display_toggle[0] - '0', &test) || main_strchr("12", display_toggle[0]))
					{
						!main_strchr("dcuixX", type[i_type][0]) ?
						printf("-->\t\"%.*s\\n\", %s\n", (int)ft_strlen(full_arg) - 1, full_arg, strings[i_string]):
						printf("-->\t\"%.*s\\n\", %d\n", (int)ft_strlen(full_arg) - 1, full_arg, ints[i_string])
						;
						dup2(fd_user, 1);
					}
					close(fd_user);
					close(fd_printf);
					test_checked++;
				}
				else if (!(ft_testarg(full_arg)%3) && (ft_testarg(full_arg)%4))
				{
					i_width = -1;
					while (++i_width < 3)
					{
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_user.txt");
						dup2(fd_user, 1);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_printf.txt");
						if (!main_strchr("dcuixX", type[i_type][0]))
						{
							ret_pf = dprintf(fd_printf, full_arg, arg_w[i_width], strings[i_string]);
							ret_ft = ft_printf(full_arg, arg_w[i_width], strings[i_string]);
						}
						else
						{
							ret_pf = dprintf(fd_printf, full_arg, arg_w[i_width], ints[i_string]);
							ret_ft = ft_printf(full_arg, arg_w[i_width], ints[i_string]);
						}
						close(fd_user);
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						close(fd_printf);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, display_toggle[0] - '0', &test) || main_strchr("12", display_toggle[0]))
						{
							dup2(fd_stdout, 1);
							!main_strchr("dcuixX", type[i_type][0]) ?
							printf("-->\t\"%.*s\\n\", %d, %s\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_w[i_width], strings[i_string]):
							printf("-->\t\"%.*s\\n\", %d, %d\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_w[i_width], ints[i_string]);
							dup2(fd_user, 1);
						}
						close(fd_user);
						close(fd_printf);
						test_checked++;
					}
				}
				else if (!(ft_testarg(full_arg)%4) && (ft_testarg(full_arg)%3))
				{
					i_accu = -1;
					while (++i_accu < 3)
					{
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_user.txt");
						dup2(fd_user, 1);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_printf.txt");
						if (!main_strchr("dcuixX", type[i_type][0]))
						{
							ret_pf = dprintf(fd_printf, full_arg, arg_a[i_accu], strings[i_string]);
							ret_ft = ft_printf(full_arg, arg_a[i_accu], strings[i_string]);
						}
						else
						{
							ret_pf = dprintf(fd_printf, full_arg, arg_a[i_accu], ints[i_string]);
							ret_ft = ft_printf(full_arg, arg_a[i_accu], ints[i_string]);
						}
						close(fd_user);
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						close(fd_printf);
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, display_toggle[0] - '0', &test) || main_strchr("12", display_toggle[0]))
						{
							dup2(fd_stdout, 1);
							!main_strchr("dcuixX", type[i_type][0]) ?
							printf("-->\t\"%.*s\\n\", %d, %s\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_a[i_accu], strings[i_string]):
							printf("-->\t\"%.*s\\n\", %d, %d\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_a[i_accu], ints[i_string]);
							dup2(fd_user, 1);
						}
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
							if (!main_strchr("dcuixX", type[i_type][0]))
							{
								ret_pf = dprintf(fd_printf, full_arg, arg_w[i_width], arg_a[i_accu], strings[i_string]);
								ret_ft = ft_printf(full_arg, arg_w[i_width], arg_a[i_accu], strings[i_string]);
							}
							else
							{
								ret_pf = dprintf(fd_printf, full_arg, arg_w[i_width], arg_a[i_accu], ints[i_string]);
								ret_ft = ft_printf(full_arg, arg_w[i_width], arg_a[i_accu], ints[i_string]);
							}
							close(fd_user);
							fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							close(fd_printf);
							fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							if (ft_checkline(fd_user, fd_printf, fd_stdout, ret_pf, ret_ft, display_toggle[0] - '0', &test) || main_strchr("12", display_toggle[0]))
							{
								dup2(fd_stdout, 1);
								!main_strchr("dcuixX", type[i_type][0]) ?
								printf("-->\t\"%.*s\\n\", %d, %d, %s\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_w[i_width], arg_a[i_accu], strings[i_string]):
								printf("-->\t\"%.*s\\n\", %d, %d, %d\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_w[i_width], arg_a[i_accu], ints[i_string]);
								dup2(fd_user, 1);
							}
							close(fd_user);
							close(fd_printf);
							test_checked++;
						}
					}
				}
				free(full_arg);
			}
		}
		if (test[0] == test[1])
		{
			dup2(fd_stdout, 1);
			printf( BGRN "\t%d/%d\t  test passed\n" BWHT, test[0], test[1]);
			dup2(fd_user, 1);
		}
		else
		{
			dup2(fd_stdout, 1);
			printf( BRED "\t%d/%d\t  test passed\n" BWHT, test[0], test[1]);
			dup2(fd_user, 1);
		}
		test[2] += test[0];
		test[3] += test[1];
		test[0] = 0;
		test[1] = 0;
		i_type++;
		i_av++;
		printf(BWHT);
	}
	dup2(fd_stdout, 1);
	ft_multitest(&test, fd_stdout, display_toggle[0] - '0');
	printf("\nFinal score:");
	if (test[2] == test[3])
	{
		printf( BGRN "\t%d/%d test passed" BWHT, test[2], test[3]);
		printf("\nSuccess to all test doesn't mean your printf is good.\n(Check your leaks!)\n");
	}
	else
		printf( BRED "\t%d/%d test passed\n" BWHT, test[2], test[3]);
	dup2(fd_user, 1);
}