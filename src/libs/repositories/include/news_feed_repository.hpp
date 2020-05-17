#ifndef NEWS_FEED_REPOSITORY_HPP
#define NEWS_FEED_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "tweet.hpp"
#include "profile.hpp"

class NewsFeedRepository {
public:
    NewsFeedRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {}
    ~NewsFeedRepository() = default;

    std::vector<Profile> get_where() {}

    std::vector<std::pair<Tweet, Profile>> get_by_id(int id, err_code &rc);

    void create(Profile &item, err_code &rc);
    void update(std::pair<Tweet, Profile> &item, int profile_id,err_code &rc);
    void erase(int id, err_code &rc);

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif
