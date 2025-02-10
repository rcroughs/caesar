/*******************************************************************************
 * Project: Caesar Cipher Decoder
 * Version: 1.0
 *
 * Author: Romain Croughs
 * Email: romain.croughs@ulb.be
 * Created: February 10, 2025
 *
 * Description:
 *     This program implements a Caesar cipher decoder that can either decode
 *     a message with a specific offset or attempt all possible decodings (brute
 *     force). The program preserves case sensitivity and ignores non-alphabetic
 *     characters.
 *
 * Usage:
 *     1. Brute force mode (tries all possible shifts):
 *        ./caesar "Hello World"
 *
 *     2. Specific offset mode:
 *        ./caesar "Hello World" 3
 *
 *     3. Interactive mode:
 *        ./caesar
 *        Then follow the prompts.
 *
 * Build:
 *     gcc -Wall -Wextra -o decode decode.c
 *
 * Dependencies:
 *     - Standard C libraries: stdio.h, stdlib.h, string.h, ctype.h
 *
 * Notes:
 *     - Maximum input length is 1000 characters
 *     - Preserves case (upper/lowercase)
 *     - Maintains spacing and punctuation
 *     - Handles command line arguments and stdin
 *
 * License:
 *     This software is released under the MIT License.
 *     Copyright (c) 2025 Romain Croughs
 ******************************************************************************/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000
#define ALPHABET_SIZE 26

typedef struct {
  char text[MAX_LENGTH];
  int offset;
  bool bruteforce;
} DecoderConfig;

void decodeCaesar(char *text, int offset);
void printDecodedText(const char *text, int offset);
DecoderConfig parseArguments(int argc, char *argv[]);
void bruteforceDecoder(const char *text);
void removeNewline(char *text);

void decodeCaesar(char *text, int offset) {
  for (int i = 0; text[i] != '\0'; i++) {
    if (isalpha(text[i])) {
      char base = isupper(text[i]) ? 'A' : 'a';
      text[i] =
          ((text[i] - base - offset + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
    }
  }
}

void printDecodedText(const char *text, int offset) {
  printf("Offset %2d: %s\n", offset, text);
}

DecoderConfig parseArguments(int argc, char *argv[]) {
  DecoderConfig config = {.bruteforce = true, .offset = 0};

  if (argc == 1) {
    printf("Enter the text to decode: ");
    fgets(config.text, MAX_LENGTH, stdin);
  } else if (argc == 2) {
    strncpy(config.text, argv[1], MAX_LENGTH - 1);
  } else {
    config.bruteforce = false;
    config.offset = atoi(argv[2]);
    strncpy(config.text, argv[1], MAX_LENGTH - 1);
  }

  removeNewline(config.text);
  return config;
}

void bruteforceDecoder(const char *text) {
  char temp[MAX_LENGTH];
  printf("All possible decodings:\n");
  printf("------------------------\n");
  for (int i = 1; i < ALPHABET_SIZE; i++) {
    strncpy(temp, text, MAX_LENGTH - 1);
    decodeCaesar(temp, i);
    printDecodedText(temp, i);
  }
}

void removeNewline(char *text) {
  size_t len = strlen(text);
  if (len > 0 && text[len - 1] == '\n') {
    text[len - 1] = '\0';
  }
}

int main(int argc, char *argv[]) {
  DecoderConfig config = parseArguments(argc, argv);

  if (config.bruteforce) {
    bruteforceDecoder(config.text);
  } else {
    decodeCaesar(config.text, config.offset);
    printf("Decoded text: %s\n", config.text);
  }

  return 0;
}
