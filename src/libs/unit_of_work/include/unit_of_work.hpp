#ifndef UNIT_OF_WORK_HPP
#define UNIT_OF_WORK_HPP

#include <iostream>

#include "unit_of_work_header.hpp"

class UnitOfWork {
public:
    UnitOfWork() {
        shared_ptr<DBController<DBConnection>> controller = make_shared<DBController<DBConnection>>(3);
        profile_repositrory = make_shared<ProfileRepository>(controller);
        tweet_repository = make_shared<TweetRepository>(controller);
        tag_repository = make_shared<TagRepository>(controller);
        user_repository = make_shared<UserRepository>(controller);
        vote_repository = make_shared<VoteRepository>(controller);
        subscription_repository = make_shared<SubscriptionRepository>(controller);
    }

    ~UnitOfWork() = default;

    std::pair<unsigned short int, std::string> sing_up() {}
    std::tuple<Tweet, Profile> get_index_tweet() {}
    unsigned short int login() {}
    unsigned short int authenticate() {}
    unsigned short int logout() {}
    std::pair<unsigned short int, std::string> user_update() {}
    User get_user() {}
	
    Profile get_profile(int profile_id)
	{
		return profile_repositrory->get_by_id(profile_id);
	}
	
    std::pair<unsigned short int, std::string> profile_update() {}
    std::tuple<Tweet, Profile> get_like_tweets() {}
    unsigned short int vote() {}
    std::pair<unsigned short int, std::string> create_tweet() {}
    std::pair<unsigned short int, std::string> delete_tweet() {}

private:
    std::vector<Profile> get_sub() {}
    std::vector<Tag> get_tags() {}

    std::shared_ptr<ProfileRepository> profile_repositrory;
    std::shared_ptr<TweetRepository>  tweet_repository;
    std::shared_ptr<TagRepository> tag_repository;
    std::shared_ptr<UserRepository> user_repository;
    std::shared_ptr<VoteRepository> vote_repository;
    std::shared_ptr<SubscriptionRepository> subscription_repository;
};

#endif // UNIT_OF_WORK_HPP
