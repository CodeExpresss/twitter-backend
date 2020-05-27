#include "session_controller.hpp"

int SessionController::get_profile_id(std::string session) {
    return worker->get_user_id_session(session);
}