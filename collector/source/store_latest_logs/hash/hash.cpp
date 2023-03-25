#include "hash.h"
#include <openssl/sha.h>
using namespace std;

string hash(string string_to_hash, string salt)
{
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX context;

  SHA256_Init(&context);
  SHA256_Update(&context, string_to_hash.c_str(), string_to_hash.length());
  SHA256_Update(&context, salt.c_str(), salt.length());
  SHA256_Final(hash, &context);

  string hashed_string((char *)hash, SHA256_DIGEST_LENGTH);
  return hashed_string;
};