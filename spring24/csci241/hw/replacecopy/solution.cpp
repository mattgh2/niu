
char* replace_copy(char* destination, const char* source, char old_char, char new_char) {
  int i;
  for (i = 0; source[i] != '\0'; i++) {
    if (source[i] == old_char)
      destination[i] = new_char;
    else {
      destination[i] = source[i];
    }
  }
  destination[i] = '\0';
  return destination;
}
