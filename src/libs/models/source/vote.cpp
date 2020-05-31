#include "vote.hpp"

Vote::Vote(int profile_id, int tweet_id, bool is_visible)
    : profile_id(profile_id), tweet_id(tweet_id),
    is_visible(is_visible) {
}

int Vote::get_profile_id() {
    return profile_id;
}

int Vote::get_tweet_id() {
    return tweet_id;
}

bool Vote::get_is_visible() {
    return is_visible;
}

void Vote::set_profile_id(int id) {
    profile_id = id;
}

void Vote::set_tweet_id(int id) {
    tweet_id = id;
}

void Vote::set_is_visible(bool status) {
    is_visible = status;
}

