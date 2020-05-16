#ifndef TWEET_HPP
#define TWEET_HPP

#include "models_header.hpp"
#include "tag.hpp"

class Tweet {
public:
    Tweet(int tweet_id, int profile_id, std::vector<Tag>& tags,
            std::string& text, std::string& date, std::string& image, bool is_visible = 1)
        : tweet_id(tweet_id), profile_id(profile_id), tags(std::move(tags)),
        text(std::move(text)), date(std::move(date)), image(std::move(image)), is_visible(is_visible) {}

    Tweet(std::string _text, int profile_id): tweet_id(0), profile_id(profile_id),
        tags(1, 1) , text(std::move(_text)), date("2020-05-16"){};

    Tweet() = default;
    ~Tweet() = default;

    int get_tweet_id() {return tweet_id;}
    int get_profile_id() {return profile_id;}
    std::vector<Tag>& get_tags() {return tags;}
    std::string& get_text() {return text;}
    std::string& get_date() {return date;}
    std::string& get_image() {return image;}
    bool get_is_visible() {return is_visible;}

    void set_tweet_id(int id) {tweet_id = id;}
    void set_profile_id(int id) {profile_id = id;}
    void set_tags(std::vector<Tag>& _tags) {tags = _tags;}
    void set_text(std::string& _text) {text = _text;}
    void set_date(std::string& _date) {date = _date;}
    void set_image(std::string& _image) {image = _image;}
    void set_is_visible(bool status) {is_visible = status;}

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
