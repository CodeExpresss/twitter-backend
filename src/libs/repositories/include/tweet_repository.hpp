#ifndef TWEET_REPOSITORY_HPP
#define TWEET_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "tweet.hpp"

class TweetRepository {
public:
    TweetRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {};
    ~TweetRepository() = default;

    std::vector<Tweet> get_where();
    Tweet get_by_id(int id, err_code& rc);
    void create(Tweet& item, err_code& rc);
    void update(Tweet& item, err_code& rc);
    void erase(int id, err_code& rc);

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // TWEET_REPOSITORY_HPP
