TARGET = contrast
OBJS = main.o
BUILD_PRX = 1
LIBS = -lpspdisplay -lpspctrl -lpspsdk
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak
