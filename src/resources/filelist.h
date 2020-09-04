/****************************************************************************
 * Resource files.
 * This file is generated automatically.
 * Includes 4 files.
 *
 * NOTE:
 * Any manual modification of this file will be overwriten by the generation.
 ****************************************************************************/
#ifndef _FILELIST_H_
#define _FILELIST_H_


#include "Resources.h"
#ifdef __WIIU__
#include "bgMusic_ogg.h"
#include "button_png.h"
#include "button_click_mp3.h"
#include "FreeSans_ttf.h"

static RecourceFile RecourceList[] =
{
	{"bgMusic.ogg", bgMusic_ogg, bgMusic_ogg_size, NULL, 0},
	{"button.png", button_png, button_png_size, NULL, 0},
	{"button_click.mp3", button_click_mp3, button_click_mp3_size, NULL, 0},
	{"FreeSans.ttf", FreeSans_ttf, FreeSans_ttf_size, NULL, 0},
	{NULL, NULL, 0, NULL, 0}
};

#else
static RecourceFile RecourceList[] =
{
	{"bgMusic.ogg", NULL, 0, NULL, 0},
	{"button.png", NULL, 0, NULL, 0},
	{"button_click.mp3", nullptr, 0, NULL, 0},
	{"FreeSans.ttf", NULL, 0, NULL, 0},
	{NULL, NULL, 0, NULL, 0}
};

#endif
#endif
