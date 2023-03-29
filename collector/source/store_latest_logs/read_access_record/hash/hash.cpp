#include "hash.h"
#include "get_salt/get_salt.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
using namespace std;

string hash(string string_to_hash, string timestamp, sqlite3 *database)
{
  string salt = get_salt(timestamp, database);

  // Get a pointer to the SHA256 digest algorithm.
  const EVP_MD *message_digest = EVP_sha256();

  // Allocate a buffer to hold the hash output.
  unsigned char hash[EVP_MAX_MD_SIZE];

  // The length of the hash output.
  unsigned int hash_length;

  // Create a new message digest context object.
  EVP_MD_CTX *context = EVP_MD_CTX_new();

  // Initialize the context with the digest algorithm.
  EVP_DigestInit_ex(context, message_digest, nullptr);

  // Update the context with the input data and salt.
  EVP_DigestUpdate(context, string_to_hash.c_str(), string_to_hash.length());
  EVP_DigestUpdate(context, salt.c_str(), salt.length());

  // Finalize the hash computation and store the output in the hash buffer.
  EVP_DigestFinal_ex(context, hash, &hash_length);

  // Free the message digest context object.
  EVP_MD_CTX_free(context);

  // Convert the hash buffer to a string and return it.
  string hashed_string((char *)hash, hash_length);
  return hashed_string;
};