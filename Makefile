CC = g++
CFLAGS = 
PROG = Kamera

INCLUDES = include
SOURCES = source

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))

OBJS = $(addprefix $(SOURCES)/, $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(sFILES:.s=.o) $(SFILES:.S=.o))

SOURCE_FILES = $(addprefix $(SOURCES)/, $(CPPFILES) $(CFILES) $(sFILES) $(SFILES))

LIBS = -lsfml-graphics -lsfml-window -lGL

all: $(PROG)

$(PROG): $(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SOURCE_FILES) -I$(INCLUDES) $(LIBS)

clean:
	rm -f $(PROG)
