#include "../include/subscription_repository.hpp" 

std::vector<int> SubscriptionRepository::get_by_id(int id, err_code &rc) 
{
	std::vector<std::vector<std::string>> query_result = {};
    std::string query = 
        (boost::format("select inviter_id, is_active from subscription where invitee_id = %1%;") % id).str();
    std::vector<int> result = {};
	if (auto ctrl = db_controller.lock())
	{
		if (ctrl->run_query(query, query_result))
		{
            for (int i = 0; i < query_result.size(); i++) {
                if (!query_result[i][1].compare("t"))
                    result.push_back(std::stoi(query_result[i][0]));
            }
			rc = OK;
		}
		else
			rc = NOT_EXIST;
	}
	else
		rc = NO_CTRL;

	return result;
}

void SubscriptionRepository::create(Subscription &item, err_code &rc)
{
	/*int inviter_id = item.get_inviter_id();
	int invitee_id = item.get_inviter_id();
    bool visible = item.get_is_active()
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("insert into subscription values(%1%, %2%, %3%);")
		% inviter_id % invitee_id % boost::io::group(std::boolalpha, 
                                                     visible)).str();
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

void SubscriptionRepository::update(Subscription &item, err_code &rc)
{
	/*int inviter_id = item.get_inviter_id();
	int invitee_id = item.get_inviter_id();
    bool visible = item.get_is_active()
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("update subscription set inviter_id = %1%, is_active = %2% where invitee_id = %3%;") 
		% inviter_id % boost::io::group(std::boolalpha, visible) % invitee_id).str();
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

void SubscriptionRepository::erase(int id, err_code &rc)
{
	std::vector<std::vector<std::string>> query_result = {};
	std::string query = 
		(boost::format("update subscription set is_active = false where invitee_id = %1%;") % id).str();
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