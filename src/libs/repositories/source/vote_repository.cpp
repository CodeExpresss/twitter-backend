#include "../include/vote_repository.hpp"

bool VoteRepository::get_by_id(int p_id, int t_id, err_code &rc) 
{
	std::vector<std::vector<std::string>> query_result = {};
    std::string query = 
        (boost::format("select * from vote where profile_id = %1% and tweet_id = %2%;") % p_id % t_id).str();
	if (auto ctrl = db_controller.lock())
	{
		if (ctrl->run_query(query, query_result) && 
			(query_result.size() == 0 || !query_result[0][2].compare("f")))
		{
			rc = OK;
			return true;
		}
		else
			rc = ALREADY_EXIST;
	}
	else
		rc = NO_CTRL;
	
	return false;
}

void VoteRepository::create(Vote &item, err_code &rc)
{
	int profile_id = item.get_profile_id();
	int tweet_id = item.get_tweet_id();
	bool visible = item.get_is_visible();
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("insert into vote values(%1%, %2%, %3%);")
		% profile_id % tweet_id % boost::io::group(std::boolalpha, visible)).str();
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

void VoteRepository::update(Vote &item, err_code &rc)
{
	int profile_id = item.get_profile_id();
	int tweet_id = item.get_tweet_id();
	bool visible = item.get_is_visible();
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("update vote set profile_id = %1%, tweet_id = %2%, is_vote = %3%;")
		% profile_id % tweet_id % boost::io::group(std::boolalpha, visible)).str();
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

void VoteRepository::erase(int p_id, int t_id, err_code &rc)
{
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("update vote set is_vote = false where profile_id = %1% and tweet_id = %2%;") % p_id % t_id).str();
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