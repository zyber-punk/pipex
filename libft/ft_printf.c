/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:03:07 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/04/23 01:15:37 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_numeric_format(t_data *data, char specifier)
{
	t_union_int	int_values;
	void		*ptr;

	int_values.uint64 = 0;
	if (my_strchr("di", specifier))
	{
		int_values.int64 = (long)va_arg(data->ap, int);
		data->format.signed_value = true;
		if (int_values.int64 < 0)
			data->format.is_negative = true;
	}
	else if ('p' == specifier)
	{
		ptr = va_arg(data->ap, void *);
		if (ptr == NULL)
		{
			putstr_buffer("(nil)", 5, data);
			return ;
		}
		int_values.uint64 = (unsigned long)ptr;
	}
	else if (my_strchr("xXub", specifier))
		int_values.uint64 = (unsigned long)va_arg(data->ap, unsigned int);
	print_int(data, int_values);
}

void	render_format(t_data *data)
{
	char		specifier;

	specifier = data->format.specifier;
	if ('%' == specifier)
		print_char(data, '%');
	else if ('c' == specifier)
		print_char(data, va_arg(data->ap, int));
	else if ('s' == specifier)
		print_str(data, va_arg(data->ap, char *));
	else
		handle_numeric_format(data, specifier);
}

static int	init_data(t_data *data, const char *format)
{
	data -> chars_written = 0;
	data -> s = format;
	data -> buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!data -> buffer)
		return (MALLOC_ERROR);
	my_memset(data -> buffer, 0, BUFFER_SIZE * sizeof(char));
	data -> buffer_index = 0;
	return (OK);
}

int	ft_printf(const char *format, ...)
{
	t_data	data;

	va_start(data.ap, format);
	if (init_data(&data, format))
		return (MALLOC_ERROR);
	while (*data.s)
	{
		if (*data.s == '%' && *(++data.s))
		{
			if (parse_format(&data))
			{
				free(data.buffer);
				va_end(data.ap);
				return (PARSE_ERROR);
			}
			render_format(&data);
		}
		else
			write_buffer(&data, *data.s);
		++data.s;
	}
	flush_buffer(&data);
	va_end(data.ap);
	free(data.buffer);
	return (data.chars_written);
}
