/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:40:45 by magostin          #+#    #+#             */
/*   Updated: 2020/02/12 05:32:34 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ALLTEST 0

#include "../test1234printf/srcs/ft_printf.h"
#include "gnl/get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

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

	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (i);
		i++;
	}
	return (0);
}

int			ft_checkline(int fd_stdout, int ret_pf, int ret_ft, int toggleok, int (*test)[4])
{
	int		ret_val = 0;
	int		fd_user;
	int		fd_printf;
	int		i;
	char	*line_user = NULL;
	char	*line_printf = NULL;

	dup2(fd_stdout, 1);
	fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	get_next_line(fd_user, &line_user);
	get_next_line(fd_printf, &line_printf);
	(void)ret_ft;
	(void)ret_pf;
	i = ft_comparelines(line_user, line_printf);
	if (i != 0 || ret_pf != ret_ft)
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
		if (toggleok == 2)
			printf("\n|\tft_printf: {%s} returned %d\n|\t   printf: {%s} returned %d\n", line_user, ret_ft - 3, line_printf, ret_pf - 3);
		(*test)[0] = (*test)[0] + 1;
	}
	else
		(*test)[0] = (*test)[0] + 1;
	free(line_printf);
	free(line_user);
	close(fd_user);
	close(fd_printf);
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
	int		ok;
	int		test[4] = {0, 0, 0, 0};
	int		i_arg_1;
	int		i_arg_2;
	int		i_width;
	int		i_accu;
	int		i_string;
	int		fd_user = -42;
	int		fd_printf = -42;
	int		test_checked = 0;
	int		fd_stdout = dup(1);
	char	*arg_1[115] =
	{
		"|%",
		"|%0",
		"|%-",
		"|%-0",
		"|%0-",
		"|%#",
		"|%-#",
		"|%#-",
		"|%#0",
		"|%0#",
		"|%-#0",
		"|%-0#",
		"|%0-#",
		"|%0#-",
		"|%#-0",
		"|%#0-",
		"|% ",
		"|% -",
		"|%- ",
		"|% 0",
		"|%0 ",
		"|% #",
		"|%# ",
		"|% #-",
		"|% -#",
		"|%# -",
		"|%- #",
		"|%#- ",
		"|%-# ",
		"|% 0-",
		"|% -0",
		"|%0 -",
		"|%- 0",
		"|%0- ",
		"|%-0 ",
		"|% #0",
		"|% 0#",
		"|%# 0",
		"|%0 #",
		"|%#0 ",
		"|%0# ",
		"|% -#0",
		"|% -0#",
		"|% 0-#",
		"|% 0#-",
		"|% #-0",
		"|% #0-",
		"|%- #0",
		"|%- 0#",
		"|%0 -#",
		"|%0 #-",
		"|%# -0",
		"|%# 0-",
		"|%-# 0",
		"|%-0 #",
		"|%0- #",
		"|%0# -",
		"|%#- 0",
		"|%#0 -",
		"|%-#0 ",
		"|%-0# ",
		"|%0-# ",
		"|%0#- ",
		"|%#-0 ",
		"|%#0- ",
		"|%+",
		"|%+-",
		"|%-+",
		"|%+0",
		"|%0+",
		"|%+#",
		"|%#+",
		"|%+#-",
		"|%+-#",
		"|%#+-",
		"|%-+#",
		"|%#-+",
		"|%-#+",
		"|%+0-",
		"|%+-0",
		"|%0+-",
		"|%-+0",
		"|%0-+",
		"|%-0+",
		"|%+#0",
		"|%+0#",
		"|%#+0",
		"|%0+#",
		"|%#0+",
		"|%0#+",
		"|%+-#0",
		"|%+-0#",
		"|%+0-#",
		"|%+0#-",
		"|%+#-0",
		"|%+#0-",
		"|%-+#0",
		"|%-+0#",
		"|%0+-#",
		"|%0+#-",
		"|%#+-0",
		"|%#+0-",
		"|%-#+0",
		"|%-0+#",
		"|%0-+#",
		"|%0#+-",
		"|%#-+0",
		"|%#0+-",
		"|%-#0+",
		"|%-0#+",
		"|%0-#+",
		"|%0#-+",
		"|%#-0+",
		"|%#0-+",
		NULL
	};
	char	*arg_2[16] =
	{
		"",
		"15",
		"0",
		"5",
		".",
		".3",
		".20",
		".0",
		"15.6",
		"15.20",
		"15.0",
		"15.",
		"*",
		".*",
		"*.*",
		NULL
	};
	char	*type[13] =
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
		"f|\n",
		"g|\n",
		"e|\n",
		NULL
	};
	char	*strings[3] =
	{
		"Coco Toto",
		"",
		NULL
	};

	double	floats[10] =
	{
		42.4578954,
		-58787.1564897452,
		45648745127,
		1.23456789,
		-1.234567890000048785,
		1.234567890000048785,
		-1.12345678512487951247845148745615,
		9.5,
		42,
		0
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
	int		answer = 0;
	char	*extra_nfge;
	char	*extra_conv;
	int		extra_flags = 0;
	char	*temppp = NULL;
	(void)ac;
	(void)av;

	display_toggle = malloc(sizeof(display_toggle) * 2);
	extra_conv = malloc(sizeof(extra_conv) * (5));
	extra_nfge = malloc(sizeof(extra_nfge) * (5));
	extra_conv[0] = 0;
	extra_nfge[0] = 0;
	display_toggle[1] = '\0';
	display_toggle[0] = '0';
	fd_printf = open("save.bonus", 'r');
	printf(BWHT);
	if (get_next_line(fd_printf, &temppp) == 0)
	{
		printf("\t\t\t__________BONUS PART__________\n");
		printf("\t\t\t| Select conversions:        |\n");
		printf("\t\t\t| 1- Yes                     |\n");
		printf("\t\t\t| 2- No  (No bonus)          |\n");
		printf("\t\t\t\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\n");
		while (answer != 1 && answer != 2)
			scanf(" %d", &answer);
		dprintf(fd_printf, "%d\n", answer);
		if (answer == 1)
		{
			printf("\t\t\t______________________________\n");
			printf("\t\t\t| Type your conversions      |\n");
			printf("\t\t\t| Exemple:                   |\n");
			printf("\t\t\t| nfeg                       |\n");
			printf("\t\t\t| fgduix                     |\n");
			printf("\t\t\t\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\n");
			scanf(" %s", extra_nfge);
			dprintf(fd_printf, "%s\n", extra_nfge);
		}
		else
			dprintf(fd_printf, "\n");
		answer = 0;
		printf("\t\t\t______________________________\n");
		printf("\t\t\t| One of l ll h hh:          |\n");
		printf("\t\t\t| 1- Yes                     |\n");
		printf("\t\t\t| 2- No                      |\n");
		printf("\t\t\t\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\n");
		while (answer != 1 && answer != 2)
			scanf(" %d", &answer);
		dprintf(fd_printf, "%d\n", answer);
		if (answer == 1)
		{
			printf("\t\t\t______________________________\n");
			printf("\t\t\t| Type your extra flags nfge |\n");
			printf("\t\t\t| Replace ll by L            |\n");
			printf("\t\t\t| Exemple:                   |\n");
			printf("\t\t\t| LHlh                       |\n");
			printf("\t\t\t| hL                         |\n");
			printf("\t\t\t\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\n");
			scanf(" %s", extra_conv);
			dprintf(fd_printf, "%s\n", extra_conv);
		}
		else
			dprintf(fd_printf, "\n");
		printf("\t\t\t______________________________\n");
		printf("\t\t\t| Did you do #, , +?         |\n");
		printf("\t\t\t| 1- Yes                     |\n");
		printf("\t\t\t| 2- No                      |\n");
		printf("\t\t\t\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\n");
		while (extra_flags != 1 && extra_flags != 2)
			scanf(" %d", &extra_flags);
		dprintf(fd_printf, "%d\n", extra_flags);
	}
	else
	{
		get_next_line(fd_printf, &extra_nfge);
		get_next_line(fd_printf, &temppp);
		get_next_line(fd_printf, &extra_conv);
		get_next_line(fd_printf, &temppp);
		extra_flags = ft_atoi(temppp);
	}
	close(fd_printf);
























	i_type = 0;
	while ((extra_nfge == NULL && type[i_type]) || (extra_nfge && extra_nfge[i_av]))
	{
		if (extra_nfge)
		{
			i_type = 0;
			while (type[i_type] && type[i_type][0] != extra_nfge[i_av])
				i_type++;
		}
		ok = 1;
		printf("Conversion %c:\n", type[i_type][0]);
		i_string = -1;
		while ((++i_string != 3 && !(main_strchr("feg", type[i_type][0]))) || (i_string != 10 && (main_strchr("feg", type[i_type][0]))))
		{
			i_arg_1 = -1;
			while (arg_1[++i_arg_1] && ((extra_flags == 2 && i_arg_1 < 5) || (extra_flags == 1)))
			{
				while (arg_1[i_arg_1] && !ft_check_flags_arg(arg_1[i_arg_1], type[i_type][0]) && !ALLTEST)
					i_arg_1++;
				if (!arg_1[i_arg_1])
					break;
				i_arg_2 = -1;
				while (arg_2[++i_arg_2])
				{
					while (arg_2[i_arg_2] && !ft_check_flags_arg(arg_2[i_arg_2], type[i_type][0]) && !ALLTEST)
						i_arg_2++;
					if (!arg_2[i_arg_2])
						break;
					full_arg = ft_strjoin(arg_1[i_arg_1], arg_2[i_arg_2]);
					full_arg = ft_strjoin(full_arg, type[i_type]);
					if (ft_testarg(full_arg) == -1)
					{
						fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_printf.txt");
						fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
						system(": > output_user.txt");
						dup2(fd_user, 1);
						if (main_strchr("sp", type[i_type][0]))
						{
							ret_pf = dprintf(fd_printf, full_arg, strings[i_string]);
							ret_ft = ft_printf(full_arg, strings[i_string]);
						}
						else if (main_strchr("dcuixX", type[i_type][0]))
						{
							ret_pf = dprintf(fd_printf, full_arg, ints[i_string]);
							ret_ft = ft_printf(full_arg, ints[i_string]);
						}
						else if (main_strchr("feg", type[i_type][0]))
						{
							ret_pf = dprintf(fd_printf, full_arg, floats[i_string]);
							ret_ft = ft_printf(full_arg, floats[i_string]);
						}
						test[1]++;
						dup2(fd_stdout, 1);
						close(fd_user);
						close(fd_printf);
						if ((ft_checkline(fd_stdout, ret_pf, ret_ft, display_toggle[0] - '0', &test)))
						{
							ok = 0;
							if (main_strchr("sp", type[i_type][0]))
								printf("-->\t\"%.*s\\n\", %s\n", (int)ft_strlen(full_arg) - 1, full_arg, strings[i_string]);
							else if (main_strchr("dcuixX", type[i_type][0]))
								printf("-->\t\"%.*s\\n\", %d\n", (int)ft_strlen(full_arg) - 1, full_arg, ints[i_string]);
							else
								printf("-->\t\"%.*s\\n\", %f\n", (int)ft_strlen(full_arg) - 1, full_arg, floats[i_string]);
							dup2(fd_user, 1);
						}
						test_checked++;
					}
					else if (!(ft_testarg(full_arg)%3) && (ft_testarg(full_arg)%4))
					{
						i_width = -1;
						while (++i_width < 3)
						{
							fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							system(": > output_printf.txt");
							fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							system(": > output_user.txt");
							dup2(fd_user, 1);
							if (main_strchr("sp", type[i_type][0]))
							{
								ret_pf = dprintf(fd_printf, full_arg, arg_w[i_width], strings[i_string]);
								ret_ft = ft_printf(full_arg, arg_w[i_width], strings[i_string]);
							}
							else if (main_strchr("dcuixX", type[i_type][0]))
							{
								ret_pf = dprintf(fd_printf, full_arg, arg_w[i_width], ints[i_string]);
								ret_ft = ft_printf(full_arg, arg_w[i_width], ints[i_string]);
							}
							else if (main_strchr("feg", type[i_type][0]))
							{
								ret_pf = dprintf(fd_printf, full_arg, arg_w[i_width], floats[i_string]);
								ret_ft = ft_printf(full_arg, arg_w[i_width], floats[i_string]);
							}
							test[1]++;
							dup2(fd_stdout, 1);
							close(fd_user);
							close(fd_printf);
							if ((ft_checkline(fd_stdout, ret_pf, ret_ft, display_toggle[0] - '0', &test)))
							{
								ok = 0;
								if (main_strchr("sp", type[i_type][0]))
									printf("-->\t\"%.*s\\n\", %d, %s\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_w[i_width], strings[i_string]);
								else if (main_strchr("dcuixX", type[i_type][0]))
									printf("-->\t\"%.*s\\n\", %d, %d\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_w[i_width], ints[i_string]);
								else
									printf("-->\t\"%.*s\\n\", %d, %f\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_w[i_width], floats[i_string]);
							}
							test_checked++;
						}
					}
					else if (!(ft_testarg(full_arg)%4) && (ft_testarg(full_arg)%3))
					{
						i_accu = -1;
						while (++i_accu < 3)
						{
							fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							system(": > output_printf.txt");
							fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
							system(": > output_user.txt");
							dup2(fd_user, 1);
							if (main_strchr("sp", type[i_type][0]))
							{
								ret_pf = dprintf(fd_printf, full_arg, arg_a[i_accu], strings[i_string]);
								ret_ft = ft_printf(full_arg, arg_a[i_accu], strings[i_string]);
							}
							else if (main_strchr("dcuixX", type[i_type][0]))
							{
								ret_pf = dprintf(fd_printf, full_arg, arg_a[i_accu], ints[i_string]);
								ret_ft = ft_printf(full_arg, arg_a[i_accu], ints[i_string]);
							}
							else if (main_strchr("feg", type[i_type][0]))
							{
								ret_pf = dprintf(fd_printf, full_arg, arg_a[i_accu], floats[i_string]);
								ret_ft = ft_printf(full_arg, arg_a[i_accu], floats[i_string]);
							}
							test[1]++;
							close(fd_user);
							close(fd_printf);
							dup2(fd_stdout, 1);
							if ((ft_checkline(fd_stdout, ret_pf, ret_ft, display_toggle[0] - '0', &test)))
							{
								ok = 0;
								if (main_strchr("sp", type[i_type][0]))
									printf("-->\t\"%.*s\\n\", %d, %s\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_a[i_accu], strings[i_string]);
								else if (main_strchr("dcuixX", type[i_type][0]))
									printf("-->\t\"%.*s\\n\", %d, %d\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_a[i_accu], ints[i_string]);
								else
									printf("-->\t\"%.*s\\n\", %d, %f\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_a[i_accu], floats[i_string]);
							}
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
								fd_printf = open("output_printf.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
								system(": > output_printf.txt");
								fd_user = open("output_user.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
								system(": > output_user.txt");
								dup2(fd_user, 1);
								if (main_strchr("sp", type[i_type][0]))
								{
									ret_pf = dprintf(fd_printf, full_arg, arg_w[i_width], arg_a[i_accu], strings[i_string]);
									ret_ft = ft_printf(full_arg, arg_w[i_width], arg_a[i_accu], strings[i_string]);
								}
								else if (main_strchr("dcuixX%", type[i_type][0]))
								{
									ret_pf = dprintf(fd_printf, full_arg, arg_w[i_width], arg_a[i_accu], ints[i_string]);
									ret_ft = ft_printf(full_arg, arg_w[i_width], arg_a[i_accu], ints[i_string]);
								}
								else if (main_strchr("feg", type[i_type][0]))
								{
									ret_pf = dprintf(fd_printf, full_arg, arg_w[i_width], arg_a[i_accu], floats[i_string]);
									ret_ft = ft_printf(full_arg, arg_w[i_width], arg_a[i_accu], floats[i_string]);
								}
								test[1]++;
								close(fd_user);
								close(fd_printf);
								dup2(fd_stdout, 1);
								if ((ft_checkline(fd_stdout, ret_pf, ret_ft, display_toggle[0] - '0', &test)))
								{
									ok = 0;
									if (main_strchr("sp", type[i_type][0]))
										printf("-->\t\"%.*s\\n\", %d, %d, %s\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_w[i_width], arg_a[i_accu], strings[i_string]);
									else if (main_strchr("dcuixX", type[i_type][0]))
										printf("-->\t\"%.*s\\n\", %d, %d, %d\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_w[i_width], arg_a[i_accu], ints[i_string]);
									else
										printf("-->\t\"%.*s\\n\", %d, %d, %f\n", (int)ft_strlen(full_arg) - 1, full_arg, arg_w[i_width], arg_a[i_accu], floats[i_string]);
								}
								test_checked++;
							}
						}
					}
					free(full_arg);
				}
			}
		}
		if (test[0] == test[1])
		{
			dup2(fd_stdout, 1);
			printf( BGRN "\t\t%d/%d\t  test passed\n" BWHT, test[0], test[1]);
			dup2(fd_user, 1);
		}
		else
		{
			dup2(fd_stdout, 1);
			printf( BRED "\t\t%d/%d\t  test passed\n" BWHT, test[0], test[1]);
			dup2(fd_user, 1);
		}
		test[2] += test[0];
		test[3] += test[1];
		test[0] = 0;
		test[1] = 0;
		i_type++;
		i_av++;
	}
	dup2(fd_stdout, 1);
	printf("\nFinal score:");
	if (test[2] == test[3])
	{
		printf( BGRN "\t\t%d/%d test passed" BWHT, test[2], test[3]);
		printf("\nSuccess to all test doesn't mean your printf is good\n");
	}
	else
		printf( BRED "\t\t%d/%d test passed" BWHT, test[2], test[3]);
}