include src/libntk/andns/build.mk
include src/libntk/utils/build.mk

LIBNTK_SRCS	= log.c \
			 $(addprefix andns/, $(LIBNTK_ANDNS_SRCS)) \
			 $(addprefix utils/, $(LIBNTK_UTILS_SRCS))
