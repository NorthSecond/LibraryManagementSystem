#pragma once
#include <QDatetime>

class PunishInfo
{
private:
    unsigned long long id;
    unsigned long long book_index;
    unsigned long long user_id;
	QDateTime punish_time;
	int punish_type;
	int punish_status;
    
public:
    PunishInfo();
	PunishInfo(unsigned long long id, unsigned long long book_index, unsigned long long user_id, QDateTime punish_time, int punish_type, int punish_status);
	unsigned long long get_id();
	unsigned long long get_book_index();
	unsigned long long get_user_id();
	QDateTime get_punish_time();
	int get_punish_type();
	int get_punish_status();

	void set_punish_status(int punish_status);
};

