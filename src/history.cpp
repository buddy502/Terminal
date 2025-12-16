#include "history.h"

// adds the 
void HistoryChannel::addHistoryBlock(std::string filestr) {
   FILE* historyPoint = fopen(historyBlock.fileName.c_str(), "a");

   if (!historyPoint) {
      perror("Error opening history block");
   }

   fputs(filestr.c_str(), historyPoint);
   fputc('\n', historyPoint);

   fclose(historyPoint);
}

// if user inputs UP ARROW read lines in history file
void HistoryChannel::readFromHistoryFile() {
}
