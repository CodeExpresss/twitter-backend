#ifndef DBCONNECTION_HPP
#define DBCONNECTION_HPP

#include <memory>
#include <string>
#include <libpq-fe.h>

using namespace std;

class DBConnection
{
public:
    DBConnection(const string& host, const string& dbname, const string& user, 
                 const string& password, int port) {
        connection.reset(PQsetdbLogin(host.c_str(), to_string(port).c_str(),
                                      nullptr, nullptr, dbname.c_str(), user.c_str(),
                                      password.c_str()), &PQfinish);

        if (PQstatus(connection.get()) != CONNECTION_OK && PQsetnonblocking(connection.get(), 1) != 0 )
        {
            throw runtime_error(PQerrorMessage(connection.get()));
        }
    }

    ~DBConnection() = default;
    
    shared_ptr<PGconn> get_connection() const
    {
        return connection;
    }

private:
    shared_ptr<PGconn> connection;
};

#endif