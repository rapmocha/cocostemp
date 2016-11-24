COMPILER  = g++
CFLAGS    = -g -MMD -MP -Wall -Wextra -Winit-self \
					 	-Wno-missing-field-initializers -std=c++11

FRAMEWORKS = -framework OpenGL \
						 -framework AppKit \
						 -framework Foundation \
						 -framework IOKit \
						 -framework Security \
						 -framework OpenAL \
						 -framework AVFoundation \
						 -framework QuartzCore \
						 -framework AudioToolbox

ifeq "$(shell getconf LONG_BIT)" "64"
	LDFLAGS = `pkg-config --libs opencv` \
					 	-lboost_filesystem-mt \
					 	-lboost_system-mt \
						-L/usr/local/mylib/ \
					 	-lcocos2dMac3.8 \
					 	-lz \
					 	-liconv
else
	LDFLAGS =
endif

# LIBS      = /usr/local/lib/libboost*-mt.a
LIBS =
PROJNAME = $(shell basename `pwd`)
INCLUDE   = -I./include \
						-I/usr/local/include \
						-I/usr/local/lib/ \
						`pkg-config --cflags opencv` \
						-isystem/usr/local/myinclude/cocos2d/cocos \
						-isystem/usr/local/myinclude/cocos2d/external/glfw3/include/mac
TARGET    = ./bin/$(PROJNAME).app/Contents/MacOS/$(PROJNAME)

SRCDIR    = ./source
ifeq "$(strip $(SRCDIR))" ""
  SRCDIR  = .
endif
SOURCES   = $(wildcard $(SRCDIR)/*.cpp)

OBJDIR    = ./obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR  = .
endif
OBJECTS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))

DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS) $(FRAMEWORKS)
	cp -r Resources bin/$(PROJNAME).app/Contents/Resources
	plutil -replace 'CFBundleExecutable' -string $(PROJNAME) Info.plist
	plutil -replace 'CFBundleName' -string $(PROJNAME) Info.plist
	plutil -replace 'CFBundleIdentifier' -string com.rapmocha.$(PROJNAME) Info.plist
	cp Info.plist bin/$(PROJNAME).app/Contents/

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

run:
	bin/$(PROJNAME).app/Contents/MacOS/$(PROJNAME)

-include $(DEPENDS)
