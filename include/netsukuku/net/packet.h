/* This file is part of Netsukuku
 * Copyright (c) 2023 d0p1
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

/**
 * @file "netstukuku/net/packet.h"
 * 
 */
#ifndef NETSUKUKU_NET_PACKET_H
# define NETSUKUKU_NET_PACKET_H 1

# include <stdint.h>

# define PACKET_MAGIC 0x6e746b31

/**
 * Packet Header
 */
typedef struct {
	uint8_t magic[4]; /**< "ntk1" */
	uint32_t id;
	uint8_t flags;
	uint8_t op;
	uint16_t chksum; /**< Checksum */
	uint32_t size;  /**< Size of the whole packet */
} __attribute__((packed)) PacketHeader;

typedef enum {
	PACKET_COMPRESSED,
} PacketFlags;

typedef enum {
	E_NONE,
} PacketOp;

typedef struct {
	uint8_t g_node;
	uint8_t level;
	uint8_t g_ttl;
	uint8_t pad;
} __attribute__((packed)) BroadcastHeader;

typedef struct {
	uint8_t flags;
} TracerHeader;

#endif /* !NETSUKUKU_NET_PACKET_H */
