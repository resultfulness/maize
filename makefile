PROJECT = maize

CC     = cc
CFLAGS = -std=c99 -pedantic -Wall
LDLIBS = -lSDL2 -lSDL2_image
SRCDIR   = ./src
BUILDDIR = ./build

OBJECTS = $(patsubst %.c,%.o,$(wildcard $(SRCDIR)/*.c))

all: $(PROJECT)

$(PROJECT): dir $(OBJECTS)
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $(patsubst %,build/%,$(OBJECTS))

$(OBJECTS): dir
	@mkdir -p $(BUILDDIR)/$(@D)
	@$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ -c $*.c

dir:
	@mkdir -p $(BUILDDIR)

clean:
	@rm -rf $(BUILDDIR) $(PROJECT)

.PHONY: all clean dir
