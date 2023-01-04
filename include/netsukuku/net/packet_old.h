/* This file is part of Netsukuku
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

#ifndef NETSUKUKU_PACKET_H
# define NETSUKUKU_PACKET_H 1

# include <stdint.h>

# define PACKET_ID "ntk"

/* flags */
# define SEND_ACK		1
# define BCAST_PKT		(1<<1)	/* In this pkt there is encapsulated a 
								 * broadcast/flood pkt. Woa */
# define HOOK_PKT		(1<<2)	/* All the pkts sent while hooking have
								 * this flag set      */
# define ASYNC_REPLY		(1<<3)	/* Tells the receiver to reply with a new 
								   connection. The reply pkt will be
								   handled by the pkt_queue. */
# define ASYNC_REPLIED		(1<<4)
# define LOOPBACK_PKT		(1<<5)	/* This is a packet destinated to me */
# define RESTRICTED_PKT		(1<<6)	/* Packet sent from a node in restricted 
									   mode */
# define COMPRESSED_PKT		(1<<7)	/* The whole packet is Z compressed */

/**
 * In this enum there are all the requests/replies op used by netsukuku
 */
enum packet_op
{
	OP_ECHO_ME, /**< The Node requests to be echoed by the destination Node */
	OP_ECHO_REPLY, /**< Yep, this isn't really a reply */
	OP_GET_FREE_NODES, /**< it means: <<Get the list of free ips in your gnode, plz>> */
	OP_GET_QSPN_ROUND, /**< <<Yo, Gimme the qspn ids and qspn times>> */

	OP_GET_INTERNET_GWS, /**< Get Internet Gateways */
	OP_SET_FOREIGN_ROUTE, /**< Set the route in the foreign Group Node */
	OP_DEL_FOREIGN_ROUTE,
	OP_NEW_BACKROUTE, /**< Tells the destination Node to use a different route to reply */
	OP_DELAYED_BROADCAST, /**< Broadcast packet to be spread only in the destination Group Node */
	OP_SPLIT_ROUTE, /**< This packet advices the source Node to split the socket in two routes */
	OP_SET_NO_IDENTY, /**< Packet that specify to the last Node in the route to change
						the source Ip of the future incoming packets */
	
	OP_QSPN_CLOSE, /**< The QSPN Packet used to trace the entire Group Node */
	OP_QSPN_OPEN, /**< The QSPN Packet sent by the extreme nodes */
	OP_QSPN_RFR, /**< RequestForRoute: This is used to get additional routes */
	OP_GET_DNODEBLOCK, /* Not used. */
	OP_GET_DNODEIP, /* Not used. */
	OP_TRACER_PACKET, /**< A tracer packet. This packet is used mainly to send a
						tracer packet. Normally a broadcast packet is marked with
						the BCAST_TRACER_PKT flag. */
	OP_TRACER_PACKET_CONNECT, /**< This is the tracer packet used to connect the
								to the destination Node.
								In the first entry of the tracer packet there's
								the source Node, in the second the destination
								Node, the remaining are as usual */

	OP_DEL_SNODE, /* Not used. */
	OP_DEL_GNODE, /* Not used. */

	OP_GET_INT_MAP,
	OP_GET_EXT_MAP,
	OP_GET_BNODE_MAP
};

/**
 * Packet Header
 */


/**
 * Broadcast packet
 */
struct packet_broadcast
{
	uint8_t g_node; /**< The G-Node the packet is restricted to */
	uint8_t level;  /**< The level of the G-Node */
	uint8_t gnode_ttl; /**< G-Node TTL: How many G-Nodes the packet
							can traverse */
	uint8_t sub_id; /**< The Node who sent the Packet
							(only used by the QSPN Open) */
	uint32_t size; /**< sizeof(the packet) */
	uint8_t flags; /**< Various flags */
} __attribute__((packed));
typedef struct packet_broadcast PacketBroadcast;

#endif /* !NETSUKUKU_PACKET_H */
