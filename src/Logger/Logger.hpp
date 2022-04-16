#pragma once
#include <iostream>
#include <type_traits>
#include "../GlobalParams.hpp"

namespace Logger{
	template <unsigned int n> using STRING_LITERAL = char[n];
	using CONST_CHAR_PTR = const char*;

	static inline std::string backLog;
	inline void log_(const std::string& val, bool nl){
		if(GlobalParams::debug){
			std::cout<<val;
			if(nl)
				std::cout<<std::endl;
		}
		backLog += val;
		if(nl)
			backLog += "\n";
	}
	template<typename T> inline void log_(const T& val, bool nl = true){
		if constexpr(std::is_pointer<T>::value){	
			std::string strT = std::to_string((size_t)((void*)val));
			log_(strT, nl);
		}else{
			std::string strT = std::to_string(val);
			log_(strT, nl);
		}
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
}
