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

#include <boost/system/error_code.hpp> //Boost Test
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

	    //printf("\n%s\n%s\n", pri_key, pub_key);
		PublicKey = std::string(pub_key);
		PrivateKey = std::string(pri_key);
		//std::cout << PublicKey << std::endl;
		//std::cout << PrivateKey << std::endl;
	}

};

class Client : public CryptographicEntity{



};
//TODO: refactor for asset factory separate from asset packets
//TODO: incorporate a JSON read/write small lib
//TODO: rewrite to support OpenPGP messages; reconsider public-key for every asset architecture
class Resource : public CryptographicEntity{	
  public:
	  std::unordered_map<std::string, double> m_Packet;
};

class ResourceFactory : public CryptographicEntity{
  public:
	  ResourceFactory(){

	  }
	  Resource MakeResource(std::string str, double val){
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
	  std::unordered_map<std::string, double> m_ResourceLedger;
  public:
    void AddAccount(Client & cl){
	/*
	/ Make a new Account for user
	/ Generate a key-pair. Give client one, store the other
	/ When client tries to do stuff, they give you their public key
	/ Use it as a hash value to look up their account info
	*/
		if (Accounts.find(cl.PublicKey) == Accounts.end()){
			std::unordered_map<std::string, double> addme;
			Accounts[cl.PublicKey] = addme;
		}
	}

	std::size_t AccountsSize(){
		return Accounts.size();
	}

	void TransferAsset(Resource res, Client & client){
		auto it = Accounts.find(client.PublicKey);
		if (it == Accounts.end()){ //Client not listed
			return;
		}
		else { //Client listed
			if ((it->second).find(res.PublicKey) == (it->second).end()){//client doesn't hve resource in ledger
				(it->second)[res.PublicKey] = res.m_Packet["Value"];
			}
			else{
				(it->second)[res.PublicKey] += res.m_Packet["Value"];
			}
			m_ResourceLedger[res.PublicKey] += res.m_Packet["Value"];
		}
	}

	void TransferAsset(Resource res, Client from, Client to){
		//Check that both client from and to exist.
		//if either does not, return
		auto fromit = Accounts.find(from.PublicKey);
		auto toit = Accounts.find(to.PublicKey);
		if (fromit == Accounts.end() || toit == Accounts.end()) return;

		auto value = res.m_Packet["Value"];

		//Check if 'from' has the resource
		//if not, assign from (-resource value)
		// else, -= froms resource value
		auto fromResource = Accounts[from.PublicKey].find(res.PublicKey);
		if (fromResource != Accounts[from.PublicKey].end())
			Accounts[from.PublicKey][res.PublicKey] -= value;
		else
			Accounts[from.PublicKey][res.PublicKey] = -value;

		//Check if 'to' has the resource
		//if not, assign 'to' (resource valu)
		//else, += to's resource value
		auto toResource = Accounts[to.PublicKey].find(res.PublicKey);
		if (toResource != Accounts[to.PublicKey].end())
			Accounts[to.PublicKey][res.PublicKey] += value;
		else
			Accounts[to.PublicKey][res.PublicKey] = value;

		return;

	}

	std::size_t QueryAsset(ResourceFactory res, std::string){
		if ((m_ResourceLedger).find(res.PublicKey) == (m_ResourceLedger).end()){ //don't got that resource
			return 0;
		}
		else{
			return m_ResourceLedger[res.PublicKey];
		}
	}

	std::size_t QueryClient(ResourceFactory res, std::string, Client client){
		//check if client listed
		//if so get their map
		//then query their resource
		//or return 0
		auto it = Accounts.find(client.PublicKey);
		if (it == Accounts.end()){ //Client not listed
			return 0;
		}
		else { //Client listed
			if ((it->second).find(res.PublicKey) == (it->second).end()){//client doesn't hve resource in ledger
				return 0;
			}
			else{
				//(it->second)[res.PublicKey] += res.m_Packet["Value"];
				return Accounts[client.PublicKey][res.PublicKey];
			}
			return 0;
		}
	}
};

