#include "scrivener.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define inbuf_len 1 << 16
#define outbuf_len 1 << 16

int main() {
  int tmp;

  /* Set input and output buffering */
  char *inbuf, *outbuf;
  inbuf = (char*) malloc(inbuf_len * sizeof(char));
  outbuf = (char*) malloc(outbuf_len * sizeof(char));
  tmp = setvbuf(stdin, inbuf, _IOFBF, inbuf_len);
  tmp = setvbuf(stdout, outbuf, _IOFBF, outbuf_len);

  Init();

  int cmd_num;
  tmp = scanf("%d", &cmd_num);
  assert(tmp == 1);

  int i;
  for (i = 0; i < cmd_num; i++) {
    char cmd;
    tmp = scanf(" %c", &cmd);
    assert(tmp == 1);
    if (cmd == 'T') {
      char letter;
      tmp = scanf(" %c", &letter);
      assert(tmp == 1);
      TypeLetter(letter);
    }
    else if (cmd == 'U') {
      int number;
      tmp = scanf("%d", &number);
      assert(tmp == 1);
      UndoCommands(number);
    }
    else if (cmd == 'P') {
      int index;
      char letter;
      tmp = scanf("%d", &index);
      assert(tmp == 1);
      letter = GetLetter(index);
      printf("%c\n", letter);
    }
  }

  return 0;

}
