/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2026 Catium2006
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#define ENABLE_DEBUG 0

#include <stdio.h>

#ifndef ENABLE_DEBUG
#define ENABLE_DEBUG 0
#endif

#if ENABLE_DEBUG
#define DEBUG(content) printf("[DEBUG] %s line %d -> %s\n", __FILE_NAME__, __LINE__, content)
#else
#define DEBUG(content)
#endif


#endif