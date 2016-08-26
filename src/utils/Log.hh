////////////////////////////////////////////////////////////
//
//-------------------By MonkeyPac and HadesFufu-------------
// >French<
//Utilisation : 
// Permet d'écrire des messages préconçus dans la console
// mais aussi dans un fichier nommé : "log.txt" dans la racine
// de l'execution. 
////////////////////////////////////////////////////////////


#ifndef DEF_LOGGER
#define DEF_LOGGER

#include <iostream>
#include <fstream>
#include <string>

#include "board/board.hh"

class Log
{
public:
	////////////////////////////
	// Enum for various logging levels
	// Levels are explicits.
	////////////////////////////
	
	static Log&				debug(std::string classe = "N/A", bool Log = true);
	static Log&				info(std::string classe = "N/A", bool Log = true);
	static Log&				warning(std::string classe = "N/A", bool Log = true);
	static Log&				error(std::string classe = "N/A", bool Log = true);
	static Log&				waypoint(std::string classe = "N/A", bool Log = true);
	static Log&				print(bool Log = true);
	////////////////////////////
	//@effect : reset the Waypoint iterator.
	////////////////////////////
	static void				resetWaypoint();
	////////////////////////////
	//@return : member function for "\n"
	////////////////////////////
	static const char*		endl;
	////////////////////////////
	//operator overload for all basics types.
	//
	////////////////////////////

	static void clearInstance(){
		delete m_instance;
	}

	Log& operator <<(bool               data);
	Log& operator <<(float              data);
	Log& operator <<(int	            data);
	Log& operator <<(unsigned int	    data);
	Log& operator <<(double				data);
	Log& operator <<(const char*		data);
	Log& operator <<(std::string		data);

	Log& operator<< (std::ostream& (*pf)(std::ostream&));

	Log& operator <<(Board& data);
	
private:
	enum Level
	{
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		WAYPOINT,
		PRINT
	};
	//Contructors are private so they can't be used
	Log();
	Log(Log const&);

	//Destructors
	~Log();

	//Draw logs
	Log& Draw(Level, std::string classe = "N/A", bool Log = true);

	//Singleton Instance controlle function
	static Log* Instance();

	//Operator rebind is private
	Log& operator=(Log const&){};
	
	//Stream to the log file
	std::fstream logFile;

	//File name
	static std::string fileName;
	
	//Level char tab
	const char* levels[5];

	//Singleton Instance controller
	static Log* m_instance;

	//for Waypointing
	int	m_currentWaypoint;
};

#endif


