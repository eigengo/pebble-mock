#pragma once
#include <vector>
#include "dict.h"

extern "C" {
#include <pebble.h>
}

namespace pebble {
namespace services {

    class app_messages {
    private:
        void *m_context;
        AppMessageInboxReceived m_received_callback;
        AppMessageInboxDropped m_dropped_callback;
        AppMessageOutboxSent m_sent_callback;
        AppMessageOutboxFailed m_failed_callback;
        std::unique_ptr<dictionary_iterator> m_current_dict;
        dictionary_iterator m_last_dict;
    public:
        dictionary_iterator last_dict() const;

        // App Messages mirror API
        AppMessageResult app_message_open(const uint32_t size_inbound, const uint32_t size_outbound);
        void app_message_deregister_callbacks();
        void *app_message_get_context();
        void *app_message_set_context(void *context);
        AppMessageInboxReceived app_message_register_inbox_received(AppMessageInboxReceived received_callback);
        AppMessageInboxDropped app_message_register_inbox_dropped(AppMessageInboxDropped dropped_callback);
        AppMessageOutboxSent app_message_register_outbox_sent(AppMessageOutboxSent sent_callback);
        AppMessageOutboxFailed app_message_register_outbox_failed(AppMessageOutboxFailed failed_callback);
        uint32_t app_message_inbox_size_maximum();
        uint32_t app_message_outbox_size_maximum();
        AppMessageResult app_message_outbox_begin(DictionaryIterator **iterator);
        AppMessageResult app_message_outbox_send();
    };

}
}