TARGET = colorspace
OBJS = main.o

BUILD_PRX = 1
# İşte sihirli satırlar! Bunlar sisteme Kernel yetkisiyle derleme yapmasını söyler:
USE_KERNEL_LIBC = 1
USE_KERNEL_LIBS = 1

# Kernel donanım sürücülerini çağırıyoruz
LIBS = -lpspdisplay_driver -lpspctrl_driver

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak

