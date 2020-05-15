#include "tweet_like_controller.hpp"

template <class Serialize>
boost::property_tree::ptree TweetLikeController<Serialize>::get_queryset(int profile_id) {
    boost::property_tree::ptree default_tree;
    default_tree.put("status", "error");
    like_wall = worker->get_like_tweets(profile_id);

    if( like_wall.size() > 0)
        return serialize(like_wall);
    else {
        return default_tree;
    }
};