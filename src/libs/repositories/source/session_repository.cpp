#include "session_repository.hpp"

std::string SessionRepository::generate_key(int profile_id) {
    return std::to_string(profile_id);
}

std::string SessionRepository::create(int user_id, err_code &rc) {
    std::string session_id = generate_key(user_id + std::rand() % 1000);
    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format("insert into session values('%1%', %2%, now());") %
             session_id % user_id)
                    .str();
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result))
            rc = OK;
        else
            rc = NOT_EXIST;
    } else
        rc = NO_CTRL;

    return session_id;
}

void SessionRepository::erase(std::string &session_id, err_code &rc) {
    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format("delete from session where id = '%1%';") % session_id)
                    .str();
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result))
            rc = OK;
        else
            rc = NOT_EXIST;
    } else
        rc = NO_CTRL;
}

bool SessionRepository::check_session(std::string &session_id, err_code &rc) {
    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format("select id from session where id = '%1%';") % session_id)
                    .str();
    bool result = false;
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result) && !query_result.empty()) {
            result = true;
            rc = OK;
        } else {
            rc = NOT_EXIST;
        }
    } else {
        rc = NO_CTRL;
    }

    return result;
}

int SessionRepository::get_profile_id(std::string &session_id, err_code &rc) {
    std::vector<std::vector<std::string>> query_result = {};
    std::string query =
            (boost::format("select user_id from session where id = '%1%';") %
             session_id)
                    .str();
    int p_id = -1;
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result) && !query_result.empty()) {
            p_id = std::stoi(query_result[0][0]);
            rc = OK;
        } else {
            rc = NOT_EXIST;
        }
    } else {
        rc = NO_CTRL;
    }

    return p_id;
}
