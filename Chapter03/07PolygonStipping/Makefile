INCFLAGS = -I /opt/homebrew/include

LINKFLAGS  = -framework OpenGL
LINKFLAGS += -framework GLUT

WARNINGS_FLAGS = -Wextra

CFLAGS    = -O2
C         = gcc
SRCS      = main.c
OBJS      = $(SRCS:.c=.o)
PROG      = polygonStippling

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(C) $(CFLAGS) $(OBJS) -o $@ $(INCFLAGS) $(LINKFLAGS)

.c.o:
	$(C) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)

