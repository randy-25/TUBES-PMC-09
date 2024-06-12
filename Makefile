# Compiler
CC := gcc

# Directories
DEPSDIR := C:/msys64/mingw64
INCDIR := header
SRCDIR := src
OBJDIR := obj

# Flags
CFLAGS := -I$(DEPSDIR) \
	-I$(DEPSDIR)/include/gtk-4.0 \
    -I$(DEPSDIR)/include/pango-1.0 \
    -I$(DEPSDIR)/include \
    -I$(DEPSDIR)/include/glib-2.0 \
    -I$(DEPSDIR)/lib/glib-2.0/include \
    -I$(DEPSDIR)/include/harfbuzz \
    -I$(DEPSDIR)/include/freetype2 \
    -I$(DEPSDIR)/include/libpng16 \
    -I$(DEPSDIR)/include/fribidi \
    -I$(DEPSDIR)/include/cairo \
    -I$(DEPSDIR)/include/pixman-1 \
    -I$(DEPSDIR)/include/gdk-pixbuf-2.0 \
    -I$(DEPSDIR)/include/webp \
    -I$(DEPSDIR)/include/graphene-1.0 \
    -I$(DEPSDIR)/lib/graphene-1.0/include \
    -mfpmath=sse \
    -msse \
    -msse2

LDFLAGS := -lxlsxio_read -lxlsxio_write \
	-lgtk-4 \
    -lpangowin32-1.0 \
    -lpangocairo-1.0 \
    -lpango-1.0 \
    -lharfbuzz \
    -lgdk_pixbuf-2.0 \
    -lcairo-gobject \
    -lcairo \
    -lgraphene-1.0 \
    -lgio-2.0 \
    -lgobject-2.0 \
    -lglib-2.0 \
    -lintl

# Source files
SRCS := $(wildcard $(SRCDIR)/*.c) main.c
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Output file
output: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o main

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) main

