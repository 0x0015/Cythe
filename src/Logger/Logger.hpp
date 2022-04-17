#pragma once
#include <iostream>
#include <type_traits>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "../GlobalParams.hpp"

namespace Logger{
	template <unsigned int n> using STRING_LITERAL = char[n];
	using CONST_CHAR_PTR = const char*;
	static inline std::ofstream backLog;
	static inline bool recordToFile = true;
	inline void endLogger(){//I know it's horrible, but I can't call this so the last thing to happen is for the log file to be closed.
		if(recordToFile){
			backLog.close();
		}
	}
	inline void log_(const std::string& val, bool nl){
		if(GlobalParams::debug){
			std::cout<<val;
			if(nl)
				std::cout<<std::endl;
		}
		backLog << val;
		if(nl)
			backLog << "\n";
	}
	template<typename T> inline void log_(const T& val, bool nl = true){
		std::ostringstream oss;
		oss << val;
		log_(oss.str(), nl);
		/*
		if constexpr(std::is_pointer<T>::value){
			std::ostringstream oss;
			oss << (void*)val;
			//std::string strT = std::to_string((size_t)((void*)val));
			log_(oss.str(), nl);
		}else{
			std::string strT = std::to_string(val);
			log_(strT, nl);
		}
		*/
	}
	template<unsigned int n> inline void log_(const STRING_LITERAL<n>& val, bool nl){
		log_(std::string(val), nl);
	}
	inline void log_(const CONST_CHAR_PTR& val, bool nl){
		log_(std::string(val), nl);
	}
	template<typename T> inline void log(const T& val, bool nl = true){
		log_(val, nl);
	}
	template<typename T, typename... Types> inline void log(const T& var1, Types... var2){
		log<T>(var1, false);
		log(var2...);
	}
	inline void initLogger(){
		if(recordToFile){
			backLog.open("Cythe.log", std::ios_base::app);
		}
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		log("===",std::put_time(&tm, "%d-%m-%Y %H:%M:%S"),"===");
		log("Successfully initialized logger!");
	}
}
