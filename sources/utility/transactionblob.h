// Copyright 2014 Max Sills. Please see root directory for applicable licenses. 

#pragma once
#include <memory>
#include <iostream>
#include <string>
/*
/  Blob of definitions and logic for simple transactions
/  To be refactored when I figure out what I'm doing
*/

class AccountManager
{
  public:
    void AddAccount(void){
	/*
	/ Make a new Account for user
	/ Generate a key-pair. Give client one, store the other
	/ When client tries to do stuff, they give you their public key
	/ Use it as a hash value to look up their account info
	*/
	  std::cout << "Make a new Account for user" << std::endl;
	  std::cout << "Generate a key-pair. Give client one, store the other" << std::endl;
	  std::cout << "When client tries to do stuff, they give you their public key" << std::endl;
	  std::cout << "Use it as a hash value to look up their account info" << std::endl;
	}

};