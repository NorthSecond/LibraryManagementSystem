#include "punishinfo.h"

PunishInfo::PunishInfo()
{

}

PunishInfo::PunishInfo(unsigned long long id, unsigned long long book_index, unsigned long long user_id, QDateTime punish_time, int punish_type, int punish_status)
	: id(id), book_index(book_index), user_id(user_id), punish_time(punish_time), punish_type(punish_type), punish_status(punish_status)
{

}

unsigned long long PunishInfo::get_id()
{
	return id;
}

unsigned long long PunishInfo::get_book_index()
{
	return book_index;
}

unsigned long long PunishInfo::get_user_id()
{
	return user_id;
}

QDateTime PunishInfo::get_punish_time()
{
	return punish_time;
}

int PunishInfo::get_punish_type()
{
	return punish_type;
}

int PunishInfo::get_punish_status()
{
	return punish_status;
}

void PunishInfo::set_punish_status(int punish_status)
{
	this->punish_status = punish_status;
}
