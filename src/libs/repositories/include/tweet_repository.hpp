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
    void create_comment(Tweet& item, int parent_id, err_code& rc);
    std::vector<int> get_comment(int parent_id, err_code& rc);
    void erase_comment(const int comment_id, err_code &rc);

    std::vector<Tweet> get_by_profile_id(int profile_id, err_code& rc);
private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // TWEET_REPOSITORY_HPP
