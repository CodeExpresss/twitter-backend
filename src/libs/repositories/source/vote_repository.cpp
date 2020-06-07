#include "vote_repository.hpp"

bool VoteRepository::get_by_id(int p_id, int t_id, err_code &rc) {
  std::vector<std::vector<std::string>> query_result = {};
  std::string query =
      (boost::format(
           "select * from vote where profile_id = %1% and tweet_id = %2%;") %
       p_id % t_id)
          .str();
  if (auto ctrl = db_controller.lock()) {
    if (ctrl->run_query(query, query_result) &&
        (query_result.size() == 0 || !query_result[0][2].compare("f"))) {
      if (query_result.size() == 0)
        rc = OK;
      else if (!query_result[0][2].compare("f"))
        rc = DELETED;
      return true;
    } else
      rc = ALREADY_EXIST;
  } else
    rc = NO_CTRL;

  return false;
}

int VoteRepository::get_by_tweet_id(int t_id, err_code &rc) {
  std::vector<std::vector<std::string>> query_result = {};
  std::string query =
      (boost::format(
              "select count(*) from vote where tweet_id = %1% and is_vote = true;") %
       t_id)
          .str();
  int result = 0;
  if (auto ctrl = db_controller.lock()) {
    if (ctrl->run_query(query, query_result) && query_result.size() > 0) {
      result = std::stoi(query_result[0][0]);
      rc = OK;
    } else
      rc = NOT_EXIST; 
  } else 
    rc = NO_CTRL;
    
  return result;
}

void VoteRepository::create(Vote &item, err_code &rc) {
  int profile_id = item.get_profile_id();
  int tweet_id = item.get_tweet_id();
  bool visible = item.get_is_visible();
  std::vector<std::vector<std::string>> query_result = {};
  std::string query =
      (boost::format("insert into vote values(%1%, %2%, %3%);") % profile_id %
       tweet_id % boost::io::group(std::boolalpha, visible))
          .str();
  if (auto ctrl = db_controller.lock()) {
    if (ctrl->run_query(query, query_result))
      rc = OK;
    else
      rc = NOT_EXIST;
  } else
    rc = NO_CTRL;
}

void VoteRepository::update(Vote &item, err_code &rc) {
  int profile_id = item.get_profile_id();
  int tweet_id = item.get_tweet_id();
  bool visible = item.get_is_visible();
  std::vector<std::vector<std::string>> query_result = {};
  std::string query =
      (boost::format(
           "update vote set is_vote = %3% where profile_id = %1% AND tweet_id = %2%;") %
       profile_id % tweet_id % boost::io::group(std::boolalpha, visible))
          .str();
  if (auto ctrl = db_controller.lock()) {
    if (ctrl->run_query(query, query_result))
      rc = OK;
    else
      rc = NOT_EXIST;
  } else
    rc = NO_CTRL;
}

void VoteRepository::erase(int p_id, int t_id, err_code &rc) {
  std::vector<std::vector<std::string>> query_result = {};
  std::string query = (boost::format("update vote set is_vote = false where "
                                     "profile_id = %1% and tweet_id = %2%;") %
                       p_id % t_id)
                          .str();
  if (auto ctrl = db_controller.lock()) {
    if (ctrl->run_query(query, query_result))
      rc = OK;
    else
      rc = NOT_EXIST;
  } else
    rc = NO_CTRL;
}
