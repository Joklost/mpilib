#ifndef MPILIB_RANDOM_H
#define MPILIB_RANDOM_H

#include <random>

namespace mpilib {
    namespace random {
//
//        template<typename RandomGenerator = std::default_random_engine>
//        class Selector {
//        public:
//            explicit Selector(RandomGenerator g = RandomGenerator{std::random_device{}()}) : eng(g) {}
//
//            template<typename Iterator>
//            Iterator select(Iterator start, Iterator end) const {
//                std::uniform_int_distribution<unsigned long> dist(0ul, std::distance(start, end) - 1ul);
//                std::advance(start, dist(eng));
//                return start;
//            }
//
//            template<typename Iterator>
//            Iterator operator()(Iterator start, Iterator end) {
//                return select(start, end);
//            }
///*
//            template<typename Container>
//            auto operator()(const Container &c) -> decltype(*begin(c)) & {
//                return *select(std::begin(c), std::end(c));
//            }
//*/
//        private:
//            RandomGenerator eng;
//        };

    }
}
#endif //MPILIB_RANDOM_H
