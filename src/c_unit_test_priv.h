/**
  \file c_unit_test_priv.h

  \brief Private functions for calling CUnitTest interface

  \author tlammi
*/
#ifndef C_UNIT_TEST_PRIV_H
#define C_UNIT_TEST_PRIV_H

/**
  \brief Register failure in an assertion with info

  \param info_str - Info string containing info about failure
*/
void __CUnitTest_registerFailure(const char* info_str);

#endif
