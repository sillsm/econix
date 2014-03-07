// Copyright 2014 Max Sills. Please see root directory for applicable licenses. 

#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>

#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
/*
/  Blob of definitions and logic for simple transactions
/  To be refactored when I figure out what I'm doing
*/

using namespace std;

class CryptographicEntity{
  
  public:
	std::string PublicKey;
	std::string PrivateKey;

	CryptographicEntity(){
		int KEY_LENGTH = 1024;
		int PUB_EXP = 3;
		RSA *keypair = RSA_generate_key(KEY_LENGTH, PUB_EXP, NULL, NULL);

		BIO *pri = BIO_new(BIO_s_mem());
		BIO *pub = BIO_new(BIO_s_mem());

		PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
		PEM_write_bio_RSAPublicKey(pub, keypair);

		std::size_t pri_len = BIO_pending(pri);
		std::size_t pub_len = BIO_pending(pub);

		char *pri_key =(char *)  malloc(pri_len + 1);
		char *pub_key =(char *) malloc(pub_len + 1);

		BIO_read(pri, pri_key, pri_len);
		BIO_read(pub, pub_key, pub_len);

		pri_key[pri_len] = '\0';
		pub_key[pub_len] = '\0';

	    printf("\n%s\n%s\n", pri_key, pub_key);
		PublicKey = std::string(pub_key);
		PrivateKey = std::string(pri_key);
	}

};

class Client : public CryptographicEntity{



};
//TODO: refactor for asset factory separate from asset packets
//TODO: incorporate a JSON read/write small lib
class Resource : public CryptographicEntity{	
  public:
	  std::unordered_map<std::string, std::size_t> m_Packet;
};

class ResourceFactory : public CryptographicEntity{
  public:
	  ResourceFactory(){

	  }
	  Resource MakeResource(std::string str, std::size_t val){
		  Resource ret;
		  ret.PublicKey = PublicKey;
		  ret.PrivateKey = "";
		  ret.m_Packet[str] = val;
		  return ret;
	  }
};

class AccountManager: public CryptographicEntity
{ 
  private:
    //Just to ensure openssl's working properly
    //SHA256_CTX state;
	  std::unordered_map<std::string, std::unordered_map<std::string, double>> Accounts;
  public:
    void AddAccount(Client & cl){
	/*
	/ Make a new Account for user
	/ Generate a key-pair. Give client one, store the other
	/ When client tries to do stuff, they give you their public key
	/ Use it as a hash value to look up their account info
	*/
	}

	std::size_t AccountsSize(){
		return Accounts.size();
	}

	void TransferAsset(Resource res, Client client){

	}

	void TransferAsset(Resource res, Client from, Client to){

	}

	std::size_t QueryAsset(ResourceFactory res, std::string){

		return 0;
	}

	std::size_t QueryClient(ResourceFactory res, std::string, Client client){
		return 0;
	}

};

