#include "history.h"

// add a string to file
void HistoryChannel::addHistoryBlock(s_historyBlock historyBlock) {
   FILE* historyPoint = fopen(historyBlock.fileName.c_str(), "a");

   if (!historyPoint) {
      perror("Error opening history block");
   }

   fputs(historyBlock.str.data(), historyPoint);

   fclose(historyPoint);
}

// if user inputs UP ARROW read lines in history file
void HistoryChannel::readFromHistoryFile() {
}
