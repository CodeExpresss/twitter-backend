#include "get_profile_tweets.hpp"

template <class Serialize>
boost::property_tree::ptree GetTweetsController<Serialize>::get_queryset(int profile_id) {
    return serialize(worker->get_profile_tweets(profile_id));
};