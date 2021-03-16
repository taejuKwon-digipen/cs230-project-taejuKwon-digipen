/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Logger.cpp
Project: CS230
Author: Taeju Kwon
Creation date:  2/10/2021
-----------------------------------------------------------------*/

#include <iostream>    // cout.rdbuf
#include "Logger.h"

CS230::Logger::Logger(Logger::Severity severity, bool useConsole) : minLevel(severity), outStream("Trace.log") {
	if (useConsole == true) {
		outStream.set_rdbuf(std::cout.rdbuf());
	}
}

CS230::Logger::~Logger() {
	outStream.flush();
	outStream.close();
}

void CS230::Logger::Log(CS230::Logger::Severity severity, std::string message) {
	
switch (severity)
{
	case Severity::Verbose:
	{
			std::string label = "Verb";
			switch (minLevel)
			{
			case Severity::Verbose:
				outStream << label + '\t' + message << std::endl;
			}
	}
	break;
	
	case Severity::Debug:
	{
		std::string label = "Debug";
		switch (minLevel)
		{
		case Severity::Verbose:
		case Severity::Debug:
			outStream << label + '\t' + message << std::endl;
		}
	}
	break;
	case Severity::Error:
	{
			std::string label = "Error";
			switch (minLevel)
			{
			case Severity::Verbose:
			case Severity::Debug:
			case Severity::Error:
			case Severity::Event:
				outStream << label + '\t' + message << std::endl;
			}
	}
	break;
	case Severity::Event:
	{
			std::string label = "Event";
			switch (minLevel)
			{
			case Severity::Verbose:
			case Severity::Debug:
			case Severity::Event:
				outStream << label + '\t' + message << std::endl;
			}
	}

	break;
	}

}