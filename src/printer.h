/**
  \file printer.h

  \brief Prints test results

*/
#ifndef PRINTER_H
#define PRINTER_H

#include "test_set.h"

/**
  \brief Format for printing test summary
*/
enum PrintFormat{
  PrintPlain = 1, ///< Print in plain format, i.e. information is separated by newlines and indentation
  PrintJSON = 2, ///< Print in JSON format
  PrintYAML = 3 ///< Print in YAML format
};


/**
  \brief Prints test results stored in linked list of TestSets

  \param list - List of Executed test sets
  \param print_format - Format the printing is produced

  \todo Not Implemented yet
*/
void Printer_printTestSetList(struct LinkedList list, enum PrintFormat print_format);

/**
  \brief Prints test results stored in an array of TestSets

  \param test_sets - Array of executed test sets
  \param set_count - Number of elements in the array
  \param print_format - Format the printing is produced

  \todo Need to implement JSON and YAML prints
*/
void Printer_printTestSetArray(struct TestSet test_sets[], int set_count, enum PrintFormat print_format);


#endif
