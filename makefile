CC := vc
ECHO=mecho

SRCS=$(wildcard *.c)
INCS := $(wildcard *.h)
OBJS=$(patsubst %.c,%.o,$(SRCS))
TARGET := memsearch 


# 163: accept l'utilisation de pragmas

CFLAGS := -g -warn=-1 -dontwarn=163 -c99 -+ -O=0 -warnings-as-errors -I/SRCLIB/ez-c -I/SRCLIB/STC-5.0/include -DDEBUG

LFLAGS := -g

# the target build
.PHONY: all
all: $(TARGET)

$(OBJS): $(INCS) /SRCLIB/ez-c/dbg/dbg.h

$(TARGET): $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

.PHONY: clean
clean:
	@-delete *.o
	@-delete $(TARGET)



