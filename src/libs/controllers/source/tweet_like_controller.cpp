#include "tweet_like_controller.hpp"

template <class Serialize>
boost::property_tree::ptree TweetLikeController<Serialize>::get_queryset(int profile_id) {
    like_wall = worker->get_like_tweets(profile_id);
    int wall_size = std::tuple_size<decltype(like_wall)>::value;
    if(wall_size > 0)
        return serialize(like_wall);
    else {
        return static_cast<boost::property_tree::ptree>(nullptr);
    }
};