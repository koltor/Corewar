/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kev.grosjean@gmail.com>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 13:06:27 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 10:42:31 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "op.h"

# define USAGE "Usage: ./asm [-a] <sourcefile.s>\n\t-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output\n"