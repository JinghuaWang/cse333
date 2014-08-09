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

#include <iostream>
#include <algorithm>

#include "./QueryProcessor.h"

extern "C" {
  #include "./libhw1/CSE333.h"
}

namespace hw3 {

QueryProcessor::QueryProcessor(list<string> indexlist, bool validate) {
  // Stash away a copy of the index list.
  indexlist_ = indexlist;
  arraylen_ = indexlist_.size();
  Verify333(arraylen_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader *[arraylen_];
  itr_array_ = new IndexTableReader *[arraylen_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::iterator idx_iterator = indexlist_.begin();
  for (HWSize_t i = 0; i < arraylen_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = new DocTableReader(fir.GetDocTableReader());
    itr_array_[i] = new IndexTableReader(fir.GetIndexTableReader());
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (HWSize_t i = 0; i < arraylen_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

// This (affectionately named) function takes a query and returns
// a QueryResult vector (sorted by rank)
// If nothing found, return empty vector
vector<QueryProcessor::QueryResult>
googleWord(DocTableReader **dtr_array_, IndexTableReader **itr_array_,
              HWSize_t arraylen_, const string word) {

  // set our retvec
  vector<QueryProcessor::QueryResult> retvec;

  // iterate
  for (HWSize_t i = 0; i < arraylen_; i++) {
    DocIDTableReader *dtr = (itr_array_[i])->LookupWord(word);
    
    // no matches, move on
    if (dtr == nullptr) {
      continue;
    } else {
      // Has matches, do stuff

      // Get document list
      list<docid_element_header> doc_list = dtr->GetDocIDList();

      while (!doc_list.empty()) {
        docid_element_header head = doc_list.front();
        doc_list.pop_front();

        string name;
        if (dtr_array_[i]->LookupDocID(head.docid, &name)) {
          QueryProcessor::QueryResult qres;

          qres.document_name = name;
          qres.rank = head.num_positions;
          retvec.push_back(qres);
        }
      }
    }
    delete dtr;
  }
  return retvec;
}

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string> &query) {
  Verify333(query.size() > 0);
  vector<QueryProcessor::QueryResult> finalresult;

  // MISSING:

  // Grab the first query word
  string first_word = query.front();

  // Get docs that match the word
  vector<QueryProcessor::QueryResult> first_vec = 
      googleWord(dtr_array_, itr_array_, arraylen_, first_word);

  // if first_vec is empty, return the empty vector
  if (first_vec.empty()) {
    return finalresult;
  }

  // Check remaining query words
  if (query.size() > 1) {

    // query iterator
    auto it_query = query.begin();
    it_query++;  // I like to move it move it

    while (it_query != query.end()) {
      vector<QueryProcessor::QueryResult> result_vec;
      result_vec = googleWord(dtr_array_, itr_array_, arraylen_, *it_query);

      // Once again, if no doc matches, return empty vector
      if (result_vec.empty()) {
        return finalresult;
      }

      // vector iterator
      auto it_vec = first_vec.begin();

      while (it_vec != first_vec.end()) {

        auto it_doc = result_vec.begin();
        for (; it_doc != result_vec.end(); it_doc++) {

          // compare document names
          if (it_vec->document_name.compare(it_doc->document_name) == 0) {
            it_vec->rank += it_doc->rank;
            it_vec++;
          } else {
            first_vec.erase(it_vec);

            if (first_vec.size() == 0) {
              return finalresult;
            }
          }
        }
      }

      it_query++;
    }
  }

  finalresult = first_vec;


  // Sort the final results.
  std::sort(finalresult.begin(), finalresult.end());
  return finalresult;
}

}  // namespace hw3
