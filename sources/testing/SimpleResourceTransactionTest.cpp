#include "SimpleResourceTransactionTest.h"
#include "utility/transactionblob.h"

TEST(SimpleResourceTransactionTest, FirstTest) {
 //Add two new accounts
 //Define a new resource
 //Give the first account 500 units of the resource
 //The first account transfers 400 units of the resource to the second account
 //Verify the first account now has 100 units of resource
 //Verify the second account now has 400 units of the resource
 
 AccountManager am;
 Client clientA;
 Client clientB;
 EXPECT_EQ(am.Accounts, 0);
 am.AddAccount(clientA);
 am.AddAccount(clientB);
 EXPECT_EQ(am.Accounts, 2);
 
 Resource gold;
 gold.addField("Value");
 
 Asset asset = gold();
 asset.set("Value", 500);
 am.CreateAsset(gold, clientA, asset);
 
 EXPECT_EQ(am.QUERY(gold, "Value"), 500);
 am.TransferAsset(gold, clientA, clientB, 400);
 
 //Attempting to add duplicate accounts here should be ignored
 am.AddAccount(clientA);
 am.AddAccount(clientB);
 
 EXPECT_EQ(am.QUERY(clientA, gold, "Value"), 100);
 EXPECT_EQ(am.QUERY(clientB, gold, "Value"), 400);
}