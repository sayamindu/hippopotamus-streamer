/*
 * hippo_streamer.c
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

#include <gst/gst.h>

#include "hippo.h"
#include "hippo_preferences.h"
#include "hippo_streamer.h"

void
hippo_streaming_start ()
{
  if (status == STREAM_STATUS_STOPPED)
    {

      GstElement *source, *colorspace_conv, *overlay, *encoder, *mux, *sink;

      pipeline = gst_pipeline_new ("streamer");

      /* create element for reading from camera */
      source = gst_element_factory_make ("v4lsrc", "source");

      /* create element for handling colorspace conversion */
      colorspace_conv =
	gst_element_factory_make ("ffmpegcolorspace", "colorspace_conv");

      /* create element for overlaying text */
      overlay = gst_element_factory_make ("textoverlay", "overlay");

      /* create element for doing theora encoding */
      encoder = gst_element_factory_make ("theoraenc", "encoder");

      /* create element for MUXing into the ogg container */
      mux = gst_element_factory_make ("oggmux", "mux");

      /* create element for sending stream to icecast (this is the sink for our pipeline) */
      sink = gst_element_factory_make ("shout2send", "sink");


      if (!source || !colorspace_conv || !overlay || !encoder || !mux
	  || !sink)
	g_warning ("Could not create pipeline\n");

      g_object_set (G_OBJECT (overlay), "text", hippo_get_overlay (), NULL);	/* Set the text which would be overlaid */
      g_object_set (G_OBJECT (overlay), "halignment", 2, NULL);
      g_object_set (G_OBJECT (overlay), "valignment", 1, NULL);
      g_object_set (G_OBJECT (overlay), "font-desc", "Sans 24", NULL);

      g_object_set (G_OBJECT (encoder), "quality", hippo_get_vquality (), NULL);	/* Set the quality value of the encoder */

      g_object_set (G_OBJECT (sink), "ip", hippo_get_host (), NULL);	/* Set the IP address for the icecast source */
      g_object_set (G_OBJECT (sink), "port", hippo_get_port (), NULL);	/* Set the port for the icecast source */
      g_object_set (G_OBJECT (sink), "password", hippo_get_passwd (), NULL);	/* Set the password for the icecast source */
      g_object_set (G_OBJECT (sink), "mount", hippo_get_mount (), NULL);	/* Set the mount point for the icecast source */

      gst_bin_add_many (GST_BIN (pipeline), source, colorspace_conv,
			overlay, encoder, mux, sink, NULL);
      gst_element_link_many (source, colorspace_conv, overlay, encoder,
			     mux, sink, NULL);
    }

  gst_element_set_state (pipeline, GST_STATE_PLAYING);

}


void
hippo_streaming_pause ()
{
  gst_element_set_state (pipeline, GST_STATE_PAUSED);
}


void
hippo_streaming_stop ()
{
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (GST_OBJECT (pipeline));
}
