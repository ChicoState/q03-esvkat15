/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}

// simple correct password check
TEST(GuesserTest, simple_correct_pw)
{
  Guesser object("Secret");
  ASSERT_TRUE( object.match("Secret") );
}

// simple correct password check with truncation
TEST(GuesserTest, simple_correct_pw_trunc)
{
  Guesser object("SecretSecretSecretSecretSecretSecret");
  ASSERT_TRUE( object.match("SecretSecretSecretSecretSecretSe") );
}

// simple incorrect password check with truncation
TEST(GuesserTest, simple_incorrect_pw_trunc)
{
  Guesser object("SecretSecretSecretSecretSecretSecret");
  ASSERT_FALSE( object.match("SecretSecretSecretSecretSecretSecret") );
}

// 1 character difference test, lowercase
TEST(GuesserTest, simple_incorrect_pw_1ch_mistake1)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("Secretsecret") );
}

// 1 character difference test, uppercase
TEST(GuesserTest, simple_incorrect_pw_1ch_mistake2)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("SecRetSecret") );
}

// 1 character difference test, special char
TEST(GuesserTest, simple_incorrect_pw_1ch_mistake3)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("Secret$ecret") );
}

// 1 character difference test, 1 less
TEST(GuesserTest, simple_incorrect_pw_1len_mistake1)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("SecretSecre") );
}

// 1 character difference test, 1 more
TEST(GuesserTest, simple_incorrect_pw_1len_mistake2)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("SecretSecrett") );
}

// correct match test with 1 close guesses
TEST(GuesserTest, simple_correct_pw_1_guess)
{
  Guesser object("SecretSecret");
  object.match("SecretSecrett");
  ASSERT_TRUE( object.match("SecretSecret") );
}

// correct match test with 2 close guesses
TEST(GuesserTest, simple_correct_pw_2_guess)
{
  Guesser object("SecretSecret");
  object.match("SecretSecre");
  object.match("SecretSecrett");
  ASSERT_TRUE( object.match("SecretSecret") );
}

// incorrect match test with 3 close guesses
TEST(GuesserTest, simple_incorrect_pw_3_guess)
{
  Guesser object("SecretSecret");
  object.match("SecretSecre");
  object.match("SecretSecrett");
  object.match("SecretSecreT");
  ASSERT_FALSE( object.match("SecretSecret") );
}

// test that guesses reset
TEST(GuesserTest, correct_pw_reset_test)
{
  Guesser object("SecretSecret");
  object.match("SecretSecre");
  object.match("SecretSecrett");
  object.match("SecretSecret");
  object.match("SecretSecrett");
  object.match("SecretSecr3t");
  ASSERT_TRUE( object.match("SecretSecret") );
}

// remaining test with 0 close guesses
TEST(GuesserTest, simple_remaining_pw_0_guess)
{
  Guesser object("SecretSecret");
  ASSERT_EQ( object.remaining(), 3 );
}

// remaining test with 1 close guesses
TEST(GuesserTest, simple_remaining_pw_1_guess)
{
  Guesser object("SecretSecret");
  object.match("SecretSecrett");
  ASSERT_EQ( object.remaining(), 2 );
}

// remaining test with 2 close guesses
TEST(GuesserTest, simple_remaining_pw_2_guess)
{
  Guesser object("SecretSecret");
  object.match("SecretSecre");
  object.match("SecretSecrett");
  ASSERT_EQ( object.remaining(), 1 );
}

// remaining test with 3 close guesses
TEST(GuesserTest, simple_remaining_pw_3_guess)
{
  Guesser object("SecretSecret");
  object.match("SecretSecre");
  object.match("SecretSecrett");
  object.match("SecretSecreT");
  ASSERT_EQ( object.remaining(), 0 );
}

// test that guesses reset
TEST(GuesserTest, remaining_pw_reset_test)
{
  Guesser object("SecretSecret");
  object.match("SecretSecre");
  object.match("SecretSecrett");
  object.match("SecretSecret");
  ASSERT_EQ( object.remaining(), 3 );
}