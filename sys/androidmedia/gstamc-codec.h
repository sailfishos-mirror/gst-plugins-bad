/*
 * Copyright (C) 2012,2018 Collabora Ltd.
 *   Author: Sebastian Dröge <sebastian.droege@collabora.co.uk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 */

#ifndef __GST_AMC_CODEC_H__
#define __GST_AMC_CODEC_H__

#include <gst/gst.h>

#include "gstamc-format.h"

G_BEGIN_DECLS

typedef struct _GstAmcBuffer GstAmcBuffer;
typedef struct _GstAmcBufferInfo GstAmcBufferInfo;
typedef struct _GstAmcCodec GstAmcCodec;

struct _GstAmcBuffer {
  guint8 *data;
  gsize size;
};

struct _GstAmcBufferInfo {
  gint flags;
  gint offset;
  gint64 presentation_time_us;
  gint size;
};

gboolean gst_amc_codec_static_init (void);

void gst_amc_buffer_free (GstAmcBuffer * buffer);
gboolean gst_amc_buffer_set_position_and_limit (GstAmcBuffer * buffer, GError ** err,
    gint position, gint limit);

GstAmcCodec * gst_amc_codec_new (const gchar *name, GError **err);
void gst_amc_codec_free (GstAmcCodec * codec);

gboolean gst_amc_codec_configure (GstAmcCodec * codec, GstAmcFormat * format, jobject surface, gint flags, GError **err);
GstAmcFormat * gst_amc_codec_get_output_format (GstAmcCodec * codec, GError **err);

gboolean gst_amc_codec_start (GstAmcCodec * codec, GError **err);
gboolean gst_amc_codec_stop (GstAmcCodec * codec, GError **err);
gboolean gst_amc_codec_flush (GstAmcCodec * codec, GError **err);
gboolean gst_amc_codec_release (GstAmcCodec * codec, GError **err);

GstAmcBuffer * gst_amc_codec_get_output_buffer (GstAmcCodec * codec, gint index, GError **err);
GstAmcBuffer * gst_amc_codec_get_input_buffer (GstAmcCodec * codec, gint index, GError **err);

gint gst_amc_codec_dequeue_input_buffer (GstAmcCodec * codec, gint64 timeoutUs, GError **err);
gint gst_amc_codec_dequeue_output_buffer (GstAmcCodec * codec, GstAmcBufferInfo *info, gint64 timeoutUs, GError **err);

gboolean gst_amc_codec_queue_input_buffer (GstAmcCodec * codec, gint index, const GstAmcBufferInfo *info, GError **err);
gboolean gst_amc_codec_release_output_buffer (GstAmcCodec * codec, gint index, gboolean render, GError **err);

G_END_DECLS

#endif /* __GST_AMC_CODEC_H__ */