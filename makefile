MAIN = main_calcetto

# COMMENTO!
OBJS += match.o
OBJS += player.o

CPP=g++
OPT=-O3
ECHO=/bin/echo



esegui: $(MAIN).x
	./$(MAIN).x

$(MAIN).x: $(OBJS) $(MAIN).cpp
	@ $(ECHO) -ne "Sto Compilando .. "
	@ $(CPP) $(OPT) $^ -o $@
	@ $(ECHO) "Fatto!"

%.o: %.cpp %.h
	$(CPP) $(OPT) -c $< -o $@

clean:
	rm -f $(MAIN).x *.o







#~ esegui: $(MAIN).x
#~ 	./$(MAIN).x

#~ $(MAIN).x: $(OBJS) $(MAIN).cpp
#~ 	@ $(ECHO) -ne "Sto Compilando .. "
#~ 	@ $(CPP) $(OPT) $^ -o $@
#~ 	@ $(ECHO) "Fatto!"

#~ %.o: %.cpp %.h
#~ 	$(CPP) $(OPT) -c $< -o $@

#~ clean:
#~ 	rm -f $(MAIN).x *.o
