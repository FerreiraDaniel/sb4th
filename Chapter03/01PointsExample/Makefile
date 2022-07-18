INCFLAGS = -I /usr/local/include/vecmath -I /opt/homebrew/include

LINKFLAGS  = -framework OpenGL
LINKFLAGS += -framework GLUT
LINKFLAGS += -L /usr/local/lib -lvecmath

WARNINGS_FLAGS = -Wextra

CFLAGS    = -O2
C        = gcc
SRCS      = main.c
OBJS      = $(SRCS:.c=.o)
PROG      = pointsExample

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(C) $(CFLAGS) $(OBJS) -o $@ $(INCFLAGS) $(LINKFLAGS)

.c.o:
	$(C) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)

