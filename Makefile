TARGET = screen_patch
OBJS = $(patsubst %.c, %.o, $(wildcard src/*.c))

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

# PRX (Plugin) olarak derle
BUILD_PRX = 1
PRX_EXPORTS = exports.exp

# Kernel (Sistem) yetkilerini ver
USE_KERNEL_LIBC = 1
USE_KERNEL_LIBS = 1

LIBDIR =
LDFLAGS = 
LIBS = -lpspdisplay_driver -lpspctrl_driver -lpsppower

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak
