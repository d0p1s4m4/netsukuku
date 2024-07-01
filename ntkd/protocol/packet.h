#ifndef NETSUKUKU_PROTOCOL_HEADER_H
# define NETSUKUKU_PROTOCOL_HEADER_H

# include <stdint.h>

# define PACKET_MAGIC0 'N'
# define PACKET_MAGIC1 'T'
# define PACKET_MAGIC2 'K'
# define PACKET_MAGIC3 '2'

enum packet_type {
	PKT_ECHO_ME,
	PKT_ECHO_REPLY,
};

struct packet_header {
	uint8_t magic[4];
	uint16_t size;
	uint8_t packet_type;
};

#endif