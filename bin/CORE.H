#ifndef CORE
#define CORE
#include <stdio.h>

#define N 10
#define MAXSTR 80
#define ESC 27
#define ENTER 13
#define TAB 9
#define BACKSPACE 8
#define UP 72
#define DOWN 80
#define PGUP 73
#define PGDN 81
#define HOME 71
#define END 79
#define WINDON 1
#define WINDOFF 0

enum WINDOWS{
  MAINPANEL,
  SEE,
  FIND,
  SORT,
  LISTMENU1,
  LISTMENU2,
};

typedef struct TicketTL{

	char cou[20];
	char tr[MAXSTR];
	int len;
	float rub;

	struct TicketTL *tprev, *tnext;

} TicketTL;

extern int str_count;
extern int active;
extern TicketTL *tfirst;

#ifdef MAIN
#endif
#ifdef BHD
#include <conio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define IN 1
#define OUT 0	

void interface(void);
void see(void);
void create(void);
void find(void);
void sort(void);
void del(TicketTL**);
void head(void);
void table(TicketTL*, int);
void choicetr(TicketTL**);
void endt(void);
void closemo(void);
void chisto(void);
void diagnos(void);
void entkey(char*);

void seeDialog(void);
void createDialog(void);
void findDialog(void);
void deleteDialog(void);
void sortDialog(void);
void exitDialog(void);
void helpDialog(char*);

void twoButtonDialog(int, int, int, int, char*, char*, char*);
void oneButtonDialog(int, int, int, int, char*, char*);
void mainPanel(size_t, char*, ...);
void listMenu(int, int, size_t, char*, ...);

void headConsole(void);
void tableConsole(TicketTL*);
void endConsole(void);

int windofch = -1;
int str_count = 0;
int active = MAINPANEL;

#endif

#ifdef TL
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
void load(void);
void save(void);

TicketTL *bsortssb(TicketTL **head);
TicketTL *bsortsbs(TicketTL **head);
TicketTL *bsortrsb(TicketTL **head);
TicketTL *bsortrbs(TicketTL **head);

void ListDestroy(TicketTL**);
TicketTL *getlast(TicketTL*);
TicketTL *addBegin(TicketTL**);
TicketTL *addEnd(TicketTL**);
TicketTL *deleteBegin(TicketTL**);
TicketTL *deleteMid(TicketTL**);
TicketTL *deleteEnd(TicketTL**);
void TLSwap(TicketTL**);

extern int windofch;

TicketTL *tfirst = NULL;

#endif

#endif