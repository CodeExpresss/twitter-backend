#ifndef TWEET_LIKE_CONTROLLER_HPP
#define TWEET_LIKE_CONTROLLER_HPP

#include "controller_header.hpp"

template <class Serialize>
class TweetLikeController {
public:
    explicit TweetLikeController(std::shared_ptr<UnitOfWork> _worker, int profile_id): worker(std::move(_worker)) {};
    ~TweetLikeController() = default;

    boost::property_tree::ptree get_queryset(int profile_id);

private:
    std::shared_ptr<UnitOfWork> worker;

    std::vector<std::tuple<Tweet, Profile>> like_wall;
    Serialize serialize;
};

#endif