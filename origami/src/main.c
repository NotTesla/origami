// main.c	: Defines the entry point for the application.
// author	: Mark Grass

#include "app.h"

int main(int argc, const char* argv[]) {

    // create an app with args, and then consume it
    return app_consume(app_with_args(argv, argc));
}
