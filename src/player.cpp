/*
 * Copyright (C) 2006, 2007 Apple Inc.
 * Copyright (C) 2007 Alp Toker <alp@atoker.com>
 * Copyright (C) 2011 Lukasz Slachciak
 * Copyright (C) 2011 Bob Murphy
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <gtk/gtk.h>
#include <webkit/webkit.h>


static void destroyWindowCb(GtkWidget* widget, GtkWidget* window);
static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window);
static void loadStatusCb(WebKitWebView *web_view, GParamSpec *pspec, void* context);
static void motionNotifyCb(WebKitWebView *web_view, GParamSpec *pspec, void* context);

static void handleLoadFinished(WebKitWebView *web_view, void* context);

int main(int argc, char* argv[])
{
    // Initialize GTK+
    gtk_init(&argc, &argv);

    // Create an 800x600 window that will contain the browser instance
    GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);

    // Create a browser instance
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

    // Create a scrollable area, and put the browser instance into it
    GtkWidget *scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolledWindow), GTK_WIDGET(webView));

    // Set up callbacks so that if either the main window or the browser instance is
    // closed, the program will exit
    g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
    g_signal_connect(webView, "close-web-view", G_CALLBACK(closeWebViewCb), main_window);
    g_signal_connect(webView, "notify::load-status", G_CALLBACK(loadStatusCb), webView);
    g_signal_connect(webView, "motion-notify-event", G_CALLBACK(motionNotifyCb), webView);

    // Put the scrollable area into the main window
    gtk_container_add(GTK_CONTAINER(main_window), scrolledWindow);

    // Load a web page into the browser instance
    //webkit_web_view_load_uri(webView, "http://www.webkitgtk.org/");
    webkit_web_view_load_uri(webView, "file:///home/ganash/Images/clouds.svg");

    // Make sure that when the browser area becomes visible, it will get mouse
    // and keyboard events
    gtk_widget_grab_focus(GTK_WIDGET(webView));

    // Make sure the main window and all its contents are visible
    gtk_widget_show_all(main_window);

    // Run the main GTK+ event loop
    gtk_main();

    return 0;
}


static void destroyWindowCb(GtkWidget* widget, GtkWidget* window)
{
    gtk_main_quit();
}

static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window)
{
    gtk_widget_destroy(window);
    return TRUE;
}
/*
static gboolean motionNotifyCb(GtkWidget *widget, GdkEventButton *event)
{
    g_print("motionNotifyCb\n");
}
*/
static void motionNotifyCb(WebKitWebView *webView, GParamSpec *pspec, void* context)
{
    GdkEventButton event;
    event.x = 0.0;
    event.y = 0.0;
    event.type = GDK_MOTION_NOTIFY;

    WebKitHitTestResult *result;
    result = webkit_web_view_get_hit_test_result(webView, &event);

    g_print("motion_event_handler\n");

    /*
    // prperty "inner-node"
    // Node node;
    // const GValue *value;
    //g_object_get_property(G_OBJECT (result), "inner-node", value);
    // g_value
    // WebKitDOMNode* node = value;
    //g_object_get(G_OBJECT (result),"inner-node", &node, NULL);
    */
}

// Implement the listener, handling each possible load status
static void loadStatusCb(WebKitWebView *web_view, GParamSpec *pspec, void* context)
{
        WebKitLoadStatus status = webkit_web_view_get_load_status (web_view);
        GObject *object = G_OBJECT (web_view);
        //g_assert(web_view == context->m_WebView);// ?

        g_object_freeze_notify (object);

        switch (status)
        {
        case WEBKIT_LOAD_FINISHED:
                handleLoadFinished(web_view, context);
                break;

        case WEBKIT_LOAD_PROVISIONAL:
                //handleLoadProvisional(web_view, context);
                break;

        case WEBKIT_LOAD_COMMITTED:
                //handleLoadCommitted(web_view, context);
                break;

        case WEBKIT_LOAD_FIRST_VISUALLY_NON_EMPTY_LAYOUT:
                //handleLoadNonEmptyLayout(web_view, context);
                break;

        case WEBKIT_LOAD_FAILED:
                //handleLoadFailed(web_view, context);
                break;

        default:
                break;
        }

        g_object_thaw_notify (object);
}

static void myFocusCallback (WebKitDOMNode *element, WebKitDOMEvent *dom_event,
                   void* context)
{
    //...
}

static void myBlurCallback (WebKitDOMNode *element, WebKitDOMEvent *dom_event,
                   void* context)
{
    //...
}

static void handleLoadFinishedProcessSvg(WebKitWebView *web_view, void* context)
{
    WebKitDOMDocument *document =
                    webkit_web_view_get_dom_document(WEBKIT_WEB_VIEW(web_view));
    WebKitDOMNodeList *elements =
                    webkit_dom_document_get_elements_by_tag_name(document, "svg");
    gulong element_count = webkit_dom_node_list_get_length(elements);
    g_print("svg = %lu\n", element_count);
    for (int i = 0; i < element_count; i++)
    {
        WebKitDOMNode *element = webkit_dom_node_list_item(elements, i);
    }

}

static void handleLoadFinished(WebKitWebView *web_view, void* context)
{
    handleLoadFinishedProcessSvg(web_view, context);

        WebKitDOMDocument *document =
                        webkit_web_view_get_dom_document(WEBKIT_WEB_VIEW(web_view));

        WebKitDOMNodeList *elements =
                        webkit_dom_document_get_elements_by_tag_name(document, "*");
        gulong element_count = webkit_dom_node_list_get_length(elements);
        for (int i = 0; i < element_count; i++)
        {
                WebKitDOMNode *element = webkit_dom_node_list_item(elements, i);

                if (WEBKIT_DOM_IS_HTML_INPUT_ELEMENT (element))
                {
                        char *element_type;
                        g_object_get (element, "type", &element_type, NULL);

                        if (g_str_equal ("text", element_type) ||
                                        g_str_equal("password", element_type))
                        {
                                webkit_dom_event_target_add_event_listener(
                                                WEBKIT_DOM_EVENT_TARGET (element), "focus",
                                                G_CALLBACK (myFocusCallback), false,
                                                context);
                                webkit_dom_event_target_add_event_listener(
                                                WEBKIT_DOM_EVENT_TARGET (element), "blur",
                                                G_CALLBACK (myBlurCallback), false,
                                                context);

                        }
                        g_free (element_type);
                }
        }

        g_object_unref(elements);

        // Is there already an active element? Sometimes this happens, and no
        // focus event is emitted afterward. This handles that situation.
        //WebKitDOMHTMLDocument *htmlDocument = WEBKIT_DOM_HTML_DOCUMENT(document);
        WebKitDOMHTMLDocument *htmlDocument = (WebKitDOMHTMLDocument *) document;

        WebKitDOMElement* activeElement =
                        webkit_dom_html_document_get_active_element(htmlDocument);
        if (WEBKIT_DOM_IS_HTML_INPUT_ELEMENT (activeElement))
        {
                char *activeElementType = NULL;
                g_object_get (activeElement, "type", &activeElementType, NULL);
                if (g_str_equal ("text", activeElementType) ||
                                g_str_equal("password", activeElementType))
                {
                        myFocusCallback(WEBKIT_DOM_NODE(activeElement), NULL, context);
                }
                g_free(activeElementType);
        }
}
