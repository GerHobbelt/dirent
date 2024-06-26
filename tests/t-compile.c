/*
 * Test program to make sure that dirent compiles cleanly with winsock.
 *
 * Copyright (C) 1998-2019 Toni Ronkko
 * This file is part of dirent.  Dirent may be freely distributed
 * under the MIT license.  For all details and documentation, see
 * https://github.com/tronkko/dirent
 */
#include <dirent.h>
#ifdef WIN32
#	include <winsock2.h>
#	include <ws2tcpip.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../examples/monolithic_examples.h"

static void test_properties(void);
static void test_length(void);
static void initialize(void);
static void cleanup(void);


#if defined(BUILD_MONOLITHIC)
#define main		dirent_compile_test_main
#endif

int
main(void)
{
	initialize();

	test_properties();
	test_length();

	cleanup();
	return EXIT_SUCCESS;
}

static void
test_properties(void)
{
#ifdef _DIRENT_HAVE_D_TYPE
	printf("Has d_type\n");
#endif
#ifdef _DIRENT_HAVE_D_NAMLEN
	printf("Has d_namlen\n");
#endif
#ifdef _D_EXACT_NAMLEN
	printf("Has _D_EXACT_NAMLEN\n");
#endif
#ifdef _D_ALLOC_NAMLEN
	printf("Has _D_ALLOC_NAMLEN\n");
#endif
#ifdef _D_ALLOC_NAMLEN
	printf("Has _D_ALLOC_NAMLEN\n");
#endif
}

static void
test_length(void)
{
	struct dirent *dirp = NULL;
	printf("Length of d_name with terminator: %d\n",
		(int) sizeof(dirp->d_name));
}

static void
initialize(void)
{
	/*NOP*/;
}

static void
cleanup(void)
{
	printf("OK\n");
}
