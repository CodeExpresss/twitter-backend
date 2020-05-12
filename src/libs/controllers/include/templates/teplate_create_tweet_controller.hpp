#include "create_tweet_controller.hpp"

template <class Serialize>
boost::property_tree::ptree AddTweetController<Serialize>::get_queryset() {
    return serialize(worker->create_tweet(tweet));
};