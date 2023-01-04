#pragma once

namespace User{
    enum Role{
        STUDENT,
        TEACHER,
        ADMIN,
        OUTCOME
    };

    enum Status{
        Normal,
        Exhausted,
        Banned
    };

}

class UserInfo
{
private:
    unsigned long long user_id;
    User::Role user_role;
    User::Status user_status;
    unsigned int borrowed_num;
public:
    UserInfo(unsigned long long user_id, User::Role user_role, User::Status user_status);
    UserInfo();
    bool commitToDB();

};

