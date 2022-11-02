#include "Exception.h"
#include<iostream>
#include<string.h>
using namespace std;
namespace FinlayLib {
	void Exception::init(const char* message, const char* file, int line) {
		if (message != NULL) {
			m_message = (message ? strdup(message) : NULL);
		}
		if (file != NULL) {
			char sl[16] = { 0 };
			//itoa(line, sl, 10);
			snprintf(sl,16,"%d",line);
			m_location =(char*) malloc(strlen(file)+strlen(sl)+2);
			if (m_location != NULL) {
				m_location = strcpy(m_location, file);
				m_location = strcat(m_location, ":");
				m_location = strcat(m_location, sl);
			}
	
		}
		else
		{
			m_location = NULL;
		}
	}

	Exception::Exception(const char* message) {
		init(message, NULL, NULL);
	}
	Exception::Exception(const char* file, int line) {
		init(NULL, file, line);
	}
	Exception::Exception(const char* message, const char* file, int line) {
		init(message, file, line);
	}
	Exception::Exception(const Exception& e) {
		m_message = strdup(e.m_location);
		m_location = strdup(e.m_location);
	}
	Exception& Exception::operator=(const Exception& e) {
		if (this != &e) {
			free(m_location);
			free(m_message);
			m_message = strdup(e.m_location);
			m_location = strdup(e.m_location);
		}
		return *this;
	}

	const char* Exception::message()const{
		return m_message;
	}
	const char* Exception::location()const {
		return m_location;
	}
	Exception::~Exception() {
		free(m_location);
		free(m_message);
	}
}
