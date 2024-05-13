/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enumeration.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhseo <wonhseo@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 04:57:21 by wonhseo           #+#    #+#             */
/*   Updated: 2024/05/14 06:42:38 by wonhseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMERATION_H
# define ENUMERATION_H

typedef enum e_exit
{
	VALID = 0,
	GENERAL = 1,
	BUILTIN = 1,
	NOTEXECUTABLE = 126,
	NOTFOUND = 127,
	SIGOFFSET = 128,
	RANGE = 255,
}	t_exit;
typedef enum e_color
{
	RED,
	BLACK,
}	t_color;
typedef enum e_type
{
	SCLN = -1,
	PIPE,
	RDR,
	CMD,
}	t_type;
typedef enum e_ict
{
	INDEX,
	CONTENT,
	TYPE,
}	t_ict;
typedef enum e_quote
{
	OFF,
	SINGLE,
	DOUBLE,
}	t_quote;
typedef enum e_inout
{
	IN,
	OUT
}	t_inout;
#endif
