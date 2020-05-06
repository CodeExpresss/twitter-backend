#ifndef UNIT_OF_WORK_HPP
#define UNIT_OF_WORK_HPP

#include <iostream>

#include "unit_of_work_header.hpp"
boost::property_tree::ptree heroTree;

class UnitOfWork {
public:
    UnitOfWork() = default;
    ~UnitOfWork() = default;

    boost::property_tree::ptree sing_up();
    boost::property_tree::ptree get_index_tweet();
    boost::property_tree::ptree login();
    boost::property_tree::ptree authenticate();
    boost::property_tree::ptree logout();
    boost::property_tree::ptree user_update();
    boost::property_tree::ptree get_user();
    boost::property_tree::ptree get_profile();
    boost::property_tree::ptree profile_update();
    boost::property_tree::ptree get_like_tweets();
    boost::property_tree::ptree vote();
    boost::property_tree::ptree create_tweet();
    boost::property_tree::ptree delete_tweet();

private:
    std::vector<Profile> get_sub();
    std::vector<Tag> get_tags();

    ProfileRepository profile_repositrory;
    TweetRepository  tweet_repository;
    TagRepository tag_repository;
    UserRepository user_repository;
    VoteRepository vote_repository;
    SubscriptionRepository subscription_repository;
};

#endif // UNIT_OF_WORK_HPP
