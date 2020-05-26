#include "session_repository.hpp"

std::string SessionRepository::generate_key(int profile_id) {
    return std::to_string(profile_id);
}

std::string SessionRepository::create(int user_id, err_code &rc) {
    std::string session_id = generate_key(user_id + std::rand() % 1000);
    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format("insert into session values('%1%', %2%, now());")
             % session_id % user_id).str();
    if (auto ctrl = db_controller.lock())
    {
        if (ctrl->run_query(query, query_result))
            rc = OK;
        else
            rc = NOT_EXIST;
    }
    else
        rc = NO_CTRL;

    return session_id;
}

void SessionRepository::erase(std::string& session_id, err_code &rc) {
    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format("delete from session where id = '%1%';")
             % session_id).str();
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

bool SessionRepository::check_session(std::string& session_id, err_code &rc) {
    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format("select id from session where id = '%1%';")
             % session_id).str();
    bool result = false;
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result) && query_result.size() > 0) {
            result = true;
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