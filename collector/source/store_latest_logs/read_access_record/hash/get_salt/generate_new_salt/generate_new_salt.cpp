#include "generate_new_salt.h"
#include <sodium.h>
using namespace std;

string generate_new_salt()
{
  unsigned char saltBuffer[crypto_generichash_KEYBYTES];
  randombytes_buf(saltBuffer, crypto_generichash_KEYBYTES);

  return string((char *)saltBuffer, crypto_generichash_KEYBYTES);
}