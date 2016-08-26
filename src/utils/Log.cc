/**
 * \file Log.cpp
 * \author Monkeypac
 */

#include "Log.hh"

Log* Log::m_instance = NULL; /// Global static pointer to ensure the singleton pattern of the class
std::string Log::fileName = "log.txt"; ///Global static var to save log file name
const char*	Log::endl = "\n";

/**
 * Constructor inits log file stream and Level string correspondance array
 */
Log::Log() : m_currentWaypoint(0)
{
	//Open log file
	logFile.open(fileName, std::ios::out);
	levels[0] = "Debug";
	levels[1] = "Info";
	levels[2] = "Warning";
	levels[3] = "Error";
	levels[4] = "Waypoint";
}

/**
 * Constructor
 */
Log::Log(Log const& log) : m_currentWaypoint(0)
{
	Log();
}

/**
 * Destructor cleans every thing used in memory stack
 */
Log::~Log()
{
	logFile.close();
}

/**
 * Returns the only instance of the class running or runs a new one if not yet launched
 *
 * @return the only instance of the class running
 */
Log* Log::Instance()
{
	//Only allow one instance of the class to be running
	if(!m_instance)
	{
		m_instance = new Log();	
	}

	return m_instance;
}
void Log::resetWaypoint(){
	Instance()->m_currentWaypoint = 0;
}

Log& Log::Draw(Level level, std::string className, bool log){
	if (level != PRINT) {
		if (log){
			logFile << std::endl << levels[level] << " (" << className << "): ";
		}
		std::cout << std::endl << levels[level] << " (" << className << "): ";
		if (level == WAYPOINT){
			logFile << m_currentWaypoint;
			std::cout << m_currentWaypoint;
			m_currentWaypoint++;
		}
	}
	return *m_instance;
}
Log& Log::debug(std::string message, bool log){
	return Log::Instance()->Draw(DEBUG, message, log);
}
Log& Log::info(std::string message, bool log){
	return Log::Instance()->Draw(INFO, message, log);
}
Log& Log::warning(std::string message, bool log){
	return Log::Instance()->Draw(WARNING, message, log);
}
Log& Log::error(std::string message, bool log){
	return Log::Instance()->Draw(ERROR, message, log);
}
Log& Log::waypoint(std::string message, bool log){
	return Log::Instance()->Draw(WAYPOINT, message, log);
}
Log& Log::print(bool log){
	return Log::Instance()->Draw(PRINT, "", log);
}
Log& Log::operator <<(bool                data){
	if (data){
		logFile << "True ";
		std::cout << "True ";
	}
	else{
		logFile << "False ";
		std::cout << "False ";
	}
	return *this;
}

Log& Log::operator <<(float               data){
	logFile << data << " ";
	std::cout << data << " "; 
	return *this;
}

Log& Log::operator <<(int	              data){
	logFile << data << " ";
	std::cout << data << " ";
	return *this;
}

Log& Log::operator <<(unsigned int	     data){
	logFile << data << " ";
	std::cout << data << " ";
	return *this;
}


Log& Log::operator <<(double              data){
	logFile << data << " ";
	std::cout << data << " ";
	return *this;
}


Log& Log::operator <<(const char*         data){
	logFile << data << " ";
	std::cout << data << " ";
	return *this;
}

Log& Log::operator <<(std::string  data){
	logFile << data << " ";
	std::cout << data << " ";
	return *this;
}

Log& Log::operator <<(std::ostream& (*data)(std::ostream&)){
	logFile << data;
	std::cout << data;
	return *this;
}

Log& Log::operator <<(Board& data){
	data.print(logFile);
	data.print(std::cout);
	return *this;
}
