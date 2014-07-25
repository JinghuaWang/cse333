/*
 * Copyright 2011 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project sequence
 *  (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

#define _POSIX_C_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "memindex.h"
#include "filecrawler.h"

static void readQuery(char** query, int* qlen);
static void printResults(LinkedList retlist, DocTable table);
static void Usage(void);

int main(int argc, char **argv) {
  if (argc != 2)
    Usage();

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - crawl from a directory provided by argv[1] to produce and index
  //  - prompt the user for a query and read the query from stdin, in a loop
  //  - split a query into words (check out strtok_r)
  //  - process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.

  // Some necessary structs
  MemIndex index;
  DocTable table;
  LinkedList retlist;

  // Intro message
  printf("Indexing '%s'\n", argv[1]);

  // check for valid directory
  int retval = CrawlFileTree(argv[1], &table, &index);

  if (retval == 0) {  // not valid
    fprintf(stderr, "Path '%s' is not indexable\n", argv[1]);  // error
    Usage();
  }

  // All's well, let's get to work:
  char* query[32];  // initialize query string (is this long enough?)
  int qlen = 0;  // length of the query (0 for now)


  // loop forever (until user quit, e.g. ctrl-c)
  while (1) {
    // Get query from user and parse into words
    readQuery(query, &qlen);

    // Process query against the index
    retlist = MIProcessQuery(index, (char **) query, qlen);

    // If we find something...
    if (retlist != NULL) {
      // ...print the results
      printResults(retlist, table);
    }

    qlen = 0;  // reset
  }

  // Free our structs
  FreeMemIndex(index);
  FreeDocTable(table);

  return EXIT_SUCCESS;
}

static void readQuery(char** query, int* qlen) {
  int bufsize = 256;
  char *buf = (char *) malloc(bufsize);
  char *saveptr;

  // Prompt user for input
  printf("enter query:\n");

  // malloc some space for the input
  fgets(buf, bufsize-1, stdin);

  // swap newline character for end character
  for (int i = 0; i < bufsize-1; i++) {
    if (buf[i] == '\n') {
      buf[i] = '\0';
      break;
    }
  }

  // Get the first element and make sure it's valid
  query[*qlen] = strtok_r(buf, " ", &saveptr);

  // if NULL input, notify user
  if (query[0] == NULL) {
    printf("Not a valid input (ctrl-C to quit)\n");
    exit(-1);
  }

  // Once we're past query[0], loop through input
  while (1) {
    // Check for null
    if (query[*qlen] == NULL) {
      break;
    }

    // if valid, increment qlen ptr
    (*qlen)++;

    // grab the next query
    query[*qlen] = strtok_r(NULL, " ", &saveptr);
  }

  return;
}

static void printResults(LinkedList retlist, DocTable table) {
  SearchResult *sr;
  int ne = NumElementsInLinkedList(retlist);
  LLIter llit = LLMakeIterator(retlist, 0);

  for (int i = 0; i < ne; i++) {
    LLIteratorGetPayload(llit, (LLPayload_t *) &sr);

    printf("  %s (%u)\n", DTLookupDocID(table, sr->docid), sr->rank);

    LLIteratorDelete(llit, &free);
  }

  LLIteratorFree(llit);
  free(retlist);

  return;
}

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(-1);
}

