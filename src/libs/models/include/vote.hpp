#ifndef VOTE_HPP
#define VOTE_HPP

#include "models_header.hpp"

class Vote {
public:
    Vote() = default;
    ~Vote() = default;

private:
    int profile_id;
    int tweet_id;
    int kind;

    bool set_like(int, int);
    bool remove_like(int, int);
};

#endif // VOTE_HPP
