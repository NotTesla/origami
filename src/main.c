// main.c	: Defines the entry point for the application.
// author	: Mark Grass

#include "device_interface.h"
#include "app.h"

#include "utils.h"
#include <stdio.h>

int main(void/* int argc, char* argv[] */) {

    App app;
	device_init(&app, "Origami");
    return device_run(&app.device);

}
