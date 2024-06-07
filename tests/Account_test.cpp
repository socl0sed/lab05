#include "gtest/gtest.h"
#include "../banking/Account.h"
#include "../banking/Transaction.h"

// Test for Account class
TEST(AccountTest, Constructor) {
    Account account(1, 1000);
    EXPECT_EQ(account.GetBalance(), 1000);
    EXPECT_FALSE(account.is_locked_);
}

TEST(AccountTest, ChangeBalance) {
    Account account(1, 1000);
    account.Lock();
    account.ChangeBalance(500);
    EXPECT_EQ(account.GetBalance(), 1500);
}

TEST(AccountTest, LockAndUnlock) {
    Account account(1, 1000);
    account.Lock();
    EXPECT_TRUE(account.is_locked_);
    account.Unlock();
    EXPECT_FALSE(account.is_locked_);
}

// Test for Transaction class

TEST(TransactionTest, InvalidTransaction) {
    Account account1(1, 1000);
    Account account2(1, 500); // Same account ID
    Transaction transaction;

    EXPECT_THROW(transaction.Make(account1, account2, 200), std::logic_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
