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

// simple correct password check
TEST(GuesserTest, simple_correct_pw_empty)
{
  Guesser object("");
  ASSERT_TRUE( object.match("") );
}

// simple correct password check
TEST(GuesserTest, simple_incorrect_pw_empty)
{
  Guesser object("");
  ASSERT_FALSE( object.match("frog") );
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

// 2 character difference test, 2 less
TEST(GuesserTest, simple_incorrect_pw_2len_mistake1)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("SecretSecr") );
}

// 2 character difference test, 2 more
TEST(GuesserTest, simple_incorrect_pw_2len_mistake2)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("SecretSecrett%") );
}

// 2 character difference test, 1 ch 1 less
TEST(GuesserTest, simple_incorrect_pw_1ch_1len_mistake1)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("Secre1Secre") );
}

// 2 character difference test, 1 ch 1 more
TEST(GuesserTest, simple_incorrect_pw_1ch_1len_mistake2)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("Secret5ecret%") );
}

// 3 character difference test, 3 less
TEST(GuesserTest, simple_incorrect_pw_3len_mistake1)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("SecretSec") );
}

// 3 character difference test, 3 more
TEST(GuesserTest, simple_incorrect_pw_3len_mistake2)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("SecretSecrett%5") );
}

// 3 character difference test, 2 more, 1 change
TEST(GuesserTest, simple_incorrect_pw_1ch_2len_mistake2)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("SecretSeCret%5") );
}

// 3 character difference test, 1 more, 2 change
TEST(GuesserTest, simple_incorrect_pw_2ch_1len_mistake)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("Secre5SeCret5") );
}

// length difference test, 100 more
TEST(GuesserTest, simple_incorrect_pw_100len_mistake)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("SecretSecrettYAYDHKN^*D*ndjdjskhfbjhbfdshjbfsdhhfYH3fdbjhjfdsjhbfdsjhbdstYAYDHKN^*D*ndjdjskhfbjhbfdshjbfsdhhfbjh") );
}

// length difference test, empty str
TEST(GuesserTest, simple_incorrect_pw_0len_mistake)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("") );
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

// remaining test with 1 far guess
TEST(GuesserTest, simple_remaining_pw_1far)
{
  Guesser object("SecretSecret");
  object.match("SecreTsecrett");
  ASSERT_EQ( object.remaining(), 2 );
}

// remaining test with 1 far guess then 1 close guess
TEST(GuesserTest, simple_remaining_pw_1far_1guess)
{
  Guesser object("SecretSecret");
  object.match("SecretSeC#ett");
  object.match("SecretSecre");
  ASSERT_EQ( object.remaining(), 1 );
}

// remaining test with 1 close guess then 1 far guess
TEST(GuesserTest, simple_remaining_pw_1guess_1far)
{
  Guesser object("SecretSecret");
  object.match("secretSecret");
  object.match("SecREtSecre");
  ASSERT_EQ( object.remaining(), 1 );
}

// remaining test with 2 close guesses then 1 far guess
TEST(GuesserTest, simple_remaining_pw_2guess_1far)
{
  Guesser object("SecretSecret");
  object.match("SecretSecre");
  object.match("SecretSecrett");
  object.match("SecreTSecreTt");
  ASSERT_EQ( object.remaining(), 0 );
}

// remaining test with 1 far guess then 2 close guesses
TEST(GuesserTest, simple_remaining_pw_1far_2guess)
{
  Guesser object("SecretSecret");
  object.match("SecreTSecre5t");
  object.match("SecretSecre");
  object.match("SecretSecrett");
  ASSERT_EQ( object.remaining(), 0 );
}

// test that guesses do not reset on a brute force
TEST(GuesserTest, remaining_pw_fake_reset_test)
{
  Guesser object("SecretSecret");
  object.match("SecretSecre");
  object.match("SecreTsecrett");
  object.match("SecretSecret");
  ASSERT_EQ( object.remaining(), 0 );
}

// match test with 1 far guess
TEST(GuesserTest, simple_match_pw_1far)
{
  Guesser object("SecretSecret");
  ASSERT_FALSE( object.match("SecreTsecrett") );
}

// match test with 1 far guess then 1 close guess
TEST(GuesserTest, simple_match_pw_1far_1guess)
{
  Guesser object("SecretSecret");
  object.match("SecretSeC#ett");
  ASSERT_FALSE( object.match("SecretSecre") );
}

// match test with 1 close guess then 1 far guess
TEST(GuesserTest, simple_match_pw_1guess_1far)
{
  Guesser object("SecretSecret");
  object.match("secretSecret");
  ASSERT_FALSE( object.match("SecREtSecre") );
}

// match test with 2 close guesses then 1 far guess
TEST(GuesserTest, simple_match_pw_2guess_1far)
{
  Guesser object("SecretSecret");
  object.match("SecretSecre");
  object.match("SecretSecrett");
  ASSERT_FALSE( object.match("SecreTSecreTt") );
}

// match test with 1 far guess then 2 close guesses
TEST(GuesserTest, simple_match_pw_1far_2guess)
{
  Guesser object("SecretSecret");
  object.match("SecreTSecre5t");
  object.match("SecretSecre");
  ASSERT_FALSE( object.match("SecretSecrett") );
}

// test that guesses do not match on a brute force
TEST(GuesserTest, match_pw_fake_reset_test1)
{
  Guesser object("SecretSecret");
  object.match("SecretSecre");
  object.match("SecreTsecrett");
  ASSERT_FALSE( object.match("SecretSecret") );
}

// test that guesses do not match on a brute force
TEST(GuesserTest, match_pw_fake_reset_test2)
{
  Guesser object("SecretSecret");
  object.match("SecretSecre");
  object.match("SecreTsecrett");
  object.match("SecretSecret");
  object.match("SecreTsecrett");
  object.match("SecretSecre");
  ASSERT_FALSE( object.match("SecretSecret") );
}