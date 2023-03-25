#include "record_in_list.h"
using namespace std;

bool record_in_list(access_record record, vector<access_record> list)
{
  for (access_record item : list)
  {
    if (item.full_text == record.full_text)
      return true;
  }

  return false;
};