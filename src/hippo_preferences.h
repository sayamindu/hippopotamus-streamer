/*
 * hippo_preferences.h
 * This file is part of Hippopotamus
 *
 * Copyright (C) 2006 - Sayamindu Dasgupta
 *
 * Hippopotamus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Hippopotamus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hippopotamus; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#ifndef __HIPPO_PREFERENCES_H__
#define __HIPPO_PREFERENCES_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS
 
void hippo_show_preferences (GtkMenuItem * menuitem, gpointer user_data);

gchar *hippo_get_host (void);
gboolean hippo_set_host (char *data);
gint hippo_get_port (void);
gboolean hippo_set_port (gint data);
gchar *hippo_get_mount (void);
gboolean hippo_set_mount (char *data);
gchar *hippo_get_passwd (void);
gboolean hippo_set_passwd (char *data);
gint hippo_get_vquality (void);
gboolean hippo_set_vquality (gint data);
gchar *hippo_get_overlay (void);
gboolean hippo_set_overlay (char *data);

G_END_DECLS
#endif /* __HIPPO_PREFERENCES_H__ */
