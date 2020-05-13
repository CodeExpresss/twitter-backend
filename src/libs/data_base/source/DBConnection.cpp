#include "../include/DBConnection.hpp"

/*DBConnection::DBConnection(const string &host, const string &dbname, const string &user, 
                 const string &password, int port) 
{
    connection.reset(PQsetdbLogin(host.c_str(), to_string(port).c_str(),
                                  nullptr, nullptr, dbname.c_str(), 
                                  user.c_str(), password.c_str()), &PQfinish);

    if (PQstatus(connection.get()) != CONNECTION_OK && PQsetnonblocking(connection.get(), 1) != 0)
    {
        throw runtime_error(PQerrorMessage(connection.get()));
    }
}

shared_ptr<PGconn> DBConnection::get_connection() const
{
    return connection;
}*/