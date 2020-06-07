#ifndef APP_GET_PROFILE_TWEETS_HPP
#define APP_GET_PROFILE_TWEETS_HPP

template<class Serialize>
class GetTweetsController {
public:
    explicit GetTweetsController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~GetTweetsController() = default;

    boost::property_tree::ptree get_queryset(int profile_id);

private:
    std::shared_ptr<UnitOfWork> worker;

    std::vector<std::tuple<Tweet, Profile>> wall;
    Serialize serialize;
};

#include "templates/template_get_profile_tweet.hpp"

#endif //APP_GET_PROFILE_TWEETS_HPP
