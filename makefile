#Makefile for Windows and Linux developed by Cristobal Medrano Alvarado.
#Makefile para Windows y Linux desarrollado por Cristobal Medrano Alvardo.

#The operating system is checked.
#Se verifica el sistema operativo.
ifeq ($(OS),Windows_NT)
    OS_detected := Windows
else
    OS_detected := $(shell uname -s)
endif

#Select the variables to change depending on the OS.
#Se seleccionan las variables a cambiar dependiendo del SO. 

EXECUTABLE_NAME = brute_force
ifeq ($(OS_detected), Windows)
	EXTENSION = .exe
	EXECUTABLE = $(EXECUTABLE_NAME)$(EXTENSION)
	EXECUTE = $(EXECUTABLE_NAME)$(EXTENSION)
    REMOVE = -del
endif
ifeq ($(OS_detected), Linux)
	EXTENSION = .out
	EXECUTABLE = $(EXECUTABLE_NAME)$(EXTENSION)
	EXECUTE = ./$(EXECUTABLE_NAME)$(EXTENSION)
    REMOVE = -rm -f
endif

#Modules and headers folders.
#Carpeta de modulos y cabeceras.
SOURCES = Source/
HEADERS = Header/

#Variables
CC = gcc
OPTS = -Wall -g3
DEBUG = -D DEBUG
INCLUDE = -I $(HEADERS)

#Main file.
#Archivo principal.
FILE = main
DEBUG_FILE = debug_$(FILE)
MAIN_FILE = $(FILE).o
DEBUG_MAIN_FILE = $(DEBUG_FILE).o

#Other files
#Otros archivos
#FILE_1 = name
#OUT_FILE_1 = name.o
FILE_1 = brute_force
FILE_2 = menu
FILE_3 = read_file
OBJECTS = $(FILE_1).o $(FILE_2).o $(FILE_3).o
DEBUG_OBJECTS = DEBUG_$(FILE_1).o DEBUG_$(FILE_2).o $(FILE_3).o

.SILENT: all debug clean
all: $(MAIN_FILE) $(OBJECTS)
	$(CC) $(OPTS) -o $(EXECUTABLE) $(MAIN_FILE) $(OBJECTS)
	echo Compilation done. Executable: $(EXECUTABLE)

execute: all
	$(EXECUTE)

debug: $(DEBUG_MAIN_FILE) $(DEBUG_OBJECTS)
	$(CC) $(OPTS) -o $(EXECUTABLE) $(DEBUG_MAIN_FILE) $(DEBUG_OBJECTS)
	echo Debug Compilation done. Executable: $(EXECUTABLE)

debug_execute: debug
	$(EXECUTE)

#Main file.
#Archivo principal.
$(FILE).o: $(FILE).c
	$(CC) $(OPTS) $(INCLUDE) -c $(FILE).c -o $(FILE).o

#Other files.
#Otros archivos.
#$(FILE).o: $(SOURCES)$(FILE).c $(HEADERS)$(FILE).h
#	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)$(FILE).c -o $(FILE).o
$(FILE_1).o: $(SOURCES)$(FILE_1).c $(HEADERS)$(FILE_1).h
	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)$(FILE_1).c -o $(FILE_1).o

$(FILE_2).o: $(SOURCES)$(FILE_2).c $(HEADERS)$(FILE_2).h
	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)$(FILE_2).c -o $(FILE_2).o

$(FILE_3).o: $(SOURCES)$(FILE_3).c $(HEADERS)$(FILE_3).h
	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)$(FILE_3).c -o $(FILE_3).o

#Debug main file.
#Depurar archivo principal.
$(DEBUG_FILE).o: $(FILE).c
	$(CC) $(OPTS) $(DEBUG) $(INCLUDE) -c $(FILE).c -o $(DEBUG_FILE).o

#Other debug files.
#Otros archivos debug.
#$(FILE).o: $(SOURCES)$(FILE).c $(HEADERS)$(FILE).h
#	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)$(FILE).c -o $(FILE).o
DEBUG_$(FILE_1).o: $(SOURCES)$(FILE_1).c $(HEADERS)$(FILE_1).h
	$(CC) $(OPTS) $(DEBUG) $(INCLUDE) -c $(SOURCES)$(FILE_1).c -o DEBUG_$(FILE_1).o

DEBUG_$(FILE_2).o: $(SOURCES)$(FILE_2).c $(HEADERS)$(FILE_2).h
	$(CC) $(OPTS) $(DEBUG) $(INCLUDE) -c $(SOURCES)$(FILE_2).c -o DEBUG_$(FILE_2).o

DEBUG_$(FILE_3).o: $(SOURCES)$(FILE_3).c $(HEADERS)$(FILE_3).h
	$(CC) $(OPTS) $(DEBUG) $(INCLUDE) -c $(SOURCES)$(FILE_3).c -o DEBUG_$(FILE_3).o

.PHONY: clean
clean:
	$(REMOVE) $(MAIN_FILE) $(DEBUG_MAIN_FILE)
	$(REMOVE) $(OBJECTS) $(DEBUG_OBJECTS)
	$(REMOVE) $(EXECUTABLE)
	echo Limpieza Completa.
