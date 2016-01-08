#include <stdio.h>
#include <string.h>

#define FALSE (0)
#define TRUE  (1)

#define cTYPE_HORIZONTAL  (0)
#define cTYPE_VERTICAL    (1)

//#define cWIDTH_MAX (10)
//#define cHEIGHT_MAX (7)
#define cWIDTH_MAX   (4)
#define cHEIGHT_MAX  (3)

#define cPAIR_HORIZONTAL_MAX  ((cWIDTH_MAX-1)*cHEIGHT_MAX) // 63
#define cPAIR_VERTICAL_MAX    ((cHEIGHT_MAX-1)*cWIDTH_MAX) // 60
#define cPAIR_PATTERN_MAX     (cPAIR_HORIZONTAL_MAX + cPAIR_VERTICAL_MAX)

#define cPAIR_MAX             ((cWIDTH_MAX*cHEIGHT_MAX)/2)
#define cPAIR_HASH_MAX        (176) // 10101111
#define PAIR_HASH(type, y, x) ((x << 4) | (y << 1) | type)

typedef struct PAIR_t {
  unsigned char x;
  unsigned char y;
  unsigned char type;
  unsigned char hash;
}PAIR;

typedef struct FIELD_t {
  int pairs_count;
  PAIR pairs[cPAIR_MAX];

  int v_pairs_count;
  PAIR v_pairs[cPAIR_VERTICAL_MAX];

  int h_pairs_count;
  PAIR h_pairs[cPAIR_HORIZONTAL_MAX];

  char buff[cHEIGHT_MAX][cWIDTH_MAX];
}FIELD;

typedef struct HASH_TREE_t {
  int fill_count;

  struct HASH_TREE_t* next[cPAIR_HASH_MAX];
}HASH_TREE;

int set_pair_to_field(FIELD* f, PAIR* p) {
  int x = 0;
  int y = 0;

  if (p->type == cTYPE_HORIZONTAL) {
    if (f->buff[p->y][p->x] == 0 && f->buff[p->y][p->x + 1] == 0) {
      f->buff[p->y][p->x] = 1;
      f->buff[p->y][p->x + 1] = 1;
      f->pairs[f->pairs_count] = *p;
      f->pairs_count++;
      return TRUE;
    }
  }
  else if (p->type == cTYPE_VERTICAL) {
    if (f->buff[p->y][p->x] == 0 && f->buff[p->y + 1][p->x] == 0) {
      f->buff[p->y][p->x] = 1;
      f->buff[p->y + 1][p->x] = 1;
      f->pairs[f->pairs_count] = *p;
      f->pairs_count++;
      return TRUE;
    }
  }
  return FALSE;
}

void pull_pair_from_field(FIELD* f, int dir, int idx) {
  int i = 0;

  if (dir == cTYPE_HORIZONTAL) {
    for (i = idx; i < f->h_pairs_count - 1; i++) {
      f->h_pairs[i] = f->h_pairs[i + 1];
    }
    f->h_pairs_count--;
  }
  else if (dir == cTYPE_VERTICAL) {
    for (i = idx; i < f->v_pairs_count - 1; i++) {
      f->v_pairs[i] = f->v_pairs[i + 1];
    }
    f->v_pairs_count--;
  }
}

void init_field_pairs(FIELD* f) {
  int x = 0;
  int y = 0;

  // init vertical pairs
  for (x = 0; x < cWIDTH_MAX; x++) {
    for (y = 0; y < cHEIGHT_MAX - 1; y++) {
      f->v_pairs[f->v_pairs_count].x = x;
      f->v_pairs[f->v_pairs_count].y = y;
      f->v_pairs[f->v_pairs_count].type = cTYPE_VERTICAL;
      f->h_pairs[f->h_pairs_count].hash = PAIR_HASH(cTYPE_VERTICAL, y, x);
      f->v_pairs_count++;
    }
  }
  // init horizontal pairs
  for (y = 0; y < cHEIGHT_MAX; y++) {
    for (x = 0; x < cWIDTH_MAX - 1; x++) {
      f->h_pairs[f->h_pairs_count].x = x;
      f->h_pairs[f->h_pairs_count].y = y;
      f->h_pairs[f->h_pairs_count].type = cTYPE_HORIZONTAL;
      f->h_pairs[f->h_pairs_count].hash = PAIR_HASH(cTYPE_HORIZONTAL, y, x);
      f->h_pairs_count++;
    }
  }
}

int fill_field(FIELD *f) {
  int i = 0;
  int j = 0;

  for (i = 0; i < f->h_pairs_count; i++) {
    if (set_pair_to_field(f, &f->h_pairs[i])) {
      if (f->pairs_count >= cPAIR_MAX) {
        
      }
    }
  }

  return 1;
}

int main(int argc, char** argv) {
  FIELD f;
  memset((void*)&f, 0, sizeof(f));
  init_field_pairs(&f);

  fill_field(&f);
/*
  for (i = 0; i < f.v_pairs_count; i++) {
    if (set_pair_to_field(&f, &f.v_pairs[i])) {
      printf("%d\n", i);
    }
  }
*/
  return 0;
}
