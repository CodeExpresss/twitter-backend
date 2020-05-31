#ifndef TWEET_HPP
#define TWEET_HPP

#include "models_header.hpp"
#include "tag.hpp"

class Tweet {
public:
    Tweet(int tweet_id, int profile_id, std::vector<Tag>& tags,
            std::string& text, std::string& date, std::string& image, bool is_visible = 1);

    Tweet(std::string _text, int profile_id);

    Tweet() = default;
    ~Tweet() = default;

    int get_tweet_id();
    int get_profile_id();
    std::vector<Tag>& get_tags();
    std::string& get_text();
    std::string& get_date();
    std::string& get_image();
    bool get_is_visible();

    void set_tweet_id(int id);
    void set_profile_id(int id);
    void set_tags(std::vector<Tag>& _tags);
    void set_text(std::string& _text);
    void set_date(std::string& _date);
    void set_image(std::string& _image);
    void set_is_visible(bool status);

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
