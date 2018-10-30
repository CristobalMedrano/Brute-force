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
FILE = brute_force
DEBUG_FILE = debug_brute_force
MAIN_FILE = $(FILE).o
DEBUG_MAIN_FILE = $(DEBUG_FILE).o

#Other files
#Otros archivos
#FILE_1 = name
#OUT_FILE_1 = name.o

OBJECTS = 



.SILENT: all debug clean
all: $(MAIN_FILE) $(OBJECTS)
	$(CC) $(OPTS) -o $(EXECUTABLE) $(MAIN_FILE) $(OBJECTS)
	echo Compilation done. Executable: $(EXECUTABLE)

debug: $(DEBUG_MAIN_FILE)
	$(CC) $(OPTS) -o $(EXECUTABLE) $(DEBUG_MAIN_FILE)
	echo Debug mode done. Executable: $(EXECUTABLE)

execute: all
	$(EXECUTE)

#Main file.
#Archivo principal.
$(FILE).o: $(FILE).c $(HEADERS)$(FILE).h
	$(CC) $(OPTS) $(INCLUDE) -c $(FILE).c -o $(FILE).o

#Debug main file.
#Depurar archivo principal.
$(DEBUG_FILE).o: $(FILE).c $(HEADERS)$(FILE).h
	$(CC) $(OPTS) $(DEBUG) $(INCLUDE) -c $(FILE).c -o $(DEBUG_FILE).o


#Other files.
#Otros archivos.
#$(FILE).o: $(SOURCES)$(FILE).c $(HEADERS)$(FILE).h
#	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)$(FILE).c -o $(FILE).o

.PHONY: clean
clean:
	$(REMOVE) $(MAIN_FILE) $(DEBUG_MAIN_FILE)
	$(REMOVE) $(OBJECTS) $(EXECUTABLE)
	echo Limpieza Completa.
