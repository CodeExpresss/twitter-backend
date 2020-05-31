#ifndef VOTE_HPP
#define VOTE_HPP

#include "models_header.hpp"

class Vote {
public:
    Vote(int profile_id, int tweet_id, bool is_visible = 1);
    Vote() = default;
    ~Vote() = default;

    int get_profile_id();
    int get_tweet_id();
    bool get_is_visible();

    void set_profile_id(int id);
    void set_tweet_id(int id);
    void set_is_visible(bool status);

private:
    int profile_id;
    int tweet_id;
    bool is_visible;

    bool set_like(int, int);
    bool remove_like(int, int);
};

#endif // VOTE_HPP
