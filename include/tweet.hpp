#ifndef TWEET_HPP
#define TWEET_HPP

#include <vector>
#include <string>

#include "tag.hpp"

class Tweet {
public:
    Tweet();

    bool set_tag(const std::vector<Tag> &tags);

private:
    int tweet_id;
    int profile_id;
    std::vector<int> tags_id;
    std::string text;
    std::string date;
    std::string image_path;
    bool is_visible;
};

#endif
