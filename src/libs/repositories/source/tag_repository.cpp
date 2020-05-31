#include "../include/tag_repository.hpp"

Tag TagRepository::get_by_title(const std::string& text, err_code& rc) {
    std::string query;
    query = (boost::format("select * from tag where text = '%1%';") % text).str();
    std::vector<std::vector<std::string>> query_result = {};
    int id = 0;
    std::string title = "";
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result) && query_result.size() > 0) {
            id = std::stoi(query_result[0][0]);
            title = query_result[0][1];
            rc = OK;
        }
        else {
            rc = NOT_EXIST;
        }
    }
    else {
        rc = NO_CTRL;
    }

    Tag tag(id, title);
    return tag;
}

std::vector<int> TagRepository::get_by_id(int id, err_code& rc) {
    std::string query;
    query = (boost::format("select tweet_id from tweet_tag where tag_id = %1%;") % id).str();
    std::vector<std::vector<std::string>> query_result = {};
    std::vector<int> result = {};
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result) && query_result.size() > 0) {
            for (int i = 0; i < query_result.size(); i++) {
                result.push_back(std::stoi(query_result[i][0]));
            }
            rc = OK;
        }
        else {
            rc = NOT_EXIST;
        }
    }
    else {
        rc = NO_CTRL;
    }

    return result;
}

void TagRepository::create(Tag& item, err_code& rc) {
    int tag_id = item.get_tag_id();
    std::string title = item.get_title();
    std::vector<std::vector<std::string>> query_result = {};
    std::string query = (boost::format("insert into tag values(%1%, %2%);")
        % tag_id % title).str();
    if (auto ctrl = db_controller.lock())
    {
        if (ctrl->run_query(query, query_result)) {
            rc = OK;
        }
        else {
            rc = NOT_EXIST;
        }
    }
    else {
        rc = NO_CTRL;
    }
}

void TagRepository::update(Tag& item, err_code &rc) {
    int tag_id = item.get_tag_id();
    std::string title = item.get_title();
    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
        (boost::format("update tag set title = '%1%' where id = %2%;")
        % title % tag_id).str();
    if (auto ctrl = db_controller.lock())
    {
        if (ctrl->run_query(query, query_result))
            rc = OK;
        else
            rc = NOT_EXIST;
    }
    else
        rc = NO_CTRL;
}

