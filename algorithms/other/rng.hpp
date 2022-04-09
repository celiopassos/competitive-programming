#ifndef ALGORITHMS_OTHER_RNG_HPP
#define ALGORITHMS_OTHER_RNG_HPP

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

#endif  // ALGORITHMS_OTHER_RNG_HPP
