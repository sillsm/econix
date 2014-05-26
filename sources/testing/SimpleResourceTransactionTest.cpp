#include "SimpleResourceTransactionTest.h"
#include "utility/transactionblob.h"
#include <boost/system/error_code.hpp> 

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
 EXPECT_EQ(am.AccountsSize(), 0);
 am.AddAccount(clientA);
 am.AddAccount(clientB);
 EXPECT_EQ(am.AccountsSize(), 2);
 
 ResourceFactory gold;
 Resource assetA = gold.MakeResource("Value", 500);

 am.TransferAsset(assetA, clientA);
 EXPECT_EQ(am.QueryAsset(gold, "Value"), 500);
 EXPECT_EQ(am.QueryClient(gold, "Value", clientA), 500);
 EXPECT_EQ(am.QueryClient(gold, "Value", clientB), 0);
 
 //Attempting to add duplicate accounts here should be ignored
 am.AddAccount(clientA);
 am.AddAccount(clientB);

 Resource assetB = gold.MakeResource("Value", 400);
 am.TransferAsset(assetB, clientA, clientB);
 EXPECT_EQ(am.QueryAsset(gold, "Value"), 500);
 EXPECT_EQ(am.QueryClient(gold, "Value", clientA), 100);
 EXPECT_EQ(am.QueryClient(gold, "Value", clientB), 400);

 //Try transfering resource from non-registered client; account error should be thrown and caught
}
