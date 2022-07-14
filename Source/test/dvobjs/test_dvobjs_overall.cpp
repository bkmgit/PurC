/*
** Copyright (C) 2022 FMSoft <https://www.fmsoft.cn>
**
** This file is a part of PurC (short for Purring Cat), an HVML interpreter.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "TestDVObj.h"

#include "../helpers.h"

TEST(dvobjs, basic)
{
    purc_instance_extra_info info = {};
    int ret = purc_init_ex(PURC_MODULE_EJSON, "cn.fmsoft.hvml.test",
            "dvobjs", &info);
    ASSERT_EQ (ret, PURC_ERROR_OK);

    purc_variant_t dvobj;

    dvobj = purc_dvobj_string_new();
    ASSERT_EQ(purc_variant_is_object(dvobj), true);
    purc_variant_unref(dvobj);

    purc_cleanup();
}

TEST(dvobjs, overall)
{
    TestDVObj tester;
    tester.run_testcases_in_file("overall");
}

