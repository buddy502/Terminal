#pragma once

#include <iostream>

#include <cstdio>
#include <array>

#define MAX_HISTORY_SIZE 2000 // stores max lines history file has
#define MAX_HISTORY_BLOCK 20  // stores starting size of history array

// write to a file to store memory blocks
struct s_historyBlock {
   std::string fileName = "history_block";
};

class HistoryChannel {
   public:
      s_historyBlock historyBlock;

      HistoryChannel() = default;

      void addHistoryBlock(std::string filestr);
      void readFromHistoryFile();
};
