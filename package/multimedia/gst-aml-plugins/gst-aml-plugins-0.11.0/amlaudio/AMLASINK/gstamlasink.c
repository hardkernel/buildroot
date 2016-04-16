/*
 * GStreamer
 * Copyright (C) 2005 Thomas Vander Stichele <thomas@apestaart.org>
 * Copyright (C) 2005 Ronald S. Bultje <rbultje@ronald.bitfreak.net>
 * Copyright (C) 2013  <<user@hostname.org>>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the
 * GNU Lesser General Public License Version 2.1 (the "LGPL"), in
 * which case the following provisions apply instead of the ones
 * mentioned above:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * SECTION:element-amlasink
 *
 * FIXME:Describe amlasink here.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch -v -m fakesrc ! amlasink ! fakesink silent=TRUE
 * ]|
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gst/gst.h>
#include "gstamlasink.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include "amlasink_prop.h"

GST_DEBUG_CATEGORY_STATIC (gst_amlasink_debug);
#define GST_CAT_DEFAULT gst_amlasink_debug


/* Filter signals and args */
enum
{
    /* FILL ME */
    LAST_SIGNAL
};


/* the capabilities of the inputs and outputs.
 *
 * describe the real formats here.
 */
static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("audio/mpeg; audio/x-eac3; audio/x-ac3; audio/x-adpcm; audio/x-flac; audio/x-wma; audio/x-vorbis; audio/x-mulaw; audio/x-raw-int; application/x-ape; audio/x-private1-dts")
    );

GST_BOILERPLATE (GstAmlAsink, gst_amlasink, GstBaseSink ,GST_TYPE_BASE_SINK);

static void gst_amlasink_set_property (GObject * object, guint prop_id, const GValue * value, GParamSpec * pspec);
static void gst_amlasink_get_property (GObject * object, guint prop_id, GValue * value, GParamSpec * pspec);
static GstStateChangeReturn gst_amlasink_change_state (GstElement *element, GstStateChange transition);
static gboolean gst_amlasink_set_caps (GstBaseSink *sink, GstCaps * caps);
static GstFlowReturn gst_amlasink_render(GstBaseSink *sink, GstBuffer *buffer);
static gboolean gst_amlasink_start(GstBaseSink *sink);
static gboolean gst_amlasink_stop(GstBaseSink *sink);
static gboolean gst_amlasink_event(GstBaseSink *sink, GstEvent *event);
static void gst_amlasink_finalize (GObject * object);

/* GObject vmethod implementations */

/* GObject vmethod implementations */

static void
gst_amlasink_base_init (gpointer gclass)
{
    GstElementClass *element_class = GST_ELEMENT_CLASS (gclass);
    gst_element_class_set_details_simple(element_class,
    "aml audio sink ",
    "Sink/Audio",    
    "aml dummy sink",
    " <<aml@aml.org>>");
    gst_element_class_add_pad_template (element_class,
    gst_static_pad_template_get (&sink_factory));
}

/* initialize the amlasink's class */
static void
gst_amlasink_class_init (GstAmlAsinkClass * klass)
{
    GObjectClass *gobject_class;
    GstBaseSinkClass *gstbasesink_class = GST_BASE_SINK_CLASS (klass);
    GstElementClass *gstelement_class;
    gobject_class = (GObjectClass *) klass;
    gstelement_class = (GstElementClass *) klass;

    gobject_class->set_property = gst_amlasink_set_property;
    gobject_class->get_property = gst_amlasink_get_property;
    gstelement_class->change_state = gst_amlasink_change_state;
    gobject_class->finalize = gst_amlasink_finalize;

    klass->getPropTable = NULL;
    klass->setPropTable = NULL;
    aml_Install_Property(gobject_class, 
        &(klass->getPropTable), 
        &(klass->setPropTable), 
        aml_get_asink_prop_interface());
    
    gstbasesink_class->render = gst_amlasink_render;  //data through
    gstbasesink_class->stop = gst_amlasink_stop; //data stop
    gstbasesink_class->start = gst_amlasink_start; //data start
    gstbasesink_class->event = gst_amlasink_event; //event
    gstbasesink_class->set_caps = gst_amlasink_set_caps; //event
   
}

/* initialize the new element
 * instantiate pads and add them to element
 * set pad calback functions
 * initialize instance structure
 */
static void
gst_amlasink_init (GstAmlAsink * amlasink,
    GstAmlAsinkClass * gclass)
{
    GstPad *pad;
    pad = GST_BASE_SINK_PAD (amlasink);
    gst_base_sink_set_sync (GST_BASE_SINK (amlasink), FALSE);
    gst_base_sink_set_async_enabled (GST_BASE_SINK(amlasink), FALSE);
    GST_WARNING("gst_amlasink_init\n");

}

static void
gst_amlasink_finalize (GObject * object)
{
    GstAmlAsink *amlasink = GST_AMLASINK(object);
    GstAmlAsinkClass *amlclass = GST_AMLASINK_GET_CLASS (object); 
    GstElementClass *parent_class = g_type_class_peek_parent (amlclass);
    aml_Uninstall_Property(amlclass->getPropTable, amlclass->setPropTable);
    amlclass->getPropTable = NULL;
    amlclass->setPropTable = NULL;
    G_OBJECT_CLASS (parent_class)->finalize (object);
}


