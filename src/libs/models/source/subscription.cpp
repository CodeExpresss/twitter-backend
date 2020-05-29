#include "subscription.hpp"

Subscription::Subscription(int inviter_id, int invitee_id, bool is_active)
    : inviter_id(inviter_id),
    invitee_id(invitee_id),
    is_active(is_active) {}

Subscription::Subscription(int inviter_id, int invitee_id)
    : inviter_id(inviter_id),
    invitee_id(invitee_id),
    is_active(1) {}

std::vector<User> Subscription::get_invitees() {};
bool Subscription::change_state() {};

int Subscription::get_inviter_id() {return inviter_id;}
int Subscription::get_invitee_id() {return invitee_id;}
bool Subscription::get_is_active() {return is_active;}

void Subscription::set_inviter_id(int id) {inviter_id = id;}
void Subscription::set_invitee_id(int id) {invitee_id = id;}
void Subscription::set_is_active(bool status) {is_active = status;}

