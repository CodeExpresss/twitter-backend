#include "news_feed_repository.hpp"

std::vector<std::pair<Tweet, Profile>> NewsFeedRepository::get_by_id(int id, err_code &rc) {
    std::vector<std::vector<std::string>> query_result = {};
    int p_id = 0, tweet_id = 0;
    std::string username = "", avatar = "", timestamp = "", text = "";
    std::vector<std::string> image;
    std::vector<std::pair<Tweet, Profile>> result;
    std::string query =
            (boost::format("select * from newsfeed_to_str(%1%);") % id).str();
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result)) {

            for (auto &row : query_result) {
                std::string image;
                Profile profile{std::stoi(row[8]), std::stoi(row[8]), row[7], image, image};
                std::vector<Tag> tags;
                Tweet tweet{std::stoi(row[2]), 0, tags, row[3], row[4], image};
                std::pair<Tweet, Profile> pair;
                pair.first = tweet;
                pair.second = profile;
                result.push_back(pair);
            }

            rc = OK;
        } else
            rc = NOT_EXIST;
    } else
        rc = NO_CTRL;

    return result;
}

void NewsFeedRepository::update(std::vector<std::pair<Tweet, Profile>> &item, err_code &rc) {
    for (auto i : item) {
        std::string query =
                (boost::format("update newsfeed set news = news || "
                               "row(%1%, '%2%', '%3%', %4%, %5%, '%6%', %7%, '%8%')::content")
                 % i.first.get_tweet_id()
                 % i.first.get_text()
                 % i.first.get_date()
                 % i.first.get_image()
                 % i.first.get_tags()
                 % i.second.get_username()
                 % i.second.get_profile_id()
                 % i.second.get_avatar()
                ).str();
    }
}