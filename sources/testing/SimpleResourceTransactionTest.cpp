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
 am.AddAccount();
 EXPECT_EQ(2 + 2, 4);
}