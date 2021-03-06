/* pkg_src_list.c - the opkg package management system

   Carl D. Worth

   Copyright (C) 2001 University of Southern California

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.
*/

#include "pkg_src_list.h"
#include "void_list.h"
#include "libbb/libbb.h"

void pkg_src_list_init(pkg_src_list_t * list)
{
	void_list_init((void_list_t *) list);
}

void pkg_src_list_deinit(pkg_src_list_t * list)
{
	pkg_src_list_elt_t *iter, *n;
	pkg_src_t *pkg_src;

	list_for_each_entry_safe(iter, n, &list->head, node) {
		pkg_src = (pkg_src_t *) iter->data;
		pkg_src_deinit(pkg_src);

		/* malloced in pkg_src_list_append */
		free(pkg_src);
		iter->data = NULL;
	}
	void_list_deinit((void_list_t *) list);
}

pkg_src_t *pkg_src_list_append(pkg_src_list_t * list,
			       const char *name, const char *base_url,
			       int gzip)
{
	/* freed in pkg_src_list_deinit */
	pkg_src_t *pkg_src = xcalloc(1, sizeof(pkg_src_t));
	pkg_src_init(pkg_src, name, base_url, gzip);

	void_list_append((void_list_t *) list, pkg_src);

	return pkg_src;
}
