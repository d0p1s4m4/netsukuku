/* This file is part of Netsukuku*
 * (c) Copyright 2004 Andrea Lo Pumo aka AlpT <alpt@freaknet.org>
 * Copyright (c) 2022 d0p1
 *
 * This source code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * Please refer to the GNU Public License for more details.
 *
 * You should have received a copy of the GNU Public License along with
 * this source code; if not, write to:
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef NTKD_OPT_H
# define NTKD_OPT_H 1

# include <stdint.h>
# include "../config.h"

# define OPT_DEFAULT_CONFIG_FILE CONF_DIR "/netsukuku.conf"
# define OPT_DEFAULT_PID_FILE    PID_DIR "/ntkd.pid"

typedef struct
{
    char *config_file;
    char *pid_file;

    int log_level;

    int8_t daemonize;
} Opt;

void opt_fill_default(Opt *opt);
void opt_parse(Opt *opt, int argc, char *const *argv);

#endif /* !NTKD_OPT_H */
