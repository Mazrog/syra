//
// Created by mazrog on 20/10/17.
//

#include <syra/utils/utils.hpp>
#include <iostream>

void error(const char *msg) {
    perror(msg);
}

int setup_signals(void (*f)(int)) {
    struct sigaction sa;
    sa.sa_handler = f;

    if (sigaction(SIGINT, &sa, 0) != 0) {
        error("sigaction()");
        return -1;
    }

    if (sigaction(SIGPIPE, &sa, 0) != 0) {
        error("sigaction()");
        return -1;
    }

    return 0;
}