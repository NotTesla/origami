// main.c	: Defines the entry point for the application.
// author	: Mark Grass

#include "device_interface.h"
#include "app.h"

#include "utils.h"
#include <stdio.h>

int main(void/* int argc, char* argv[] */) {

    // create an app
    struct App app;

    // initialize the device with a window title
	device_init(&app, "Origami");

    // run the engine
    return device_run(&app.device);

}
