#include "pad_left.h"

string pad_left(string unpadded, char padding, int target_length)
{
  int unpadded_length = unpadded.length();
  int number_of_padding_characters = target_length - min(target_length, unpadded_length);

  return string(number_of_padding_characters, padding) + unpadded;
};