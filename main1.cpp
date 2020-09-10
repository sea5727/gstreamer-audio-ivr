#include <gst/gst.h>

#include <iostream>

static void
cb_state (GstBus * bus, GstMessage * message, gpointer data)
{
}
int main(int argc, char* argv[]) {

    gst_init (&argc, &argv);

    
    // SessionData *videoSession;
    // SessionData *audioSession;
    // GstElement *rtpBin;

    // GMainLoop * loop = g_main_loop_new (NULL, FALSE);
    GstPipeline * pipe = GST_PIPELINE(gst_pipeline_new(NULL));
    GstBus *bus = gst_element_get_bus (GST_ELEMENT (pipe));
    // g_signal_connect (bus, "message::state-changed", G_CALLBACK (cb_state), pipe);

    GstPipeline * pipe2 = GST_PIPELINE(gst_pipeline_new(NULL));
    GstBus *bus2 = gst_element_get_bus (GST_ELEMENT (pipe2));
    GstPipeline * pipe3 = GST_PIPELINE(gst_pipeline_new(NULL));
    GstBus *bus3 = gst_element_get_bus (GST_ELEMENT (pipe3));

    g_print("bus:%p\n", bus);
    g_print("bus2:%p\n", bus2);
    g_print("bus3:%p\n", bus3);




    // bus를 구현하는 방법은 크게 2가지
    // 1. g_main_loop_new 로 GMainLoop 를 호출하여 g_signal_connect로 콜백을 등록시켜 버스를 구현
    // 2. 직접 poll(sync), peek, gst_bus_timed_pop_filtered(async) 를 사용하여 구현
    // bus loop 는 2. poll로 구현하였음.
    GstMessage *message = NULL;
    while (TRUE) {
        message = gst_bus_poll (bus, GST_MESSAGE_ANY, -1);
        g_assert (message != NULL);
        switch (message->type) {
            case GST_MESSAGE_EOS:
            {
                g_message ("received EOS");
                gst_message_unref (message);
                break;
            }
            case GST_MESSAGE_STATE_CHANGED:
            {
                GstState old_state, new_state, pending_state;
                gst_message_parse_state_changed(message, &old_state, &new_state, &pending_state);
                g_print("Pipeline state changed from %s to %s:\n", 
                    gst_element_state_get_name(old_state), 
                    gst_element_state_get_name(new_state));
                break;
            }
            case GST_MESSAGE_WARNING:
            {
                GError *gerror;
                gchar *debug;
                gst_message_parse_warning (message, &gerror, &debug);
                gst_object_default_error (GST_MESSAGE_SRC (message), gerror, debug);
                gst_message_unref (message);
                g_error_free (gerror);
                g_free (debug);
                break;
            }
            case GST_MESSAGE_ERROR:
            {
                GError *gerror;
                gchar *debug;
                gst_message_parse_error (message, &gerror, &debug);
                gst_object_default_error (GST_MESSAGE_SRC (message), gerror, debug);
                gst_message_unref (message);
                g_error_free (gerror);
                g_free (debug);
                break;
            }
            default:
                gst_message_unref (message);
            break;
        }
    }

    gst_object_unref (bus);


    // g_main_loop_run (loop);
    // g_main_loop_unref (loop);


}
