// Copyright 2014 Max Sills. Please see root directory for applicable licenses. 

#ifndef _UTILITY_ENTITY_H
#define _UTILITY_ENTITY_H

#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>

// An Entity can do two things: Send and Receive Packets.
// A Packet has the following attributes: 
// 1. list of its required Signers by pub-key
// 2. unique Token
// [Impl. note: ideally the message format is a proto but need to find
// 1. Reliable conversion to and from json
// 2. Open RPC framework I can trust
// Sample Workflow:
// A sends B a packet, x.
// x has a MESSAGE_PORTION_W_TOKEN_And_Signers | DELIMITER | signed hash
//  Sample Message:
// {  Message: "I want to deposit 30 units of resource with you", 
//    [optional]: timestamp,
//    [optional]: expiration date,
//    Unique_Token: szhgzajq2fxl6nwy,
//    Approvers by Pub_key (they need to sign message hash):
//    igc9kvwhuyjfv9krnqeil8psm7djvbyr, "Game Bank"
//    6wcrfljoZc7qgyhNKyUnBtSNUFjoIhvM, "Player-run better biz bureau"
//    
//    MessageHash: Dy6pbdsyaxEoEg3NUR3mmsDqevQfVgWv
//    SignatureList {
//         Identitiy: [A]
//         Signature of Msg Hash: dgABepWiAaAjfLynedruSlkr3Dnf9ups
//               }
//    B either agrees or disagrees
//    If B agrees: mirrors message but adds the required approvers signature
//
//


#endif
