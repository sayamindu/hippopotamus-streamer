/*
 * hippo_preferences.c
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

#include <gconf/gconf-client.h>
#include <glade/glade.h>
#include <gtk/gtk.h>
#include <gst/gst.h>

#include "hippo.h"
#include "hippo_preferences.h"
#include "hippo_streamer.h"

gboolean was_playing = FALSE;

gchar *
hippo_get_host (void)
{
  gchar *ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_get_string (client,
			     "/apps/hippopotamus/icecast/hostname", NULL);
  g_object_unref (client);

  return (ret);
}

gboolean
hippo_set_host (char *data)
{
  gboolean ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_set_string (client,
			     "/apps/hippopotamus/icecast/hostname",
			     data, NULL);
  g_object_unref (client);

  return (ret);
}


gint
hippo_get_port (void)
{
  gint ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_get_int (client, "/apps/hippopotamus/icecast/port", NULL);
  g_object_unref (client);

  return (ret);
}

gboolean
hippo_set_port (int data)
{
  gboolean ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_set_int (client, "/apps/hippopotamus/icecast/port",
			  data, NULL);
  g_object_unref (client);

  return (ret);
}


gchar *
hippo_get_mount (void)
{
  gchar *ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_get_string (client,
			     "/apps/hippopotamus/icecast/mountpoint", NULL);
  g_object_unref (client);

  return (ret);
}

gboolean
hippo_set_mount (char *data)
{
  gboolean ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_set_string (client,
			     "/apps/hippopotamus/icecast/mountpoint",
			     data, NULL);
  g_object_unref (client);

  return (ret);
}

gchar *
hippo_get_passwd (void)
{
  gchar *ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_get_string (client,
			     "/apps/hippopotamus/icecast/passwd", NULL);
  g_object_unref (client);

  return (ret);
}

gboolean
hippo_set_passwd (char *data)
{
  gboolean ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_set_string (client,
			     "/apps/hippopotamus/icecast/passwd", data, NULL);
  g_object_unref (client);

  return (ret);
}

gint
hippo_get_vquality (void)
{
  gint ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_get_int (client, "/apps/hippopotamus/video/vquality", NULL);
  g_object_unref (client);

  return (ret);
}

gboolean
hippo_set_vquality (int data)
{
  gboolean ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_set_int (client, "/apps/hippopotamus/video/vquality",
			  data, NULL);
  g_object_unref (client);

  return (ret);
}

gchar *
hippo_get_overlay (void)
{
  gchar *ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_get_string (client, "/apps/hippopotamus/video/overlay",
			     NULL);
  g_object_unref (client);

  return (ret);
}

gboolean
hippo_set_overlay (char *data)
{
  gboolean ret;
  GConfClient *client = gconf_client_get_default ();

  ret =
    gconf_client_set_string (client, "/apps/hippopotamus/video/overlay",
			     data, NULL);
  g_object_unref (client);

  return (ret);
}


static void
on_close_button_clicked (GtkWidget * widget, gpointer user_data)
{
  gtk_widget_destroy (GTK_WIDGET (gtk_widget_get_toplevel (widget)));
  if (was_playing == TRUE)
    {
      hippo_streaming_start ();
      status = STREAM_STATUS_STREAMING;
      hippo_update_icon (GTK_STATUS_ICON (user_data));
    }
}


static void
on_host_entry_changed (GtkWidget * widget, gpointer user_data)
{
  gchar *text = (gchar *) gtk_entry_get_text (GTK_ENTRY (widget));
  hippo_set_host (text);
}

static void
on_port_spin_changed (GtkWidget * widget, gpointer user_data)
{
  gint num = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));
  hippo_set_port (num);
}

static void
on_mountpoint_entry_changed (GtkWidget * widget, gpointer user_data)
{
  gchar *text = (gchar *) gtk_entry_get_text (GTK_ENTRY (widget));
  hippo_set_mount (text);
}

static void
on_passwd_entry_changed (GtkWidget * widget, gpointer user_data)
{
  gchar *text = (gchar *) gtk_entry_get_text (GTK_ENTRY (widget));
  hippo_set_passwd (text);
}

static void
on_vquality_spin_changed (GtkWidget * widget, gpointer user_data)
{
  gint num = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));
  hippo_set_vquality (num);
}

static void
on_overlay_entry_changed (GtkWidget * widget, gpointer user_data)
{
  gchar *text = (gchar *) gtk_entry_get_text (GTK_ENTRY (widget));
  hippo_set_overlay (text);
}

void
hippo_show_preferences (GtkMenuItem * item, gpointer user_data)
{
  GtkWidget *hippo_prefs_win, *widget;
  GladeXML *xml;
  if (status == STREAM_STATUS_STREAMING || status == STREAM_STATUS_PAUSED)
    {
      /* We need to stop streaming while the preferences get updated */
      /* TODO - Update element properties on the fly maybe ? */
      was_playing = (status == STREAM_STATUS_STREAMING) ? TRUE : FALSE;
      hippo_streaming_stop ();
      status = STREAM_STATUS_STOPPED;
      hippo_update_icon (GTK_STATUS_ICON (user_data));
    }

  /*FIXME: A #define maybe ?? */

  xml = glade_xml_new (HIPPO_DATADIR"/hippo-prefs.glade", NULL, NULL);
  glade_xml_signal_autoconnect (xml);
  hippo_prefs_win = glade_xml_get_widget (xml, "preferences_win");
  widget = glade_xml_get_widget (xml, "close_button");
  g_signal_connect (G_OBJECT (widget), "clicked",
		    G_CALLBACK (on_close_button_clicked), user_data);
  widget = glade_xml_get_widget (xml, "host_entry");
  gtk_entry_set_text (GTK_ENTRY (widget), hippo_get_host ());
  g_signal_connect (G_OBJECT (widget), "changed",
		    G_CALLBACK (on_host_entry_changed), NULL);
  widget = glade_xml_get_widget (xml, "port_spin");
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), (gdouble)
			     hippo_get_port ());
  g_signal_connect (G_OBJECT (widget), "changed",
		    G_CALLBACK (on_port_spin_changed), NULL);
  widget = glade_xml_get_widget (xml, "mountpoint_entry");
  gtk_entry_set_text (GTK_ENTRY (widget), hippo_get_mount ());
  g_signal_connect (G_OBJECT (widget), "changed",
		    G_CALLBACK (on_mountpoint_entry_changed), NULL);
  widget = glade_xml_get_widget (xml, "passwd_entry");
  gtk_entry_set_text (GTK_ENTRY (widget), hippo_get_passwd ());
  gtk_entry_set_invisible_char (GTK_ENTRY (widget), '*');
  gtk_entry_set_visibility (GTK_ENTRY (widget), FALSE);
  g_signal_connect (G_OBJECT (widget), "changed",
		    G_CALLBACK (on_passwd_entry_changed), NULL);
  widget = glade_xml_get_widget (xml, "vquality_spin");
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), (gdouble)
			     hippo_get_vquality ());
  g_signal_connect (G_OBJECT (widget), "changed",
		    G_CALLBACK (on_vquality_spin_changed), NULL);
  widget = glade_xml_get_widget (xml, "overlay_entry");
  gtk_entry_set_text (GTK_ENTRY (widget), hippo_get_overlay ());
  g_signal_connect (G_OBJECT (widget), "changed",
		    G_CALLBACK (on_overlay_entry_changed), NULL);
  gtk_widget_show (hippo_prefs_win);
}
