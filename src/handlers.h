/*
 * This file is part of usysconf.
 *
 * Copyright © 2017 Solus Project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include "context.h"

/* Implemented elsewhere in the codebase */
extern UscHandler usc_handler_ldconfig;
extern UscHandler usc_handler_cbm;
extern UscHandler usc_handler_depmod;

extern UscHandler usc_handler_hwdb;
extern UscHandler usc_handler_ldm;
extern UscHandler usc_handler_sysusers;
extern UscHandler usc_handler_tmpfiles;

extern UscHandler usc_handler_glib2;
extern UscHandler usc_handler_fonts;
extern UscHandler usc_handler_mime;
extern UscHandler usc_handler_icon_cache;
extern UscHandler usc_handler_desktop_files;

extern UscHandler usc_handler_mandb;

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
