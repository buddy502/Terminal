#include "history.h"

// adds the 
void HistoryChannel::addHistoryBlock(char* filestr) {
   FILE* historyPoint = fopen(historyBlock.fileName.c_str(), "a");

   if (!historyPoint) {
      perror("Error opening history block");
   }

   fputs(filestr, historyPoint);
   fputc('\n', historyPoint);

   fclose(historyPoint);
}

// if user inputs UP ARROW read lines in history file
void HistoryChannel::readFromHistoryFile() {
}
