#include "../include/DBConnection.hpp"

shared_ptr<PGconn> DBConnection::get_connection() const
{
    return connection;
}