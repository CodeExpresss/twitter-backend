#ifndef SUBSCRIPTION_HPP
#define SUBSCRIPTION_HPP

#include <vector>

#include "user.hpp"

class Subscription {
public:
	std::vector<User> get_invitees();
	bool change_state();

private:
	int inviter_id;
	int invitee_id;
	bool is_active;
};

#endif
