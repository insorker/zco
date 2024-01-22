#include <stdio.h>
#include "../zco.h"
#include "../zco_queue.h"

int main()
{
  FILE *file_src = fopen("Pride and Prejudice", "r");
  FILE *file_dest = fopen("Pride and Prejudice copy", "w");

  if (!file_src || !file_dest) {
    perror("Fail to open file.");
    return 1;
  }
  
  char buffer[1024];
  size_t buffer_read = 0;

  while ((buffer_read = fread(buffer, 1, sizeof(buffer), file_src)) > 0) {
    fwrite(buffer, 1, buffer_read, file_dest);
  }

  fclose(file_src);
  fclose(file_dest);
}