/*
 * Test program to make sure that dirent compiles cleanly with C++
 *
 * Copyright (C) 1998-2019 Toni Ronkko
 * This file is part of dirent.  Dirent may be freely distributed
 * under the MIT license.  For all details and documentation, see
 * https://github.com/tronkko/dirent
 */
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <assert.h>

#include "../examples/monolithic_examples.h"

using namespace std;

/* Filter and sort functions */
static int only_readme(const struct dirent *entry);
static void test_retrieval(void);
static void test_scan(void);
static void initialize(void);
static void cleanup(void);


#if defined(BUILD_MONOLITHIC)
#define main		dirent_cpp_test_main
#endif

int
main(void)
{
	initialize();

	test_retrieval();
	test_scan();

	cleanup();
	return EXIT_SUCCESS;
}

/* Test basic directory retrieval */
static void
test_retrieval(void)
{
	/* Open directory */
	DIR *dir = opendir("tests/1");
	if (dir == NULL) {
		cerr << "Directory tests/1 not found" << endl;
		abort();
	}

	/* Read directory entries */
	struct dirent *ent;
	int found = 0;
	while ((ent = readdir(dir)) != NULL) {
		/* Check each file */
		if (strcmp(ent->d_name, ".") == 0) {
			/* Directory itself */
#ifdef _DIRENT_HAVE_D_TYPE
			assert(ent->d_type == DT_DIR);
#endif
#ifdef _DIRENT_HAVE_D_NAMLEN
			assert(ent->d_namlen == 1);
#endif
#ifdef _D_EXACT_NAMLEN
			assert(_D_EXACT_NAMLEN(ent) == 1);
#endif
#ifdef _D_ALLOC_NAMLEN
			assert(_D_ALLOC_NAMLEN(ent) > 1);
#endif
			found += 1;
		} else if (strcmp(ent->d_name, "..") == 0) {
			/* Parent directory */
#ifdef _DIRENT_HAVE_D_TYPE
			assert(ent->d_type == DT_DIR);
#endif
#ifdef _DIRENT_HAVE_D_NAMLEN
			assert(ent->d_namlen == 2);
#endif
#ifdef _D_EXACT_NAMLEN
			assert(_D_EXACT_NAMLEN(ent) == 2);
#endif
#ifdef _D_ALLOC_NAMLEN
			assert(_D_ALLOC_NAMLEN(ent) > 2);
#endif
			found += 2;
		} else if (strcmp(ent->d_name, "file") == 0) {
			/* Regular file */
#ifdef _DIRENT_HAVE_D_TYPE
			assert(ent->d_type == DT_REG);
#endif
#ifdef _DIRENT_HAVE_D_NAMLEN
			assert(ent->d_namlen == 4);
#endif
#ifdef _D_EXACT_NAMLEN
			assert(_D_EXACT_NAMLEN(ent) == 4);
#endif
#ifdef _D_ALLOC_NAMLEN
			assert(_D_ALLOC_NAMLEN(ent) > 4);
#endif
			found += 4;
		} else if (strcmp(ent->d_name, "dir") == 0) {
			/* Just a directory */
#ifdef _DIRENT_HAVE_D_TYPE
			assert(ent->d_type == DT_DIR);
#endif
#ifdef _DIRENT_HAVE_D_NAMLEN
			assert(ent->d_namlen == 3);
#endif
#ifdef _D_EXACT_NAMLEN
			assert(_D_EXACT_NAMLEN(ent) == 3);
#endif
#ifdef _D_ALLOC_NAMLEN
			assert(_D_ALLOC_NAMLEN(ent) > 3);
#endif
			found += 8;
		} else {
			/* Other file */
			cerr << "Unexpected file " << ent->d_name << endl;
			abort();
		}
	}

	/* Make sure that all files were found */
	assert(found == 0xf);

	closedir(dir);
}

/* Text basic scan with simple filter function */
static void
test_scan(void)
{
	struct dirent **files;

	/* Read directory entries */
	int n = scandir("tests/3", &files, only_readme, alphasort);
	assert(n == 1);

	/* Make sure that the filter works */
	assert(strcmp(files[0]->d_name, "README.txt") == 0);

	/* Release file names */
	for (int i = 0; i < n; i++) {
		free(files[i]);
	}
	free(files);
}

/* Only pass README.txt file */
static int
only_readme(const struct dirent *entry)
{
	int pass;

	if (strcmp (entry->d_name, "README.txt") == 0) {
		pass = 1;
	} else {
		pass = 0;
	}

	return pass;
}

static void
initialize(void)
{
	/*NOP*/;
}

static void
cleanup(void)
{
	cout << "OK" << endl;
}
