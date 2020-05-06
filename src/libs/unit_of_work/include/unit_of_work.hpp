#ifndef UNIT_OF_WORK_HPP
#define UNIT_OF_WORK_HPP

#include <iostream>

#include "unit_of_work_header.hpp"

class UnitOfWork {
public:
    UnitOfWork() = default;
    ~UnitOfWork() = default;

    std::pair<unsigned short int, std::string> sing_up();
    std::tuple<Tweet, Profile> get_index_tweet();
    unsigned short int login();
    unsigned short int authenticate();
    unsigned short int logout();
    std::pair<unsigned short int, std::string> user_update();
    User get_user();
    Profile get_profile();
    std::pair<unsigned short int, std::string> profile_update();
    std::tuple<Tweet, Profile> get_like_tweets();
    unsigned short int vote();
    std::pair<unsigned short int, std::string> create_tweet();
    std::pair<unsigned short int, std::string> delete_tweet();

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
