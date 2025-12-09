#pragma once

#include <iostream>

#include <cstdio>
#include <array>

#define MAX_HISTORY_BLOCK 20

// write to a file to store memory blocks

struct s_historyBlock {
   std::string fileName = "history_block";
   std::array<char, MAX_HISTORY_BLOCK> str; 
};

class HistoryChannel {
   public:
      s_historyBlock historyBlock;

      HistoryChannel() = default;

      void addHistoryBlock(s_historyBlock historyBlock);
      void readFromHistoryFile();
};
