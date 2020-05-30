#ifndef SUBSCRIPTION_HPP
#define SUBSCRIPTION_HPP

#include "user.hpp"

class Subscription {
public:
    Subscription(int inviter_id, int invitee_id, bool is_active);
    Subscription(int inviter_id, int invitee_id);

	std::vector<User> get_invitees();
	bool change_state();

    int get_inviter_id();
    int get_invitee_id();
    bool get_is_active();
    void set_inviter_id(int id);
    void set_invitee_id(int id);
    void set_is_active(bool status);

private:
	int inviter_id;
	int invitee_id;
	bool is_active;
};

#endif