static gboolean
gst_amlasink_event (GstBaseSink * sink, GstEvent  *event)
{
    gboolean ret;
    GstTagList *tag_list;
    GstAmlAsink *amlasink = GST_AMLASINK(sink);
    GST_WARNING ("asink got event %s\n",gst_event_type_get_name (GST_EVENT_TYPE (event))); 
  
    switch (GST_EVENT_TYPE (event)) {  
    case GST_EVENT_NEWSEGMENT:{
        gboolean update;
        gdouble rate;
        GstFormat format;
        gint64 start, stop, time;
        gst_event_parse_new_segment (event, &update, &rate, &format,&start, &stop, &time);
        ret=TRUE;        
        break;
    }		
    case GST_EVENT_TAG:
        gst_event_parse_tag (event, &tag_list);
        if (gst_tag_list_is_empty (tag_list))
            g_print("null tag list\n");
        ret=TRUE;;
        break;	
    case GST_EVENT_FLUSH_STOP:{
        ret=TRUE;
        break;
    }		
    case GST_EVENT_FLUSH_START:{
        ret=TRUE;
        break;
    }		
    case GST_EVENT_EOS:
        ret = TRUE;;//gst_pad_event_default (pad,event);
        break;
    default:
        /* just call the default handler */
        ret = TRUE;;// gst_pad_event_default (pad, event);
        break;
    }
    return ret;
}

static void
gst_amlasink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
    GstAmlAsink *amlasink = GST_AMLASINK(object);  
    GstAmlAsinkClass *amlclass = GST_AMLASINK_GET_CLASS (object);  
    AmlPropFunc amlPropFunc = aml_find_propfunc(amlclass->setPropTable, prop_id);
    if(amlPropFunc){
        g_mutex_lock(&amlclass->lock);
        amlPropFunc(object, prop_id, value, pspec);
        g_mutex_unlock(&amlclass->lock);
    }
}

static void
gst_amlasink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
    GstAmlAsink *amlasink = GST_AMLASINK(object);  
    GstAmlAsinkClass *amlclass = GST_AMLASINK_GET_CLASS (object);  
    AmlPropFunc amlPropFunc = aml_find_propfunc(amlclass->getPropTable, prop_id);
    if(amlPropFunc){
        g_mutex_lock(&amlclass->lock);
        amlPropFunc(object, prop_id, value, pspec);
        g_mutex_unlock(&amlclass->lock);
    }
}
/* this function handles the link with other elements */
static gboolean
gst_amlasink_set_caps (GstBaseSink *sink, GstCaps * caps)
{ 
    return TRUE; 
}
/* chain function
 * this function does the actual processing
 */
static GstFlowReturn
gst_amlasink_render (GstBaseSink * sink, GstBuffer * buf)
{    
    return GST_FLOW_OK;
}

static gboolean
gst_amlasink_start (GstBaseSink * basesink)
{
    return TRUE;
}

static gboolean
gst_amlasink_stop (GstBaseSink * basesink)
{ 	
    return TRUE;
}

static GstStateChangeReturn
gst_amlasink_change_state (GstElement * element, GstStateChange transition)
{
    GstAmlAsink *amlasink= GST_AMLASINK(element);
    GstStateChangeReturn result;
    gint ret=-1;	

    switch (transition) {
        case GST_STATE_CHANGE_NULL_TO_READY:
            break;
        case GST_STATE_CHANGE_READY_TO_PAUSED:
            break;
        case GST_STATE_CHANGE_PAUSED_TO_PLAYING:  	
            break;
        default:
            break;
    }

    result = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);
  
    switch (transition) {
        case GST_STATE_CHANGE_PLAYING_TO_PAUSED:
	    break;
        case GST_STATE_CHANGE_PAUSED_TO_READY:			
            break;
        case GST_STATE_CHANGE_READY_TO_NULL:    
            break;
        default:
            break;
    }
    return result;
}

/* entry point to initialize the plug-in
 * initialize the plug-in itself
 * register the element factories and other features
 */
static gboolean
amlasink_init (GstAmlAsink * amlasink)
{
  /* debug category for fltering log messages
   *
   * exchange the string 'Template amlasink' with your description
   */
    GST_DEBUG_CATEGORY_INIT (gst_amlasink_debug, "amlasink",
        0, "Template amlasink");
  
    return gst_element_register (amlasink, "amlasink", GST_RANK_PRIMARY,
        GST_TYPE_AMLASINK);
}

/* PACKAGE: this is usually set by autotools depending on some _INIT macro
 * in configure.ac and then written into and defined in config.h, but we can
 * just set it ourselves here in case someone doesn't use autotools to
 * compile this code. GST_PLUGIN_DEFINE needs PACKAGE to be defined.
 */
#ifndef PACKAGE
#define PACKAGE "myfirstamlasink"
#endif

/* gstreamer looks for this structure to register amlasinks
 *
 * exchange the string 'Template amlasink' with your amlasink description
 */
GST_PLUGIN_DEFINE (
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    "amlasink",
    "Template amlasink",
    amlasink_init,
    VERSION,
    "LGPL",
    "GStreamer",
    "http://gstreamer.net/"
)
