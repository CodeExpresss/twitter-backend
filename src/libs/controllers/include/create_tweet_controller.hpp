#ifndef CREATE_TWEET_CONTROLLER_HPP
#define CREATE_TWEET_CONTROLLER_HPP

#include "controller_header.hpp"

template <class Serialize>
class AddTweetController {
public:
    explicit AddTweetController(std::shared_ptr<UnitOfWork> _worker, std::string text, int profile_id):
        worker(std::move(_worker)),
        tweet(std::move(text), profile_id) {};

    ~AddTweetController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;

    Tweet tweet;
    Serialize serialize;
};

#include "templates/teplate_create_tweet_controller.hpp"

#endif