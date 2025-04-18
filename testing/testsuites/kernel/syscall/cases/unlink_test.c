/****************************************************************************
 * apps/testing/testsuites/kernel/syscall/cases/unlink_test.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/config.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "SyscallTest.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: test_nuttx_syscall_unlink01
 ****************************************************************************/

void test_nuttx_syscall_unlink01(FAR void **state)
{
  char fname[64] =
  {
    0
  };

  int fd;
  int ret;

  sprintf(fname, "%s_file", __func__);

  fd = open(fname, O_RDWR | O_CREAT);
  if (fd > 0)
    {
      close(fd);
    }

  else
    {
      syslog(LOG_ERR, "open test file fail !\n");
      fail_msg("test fail");
    }

  ret = unlink(fname);
  assert_int_equal(ret, 0);

  if (!access(fname, F_OK))
    {
      fail_msg("test fail !\n");
      syslog(LOG_ERR,
             "FAIL, unlink(%s) succeeded, but %s still existed\n", fname,
             fname);
    }
}
