# MAKEFILE NOT TESTED YET IT IS BOUND TO NOT WORK
#
# Changes you will want to make:
# 1)  Give a name the program you want to create PROGRAM = myprog.
# 2)  Specify all the .cc files after CXX_SRCS
# 3)  If you are using a library (such as math function routines)
#	adjust CXXLIBS (example: CXXLIBS = -lcc -lm)
# 4)  If you want to include any of Horstmann's classes (e.g Time),
#       include the corresponding object file after CCC_OBJS
#       (in our example ccc_time.o).  Note that if you want to use
#       cwin, this list must include ccc_x11.o and ccc_shap.o
# 5)  CCC_FILESDIR is where you keep your cccfiles directory
# 6)  Type the Unix command, "touch .depend.mk"
#     This will be a "hidden file".  To see it type "ls -a" in the shell.

################################################################
#            VARIABLES YOU'LL WANT TO CHANGE                   #
################################################################

PROGRAM = letest

CXX_SRCS = object.cc player.cc gameState.cc gameStateTest.cc bullet.cc asteroid.cc

CXXLIBS = -lSDL2 -lSDL2_gfx

CXXINCLUDEPATHS = 

################################################################
#          STUFF YOU PROBABLY WANT TO LEAVE ALONE              #
################################################################

CXX = g++
CC = $(CXX)
LDFLAGS = -g -pipe $(CXX_LIBS)
CXXFLAGS = -g -pipe -Wall $(CXXINCLUDEPATHS)

OBJS = $(CXX_SRCS:.cc=.o)

DEMANGLER = c++filt

$(PROGRAM) : depend $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(CXXLIBS) -o $(PROGRAM) 2>&1 \
             | $(DEMANGLER)

clean:
	/bin/rm -f *.o $(PROGRAM) *~ core \#*\#

depend:
	$(CXX) -MM $(CXX_SRCS) $(CXXINCLUDEPATHS) > .depend.mk

###
include .depend.mk
