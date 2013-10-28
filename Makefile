COMPILER=gcc
TEST=tests/
DIJKSTRA=dijkstra
EVENTS=events
MERGE_SORT=merge-sort
MM=mm
MUTEX=mutex
SOR=sor

.PHONY: dijkstra events merge-sort mm mutex sor all

dijkstra:
	@echo compilando $(DIJKSTRA)
	@$(COMPILER) -o $(DIJKSTRA) -O3 $(TEST)$(DIJKSTRA).c -Wall
	@echo executando $(DIJKSTRA)
	./$(DIJKSTRA)
	@echo ..............ok
	rm $(DIJKSTRA)

events:
	@echo compilando $(EVENTS)
	@$(COMPILER) -o $(EVENTS) -O3 $(TEST)$(EVENTS).c -Wall -lpthread 
	@echo executando $(EVENTS)
	./$(EVENTS)
	@echo ..............ok
	rm $(EVENTS)

merge-sort:
	@echo compilando $(MERGE_SORT)
	@$(COMPILER) -o $(MERGE_SORT) -O3 $(TEST)$(MERGE_SORT).c -Wall
	@echo executando $(MERGE_SORT)
	./$(MERGE_SORT)
	@echo ..............ok
	rm $(MERGE_SORT)

mm:
	@echo compilando $(MM)
	@$(COMPILER) -o $(MM) $(TEST)$(MM).c -lpthread -g -Wall -O3
	@echo executando $(MM)
	./$(MM)
	@echo ..............ok
	rm $(MM)

mutex:
	@echo compilando $(MUTEX)
	@$(COMPILER) -o $(MUTEX) -O3 $(TEST)$(MUTEX).c -lpthread -D DEBUG
	@echo executando $(MUTEX)
	./$(MUTEX)
	@echo ..............ok
	rm $(MUTEX)

sor:
	@echo compilando $(SOR)
	@$(COMPILER) -o $(SOR) -O3 $(TEST)$(SOR).c -Wall
	@echo executando $(SOR)
	./$(SOR)
	@echo ..............ok
	rm $(SOR)

all:
	#make $(DIJKSTRA)
	make $(EVENTS)
	make $(MERGE_SORT)
	make $(MM)
	#make $(MUTEX)
	make $(SOR)
