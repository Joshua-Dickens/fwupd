/*
 * Copyright (C) 2017 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#define G_LOG_DOMAIN "FuCommon"

#include "config.h"

#include <gio/gio.h>
#include <shlwapi.h>
#include <sysinfoapi.h>

#include "fu-common-private.h"

GPtrArray *
fu_common_get_block_devices(GError **error)
{
	g_set_error(error,
		    G_IO_ERROR,
		    G_IO_ERROR_NOT_SUPPORTED,
		    "getting block devices is not supported on Windows");
	return NULL;
}

guint64
fu_common_get_memory_size_impl(void)
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return (guint64)status.ullTotalPhys;
}

gchar *
fu_common_get_kernel_cmdline_impl(GError **error)
{
	return g_strdup("");
}
