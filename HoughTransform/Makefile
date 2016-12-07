ARFLAGS=rcs
CFLAGS=-ggdb2

.PHONY: all clean

all: libsweetsleepcontrol.a(state.o sweetsleep.o scheduler.o control.o)
	mv libsweetsleepcontrol.a ./..

clean:
	rm -f ../libsweetsleepcontrol.a
