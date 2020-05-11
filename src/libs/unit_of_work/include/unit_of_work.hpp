#ifndef UNIT_OF_WORK_HPP
#define UNIT_OF_WORK_HPP

#include <iostream>

#include "unit_of_work_header.hpp"

class UnitOfWork {
public:
    UnitOfWork(ProfileRepository profile_repository,
        TweetRepository  tweet_repository,
        TagRepository tag_repository,
        UserRepository user_repository,
        VoteRepository vote_repository,
        SubscriptionRepository subscription_repository)
        : profile_repositrory(std::move(profile_repository)),
        tweet_repository(std::move(tweet_repository)),
        tag_repository(std::move(tag_repository)),
        user_repository(std::move(user_repository)),
        vote_repository(std::move(vote_repository)),
        subscription_repository(std::move(subscription_repository)) {}

    ~UnitOfWork() = default;

    std::pair<unsigned short int, std::string> sing_up(User user, Profile profile) {}
    std::tuple<Tweet, Profile> get_index_tweet(int profile_id) {}
    unsigned short int login(User user) {}
    unsigned short int authenticate() {}
    unsigned short int logout(User user) {}
    std::pair<unsigned short int, std::string> user_update(User user) {}
    User get_user() {}
    Profile get_profile(int profile_id);
    std::vector<Tag> get_tag_list();
    std::vector<Profile> get_subscriptions(int profile_id);
    Profile profile_update(int profile_id) {}
    std::tuple<Tweet, Profile> get_like_tweets(int profile_id) {}
    unsigned short int vote(Vote vote) {}
    std::pair<unsigned short int, std::string> create_tweet(Tweet tweet) {}
    std::pair<unsigned short int, std::string> delete_tweet() {}

private:
    std::vector<Profile> get_sub() {}
    std::vector<Tag> get_tags() {}

    ProfileRepository profile_repositrory;
    TweetRepository  tweet_repository;
    TagRepository tag_repository;
    UserRepository user_repository;
    VoteRepository vote_repository;
    SubscriptionRepository subscription_repository;
};

#endif // UNIT_OF_WORK_HPP
