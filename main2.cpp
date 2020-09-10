#include <gst/gst.h>

#include <iostream>

static void
cb_state (GstBus * bus, GstMessage * message, gpointer data)
{
}
int main(int argc, char* argv[]) {

    gst_init (&argc, &argv);


    GMainLoop * loop = g_main_loop_new (NULL, FALSE);


    GstPipeline * pipe = GST_PIPELINE(gst_pipeline_new(NULL));
    GstBus *bus = gst_element_get_bus (GST_ELEMENT (pipe));
    g_signal_connect (bus, "message::state-changed", G_CALLBACK (cb_state), pipe);
    gst_bus_add_signal_watch (bus);
    gst_object_unref (bus);


    GstElement *rtpBin = gst_element_factory_make ("rtpbin", NULL);

    gst_bin_add(GST_BIN(pipe), rtpBin);

    GstBin * audioBin = GST_BIN(gst_bin_new(NULL));
    GstElement *audioQueue = gst_element_factory_make("queue", "audio_queue");
    GstElement *audioRtpPcmaPay = gst_element_factory_make("rtppcmapay", NULL);

    gst_bin_add_many(audioBin, audioQueue, audioRtpPcmaPay, NULL);
    g_object_set(audioRtpPcmaPay, "pt", 98, NULL);

    GstPad *ghost_src_pad_audio = gst_element_get_static_pad(audioRtpPcmaPay, "src");
    GstPad *ghost_bin_pad_audio = gst_ghost_pad_new("src", ghost_src_pad_audio);
    gst_element_add_pad(GST_ELEMENT(audioBin), ghost_bin_pad_audio);






    g_main_loop_run (loop);
    g_main_loop_unref (loop);


}
