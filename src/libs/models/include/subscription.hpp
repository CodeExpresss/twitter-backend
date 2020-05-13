#ifndef SUBSCRIPTION_HPP
#define SUBSCRIPTION_HPP

#include "user.hpp"

class Subscription {
public:
	std::vector<User> get_invitees();
	bool change_state();

    int get_inviter_id() {return inviter_id;}
    int get_invitee_id() {return invitee_id;}
    bool get_is_active() {return is_active;}

    void set_inviter_id(int id) {inviter_id = id;}
    void set_invitee_id(int id) {invitee_id = id;}
    void set_is_active(bool status) {is_active = status;}

private:
	int inviter_id;
	int invitee_id;
	bool is_active;
};

#endif
