#include "tweet.hpp"
Tweet::Tweet(int tweet_id, int profile_id,
        std::vector<Tag>& tags, std::string& text,
        std::string& date, std::string& image,
        bool is_visible)
    : tweet_id(tweet_id), profile_id(profile_id),
    tags(std::move(tags)), text(std::move(text)),
    date(std::move(date)), image(std::move(image)),
    is_visible(is_visible) {
}

Tweet::Tweet(std::string _text, int profile_id)
    : tweet_id(0), profile_id(profile_id),
    tags(1, 1) , text(std::move(_text)),
    date("2020-05-16"), is_visible(true) {
}


int Tweet::get_tweet_id() {
    return tweet_id;
}

int Tweet::get_profile_id() {
    return profile_id;
}

std::vector<Tag>& Tweet::get_tags() {
    return tags;
}

std::string& Tweet::get_text() {
    return text;
}

std::string& Tweet::get_date() {
    return date;
}

std::string& Tweet::get_image() {
    return image;
}

bool Tweet::get_is_visible() {
    return is_visible;
}

void Tweet::set_tweet_id(int id) {
    tweet_id = id;
}

void Tweet::set_profile_id(int id) {
    profile_id = id;
}

void Tweet::set_tags(std::vector<Tag>& _tags) {
    tags = _tags;
}

void Tweet::set_text(std::string& _text) {
    text = _text;
}

void Tweet::set_date(std::string& _date) {
    date = _date;
}

void Tweet::set_image(std::string& _image) {
    image = _image;
}

void Tweet::set_is_visible(bool status) {
    is_visible = status;
}
