/* -*- c -*- */
/*
 * Copyright (C) 2017 The Regents of the University of New Mexico
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Author: Dave Ackley <ackley@ackleyshack.com>
 *
 */

#include "LinuxIO.h"

extern void mainLoop(); // In asm

/*
* main.c
*/
void main(void)
{
  initLinuxIO();

  /* Never look back */
  mainLoop();
}

