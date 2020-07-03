MAP_PATH = lib/ADTMap/
LIST_PATH = lib/ADTList/
QUEUE_PATH = lib/ADTQueue/
PROG = prog
TEST_PATH = test/

# Project implementation
all:
	gcc -o ${PROG} -g main.c \
	Utils.c Date.c Patient.c Region.c Command.c				\
	${MAP_PATH}/mapArrayList.c ${MAP_PATH}/mapElem_region.c	\
	${LIST_PATH}/listElem.c    ${LIST_PATH}/listArrayList.c    \
	${QUEUE_PATH}/queueElem.c  ${QUEUE_PATH}/queueArrayList.c -lm
# Tests for project modules
testDate:
	gcc -o ${PROG} -g ${TEST_PATH}/testDate.c Date.c 
testRegion:
	gcc -o ${PROG} -g ${TEST_PATH}/testRegion.c Region.c
testPatient:
	gcc -o ${PROG} -g ${TEST_PATH}/testPatient.c Region.c Date.c Patient.c
testUtils:
	gcc -o ${PROG} -g ${TEST_PATH}/testUtils.c Utils.c Region.c Date.c Patient.c  \
	${MAP_PATH}/mapArrayList.c ${MAP_PATH}/mapElem_region.c		  \
	${LIST_PATH}/listElem.c    ${LIST_PATH}/listArrayList.c
# Tests the whole project using a LinkedList implementation for all Data Structures
testProjectLinked:
	gcc -o ${PROG} -g ${TEST_PATH}testProject.c \
	Utils.c Date.c Patient.c Region.c Command.c				\
	${MAP_PATH}/mapLinkedList.c ${MAP_PATH}/mapElem_region.c	\
	${LIST_PATH}/listElem.c    ${LIST_PATH}/listLinkedList.c    \
	${QUEUE_PATH}/queueElem.c  ${QUEUE_PATH}/queueLinkedList.c -lm
# Tests the whole project using a ArrayList implementation for all Data Structures
testProject:
	gcc -o ${PROG} -g ${TEST_PATH}testProject.c \
	Utils.c Date.c Patient.c Region.c Command.c				\
	${MAP_PATH}/mapArrayList.c ${MAP_PATH}/mapElem_region.c	\
	${LIST_PATH}/listElem.c    ${LIST_PATH}/listArrayList.c    \
	${QUEUE_PATH}/queueElem.c  ${QUEUE_PATH}/queueArrayList.c -lm
# Removes current binaries 
clean:
	rm -rf ${PROG}



