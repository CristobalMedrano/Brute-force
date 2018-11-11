#Version 0.5 - 11-11-2018
#Makefile for Windows and Linux developed by Cristobal Medrano Alvarado.
#Makefile para Windows y Linux desarrollado por Cristobal Medrano Alvardo.

#Falta corregir la salida de archivos a otra carpeta.

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
	EXECUTE = $(EXECUTABLE)
    REMOVE = -del
endif
ifeq ($(OS_detected), Linux)
	EXTENSION = .out
	EXECUTABLE = $(EXECUTABLE_NAME)$(EXTENSION)
	EXECUTE = ./$(EXECUTABLE)
    REMOVE = -rm -f
endif

#Modules and headers folders.
#Carpeta de modulos y cabeceras.
HEADERS = headers
SOURCES = sources
BUILD = build

#Variables
CC = gcc
CFLAGS = -Wall -g3
CPPFLAGS = -I $(HEADERS)/
DEBUG = -D DEBUG

SRCS = $(wildcard $(SOURCES)/*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
MAIN = $(patsubst %.c,%.o,$(wildcard *.c))

.SILENT: all debug clean $(EXECUTABLE) debug_$(EXECUTABLE)
#all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ 
	echo Compilation done. Executable: $(EXECUTABLE)

debug: debug_$(EXECUTABLE)

debug_$(EXECUTABLE): $(OBJS) main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUG) -o $@ $^ 
	echo Compilation done. Executable: debug_$(EXECUTABLE)

.PHONY: clean
clean:
	$(REMOVE) $(SOURCES)\*.o
	$(REMOVE) main.o
	$(REMOVE) $(EXECUTABLE) debug_$(EXECUTABLE)
	echo Full wipe.
