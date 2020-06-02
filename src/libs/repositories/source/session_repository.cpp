#include "session_repository.hpp"
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

using boost::uuids::detail::md5;

std::string toString(const md5::digest_type &digest)
{
    const auto charDigest = reinterpret_cast<const char *>(&digest);
    std::string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
    return result;
}

std::string SessionRepository::create(int user_id, err_code &rc) {
    md5 hash;
    md5::digest_type digest;
    std::string u_id = std::to_string(user_id);
    hash.process_bytes(u_id.data(), u_id.size());
    hash.get_digest(digest);
    std::string session_id = toString(digest);
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
