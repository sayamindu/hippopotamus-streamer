/*
 * hippo.c
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


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <gst/gst.h>

#include "hippo.h"
#include "hippo_preferences.h"
#include "hippo_streamer.h"


void
hippo_update_icon (GtkStatusIcon * status_icon)
{
  gchar *icon_name;
  gchar *tooltip;

  if (status == STREAM_STATUS_PAUSED)
    {
      icon_name = GTK_STOCK_MEDIA_PAUSE;
      tooltip = "Streaming is paused ...";
      gtk_status_icon_set_blinking (status_icon, FALSE);
    }
  else if (status == STREAM_STATUS_STOPPED)
    {
      icon_name = GTK_STOCK_MEDIA_STOP;
      tooltip = "Streaming is stopped ...";
      gtk_status_icon_set_blinking (status_icon, FALSE);
    }
  else
    {
      icon_name = GTK_STOCK_MEDIA_RECORD;
      tooltip = "Streaming ...";
      gtk_status_icon_set_blinking (status_icon, TRUE);
    }

  gtk_status_icon_set_from_icon_name (status_icon, icon_name);
  gtk_status_icon_set_tooltip (status_icon, tooltip);
}

static void
hippo_icon_activated (GtkStatusIcon * icon)
{
  if (status == STREAM_STATUS_PAUSED || status == STREAM_STATUS_STOPPED)
    {
      hippo_streaming_start ();
      status = STREAM_STATUS_STREAMING;
      hippo_update_icon (icon);
    }
  else
    {
      hippo_streaming_pause ();
      status = STREAM_STATUS_PAUSED;
      hippo_update_icon (icon);
    }
}

static void
hippo_show_about (GtkCheckMenuItem * item, GtkStatusIcon * icon)
{
  char *authors[] = { "Sayamindu Dasgupta <sayamindu@gnu.org.in>", NULL };

  char license[] =
    "This program is free software; you can redistribute it and/or\n"
    "modify it under the terms of the GNU General Public License as\n"
    "published by the Free Software Foundation; either version 2 of the\n"
    "License, or (at your option) any later version.\n\n"
    "This program is distributed in the hope that it will be useful,\n"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n"
    "GNU General Public License for more details.\n\n"
    "You should have received a copy of the GNU General Public License\n"
    "along with this program; if not, write to the Free Software\n"
    "Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02111-1307\n"
    "USA";

  GdkPixbuf *logo =
    gdk_pixbuf_new_from_file (HIPPO_IMAGEDIR"/hippo-logo.png",
			      NULL);


  gtk_show_about_dialog (NULL,
			 "name", "Hippopotamus",
			 "authors", authors,
			 "comments",
			 "Hippopotamus is a tool which lets you send a video stream to a Icecast server.",
			 "copyright",
			 "Copyright \xc2\xa9 2006 Sayamindu Dasgupta",
			 "license", license, "version", VERSION, "logo",
			 logo, NULL);
}

static void
hippo_quit (GtkMenuItem * item, GtkStatusIcon * icon)
{
  if (status == STREAM_STATUS_STREAMING)
    {
      hippo_streaming_stop ();
    }
  gtk_status_icon_set_visible (icon, FALSE);
  g_object_unref (icon);
  gtk_main_quit ();
}


static void
hippo_popup_menu (GtkStatusIcon * icon, guint button, guint32 activate_time)
{
  GtkWidget *menu, *menuitem;

  menu = gtk_menu_new ();

  menuitem = gtk_image_menu_item_new_from_stock (GTK_STOCK_PREFERENCES, NULL);
  g_signal_connect (menuitem, "activate",
		    G_CALLBACK (hippo_show_preferences), icon);
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

  gtk_widget_show (menuitem);

  menuitem = gtk_image_menu_item_new_from_stock (GTK_STOCK_ABOUT, NULL);
  g_signal_connect (menuitem, "activate", G_CALLBACK (hippo_show_about),
		    icon);
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

  gtk_widget_show (menuitem);

  menuitem = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, NULL);
  g_signal_connect (menuitem, "activate", G_CALLBACK (hippo_quit), icon);
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

  gtk_widget_show (menuitem);

  gtk_menu_popup (GTK_MENU (menu),
		  NULL, NULL, NULL, NULL, button, activate_time);
}



int
main (int argc, char *argv[])
{
  GtkStatusIcon *hippo_icon;

  gtk_init (&argc, &argv);
  gst_init (&argc, &argv);


  hippo_icon = gtk_status_icon_new ();

  status = STREAM_STATUS_STOPPED;

  hippo_update_icon (hippo_icon);

  g_signal_connect (hippo_icon, "activate",
		    G_CALLBACK (hippo_icon_activated), NULL);

  g_signal_connect (hippo_icon, "popup-menu",
		    G_CALLBACK (hippo_popup_menu), NULL);

  gdk_notify_startup_complete ();

  gtk_main ();

  return 0;
}
