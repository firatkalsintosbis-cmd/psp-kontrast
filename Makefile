TARGET = minicraft_pe
OBJS = main.o

BUILD_PRX = 1
# Oyun olduğu için kullanıcı modunda kalmamız daha stabil olur
PSP_FW_VERSION = 500 

LIBS = -lpspgum -lpspgu -lpng -lz -lm

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak

