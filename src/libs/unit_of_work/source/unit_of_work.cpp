#include "unit_of_work_header.hpp"
#include "unit_of_work.hpp"
#include "repositories_header.hpp"
#include "subscription_repository.hpp"

std::vector<Profile> UnitOfWork::get_subscriptions(int profile_id, err_code& rc) {
    std::vector<int> profiles_id = subscription_repository->get_by_id(profile_id, rc);
    std::vector<Profile> profiles;

    for (auto i: profiles_id) {
        profiles.push_back(profile_repositrory->get_by_id(i, rc));
    }

    return profiles;
}

std::pair<unsigned short int, std::string> UnitOfWork::create_tweet(Tweet tweet) {
    err_code rc;

    std::vector<Tag> tags = tweet.get_tags();
    tweet_repository->create(tweet, rc);
    if (rc != OK) {
        return std::pair<unsigned short, std::string>(404, "err");
    }

/*    for (auto tag: tags) {*/
        //tag_repository->create(tag, rc);
        //if (rc != OK) {
            //return std::pair<unsigned short, std::string>(404, "err");
        //}
    /*}*/

    auto subs = subscription_repository->get_by_id(tweet.get_profile_id(), rc);
    std::vector<std::pair<Tweet, Profile>> updates;

    for (int i : subs) {
        std::pair<Tweet, Profile> upd;
        upd.first = tweet;
        upd.second = profile_repositrory->get_by_id(i, rc);
        updates.push_back(upd);
    }

    news_feed_repository->update(updates, rc);

    return std::pair<unsigned short, std::string>(200, "Ok");
}
/*Profile UnitOfWork::get_profile(int profile_id) {*/
    //Profile _profile;
    //return _profile;
/*}*/
