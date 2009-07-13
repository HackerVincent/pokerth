/***************************************************************************
 *   Copyright (C) 2007 by Lothar May                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef POKERTH_DEDICATED_SERVER
#error This file is only for the server.
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)
#endif

#include <core/loghelper.h>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/date_time.hpp>


using namespace std;
using namespace boost::filesystem;
using namespace boost::posix_time;

#define SERVER_MSG_LOG_FILE_NAME				"server_messages.log"

static string g_logFile;
static int g_logLevel = 1;

void
loghelper_init(const string &logDir, int logLevel)
{
	path tmpLogFile(logDir);
	tmpLogFile /= SERVER_MSG_LOG_FILE_NAME;

	g_logFile = tmpLogFile.directory_string();
	g_logLevel = logLevel;
}

void
internal_log_err(const string &msg)
{
	if (!g_logFile.empty())
	{
		ofstream o(g_logFile.c_str(), ios_base::out | ios_base::app);
		if (!o.fail())
		{
			o << second_clock::local_time() << " ERR: " << msg;
			o.flush();
		}
	}
}

void
internal_log_msg(const std::string &msg)
{
	if (g_logLevel)
	{
		if (!g_logFile.empty())
		{
			ofstream o(g_logFile.c_str(), ios_base::out | ios_base::app);
			if (!o.fail())
				o << second_clock::local_time() << " MSG: " << msg;
		}
	}
}

void
internal_log_level(const std::string &msg, int logLevel)
{
	if (g_logLevel >= logLevel)
	{
		if (!g_logFile.empty())
		{
			ofstream o(g_logFile.c_str(), ios_base::out | ios_base::app);
			if (!o.fail())
				o << second_clock::local_time() << " OUT: " << msg;
		}
	}
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

