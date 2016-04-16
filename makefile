# ------------------------------------------------
#  Deze makefile gaat er van uit dat het programma
#  uit alle .c and .cc source files bestaat.
# ------------------------------------------------
# VARIABELEN
# ----------

# Hieronder zonodig aanpassen naar behoefte

# Waar zitten eventuele extra .h files voor het programma ...
INCDIR	= 
# ... en waar zitten de eventuele extra libraries
LIBDIR	=

# -------------------------------------------
# Hieronder hoef je zelden iets aan te passen
# -------------------------------------------
# Vertel make welke compiler we willen gebruiken
CCC=g++
CXX=g++
CC =g++

# Dit laat make zelf de sources uitzoeken op basis van de filenamen
HEADERS		:= $(wildcard *.h)
SOURCE.c	:= $(wildcard *.c)
SOURCE.cc	:= $(wildcard *.cc)
SOURCE.cpp	:= $(wildcard *.cpp)

# make bedenkt zo zelf de namen van de .o files
OBJECTS	= $(SOURCE.c:.c=.o) $(SOURCE.cc:.cc=.o) $(SOURCE.cpp:.cpp=.o)

# idem, maak een lijst van alle sources
SOURCES	= $(SOURCE.c) $(SOURCE.cc) $(SOURCE.cpp)

# het te maken programma heet 'main'
PROGRAM	:= main

# Laat de compiler (zo nodig) ook de extra .h files vinden
#CPPFLAGS += -I$(INCDIR)
# ... zet de warnings aan
CPPFLAGS += -Wall -Wextra
# ... kies de C++ standaard
#CPPFLAGS += --std=c++0x
CPPFLAGS += --std=c++11
# En, optioneel, extra debugging informatie toevoegen
# voor de debuggers zoals gdb/ddd
CPPFLAGS += -g

# Welke bibliotheken hebben we nodig (en van waar)
#LDLIBS	= -L$(LIBDIR) -lxxx -lyyy

# ---------------------------------------------------------------
# Dit is misschien nodig voor oudere make versies
## Regels zodat make ook weet hoe je van .cc of .cpp naar .o komt
#.SUFFIXES	: .o .cc .cpp
#.cc.o	:
#	$(COMPILE.cc) $<
#.cpp.o	:
#	$(COMPILE.cpp) $<
# ---------------------------------------------------------------
# DOELEN
# ------

# Het hoofdoel is dit programma
MAIN	: main

# Hoe maak je 'main'
main	: $(OBJECTS)
	$(LINK.cc) -o $@ $(OBJECTS) $(LDLIBS)

# Bepaal de onderlinge afhankelijkheden van de files
_deps	: $(HEADERS) $(SOURCES)
	$(CXX) -MM $(CPPFLAGS) $(SOURCES) > _deps
include _deps

# Hou opruiming
clean		:
	-rm -f main *.o *.gch _deps
realclean	:
	-rm -rf main *.o _deps bin/ obj/
pristine	:
	-rm -rf main *.o _deps bin/ obj/ docs *.layout *.depend

# Maak de doxygen files
docs	: doxyfile ../diversen/act.css ../diversen/doxydefault opdracht.dox $(HEADERS) $(SOURCES)
	doxygen
