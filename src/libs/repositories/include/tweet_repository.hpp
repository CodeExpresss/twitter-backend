#ifndef TWEET_REPOSITORY_HPP
#define TWEET_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "tweet.hpp"

class TweetRepository {
public:
    TweetRepository() = default;
    ~TweetRepository() = default;


    std::vector<Tweet> get_all();
    Tweet get_by_id(int id);
    void create(Tweet item);
    void update(Tweet item);
    void erase(int id);

private:
};

#endif // TWEET_REPOSITORY_HPP
