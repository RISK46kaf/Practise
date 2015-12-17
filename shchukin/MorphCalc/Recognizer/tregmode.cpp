#include "tregmode.h"

using namespace Recognizer;

TRegMode::TRegMode():
             last_all(false),last_extunique(false),last_ext(false),
             last_intunique(false),last_int(false),
             LastAll(last_all),LastExtUnique(last_extunique),LastExt(last_ext),
             LastIntUnique(last_intunique),LastInt(last_int)
{}

TRegMode::TRegMode(const TRegMode& RM):
             last_all(RM.last_all),last_extunique(RM.last_extunique),last_ext(RM.last_ext),
             last_intunique(RM.last_intunique),last_int(RM.last_int),
             LastAll(last_all),LastExtUnique(last_extunique),LastExt(last_ext),
             LastIntUnique(last_intunique),LastInt(last_int)
{}

TRegMode& TRegMode::operator=(const TRegMode& RM)
{
  last_all=RM.last_all;
  last_extunique=RM.last_extunique;
  last_ext=RM.last_ext;
  last_intunique=RM.last_intunique;
  last_int=RM.last_int;
  return *this;
}

void TRegMode::SetLast()
{
 last_all=All;
 last_extunique=ExtUnique;
 last_ext=Ext;
 last_intunique=IntUnique;
 last_int=Int;
}
