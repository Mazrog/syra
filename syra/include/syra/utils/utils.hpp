//
// Created by mazrog on 20/10/17.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include <tuple>
#include <signal.h>
#include <functional>

#define LOG_DEBUG(a) std::cerr << a << std::endl;
#define FLUSH_DEBUG std::cout << std::flush;

void error(const char * msg);

int setup_signals(void (*f)(int));

/* Tuple Apply */
template <size_t N, typename F, typename ...Ts>
typename std::enable_if<N == sizeof...(Ts), void>::type
    tuple_apply(std::tuple<Ts...> &, F) {}

template <size_t N, typename F, typename ...Ts>
typename std::enable_if<N < sizeof...(Ts), void>::type
    tuple_apply(std::tuple<Ts...> & tuple, F func) {
        func(std::get<N>(tuple));
        tuple_apply<N+1, F, Ts...>(tuple, func);
    }


#endif
