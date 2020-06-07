#include "profile_repository.hpp"

Profile ProfileRepository::get_by_id(int id, err_code &rc) {
  std::vector<std::vector<std::string>> query_result = {};
  int p_id = 0, user_id = 0;
  std::string username = "", avatar = "", birthday = "";
  std::string query =
      (boost::format("select * from profile where id = %1%;") % id).str();
  if (auto ctrl = db_controller.lock()) {
    if (ctrl->run_query(query, query_result) && query_result.size() > 0) {
      p_id = std::stoi(query_result[0][0]);
      user_id = std::stoi(query_result[0][1]);
      username = query_result[0][2];
      avatar = query_result[0][3];
      birthday = query_result[0][4];
      rc = OK;
    } else
      rc = NOT_EXIST;
  } else
    rc = NO_CTRL;

  Profile p = Profile(p_id, user_id, username, avatar, birthday);
  return p;
}

int ProfileRepository::check_last_id(err_code &rc) {

    std::vector<std::vector<std::string>> query_result = {};
    std::string query("select * from profile where id = (select max(id) from users);");
    if (auto ctrl = db_controller.lock()) {
        if (ctrl->run_query(query, query_result)) {
            rc = OK;
            return std::stoi(query_result[0][0]);
        }
        else
            rc = NOT_EXIST;
    } else
        rc = NO_CTRL;
    return -1;
}

bool ProfileRepository::check_profile_username(Profile &item, err_code &rc) {
  std::vector<std::vector<std::string>> query_result = {};
  std::string username = item.get_username();
  std::string query =
      (boost::format("select id from profile where username = %1%;") % username)
          .str();
  bool result = false;
  if (auto ctrl = db_controller.lock()) {
    if (ctrl->run_query(query, query_result) && query_result.size() > 0) {
      /*            if (!query_result[0][0].compare("t")) {*/
      // result =  true;
      // rc = OK;
      //}
      // else {
      // rc = DELETED;
      /*}*/
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

void ProfileRepository::create(Profile &item, err_code &rc) {
  int user_id = item.get_user_id();
  std::string username = item.get_username();
  std::string avatar = item.get_avatar();
  std::string birthday = item.get_birthday();
  std::vector<std::vector<std::string>> query_result = {};
  std::string query =
      (boost::format(
           "insert into profile values(%1%, %2%, '%3%', '%4%', '%5%');") %
       "default" % user_id % username % 'a' % "2000-01-31")
          .str();
  if (auto ctrl = db_controller.lock()) {
    if (ctrl->run_query(query, query_result))
      rc = OK;
    else
      rc = NOT_EXIST;
  } else
    rc = NO_CTRL;
}

void ProfileRepository::update(Profile &item, err_code &rc) {
  int id = item.get_profile_id();
  std::string username = item.get_username();
  std::string avatar = item.get_avatar();
  std::string birthday = item.get_birthday();
  std::vector<std::vector<std::string>> query_result = {};
  std::string query =
      (boost::format("update profile set username = '%1%', avatar = '%2%', "
                     "birthday = '%3%' where id = %4%;") %
       username % avatar % birthday % id)
          .str();
  if (auto ctrl = db_controller.lock()) {
    if (ctrl->run_query(query, query_result))
      rc = OK;
    else
      rc = NOT_EXIST;
  } else
    rc = NO_CTRL;
}

void ProfileRepository::erase(int id, err_code &rc) {
  /*std::vector<std::vector<std::string>> query_result = {};
  std::string query =
          (boost::format("update profile set deleted = true where id = %1%;") %
  id).str();
  if (auto ctrl = db_controller.lock())
  {
          if (ctrl->run_query(query, query_result))
                  rc = OK;
          else
                  rc = NOT_EXIST;
  }
  else
          rc = NO_CTRL;*/
}
