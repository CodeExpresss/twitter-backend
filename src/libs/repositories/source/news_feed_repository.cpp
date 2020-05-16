#include "news_feed_repository.hpp"

std::vector<std::pair<Tweet, Profile>> NewsFeedRepository::get_by_id(int id, err_code &rc) {
    std::vector<std::vector<std::string>> query_result = {};
    int p_id = 0, tweet_id = 0;
    std::string username = "", avatar = "", timestamp = "", text = "";
    std::vector<std::string> image;
    std::vector<std::pair<Tweet, Profile>> result;
    std::string query =
            (boost::format("select * from profile where id = %1%;") % id).str();
//    if (auto ctrl = db_controller.lock())
//    {
//        if (ctrl->run_query(query, query_result))
//        {
//            p_id = std::stoi(query_result[0][0]);
//            user_id = std::stoi(query_result[0][1]);
//            username = query_result[0][2];
//            avatar = query_result[0][3];
//            birthday = query_result[0][4];
//            rc = OK;
//        }
//        else
//            rc = NOT_EXIST;
//    }
//    else
//        rc = NO_CTRL;
//
//    // need to specify the object with params
//    Profile p = Profile(p_id, user_id, username, avatar, birthday);
    //Profile p = Profile();
    return result;
}