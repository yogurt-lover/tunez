#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "link_list.h"

song_node *table[26];

// add songs
void add_song(char *artist, char *name) {
  table[artist[0] - 'a'] = insert_order(table[artist[0] - 'a'], artist, name);
  printf(">> Added ");
  print_node(table[artist[0] - 'a']);
}

// delete a song
void delete_song(char *artist, char *name) {
  table[artist[0] - 'a'] = remove_song(table[artist[0] - 'a'], artist, name);
  printf(">> Removed ");
  print_node(table[artist[0] - 'a']);  
}

// delete all the nodes
void delete_all() {
  int i = 0;
  for (; i < 26; i++)
    free_list(table[i]);
  printf(">> Removed all songs\n");
}

// search for a song
song_node *search_song(char* name) {
  int i = 0;
  for (; i < 26; i++) {
    song_node *letter_node = table[i];
    song_node *potential_find = find_song(letter_node, name);
    if (potential_find)
      return potential_find;
  }
  return 0;
}

// search for an artist
song_node *search_artist(char* artist) {
  song_node *letter_node = table[artist[0] - 'a'];
  song_node *potential_find = find_artist(letter_node, artist);
  if (potential_find)
    return potential_find;
  return 0;
}

// print out all the entries under a certain letter
void print_letter_entries(char c) {
  printf(">> Songs under '%c':\n", c);
  print_list(table[c - 'a']);
}

// print out all the songs of a certain artist
void print_artist_entries(char *artist) {
  song_node *artist_node = search_artist(artist);
  if (artist_node) {
    printf("|");
    while (artist_node) {
      if (strcmp(artist, artist_node->artist) == 0)
	printf(" %s - %s |", artist_node->artist, artist_node->name);
      else 
	break;
      artist_node = artist_node->next;
    }
    printf("\n");
  }
}

// print out the entire library
void print_library() {
  char c = 'a';
  for (; c <= 'z'; c++)
    print_letter_entries(c);
}

// shuffle
void shuffle(int i) {
  srand(time(NULL));

  char any_songs[26];
  int k = 0;
  
  int j = 0;
  for (; table[j]; j++)
    if (table[j]) {
      any_songs[k] = j;
      k++;
    }

  int letters_with_songs = k;
  for (; k < 26; k++)
    any_songs[k] = -1;
  
  if (!letters_with_songs) return;

  printf("|");
  while (i) {
    int rand_index = any_songs[(int)(letters_with_songs * ((double)rand()/RAND_MAX) )];
    song_node *rand_song = find_random(table[rand_index]);
    printf(" %s - %s |", rand_song->artist, rand_song->name);
    i--;
  }
  printf("\n");
}

