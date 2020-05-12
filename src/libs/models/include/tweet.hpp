#ifndef TWEET_HPP
#define TWEET_HPP

#include "models_header.hpp"
#include "tag.hpp"

class Tweet {
public:
    Tweet(std::string _text, int _profile_id): profile_id(_profile_id), text(std::move(_text)) {};
    ~Tweet() = default;

    bool set_tag(const std::vector<Tag> &tags);

private:
    int tweet_id;
    int profile_id;
    std::vector<Tag> tags;
    std::string text;
    std::string date;
    std::string image;
    bool is_visible;
};

#endif
