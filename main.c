/*/	
 *		ptimer: main.c 
 *
 *		Created by dimpk
/*/


#include <stdio.h>
#include <signal.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

static const int p_session = 50 * 60;	// default session duration
static const int p_break = 10 * 60;		// default break duration
static const int p_number = 2;			// default number of sessions
static const int p_indicator_size = 20;	// process indicator size (0__0)
static const int p_divider = 5;			// number of percentages in one indicator mark

void interrupt_handler(int sig)
{
	puts("\n\n\033[1;35mBye, 0w0/\033[0m");
	exit(0);
}

void print_state(int time_left, double percent, double *cur_percent)
{
	int fragments;

	printf("\r");
	*cur_percent += percent;
	fragments = (int)*cur_percent / p_divider;

	putchar('[');
	for (int j = 0; j < fragments; j++)
		putchar('#');
	for (int j = 0; j < p_indicator_size - fragments; j++)
		putchar('-');
	putchar(']');

	printf(" %d%% - %d seconds left", (int)*cur_percent, time_left);
	fflush(stdout);
}

void session_break_loop(int ssn_drtn, int brk_drtn, int num_ssn)
{
	int c;
	double percent, cur_percent;

	for (int i = 1; i <= num_ssn; i++) {
		printf("\033[1;32mSession %d/%d. Duration: %d minute(s). "
		       "Good luck!\033[0m\n\n", i, num_ssn, ssn_drtn / 60);

		percent = 100.0 / ssn_drtn;
		cur_percent = 0;

		for (int j = ssn_drtn - 1; j >= 0; j--) {
			print_state(j, percent, &cur_percent);
			sleep(1);
		}
		printf("\n\n");
		
		if (i != num_ssn) {
			printf("\033[1;32mSession is finished. This is extra time.\033[0m\n"	
			       "Type (C)ontinue to start a break: ");
			while ((c = getchar()) != -1)
				if (c == 'C' || c == 'c')
					break;
			putchar('\n');

//			printf("\a");

			printf("\033[1;36mBreak %d/%d. Duration: %d minute(s). "
			       "Take a rest!\033[0m\n\n", i, num_ssn - 1, brk_drtn / 60);

			percent = 100.0 / brk_drtn;
			cur_percent = 0;

			for (int j = brk_drtn - 1; j >= 0; j--) {
				print_state(j, percent, &cur_percent);
				sleep(1);
			}
			printf("\n\n");

			printf("\033[1;36mBreak is finished. This is extra time.\033[0m\n"	
			       "Type (C)ontinue to start a session: ");
			while ((c = getchar()) != -1)
				if (c == 'C' || c == 'c')
					break;
			putchar('\n');
		} else {
			printf("\033[1;31mAll sessions are finished. Great job!\033[0m\n");
		}
	}
}

int main(int argc, char **argv)
{
	// signal disposition
	signal(SIGINT, interrupt_handler);

	// turns off 'getopt()' error messages
	opterr = 0;

	int c;
	int ssn_drtn = p_session;
	int brk_drtn = p_break;
	int num_ssn = p_number;

	while ((c = getopt(argc, argv, "s:b:n:")) != -1) {
		switch (c) {
			case 's':
				ssn_drtn = atoi(optarg) * 60;
				if (ssn_drtn <= 0) {
					fprintf(stderr, "\033[1;31mError:\033[0m option '-c' has wrong argument\n");
					exit(1);
				}
				break;
			case 'b':
				brk_drtn = atoi(optarg) * 60;
				if (brk_drtn <= 0) {
					fprintf(stderr, "\033[1;31mError:\033[0m option '-b' has wrong argument\n");
					exit(2);
				}
				break;
			case 'n':
				num_ssn = atoi(optarg);
				break;
			case '?':
				fprintf(stderr, "\033[1;31mError:\033[0m unrecognized options\n");
				exit(3);
		};
	};

	session_break_loop(ssn_drtn, brk_drtn, num_ssn);

	return 0;
}
