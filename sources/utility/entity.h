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
//
//   Level Two comprrises automating and combining the "Packet" primitive to simulate
//   basic social and financial institutions.
//   Practically speaking this means making a small API and a simple .proto around the 
//   "Message" portion of "Packet".
//
//   E.g. Market. 
//   Market allows Clients to submit Packets. It provides two functions.
//     1. Passive matching and signing of Packets.
//     2. A "Book" of depth n. Clients peruse books for Packets, then sign and execute satisfactory contracts.
//
//   Impl. 1: clients are able to temporarily delegate their authority to sign ks to Market
//   Impl. 2: clients only ever make ks with Market. Market acts as intermediary for all transactions.
//
//   To dig further into Impl. 1, there are two ways that come to mind. 
//  a. Client A goes to Market. Client A creates new entity, ClientA_at_Market. Gives Market private key for this entity.
//     ClientA makes certain ks with ClientA_at_Market (limited liability funding).
//     Market goes ahead and signs whatever Ks it wants on behalf of ClientA_at_Market. A on hook to extent of liability.
// 
//  b. [the more attractive] To delegate packet authority, the signer merely lists you as a required authenticator!
//     E.g. A tells Market: enter me into binding buy and sell agreements I'd find advantageous.
//     Market engages in transactions where A is listed as a required signing authority on packets.
//     A incurs a monitoring cost- A shouldn't sign all packets without inspecting them, but it probably
//     doesn't have to inspect all of them before it signs because of CBA


#endif