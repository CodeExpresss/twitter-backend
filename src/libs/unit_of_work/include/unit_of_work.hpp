#ifndef UNIT_OF_WORK_HPP
#define UNIT_OF_WORK_HPP

#include <iostream>

#include "unit_of_work_header.hpp"

class UnitOfWork {
public:
    UnitOfWork() {
        controller = make_shared<DBController<DBConnection>>(3);
        profile_repositrory = make_shared<ProfileRepository>(controller);
        tweet_repository = make_shared<TweetRepository>(controller);
        tag_repository = make_shared<TagRepository>(controller);
        user_repository = make_shared<UserRepository>(controller);
        vote_repository = make_shared<VoteRepository>(controller);
        subscription_repository = make_shared<SubscriptionRepository>(controller);
        news_feed_repository = make_shared<NewsFeedRepository>(controller);
        session_repository = make_shared<SessionRepository>(controller);
    }

    ~UnitOfWork() = default;

    std::pair<unsigned short int, std::string> sing_up(User user, Profile profile);
    std::vector<std::pair<Tweet, Profile>> get_index_tweet(int profile_id);
    std::pair<int, std::string> login(User user);
    std::pair<unsigned short int, std::string> authenticate() {}
    std::pair<unsigned short int, std::string> logout(User user) {}
    std::pair<unsigned short int, std::string> following(Subscription subscription);
    bool check_subscriptions(Subscription& sub, err_code rc) {
        bool status = subscription_repository->check_subscription(sub, rc);
        return status;
    }


    std::pair<int, std::string> create_session(int user_id);
    int get_user_id_session(std::string& session_id);
    void delete_session(std::string& session_id);
    bool check_session(std::string& session_id);


    User user_update(User user) {}

    User get_user() {}

    Profile get_profile(int profile_id, err_code &rc) {
		  return profile_repositrory->get_by_id(profile_id, rc);

    }

    std::vector<Tag> get_tag_list();

    std::vector<Profile> get_subscriptions(int profile_id, err_code& rc);/* {*/
        //std::vector<int> profiles_id = subscription_repository->get_by_id(profile_id, rc);
        //std::vector<Profile> profiles;

        //for (auto i: profiles_id) {
            //profiles.push_back(profile_repositrory->get_by_id(i, rc));
        //}

        //return profiles;
    //}

    Profile profile_update(Profile profile_id) {}
    std::vector<std::tuple<Tweet, Profile>> get_like_tweets(int profile_id) {}
    std::pair<unsigned short int, std::string> vote(Vote vote) {}
    std::pair<unsigned short int, std::string> create_tweet(Tweet tweet);/* {*/
        //std::vector<Tag> tags = tweet.get_tags();

    /*}*/
    std::pair<unsigned short int, std::string> delete_tweet() {}

    std::vector<std::pair<Tweet, Profile>> find_by_tag(const std::string& tag, err_code& rc);

private:
    std::vector<Profile> get_sub() {}
    std::vector<Tag> get_tags() {}

    std::shared_ptr<DBController<DBConnection>> controller;
    std::shared_ptr<ProfileRepository> profile_repositrory;
    std::shared_ptr<TweetRepository>  tweet_repository;
    std::shared_ptr<TagRepository> tag_repository;
    std::shared_ptr<UserRepository> user_repository;
    std::shared_ptr<VoteRepository> vote_repository;
    std::shared_ptr<SubscriptionRepository> subscription_repository;
    std::shared_ptr<NewsFeedRepository> news_feed_repository;
    std::shared_ptr<SessionRepository> session_repository;
};

#endif // UNIT_OF_WORK_HPP
