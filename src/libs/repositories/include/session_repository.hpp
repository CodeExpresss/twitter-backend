#ifndef SESSION_REPOSITORY_HPP
#define SESSION_REPOSITORY_HPP

#include "repositories_header.hpp"

class SessionRepository {
public:
    SessionRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {}
    ~SessionRepository() = default;

    bool check_session(std::string& session_id, err_code& rc);
    std::string create(int user_id, err_code &rc);
    void erase(std::string& session_id, err_code &rc);

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;

    std::string generate_key(int profile_id);
};

#endif
