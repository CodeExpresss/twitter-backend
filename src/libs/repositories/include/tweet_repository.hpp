#ifndef TWEET_REPOSITORY_HPP
#define TWEET_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "tweet.hpp"

class TweetRepository {
public:
    TweetRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {};
    ~TweetRepository() = default;

    std::vector<Tweet> get_where() {}
    Tweet get_by_id(int id) {}
    void create(Tweet item) {}
    void update(Tweet item) {}
    void erase(int id) {}

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // TWEET_REPOSITORY_HPP
