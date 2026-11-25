#include <stdio.h>
#include "movie_lib.h"
int main(void)
{
	movie_load("./1.mpg");
	movie_play();
	return (0);
}
