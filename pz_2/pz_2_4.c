#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define MSG "In function %20s; &localvar = %p\n"


static void blocking_function(void) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    printf("\nNow blocking on pause()...\n");
    pause();
}

static void nested_func3(void) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    blocking_function();
}

static void nested_func2(void) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    nested_func3();
}

static void nested_func1(void) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    nested_func2();
}

int main(int argc, char **argv) {
    int localvar = 5;
    printf("PID процесу: %d\n", getpid());
    printf(MSG, __FUNCTION__, &localvar);
    
    nested_func1();
    
    exit(EXIT_SUCCESS);
}
