CFLAGS=-Wall
LIBDIR=../..
LIB=$(LIBDIR)/libsweetsleepcontrol.a
LDFLAGS=-L$(LIBDIR) -lsweetsleepcontrol
SOURCES=TestSweetSleep.c
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
EXECUTABLE=exe

.PHONY: all clean cleanall

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) $(LIB)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

$(LIB):
	$(MAKE) -C ..

clean:
	rm -rf $(OBJECTS)

cleanall: clean
	rm -rf $(EXECUTABLE)
