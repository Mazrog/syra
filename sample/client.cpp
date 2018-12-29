#include <syra/node.hpp>

#include <cmath>
#include <unistd.h>

struct {
    std::function<void()>   shutdown;
    volatile bool           running = true;
} global;


int main() {
    /* On définit le comportement des signaux attrapés */
    setup_signals([] (int sig_number) {
        switch (sig_number) {
            case SIGINT:
                puts("SIGINT");
                global.shutdown();
                break;
            
            case SIGPIPE:
                puts("SIGPIPE");
            default:;
        }
    });

    /* Définition de la fonction en cas de déconnexion du client robot */
    /* Sera appelée en cas de Ctrl + C (SIGINT) ou appui sur 'q' pour quitter le client */
    global.shutdown = [] () {
        global.running = false;
    };
    
    return 0;
}
