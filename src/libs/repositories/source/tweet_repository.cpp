#include "tweet_repository.hpp"

void TweetRepository::create(Tweet &item, err_code &rc) {
    int profile_id = item.get_profile_id();
    std::vector<Tag> tags = item.get_tags();
    std::string text = item.get_text();
    std::string date = item.get_date();
    // std::string image = item.get_image();
    std::string image = "NULL";
    bool is_visible = item.get_is_visible();

    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format(
                    "insert into tweet values(DEFAULT, %1%, '%2%', '%3%', %4%, %5%);") %
             profile_id % text % date % image %
             boost::io::group(std::boolalpha, is_visible))
                    .str();
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result)) {
            rc = OK;
        } else {
            rc = NOT_EXIST;
        }
    } else {
        rc = NO_CTRL;
    }
}

Tweet TweetRepository::get_by_id(int id, err_code &rc) {
    std::string query_tweet =
            (boost::format("select * from tweet where id = %1%;") % id).str();
    std::vector<std::vector<std::string>> query_result = {};

    int tweet_id = 0;
    int profile_id = 0;
    std::string text = "";
    std::string date = "";
    std::string image = "";
    bool is_visible = 0;
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query_tweet, query_result) && query_result.size() > 0) {
            is_visible = !((query_result[0][5]).compare("t")) ? true : false;
            if (is_visible) {
                tweet_id = std::stoi(query_result[0][0]);
                profile_id = std::stoi(query_result[0][1]);
                text = query_result[0][2];
                date = query_result[0][3];
                image = query_result[0][4];

                rc = OK;
            } else {
                rc = NOT_EXIST;
            }
        } else {
            rc = NOT_EXIST;
        }
    } else {
        rc = NO_CTRL;
    }

    std::string query_tweet_tag =
            (boost::format("select tag_id from tweet_tag where tweet_id = %1%;") %
             tweet_id)
                    .str();
    std::vector<Tag> tags_id;
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query_tweet_tag, query_result)) {
            for (size_t i = 0; i < query_result.size(); i++) {
                tags_id.push_back(Tag(std::stoi(query_result[i][0])));
            }
            // rc = OK;
        }
        /*        else {*/
        // rc = NOT_EXIST;
        /*}*/
    } else {
        rc = NO_CTRL;
    }

    // std::string query_tag;
    // std::vector<Tag> tags;
    // int tag_id = 0;
    // std::string title = "";
    // for (size_t i = 0; i < tags_id.size(); i++) {
    // query_tag = (boost::format("select * from tag where tag_id = %1%;") %
    // tags_id[i]).str();

    // if (auto ctrl = db_controller.lock()) {
    // if (ctrl->run_query(query_tweet_tag, query_result)) {
    // tag_id = std::stoi(query_result[0][0]);
    // title = query_result[0][1];

    // tags.push_back(Tag(tag_id, title));
    // rc = OK;
    //}
    // else {
    // rc = NOT_EXIST;
    //}
    //}
    // else {
    // rc = NO_CTRL;
    //}
    //}

    Tweet tweet(tweet_id, profile_id, tags_id, text, date, image, is_visible);
    return tweet;
}

void TweetRepository::erase(int id, err_code &rc) {
    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format(
                    "update tweet set is_visible = false where tweet_id = %1%;") %
             id)
                    .str();
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result)) {
            rc = OK;
        } else {
            rc = NOT_EXIST;
        }
    } else {
        rc = NO_CTRL;
    }
}

std::vector<Tweet> TweetRepository::get_by_profile_id(int profile_id,
                                                      err_code &rc) {
    std::string query_tweet =
            (boost::format("select * from tweet where profile_id = %1%;") %
             profile_id)
                    .str();
    std::vector<std::vector<std::string>> query_result = {};
    std::vector<Tweet> tweets;
    std::vector<Tag> tags;

    int tweet_id = 0;
    std::string text = "";
    std::string date = "";
    std::string image = "";
    bool is_visible = 0;
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query_tweet, query_result) && query_result.size() > 0) {
            for (int i = 0; i < query_result.size(); i++) {
                is_visible = query_result[i][5] == "t";
                if (is_visible) {
                    tweet_id = std::stoi(query_result[i][0]);
                    profile_id = std::stoi(query_result[i][1]);
                    text = query_result[i][2];
                    date = query_result[i][3];
                    image = query_result[i][4];

                    tweets.push_back(
                            Tweet(tweet_id, profile_id, tags, text, date, image, is_visible));
                }
            }
            rc = OK;
        } else {
            rc = NOT_EXIST;
        }
    } else {
        rc = NO_CTRL;
    }

    return tweets;
}

void TweetRepository::create_comment(Tweet &item, int parent_id, err_code &rc) {
    int comment_id = -1;

    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format("insert into tweet values(DEFAULT, %1%, '%2%', '%3%', "
                           "%4%, %5%) returning id;") %
             item.get_profile_id() % item.get_text() % item.get_date() % "NULL" %
             boost::io::group(std::boolalpha, item.get_is_visible()))
                    .str();
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result)) {
            rc = OK;
            comment_id = std::stoi(query_result[0][0]);
        } else {
            rc = NOT_EXIST;
        }
    } else {
        rc = NO_CTRL;
    }

    if (rc != OK) return;

    query = (boost::format("insert into comment values(%1%, %2%);") % comment_id %
             parent_id)
            .str();
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result)) {
            rc = OK;
        } else {
            rc = NOT_EXIST;
        }
    } else {
        rc = NO_CTRL;
    }
}

std::vector<int> TweetRepository::get_comment(const int parent_id,
                                              err_code &rc) {
    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format("select comment_id from comment where tweet_id = %1%;") %
             parent_id)
                    .str();
    std::vector<int> comment_id;
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result)) {
            rc = OK;
            for (auto i : query_result) {
                comment_id.push_back(std::stoi(i.at(0)));
            }
        } else {
            rc = NOT_EXIST;
        }
    } else {
        rc = NO_CTRL;
    }

    return comment_id;
}

void TweetRepository::erase_comment(const int comment_id, err_code &rc) {
    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format(
                    "update tweet set is_visible = false where tweet_id = %1%;") %
             comment_id)
                    .str();
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result)) {
            rc = OK;
        } else {
            rc = NOT_EXIST;
        }
    } else {
        rc = NO_CTRL;
    }
}
